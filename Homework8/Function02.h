#pragma once

namespace fre {
    class Function
    {
    public:
        virtual double Value(double x) = 0;
        virtual double Deriv(double x) = 0;
        virtual ~Function() {}
    };

    class F1 : public Function
    {
    public:
        double Value(double x);
        double Deriv(double x);
    };

    class F2 : public Function
    {
    private:
        double a; //any real number
    public:
        F2(double a_) { a = a_; }
        double Value(double x);
        double Deriv(double x);
    };
}

