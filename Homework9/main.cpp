// TestEuropeanOption.cpp
//
// Test program for the exact solutions of European options.
// Check answers with Haug 1998
//
// (C) Datasim Component Technology BV 2003-2006
//

#include "EuropeanOption.hpp"
#include <iostream>

int main()
{
    EuropeanOption option1;
    cout << "Q1: " << option1.getOptType() << " option on a stock: " << option1.Price() << endl;

    // Q2
    char optionName[] = "Put";
    EuropeanOption option2(0.1, 0.3, 50.0, 0.25, 50.0, 0.1, optionName);
    cout << "Q2: " << option2.getOptType() << " option on a stock: " << option2.Price() << endl;

    // Q3
    double U = 50.0 - 1.5 * exp(-0.1 * (2.0/12.0));
    EuropeanOption option3(0.1, 0.3, 50.0, 0.25, U, 0.1, optionName);
    cout << "Q3: " << option3.getOptType() << " option with dividend: " << option3.Price() << endl;
    
    /*
    EuropeanOption* option = new EuropeanOption;
    EuropeanOption* option4 = option;

    cout << "Address in option: " << option << endl; // Address on the heap
    cout << "Address in option4: " << option4 << endl; // Address on the heap
    cout << endl;
    cout << "Address in option: " << &option << endl; // Address on the stack
    cout << "Address in option4: " << &option4 << endl; // Address on the stack
    
    delete option; // or `delete option1;`
    option = nullptr;
    option4 = nullptr;
    */
    
    return 0;
}

/*
Q1: Call option on a stock: 2.13293
Q2: Put option on a stock: 2.37561
Q3: Put option with dividend: 3.03039
*/
