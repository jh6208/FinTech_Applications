#include <iostream>
#include <iomanip>
#include "Function02.h"
#include "NonlinearSolver02.h"
#include "Bond.h"
using namespace std;
using namespace fre;
int main()
{
    double F=100.0;
    double T=3.0;
    double C=1.2;
    double Tgt=98.56;

    double Acc=0.0001;
    double LEnd=0.0;
    double REnd=1.0;
    double Guess=0.2;

    Intermediary Bond(F, C, T);

    NonlinearSolver solver(Tgt, LEnd, REnd, Acc, Guess);
    cout << "Yield by Bisection method: " << fixed << setprecision(4) << solver.SolveByBisect(&Bond) << endl;
    cout << "Yield by Newton-Raphson method: " << fixed << setprecision(4) << solver.SolveByNR(&Bond) << endl << endl;

    return 0;
}

/*
Yield by Bisection method: 0.0168
Yield by Newton-Raphson method: 0.0168
*/
