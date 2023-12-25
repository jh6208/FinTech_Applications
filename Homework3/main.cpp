#include <iostream>
using namespace std;

/*
 (1) Trapesoid Approximation Formula:
 integral (a to b) f(x) dx = (b - a) / (2*N) * (f(a) + 2*f(x1) + 2*f(2) + 2*f(x3) + 2*f(x4) + ... + 2*f(x_{N-1}) + f(b))
 
 (2) Simpson Approximation Formula:
 integral (a to b) f(x) dx = (b - a) / (3*N) * (f(a) + 4*f(x1) + 2*f(2) + 4*f(x3) + 2*f(x4) + ... + 4*f(x_{N-1}) + f(b)) 
 
 (Note: Let N be a positive even integer.)
*/

class DefInt 
{
private:
    double a;
    double b;
    double (*f) (double);
    
public:
    DefInt(double a_, double b_, double (*f_) (double)): a(a_), b(b_), f(f_) {}
    double ByTrapzoid(int N);
    double BySimpson(int N);
    double ByMidPoint(int N);
};

double DefInt::ByTrapzoid(int N)
{
    double result = f(a);
    double h = (b-a)/N;
    
    for (int k=1; k<N; k++)
    {
        result += 2*f(a+k*h);
    }
    result += f(b);
    result *=0.5*h;
    
    return result;
}

/*
double DefInt::BySimpson(int N)
{
    double result = f(a);
    double h = (b-a)/N;
    int count = 1; //counter counting whether use "4" or "2" in the Simpson formula
    int four_or_two;
    
    for (int k=1; k<N; k++)
    {
        if (count % 2 != 0)
        {
            four_or_two = 4;
        }
        else 
        {
            four_or_two = 2;
        }
        result += four_or_two*f(a+k*h);
        count += 1;
    }
    result += f(b);
    result *= (1.0/3)*h;
    
    return result;
}
*/

double DefInt::BySimpson(int N)
{
    double result = f(a);
    double h = (b-a)/N;
   
    for (int k=0; k<N/2; k++)
    {
        result += 4*f(a+(2*k+1)*h)+2*f(a+(2*k+2)*h);
    }
    result -= 2*f(a+(2*(N/2-1)+2)*h);
    result += f(b);
    result *= (1.0/3)*h;
    
    return result;
}

/*
double DefInt::ByMidPoint(int N)
{
    double result = 0.0;
    double h = (b-a)/N;
    double x_pre = a;
    double x_now = a + h;
    
    for (int k=2; k<=N; k++)
    {
        result += f((x_pre+x_now)/2.0);
        x_pre = x_now;
        x_now = a+k*h;
    }
    
    result += f((x_pre+x_now)/2.0);
    result *= h;
 
    return result;
}
*/


double DefInt::ByMidPoint(int N)
{
    double result = 0.0;
    double h = (b-a)/N;
    
    for (int k=0; k<N; k++)
    {
        result += f(a+h*(k+0.5));
    }
    result *= h;
    
    return result;
}


double f(double x) {return x * x * x - x * x + 1;}

int main()
{
    double a = 1.0;
    double b = 2.0;
    DefInt MyInt(a, b, f);
    int N = 1000;
    cout << "The Trapezoid method is: " << MyInt.ByTrapzoid(N) << ";" << endl;
    cout << "The Simpson method is: " << MyInt.BySimpson(N) << ";" << endl;
    cout << "The Midpoint method is: " << MyInt.ByMidPoint(N) << ";" << endl;
    
}
/*
 The Trapezoid method is: 2.41667;
 The Simpson method is: 2.41667;
 The Midpoint method is: 2.41667;
 Program ended with exit code: 0
*/

