#include "Stock.h"

namespace fre {
    ostream& operator<<(ostream& out, const Price& price)
    {
        out << "$" << price.p;
        return out;
    }
    
    ostream& operator<<(ostream& out, const Return& log_return)
    {
        out << log_return.r;
        return out;
    }
    
    void* Stock::myrealloc(void* ptr, size_t size)
    {
        if (ptr)
            return realloc(ptr, size);
        else
            return malloc(size);
    }
    
    int Stock::write_data(void* ptr, size_t size, size_t nmemb, void* data)
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
    
    void Stock::UpdateDailyPrices(string api_token_)
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
            // get all stocks' prices from the url
            struct MemoryStruct data;
            data.memory = NULL;
            data.size = 0;
            // get prices from curl
            string url_request = url_common + symbol + ".US?" + "from=" + start_date + "&to=" + end_date + "&api_token=" + api_token_ + "&period=d";
            curl_easy_setopt(handle, CURLOPT_URL, url_request.c_str());
            // adding a user agent
            curl_easy_setopt(handle, CURLOPT_USERAGENT, "Mozilla/5.0 (Windows NT 10.0; Win64; x64; rv:74.0) Gecko/20100101 Firefox/74.0");
            curl_easy_setopt(handle, CURLOPT_SSL_VERIFYPEER, 0);
            curl_easy_setopt(handle, CURLOPT_SSL_VERIFYHOST, 0);
            // record prices
            curl_easy_setopt(handle, CURLOPT_WRITEFUNCTION, write_data);
            curl_easy_setopt(handle, CURLOPT_WRITEDATA, (void*)&data);
            // perform, then store the expected code in result
            result = curl_easy_perform(handle);
            if (result != CURLE_OK)
            {
                // if errors have occured, tell us what is wrong with result
                cout << "curl_easy_perform() failed: " << curl_easy_strerror(result) << endl;
                return;
            }
            stringstream prices;
            prices.str(data.memory);
            string Date, Adj_close;
            double adj = 0;
            string line;
            while (getline(prices, line)) 
            {
                size_t found = line.find('-');
                if (found != std::string::npos)
                {
                    Date = line.substr(0, line.find_first_of(','));
                    line.erase(line.find_last_of(','));
                    Adj_close = line.substr(line.find_last_of(',') + 1);
                    adj = strtod(Adj_close.c_str(), NULL);
                    Price price;
                    price.d = Date;
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
    
    void Stock::CalculateReturns()
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
    
    void Stock::CalculateAbnReturns()
    {
        int size = (int)Returns.size();
        int i = 0, j = 0;
        while (i < size)
        {
            if (Returns[i].d == IWVReturns[j].d) 
            {
                AbnReturns.push_back(Returns[i].r - IWVReturns[j].r);
                i += 1;
                j += 1;
            }
            else { j += 1; }
        }
    }
    
    void Stock::Clear()
    {
        Prices.clear();
        Returns.clear();
        IWVReturns.clear();
        AbnReturns.clear();
    }
    
    bool Stock::operator<(const Stock& stock_) const
    {
        return surprise_pct < stock_.surprise_pct;
    }
    
    bool Stock::operator>(const Stock& stock_) const
    {
        return surprise_pct > stock_.surprise_pct;
    }
    
    bool Stock::operator==(const Stock& stock_) const
    {
        return symbol == stock_.symbol;
    }
}