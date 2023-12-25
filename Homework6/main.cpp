#include "BinomialTreeModel02.h"
#include "Option08.h"
#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;
using namespace fre;
//namespace fs = std::__fs::filesystem;
int main()
{
    int N = 8;
    double U = 1.15125, D = 0.86862, R = 1.00545;
    double S0 = 106.00, K = 100.00;
    BinomialTreeModel Model(S0, U, D, R);
    //string directoryPath = "/Users/hejifan/Library/Mobile Documents/com~apple~CloudDocs/Graduate Courses/Third Semester/FRE-GY 6883/Homework06_AnswerKey/";
    //string filePath = directoryPath + "Results.txt";
    //ofstream fout(filePath);
    ofstream fout;
    fout.open("Results.txt");
    Call call(N, K);
    OptionCalculation callCalculation(&call);
    
    BinLattice<double> PriceTree;
    BinLattice<double> XTree;
    BinLattice<double> YTree;
    
    fout << "European call prices by PriceByCRR:"
        << fixed << setprecision(3) << callCalculation.PriceByCRR(Model) << endl << endl;
    
    fout << "European call prices by HW6 PriceByCRR:"
        << fixed << setprecision(3) << callCalculation.PriceByCRR(Model, PriceTree, XTree, YTree)
        << endl << endl;
    
    fout << "Stock positions in replicating strategy:" << endl << endl;
    XTree.Display(fout);
    
    fout << "Money market account positions in replicating strategy:" << endl << endl;
    YTree.Display(fout);
    
    Put put(N, K);
    OptionCalculation putCalculation(&put);
    
    fout << "European put prices by PriceByCRR:"
        << fixed << setprecision(3) << putCalculation.PriceByCRR(Model) << endl << endl;
    
    fout << "European put prices by HW6 PriceByCRR:"
        << fixed << setprecision(3) << putCalculation.PriceByCRR(Model, PriceTree, XTree, YTree)
        << endl << endl;
    
    fout << "Stock positions in replicating strategy:" << endl << endl;
    XTree.Display(fout);
    
    fout << "Money market account positions in replicating strategy:" << endl << endl;
    YTree.Display(fout);
    
    fout.close();
    
    //fs::path currentPath = fs::current_path();
    //std::cout << "Current directory for 'Results.txt' file: " << currentPath << std::endl;
    
    return 0;
    
}
/*
 Current directory for 'Results.txt' file:
 "/Users/hejifan/Library/Developer/Xcode/DerivedData/Homework6-bnqzxngjvjqvgufqstahpnguituo/Build/Product
 /Debug"
*/
