#pragma once
#include "MCModel.h"

namespace fre {
    class PathDepOption
    {
    protected:
        double Price, PricingError, delta, gamma;
        int m;
        double K;
        double T;
    public:
        PathDepOption(double T_, double K_, int m_) :Price(0.0), PricingError(0.0), delta(0.0), gamma(0.0), T(T_), K(K_), m(m_)
        {}
        virtual ~PathDepOption() {}
        virtual double Payoff(const SamplePath& S) const = 0;
        double PriceByMC(const MCModel& Model, long N, double epsilon);
        double GetT() { return T; }
        double GetPrice() { return Price; }
        double GetPricingError() { return PricingError; }
        double GetDelta() { return delta; }
        double GetGamma() { return gamma; }
    };

    class ArthmAsianCall : public PathDepOption
    {
    public:
        ArthmAsianCall(double T_, double K_, int m_) :PathDepOption(T_, K_, m_) {}
        double Payoff(const SamplePath& S) const;
    };
}





