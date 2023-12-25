#include "Bootstrap.h"

namespace fre {
    Vector Bootstrap::CalculateAAR(vector<Stock>* SamplingStocks_) 
    {
        Vector AAR_i(2 * N, 0.0);
        auto it = SamplingStocks_->begin();
        for (; it != SamplingStocks_->end(); it++)
        {
            Vector AR = *(it->GetAbnReturns());
            // int size = AR.size();
            // if (size < 2 * N) { for (int i = 0; i < 2 * N - size; i++) AR.push_back(0.0); }
            AAR_i = AAR_i + AR;
        }
        return (1.0 / SamplingStocks_->size()) * AAR_i;
    }
    
    Vector Bootstrap::CalculateCAAR(Vector* AAR_)
    {
        Vector CAAR_i(2 * N, 0.0);
        int size = 2 * N;
        CAAR_i[0] = AAR_->at(0);
        for (int j = 1; j < size; j++)
        {
            CAAR_i[j] = CAAR_i[j-1] + AAR_->at(j); 
        }
        return CAAR_i;
    }
    
    Vector Bootstrap::CalculateAverage(Matrix& M)
    {
        Vector Average;
        // iterator every sampling to calculate average
        int size = 2 * N;
        for (int i = 0; i < size; i++)
        {
            double average = 0.0;
            auto it = M.begin();
            for (; it != M.end(); it++) average += it->at(i);
            Average.push_back(average / T);
        }
        return Average;
    }
    
    Vector Bootstrap::CalculateStandardDeviation(Matrix& M)
    {
        Vector StandardDeviation;
        // iterator every sampling to calculate standard deviation
        Vector Average = CalculateAverage(M);
        int size = 2 * N;
        for (int i = 0; i < size; i++)
        {
            double average = Average[i];
            double variance = 0.0;
            auto it = M.begin();
            for (; it != M.end(); it++) 
            {
                variance += pow(it->at(i) - average, 2.0);
            }
            StandardDeviation.push_back(sqrt(variance / (T - 1)));
        }
        return StandardDeviation;
    }
    
    void Bootstrap::ImplementBoostrapping()
    {
        srand((unsigned)time(NULL));
        for(int i = 0; i < T; i++)
        {
            random_shuffle(Stocks->begin(), Stocks->end());
            vector<Stock> SamplingStocks(Stocks->begin(), Stocks->begin() + 30);
            Vector AAR_i = CalculateAAR(&SamplingStocks);
            Vector CAAR_i = CalculateCAAR(&AAR_i);
            AAR.push_back(AAR_i);
            CAAR.push_back(CAAR_i);
        }
    }
}