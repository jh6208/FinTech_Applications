#include "Option01.h"
#include "BinomialTreeModel.h"
#include <iostream>
#include <cmath>
using namespace std;

namespace fre {
    double PriceByCRR(double S0, double U, double D, double R, unsigned int N, double K)
    {
        double q = RiskNeutProb(U, D, R);
        double Price = 0;
        double FactorialN = Factorial(N);
        
        for (int i = 0; i <= N; i++) {
            Price += FactorialN / (Factorial(i) * Factorial(N-i)) * pow(q,i) * pow(1-q, N-i) * CallPayoff(CalculateAssetPrice(S0, U, D, N, i), K);
        }
        
        Price /= pow(R, N);
        
        return Price;
    }

    double CallPayoff(double z, double K)
    {
        if (z > K) return z - K;
        return 0.0;
    }

    double Factorial(int n)
    {
        double num = 1.0;
    
        if (n == 0 || n == 1) return num;
    
        while (n > 1) {
            num *= n;
            --n;
        }
    
        return num;
    }
}
