// EuropeanOption2.hpp
//
// Class that represents  solutions to European options. This is
// an implementation using basic C++ syntax only. It has been 
// written for pedagogical reasons
//
// (C) Datasim Component Technology BV 2003-2006
//

#pragma once

#include <string>

using namespace std;

class EuropeanOption
{
private:
	double r;		// Interest rate
	double sig;		// Volatility
	double K;		// Strike price
	double T;		// Expiry date
	double U;		// Current underlying price (e.g. stock, forward)
	double b;		// Cost of carry

	char *optType;	// Option name (call, put)
	
	// Gaussian functions
	double n(double x) const;
	double N(double x) const;
	// 'Kernel' functions for option calculations
	double CallPrice() const;
	double PutPrice() const;

public:	// Public functions
	// Q1
	EuropeanOption();								// Default call option
	EuropeanOption(const EuropeanOption& option2);	// Copy constructor
	EuropeanOption(char* optType_);					// Create option type
	EuropeanOption(double r_,
		double sig_,
		double K_,
		double T_,
		double U_,
		double b_,
		char *optType_);

	virtual ~EuropeanOption();	

	EuropeanOption& operator = (const EuropeanOption& option2);

	// Functions that calculate option price and sensitivities
	double Price() const;

	// Modifier functions
	void toggle();		// Change option type (C/P, P/C)

	char* getOptType();
};
