#pragma once
#include "MCModel02.h"

namespace fre {
    class PathDepOption
    {
    protected:
        double T;
        double K;
        double Price;
        int m;
        Vector delta;
    public:
        PathDepOption(double T_, double K_, int m_) : Price(0.0), T(T_), K(K_), m(m_) {}
        double PriceByMC(const MCModel& Model, long N, double epsilon);
        Vector GetDelta() const { return delta; }
        virtual ~PathDepOption() {}
        virtual double Payoff(const SamplePath& S) const = 0;
    };

    class ArthmAsianCall : public PathDepOption
    {
    public:
        ArthmAsianCall(double T_, double K_, int m_) : PathDepOption(T_, K_, m_) {}
        double Payoff(const SamplePath& S) const;
    };
}

