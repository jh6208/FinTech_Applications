#include "FetchStocks.h"

namespace fre {
    FetchStocks::FetchStocks(string file_name_, string api_token_): file_name(file_name_), api_token(api_token_)
    {
        ifstream fin;
    	fin.open(file_name, ios::in);
    	// stop when there's error in opening file
    	if (!fin.is_open()) {
            cerr << "Error opening file." << endl;
            return;
        }
    	// skip first line
    	bool skip = true;
    	string line, symbol, date, period_ending, estimate, reported, surprise, surprise_pct;
    	while (!fin.eof())
    	{
    	    getline(fin, line);
    		// skip first line and empty lines
    		if (skip || line.size() == 0)
    		{ 
    		    skip = false;
    		    continue;
    		}
    		stringstream sin(line);
    		getline(sin, symbol, ',');
    		getline(sin, date, ',');
    		getline(sin, period_ending, ',');
    		getline(sin, estimate, ',');
    		getline(sin, reported, ',');
    		getline(sin, surprise, ',');
    		getline(sin, surprise_pct, ',');
    		// create a stock object
    		Stock stock(symbol, ConvertDateFormat(date), period_ending, stod(estimate), stod(reported), stod(surprise), stod(surprise_pct));
    	    Stocks.push_back(stock);
    	}
    }
    
    string FetchStocks::ConvertDateFormat(const string& date_)
    {
        struct std::tm tm = {};
        istringstream iss(date_);
        // Check if the day part of the date is a single digit
        if (date_.size() > 1 && date_[1] == '-') 
        {
            // Insert '0' before the single digit
            iss.str("0" + iss.str());
        }
        // Parse the date in "DD-MMM-YY" format
        if (!(iss >> get_time(&tm, "%d-%b-%y"))) 
        {
            throw invalid_argument("Invalid date format");
        }
        // Adjust for years in the 21st century
        if (tm.tm_year < 100) 
        {
            tm.tm_year += 100; // This adjusts 00-99 to 2000-2099
        }
        // Convert to "YYYY-MM-DD" format
        ostringstream oss;
        oss << put_time(&tm, "%Y-%m-%d");
        return oss.str();
    }
    
    void FetchStocks::UpdatePrices(string api_token_, vector<Stock>* Stocks_)
    {
        vector<Stock>::iterator iter = Stocks_->begin();
        for (; iter != Stocks_->end(); iter++) { iter->UpdateDailyPrices(api_token_); }
    }
    
    void FetchStocks::UpdateStocksPrices(int number_of_threads)
    {
        // calculate the size of each subvector
        size_t SubStocksSize = Stocks.size() / number_of_threads;
        // vector to store thread objects
        thread threads[number_of_threads];
        vector<vector<Stock>> StocksArrays;
        for (int i = 0; i < number_of_threads; i++)
        {
            size_t start = i * SubStocksSize;
            size_t end = (i == number_of_threads - 1) ? Stocks.size() : (i + 1) * SubStocksSize;
            vector<Stock> StocksArray(Stocks.begin() + start, Stocks.begin() + end);
            StocksArrays.push_back(StocksArray);
        }
        for (int i = 0; i < number_of_threads; i++)
        {
            threads[i] = thread(UpdatePrices, api_token, &StocksArrays[i]);
        }
        // join the threads with the main thread
        for (thread& thread : threads) 
        {
            thread.join();
        }
        // combine vector<vector<Stock>> into one vector
        vector<Stock> UpdatedStocks;
        for (const auto& vec : StocksArrays) {
            UpdatedStocks.insert(UpdatedStocks.end(), vec.begin(), vec.end());
        }
        Stocks = UpdatedStocks;
    }
    
    void FetchStocks::CheckStocks(int N)
    {
        vector<Stock>::iterator iter = Stocks.begin();
        for(; iter != Stocks.end();)
        {
            int NumberOfPrices = iter->GetPrices()->size();
            if (NumberOfPrices != 2 * N + 1)
            {
                cout << "Downloading Reminder: There are only " << NumberOfPrices << " historical prices for " << *iter->GetSymbol() << endl;
                iter = Stocks.erase(iter);
            }
            else iter++;
        }
        // cout << Stocks.size() << endl;
    }
    
    void FetchStocks::CalculateStocksReturns()
    {
        vector<Stock>::iterator iter = Stocks.begin();
        for (; iter != Stocks.end(); iter++) { iter->CalculateReturns(); }
    }
    
    void FetchStocks::CalculateStocksAbnReturns()
    {
        vector<Stock>::iterator iter = Stocks.begin();
        for (; iter != Stocks.end(); iter++) { iter->CalculateAbnReturns(); }
    }
    
    void FetchStocks::SortStocks()
    {
        // sort the stocks
        sort(Stocks.begin(), Stocks.end(), greater<Stock>());
        // seperate into 3 groups
        size_t i = Stocks.size() / 3;
        vector<Stock> BeatEstimateGroup_(Stocks.begin(), Stocks.begin() + i);
        vector<Stock> MeetEstimateGroup_(Stocks.begin() + i, Stocks.begin() + 2 * i);
        vector<Stock> MissEstimateGroup_(Stocks.begin() + 2 * i, Stocks.end());
        BeatEstimateGroup = BeatEstimateGroup_;
        MeetEstimateGroup = MeetEstimateGroup_;
        MissEstimateGroup = MissEstimateGroup_;
    }
    
    void FetchStocks::ClearStocks()
    {
        vector<Stock>::iterator iter = Stocks.begin();
        for (; iter != Stocks.end(); iter++) { iter->Clear(); }
    }
    
    void FetchStocks::UpdateStocksMap()
    {
        for (auto iter = Stocks.begin(); iter != Stocks.end(); iter++)
    	{
    	    string stock_symbol = *iter->GetSymbol();
    	    StocksMap[stock_symbol] = &(*iter);
    	}
    }
    
    Stock* FetchStocks::GetStock(string symbol)
    {
        auto iter = StocksMap.find(symbol);
        if (iter != StocksMap.end()) return iter->second;
        else { cout << "The stock does not exist; please try again." << endl; return nullptr; }
    }
}
