#pragma once
#include "BinomialTreeModel02.h"
#include <cmath>
using namespace std;
namespace fre {
    class BSMod
    {
    private:
        double S0, r, sigma, h, U, D, R;
    public:
        BSMod(double S0_, double r_, double sigma_, double h_): S0(S0_), r(r_), sigma(sigma_), h(h_), U(0.0), D(0.0), R(0.0) {}
        BinomialTreeModel BSBinMod()
        {
            U = exp(sigma * sqrt(h));
            D = 1 / U;
            R = exp(r * h);
            BinomialTreeModel BSTreeMod(S0, U, D, R);
            return BSTreeMod;
        }
    };
}
