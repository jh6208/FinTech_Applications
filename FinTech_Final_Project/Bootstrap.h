#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include "Stock.h"
#include "Matrix.h"

using namespace std;

namespace fre {
    class Bootstrap
    {
        private:
            int T;                  // number of samplings
            int N;                  // number of days
            vector<Stock>* Stocks;  // stocks group
            
            Matrix AAR;             // average daily abnormal returns
            Matrix CAAR;            // cumulative average abnormal returns
            
            // member functions
            Vector CalculateAAR(vector<Stock>* SamplingStocks_);    // calculate AAR
            Vector CalculateCAAR(Vector* AAR_);                     // calculate CAAR
            Vector CalculateAverage(Matrix& M);                     // calculate average
            Vector CalculateStandardDeviation(Matrix& M);           // calculate standard deviation
        
        public:
            // constructor
            Bootstrap(int T_, int N_, vector<Stock>* Stocks_): T(T_), N(N_), Stocks(Stocks_) {}
            
            // member functions
            void ImplementBoostrapping(); // implement bootstrapping
            
            // getter functions
            Matrix* GetAAR() { return &AAR; }
            Matrix* GetCAAR() { return &CAAR; }
            
            Vector GetAveragedAAR() { return CalculateAverage(AAR); }
            Vector GetAveragedCAAR() { return CalculateAverage(CAAR); }
            Vector GetAARSTD() { return CalculateStandardDeviation(AAR); }
            Vector GetCAARSTD() { return CalculateStandardDeviation(CAAR); }
    };
}