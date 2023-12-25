#include "MCModel.h"
#include <cmath>

namespace fre {
    const double pi = 4.0 * atan(1.0);
    double Gauss()
    {   // generate random numbers that follow a Gaussian (normal) distribution
        double U1 = (rand() + 1.0) / (RAND_MAX + 1.0);
        double U2 = (rand() + 1.0) / (RAND_MAX + 1.0);
        // the Box-Muller transformation to obtain a random number that follows a Gaussian distribution
        return sqrt(-2.0 * log(U1)) * cos(2.0 * pi * U2);
    }

    void MCModel::GenerateSamplePath(double T, int m, SamplePath& S) const
    {
        double St = S0;
        for (int k = 0; k < m; k++)
        {
            S[k] = St * exp((r - sigma * sigma * 0.5) * (T / m) + sigma * sqrt(T / m) * Gauss());
            St = S[k];
        }
    }
}

