#include "PathDepOption02.h"
#include <cmath>

namespace fre {
    void Rescale(SamplePath& S, double x, int j)
    {
        int m = (int)S.size();
        for (int k = 0; k < m; k++) S[k][j] = x * S[k][j];
    }

    double PathDepOption::PriceByMC(const MCModel& Model, long N, double epsilon)
    {
        double H = 0.0;
        SamplePath S(m);

        int d = (int)Model.GetS0().size();
        delta.resize(d);

        Vector Heps(d);
        for (int i = 0; i < d; i++) Heps[i] = 0.0;

        for (long i = 0; i < N; i++)
        {
            Model.GenerateSamplePath(T, m, S);
            H = (i * H + Payoff(S)) / (i + 1.0);

            for (int j = 0; j < d; j++)
            {
                Rescale(S, 1.0 + epsilon, j);
                Heps[j] = (i * Heps[j] + Payoff(S)) / (i + 1.0);
                if (j < d - 1) Rescale(S, 1.0 / (1.0 + epsilon), j);
            }
        }
        Price = std::exp(-Model.GetR() * T) * H;
        for (int j = 0; j < d; j++) delta[j] = std::exp(-Model.GetR() * T) * (Heps[j] - H) / (epsilon * Model.GetS0()[j]);
        return Price;
    }

    double ArthmAsianCall::Payoff(const SamplePath& S) const
    {
        double Ave = 0.0;
        int d = (int)S[0].size();
        Vector one(d);
        for (int i = 0; i < d; i++) one[i] = 1.0;
        for (int k = 0; k < m; k++)
        {
            Ave = (k * Ave + (one ^ S[k])) / (k + 1.0);
        }
        if (Ave < K) return 0.0;
        return Ave - K;
    }
}
