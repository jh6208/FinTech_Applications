// OptionPricer02.cpp
//

#include "BinomialTreeModel.h"
#include "Option02.h"
#include <iostream>
#include <iomanip>
using namespace std;
using namespace fre;

int main()
{
    double S0 = 0.0, U = 0.0, D = 0.0, R = 0.0;

    if (GetInputData(S0, U, D, R) != 0)
        return -1;

    double K = 0.0;   //strike price
    int N = 0;      //steps to expiry

    cout << "Enter call option data:" << endl;
    GetInputData(N, K);

    double* optionPrice = NULL;
    
    optionPrice = PriceByCRR(S0, U, D, R, N, K, CallPayoff);
    cout << "European Call option price = " << fixed << setprecision(2) << optionPrice[0] << endl;
    delete[] optionPrice;
    optionPrice = PriceByCRR(S0, U, D, R, N, K, PutPayoff);
    cout << "European Put option price = " << fixed << setprecision(2) << optionPrice[0] << endl;
    delete[] optionPrice;
    optionPrice = PriceByCRR(S0, U, D, R, N, K, DigitCallPayoff);
    cout << "Digit Call option price = " << fixed << setprecision(2) << optionPrice[0] << endl;
    delete[] optionPrice;
    optionPrice = PriceByCRR(S0, U, D, R, N, K, DigitPutPayoff);
    cout << "Digit Put option price = " << fixed << setprecision(2) << optionPrice[0] << endl;
    delete [] optionPrice;
    optionPrice = NULL;

    return 0;
}
/*
Enter S0: 106
Enter U:  1.15125
Enter D:  0.86862
Enter R:  1.00545

Input data checked
There is no arbitrage

Enter call option data:
Enter steps to expiry N: 8
Enter strike price K:    100

European Call option price = 21.68
European Put option price = 11.43
Digit Call option price = 0.58
Digit Put option price = 0.38
*/

