#pragma once
#include <vector>
#include "Function02.h"

using namespace std;
namespace fre {
    class Bond
    {
    private:
        double F;
        double C;
        double T;
    public:
        Bond(double F_, double C_, double T_): F(F_), C(C_), T(T_) {}
        double PriceByCFFormula(double y);
        double DerivByCFFormula(double y);
    };

    class Intermediary: public Bond, public Function
    {
    public:
        Intermediary(double F_, double C_, double T_): Bond(F_, C_, T_) {}
        double Value(double y);
        double Deriv(double y);
    };
}
