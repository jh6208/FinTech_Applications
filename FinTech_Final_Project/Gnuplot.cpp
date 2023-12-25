#include "Gnuplot.h"

namespace fre {
    Gnuplot::Gnuplot(int N_, Vector Beat_, Vector Meet_, Vector Miss_): N(N_), Beat(Beat_), Meet(Meet_), Miss(Miss_) 
    { 
        for (int i = -N + 1; i <= N; i++) Dates.push_back(i);
    }
        
    void Gnuplot::PlotResults(string title_, string yLabel_, bool pct_)
    {
        double pct = 1.0;
        if (pct_) pct = 100.0;        
        // begin plot
        FILE *gnuplotPipe, *tempDataFile;
        const char *tempDataFileName1 = "Beat Estimate Group";
        const char *tempDataFileName2 = "Meet Estimate Group";
        const char *tempDataFileName3 = "Miss Estimate Group";
        double date1, beat, date2, meet, date3, miss;
        int i;
        const char *title = title_.c_str();
        const char *yLabel = yLabel_.c_str();
        gnuplotPipe = popen("gnuplot -persist", "w");
        fprintf(gnuplotPipe, "set grid\n");
        fprintf(gnuplotPipe, "set title '%s'\n", title);
        fprintf(gnuplotPipe, "set autoscale\n");
        fprintf(gnuplotPipe, "set xlabel 'Announcement Date'\nset ylabel '%s'\n", yLabel);
        fprintf(gnuplotPipe, "set arrow from 0, graph 0 to 0, graph 1 nohead lc rgb 'black'\n");
        if (gnuplotPipe) 
        {
            fprintf(gnuplotPipe, "plot \"%s\" with lines, \"%s\" with lines, \"%s\" with lines\n", tempDataFileName1, tempDataFileName2, tempDataFileName3);
            fflush(gnuplotPipe);
            // beat estimate group
            tempDataFile = fopen(tempDataFileName1, "w");
            for (i = 0; i < 2 * N; i++) 
            {
                date1 = Dates[i];
                beat = Beat[i] * pct;
                fprintf(tempDataFile, "%lf %lf\n", date1, beat);
            }
            fclose(tempDataFile);
            // meet estimate group
            tempDataFile = fopen(tempDataFileName2, "w");
            for (i = 0; i < 2 * N; i++) 
            {
                date2 = Dates[i];
                meet = Meet[i] * pct;
                fprintf(tempDataFile, "%lf %lf\n", date2, meet);
            }
            fclose(tempDataFile);
            // miss estimate group
            tempDataFile = fopen(tempDataFileName3, "w");
            for (i = 0; i < 2 * N; i++) {
                date3 = Dates[i];
                miss = Miss[i] * pct;
                fprintf(tempDataFile, "%lf %lf\n", date3, miss);
            }
            fclose(tempDataFile);
            printf("press enter to continue...");
            getchar();
            remove(tempDataFileName1);
            remove(tempDataFileName2);
            remove(tempDataFileName3);
            fprintf(gnuplotPipe,"exit \n");
        } 
        else { printf("gnuplot not found..."); }
    }
}