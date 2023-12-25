#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "Matrix.h"

using namespace std;

namespace fre {
    class Gnuplot
    {
        private:
            int N;          // the number of days
            Vector Dates;   // the days for all averaged CAAR
            Vector Beat;    // results for beat group
            Vector Meet;    // results for meet group
            Vector Miss;    // results for miss group
        
        public:
            // constructor
            Gnuplot() {}
            Gnuplot(int N_, Vector Beat_, Vector Meet_, Vector Miss_);
            
            // member functions
            void PlotResults(string title_, string yLabel_, bool pct_=false);  // generate a gnuplot chart showing the results of all three groups
    };
}