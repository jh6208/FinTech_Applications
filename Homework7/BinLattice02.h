#pragma once

#include <iostream>
#include <iomanip>
#include <vector>
using namespace std;

namespace fre {
    template<typename Type>
    class BinLattice
    {
    private:
        int N;
        vector< vector<Type> > Lattice;

    public:
        BinLattice() : N(0) {}
        BinLattice(int N_) :N(N_)
        {
            Lattice.resize(N + 1);
            for (int n = 0; n <= N; n++) Lattice[n].resize(n + 1);
        }
        ~BinLattice() {}
        void SetN(int N_)
        {
            N = N_;
            Lattice.resize(N + 1);
            for (int n = 0; n <= N; n++) Lattice[n].resize(n + 1);
        }
        void SetNode(int n, int i, Type x)
        {
            Lattice[n][i] = x;
        }
        Type GetNode(int n, int i)
        {
            return Lattice[n][i];
        }
        void Display()
        {
            cout << setiosflags(ios::fixed) << setprecision(3);
            for (int n = 0; n <= N; n++)
            {
                for (int i = 0; i <= n; i++)
                    cout << setw(7) << GetNode(n, i);
                cout << endl;
            }
            cout << endl;
        }
        friend ostream& operator<< (ostream& out, const BinLattice& b)
        {
            out << setiosflags(ios::fixed) << setprecision(3);
            for (int n = 0; n <= b.N; n++)
            {
                for (int i = 0; i <= n; i++)
                    out << setw(15) << b.Lattice[n][i];
                out << endl;
            }
            out << endl;

            return out;
        }
    };
}
