#pragma once
#include <fstream>
#include <iomanip>
#include <map>
#include <algorithm>
#include <thread>
#include "Stock.h"

using namespace std;

namespace fre {
    class FetchStocks
    {
        private:
            string file_name;               // file name
            string api_token;               // api token to fetch market data
            vector<Stock> Stocks;           // vector to store stocks
            map<string, Stock*> StocksMap;  // map to store stocks
            
            vector<Stock> BeatEstimateGroup;    // highest surprise group
            vector<Stock> MissEstimateGroup;    // lowest surprise group
            vector<Stock> MeetEstimateGroup;    // rest stocks in between
            
            // static member functions
            static string ConvertDateFormat(const string& date_);                   // convert date format
            static void UpdatePrices(string api_token_, vector<Stock>* Stocks_);    // update each stock's daily prices
            
        public:
            // constructor with parameters
            FetchStocks() {}
            FetchStocks(string file_name_, string api_token_);
            
            // member functions
            void UpdateStocksPrices(int number_of_threads); // update stocks daily prices
            void CheckStocks(int N);                        // check if the stock have enough daily prices
            void CalculateStocksReturns();                  // calculate stocks daily returns    
            void CalculateStocksAbnReturns();               // calculate stocks daily abnormal returns
            void SortStocks();                              // sort stocks vector and seperate into three groups
            void ClearStocks();                             // clear stocks' daily prices, daily returns, and daily abnormal returns
            void UpdateStocksMap();                         // update map
            Stock* GetStock(string symbol);                 // find a stock based on symbol
            
            // getter functions
            vector<Stock>* GetStocks() { return &Stocks; }
            vector<Stock>* GetBeatEstimateGroup() { return &BeatEstimateGroup; }
            vector<Stock>* GetMissEstimateGroup() { return &MissEstimateGroup; }
            vector<Stock>* GetMeetEstimateGroup() { return &MeetEstimateGroup; }
    };
}