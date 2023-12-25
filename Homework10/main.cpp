#include <iostream>
#include "PathDepOption.h"

using namespace std;
using namespace fre;

int main()
{
    double S0=100.0, r=0.03, sigma=0.2;
    MCModel Model(S0,r,sigma);

    double T =1.0/12.0, K=100.0;
    int m=30;

    ArthmAsianCall Option(T,K,m);
    
    long N=30000;
    double epsilon =0.001;
    Option.PriceByMC(Model,N,epsilon);
    cout << "Asian Call Price = " << Option.GetPrice() << endl
        << "Error = " << Option.GetPricingError() << endl
        << "delta = " << Option.GetDelta() << endl
        << "gamma = " << Option.GetGamma() << endl;
    return 0;
}
/*
 Asian Call Price = 1.41402
 Error = 0.0119888
 delta = 0.524634
 gamma = 0.116126
*/
