#pragma once
#include <string>
#include <cstring>
#include <utility>
#include <algorithm>
#include "curl/curl.h"
#include "Stock.h"

using namespace std;

namespace fre {
    class Benchmark
    {
        private:
            string api_token;               // api token
            string symbol;                  // fund's symbol
            string year;                    // year
            
            vector<string> TradingDates;    // trading dates
            vector<Price> Prices;           // fund's daily price
            vector<Return> Returns;         // fund's daily return
            
            // static member functions
            static void* myrealloc(void* ptr, size_t size);
            static int write_data(void* ptr, size_t size, size_t nmemb, void* data);
        
        public:
            // constructor
            Benchmark(string api_token_, string symbol_, string year_);
            
            // member functions
            void CalculateReturns();                                        // calculate IWV daily prices
            void FindStartDateAndEndDate(int N_, vector<Stock>* Stocks_);   // set stocks' start date, end date and IWV returns
            
            // getter functions
            vector<Price>* GetPrices() { return &Prices; }
            vector<Return>* GetReturns() { return &Returns; }
    };
}