#pragma once
#include <iostream>
#include <sstream>
#include <string>
#include <cstring>
#include <vector>
#include <cmath>
#include "curl/curl.h"

using namespace std;

namespace fre {
    // date types
    struct Price {
        string d; // date
        double p; // price
    };
    ostream& operator<<(ostream& out, const Price& price);
    struct Return {
        string d; // date
        double r; // return
    };
    ostream& operator<<(ostream& out, const Return& log_return);
    struct MemoryStruct {
        char *memory;
        size_t size;
    };
    
    class Stock
    {
        private:
            string symbol;              // stock's symbol
            string date;                // stock's date (the earning is announced)
            string period_ending;       // stock's period_ending
            double estimate;            // stock's estimate earning
            double reported;            // stock's reported earning   
            double surprise;            // stock's surprise
            double surprise_pct;        // stock's surprise%
                             
            string start_date;          // stock's daily price start date
            string end_date;            // stock's daily price end date
            
            vector<string> Dates;       // stock's trading dates
            vector<Price> Prices;       // stock's daily price
            vector<Return> Returns;     // stock's daily return
            vector<Return> IWVReturns;  // IWV's daily return
            vector<double> AbnReturns;  // stock's abnormal return
        
            // static member functions
            static void* myrealloc(void* ptr, size_t size);
            static int write_data(void* ptr, size_t size, size_t nmemb, void* data);
        
        public:
            // constructor with parameters
            Stock(string symbol_, string date_, string period_ending_, double estimate_, double reported_, double surprise_, double surprise_pct_): 
                symbol(symbol_), date(date_), period_ending(period_ending_), estimate(estimate_), reported(reported_), surprise(surprise_), surprise_pct(surprise_pct_) {}
            
            // member functions
            void UpdateDailyPrices(string api_token_);  // update daily price between start date and end date
            void CalculateReturns();                    // calculate daily return between start date and end date
            void CalculateAbnReturns();                 // calculate daily abnormal return between start date and end date
            void Clear();                               // clear daily prices, daily returns, and daily abnormal returns
            
            // operators
            bool operator<(const Stock& stock_) const;
            bool operator>(const Stock& stock_) const;
            bool operator==(const Stock& stock_) const;
            
            // setter functions
            void SetStartDate(string start_date_) { start_date = start_date_; }
            void SetEndDate(string end_date_) { end_date = end_date_; }
            void SetDates(vector<string> Dates_) { Dates = Dates_; }
            void SetIWVReturns(vector<Return> IWVReturns_) { IWVReturns = IWVReturns_; }
            
            // getter functions
            string* GetSymbol() { return &symbol; }
            string* GetDate() { return &date; }
            string* GetPeriodEnding() { return &period_ending; }
            double GetEstimate() { return estimate; }
            double GetReported() { return reported; }
            double GetSurprise() { return surprise; }
            double GetSurprisePct() { return surprise_pct; }
            vector<string>* GetDates() { return &Dates; }
            vector<Price>* GetPrices() { return &Prices; }
            vector<Return>* GetReturns() { return &Returns; }
            vector<Return>* GetIWVReturns() { return &IWVReturns; }
            vector<double>* GetAbnReturns() { return &AbnReturns; }
    };
}
