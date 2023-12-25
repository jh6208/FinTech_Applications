#include "Benchmark.h"

namespace fre {
    Benchmark::Benchmark(string api_token_, string symbol_, string year_): api_token(api_token_), symbol(symbol_), year(year_)
    {
        // declaration of an object CURL 
        CURL* handle;
        CURLcode result;
        // set up the program environment that libcurl needs 
        curl_global_init(CURL_GLOBAL_ALL);
        // curl_easy_init() returns a CURL easy handle 
        handle = curl_easy_init();
        // if everything's all right with the easy handle...
        if (handle)
        {
            string url_common = "https://eodhistoricaldata.com/api/eod/";
            string start_date = year + "-01-01";
            string end_date = year + "-12-31";
            // get prices from the url
            struct MemoryStruct data;
            data.memory = NULL;
            data.size = 0;
            string url_request = url_common + symbol + ".US?" + "from=" + start_date + "&to=" + end_date + "&api_token=" + api_token + "&period=d";
            curl_easy_setopt(handle, CURLOPT_URL, url_request.c_str());
            // adding a user agent
			curl_easy_setopt(handle, CURLOPT_USERAGENT, "Mozilla/5.0 (Windows NT 10.0; Win64; x64; rv:74.0) Gecko/20100101 Firefox/74.0");
			curl_easy_setopt(handle, CURLOPT_SSL_VERIFYPEER, 0);
			curl_easy_setopt(handle, CURLOPT_SSL_VERIFYHOST, 0);
            // record prices
			curl_easy_setopt(handle, CURLOPT_WRITEFUNCTION, Benchmark::write_data);
			curl_easy_setopt(handle, CURLOPT_WRITEDATA, (void*)&data);
			// perform, then store the expected symbol in result
			result = curl_easy_perform(handle);
			if (result != CURLE_OK)
			{
				// if errors have occured, tell us what is wrong with result
				cout << "curl_easy_perform() failed: " << curl_easy_strerror(result) << endl;
				return;
			}
			stringstream prices;
    		prices.str(data.memory);
    		string date, adj_close;
    		double adj = 0;
    		string line;
    		while (getline(prices, line)) {
    			size_t found = line.find('-');
    			if (found != std::string::npos)
    			{
    				date = line.substr(0, line.find_first_of(','));
    				line.erase(line.find_last_of(','));
    				adj_close = line.substr(line.find_last_of(',') + 1);
    				adj = strtod(adj_close.c_str(), NULL);
    				// add trading date
    				TradingDates.push_back(date);
    				// add today's price
    				Price price;
                    price.d = date;
                    price.p = adj;
                    Prices.push_back(price);
    			}
    		}
    		// free memory
    		free(data.memory);
    		data.size = 0;
        }
        else
    	{
    		cout << "Curl init failed!" << endl;
    		return;
    	}
        // cleanup since you've used curl_easy_init  
    	curl_easy_cleanup(handle);
    	// release resources acquired by curl_global_init() 
    	curl_global_cleanup();
    }
    
    void* Benchmark::myrealloc(void* ptr, size_t size)
    {
        if (ptr)
            return realloc(ptr, size);
        else
            return malloc(size);
    }
    
    int Benchmark::write_data(void* ptr, size_t size, size_t nmemb, void* data)
    {
        size_t realsize = size * nmemb;
        struct MemoryStruct* mem = (struct MemoryStruct*)data;
        mem->memory = (char*)myrealloc(mem->memory, mem->size + realsize + 1);
        if (mem->memory) 
        {
            memcpy(&(mem->memory[mem->size]), ptr, realsize);
            mem->size += realsize;
            mem->memory[mem->size] = 0;
        }
        return realsize;
    }
    
    void Benchmark::CalculateReturns()
    {
        int N = Prices.size();
        for (int i = 1; i < N; i++)
        {
            Return log_return;
            log_return.d = Prices[i].d;
            log_return.r = log(Prices[i].p / Prices[i-1].p);
            Returns.push_back(log_return);
        }
    }
    
    void Benchmark::FindStartDateAndEndDate(int N_, vector<Stock>* Stocks_)
    {
        int index = 0, max_index = TradingDates.size()-1;
        string start_date, end_date;
        size_t start, end;
        // for all stocks
        vector<Stock>::iterator ptr = Stocks_->begin();
    	for (; ptr != Stocks_->end(); ptr++)
    	{
            // find index of the given date
            string date = *(ptr->GetDate());
            auto iter = find(TradingDates.begin(), TradingDates.end(), date);
            if (iter != TradingDates.end()) index = distance(TradingDates.begin(), iter);
            else cout << "The earnings release date is invalid" << endl;
            // get dates
            start_date = TradingDates[index-N_];
            start = index - N_;
            // check if out of index
            if (index+N_ > max_index) 
            { 
                end_date = TradingDates[max_index];
                end = max_index;
            }
            else 
            { 
                end_date = TradingDates[index+N_];
                end = index + N_;
            }
            ptr->SetStartDate(start_date);
            ptr->SetEndDate(end_date);
            vector<string> Dates(TradingDates.begin() + start, TradingDates.begin() + end + 1);
            ptr->SetDates(Dates);
            vector<Return> IWVReturns(Returns.begin() + start, Returns.begin() + end);
            ptr->SetIWVReturns(IWVReturns);
    	}
    }
}