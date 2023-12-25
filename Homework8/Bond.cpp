#include "Bond.h"
#include <cmath>
namespace fre {
    double Bond::PriceByCFFormula(double y)
    {
        double P = 0;
        for (int t = 0; t < T; t++)
            P += C * exp(-y * double(t + 1));
        P += F * exp(-y * T);
        return P;
    }
    double Bond::DerivByCFFormula(double y)
    {
        double D = 0;
        for (int t = 0; t < T; t++)
            D += -C * double(t + 1) * exp(-y * double(t + 1));
        D += -F * T * exp(-y * T);
        return D;
    }
    double Intermediary::Value(double y)
    {
        return PriceByCFFormula(y);
    }
    double Intermediary::Deriv(double y)
    {
        return DerivByCFFormula(y);
    }
}
