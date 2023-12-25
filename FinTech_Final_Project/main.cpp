#include "FetchStocks.h"
#include "Benchmark.h"
#include "Bootstrap.h"
#include "Matrix.h"
#include "Gnuplot.h"

using namespace std;
using namespace fre;

void DisplayMenu()
{
    cout << "-----------------------------------MENU-----------------------------------\n";
    cout << "1. Enter N to retrieve 2N+l days of historical price data for all stocks.\n";
    cout << "2. Pull information for one stock from one group.\n";
    cout << "3. Show AAR, AAR-STD, CAAR, and CAAR-STD for one group.\n";
    cout << "4. Plot Avg CAAR for 3 groups.\n";
    cout << "5. Plot STD CAAR for 3 groups.\n";
    cout << "6. Plot Avg AAR for 3 groups.\n";
    cout << "7. Plot STD AAR for 3 groups.\n";
    cout << "8. Exit\n";
}

template <typename T>
void print(const vector<T>& vec, int digit = 5, int numColumns=10, int fieldWidth=15) {
    // Set precision for floating-point numbers
    cout << fixed << setprecision(digit);
    // Print the vector in a grid
    for (size_t i = 0; i < vec.size(); ++i) {
        cout << setw(fieldWidth) << vec[i];
        // Move to the next line after printing the specified number of columns
        if ((i + 1) % numColumns == 0 || i == vec.size() - 1) {
            cout << endl;
        } else {
            cout << " ";
        }
    }
}

string GetStockGroup(Stock* stock, vector<Stock>* beat, vector<Stock>* meet, vector<Stock>* miss)
{
    auto iter = find(beat->begin(), beat->end(), *stock);
    if (iter != beat->end()) return "Beat";
    iter = find(meet->begin(), meet->end(), *stock);
    if (iter != meet->end()) return "Meet";
    iter = find(miss->begin(), miss->end(), *stock);
    if (iter != miss->end()) return "Miss";
    return "";
}

int main()
{
    // set file name and api token
    string file_name = "Russell3000EarningsAnnouncements.csv";
    string api_token = "6568c6cf389dc8.94080452";
    // fetch IWV
    string symbol = "IWV";
    string year = "2023";
    Benchmark IWV(api_token, symbol, year);
    IWV.CalculateReturns();
    // inputs
    char choice;
    string UserInput;
    bool pull_data = false;
    FetchStocks fetch_stocks;
    int N = 0;
    vector<Stock>* BeatEstimateGroup;
    vector<Stock>* MeetEstimateGroup;
    vector<Stock>* MissEstimateGroup;
    string stock_symbol;
    Vector AvgAAR_beat, STDAAR_beat, AvgCAAR_beat, STDCAAR_beat;
    Vector AvgAAR_meet, STDAAR_meet, AvgCAAR_meet, STDCAAR_meet;
    Vector AvgAAR_miss, STDAAR_miss, AvgCAAR_miss, STDCAAR_miss;
    map<string, Matrix>  FinalMatrix;
    string group;
    
    do {
        DisplayMenu();
        cout << "Enter your choice and press return: ";
        cin >> choice;
        switch (choice) 
        {
            case '1':
            {
                cout << "Enter N (N must be between 60 and 90): ";
                cin >> N;
                while (N < 60 || N > 90)
                { 
                    cout << "N is Invalid; please re-enter." << endl;
                    cout << "Enter N (N must be between 60 and 90): ";
                    cin >> N;
                }
                // fetch selected Russell 3000 stocks from csv file
                fetch_stocks = FetchStocks(file_name, api_token);
                // get start date and end date for each stock
                IWV.FindStartDateAndEndDate(N, fetch_stocks.GetStocks());
                // fetch stock's price
                fetch_stocks.UpdateStocksPrices(10);
                // check if there are not enough historical prices for 2N+1
                fetch_stocks.CheckStocks(N);
                // calculate returns
                fetch_stocks.CalculateStocksReturns();
                fetch_stocks.CalculateStocksAbnReturns();
                // sort stocks
                fetch_stocks.SortStocks();
                // update map that stores stocks
                fetch_stocks.UpdateStocksMap();
                // get three groups
                BeatEstimateGroup = fetch_stocks.GetBeatEstimateGroup();
                MeetEstimateGroup = fetch_stocks.GetMeetEstimateGroup();
                MissEstimateGroup = fetch_stocks.GetMissEstimateGroup();
                // set the number of bootstrapping
                int T = 40;
                // implement bootstrapping
                // for beat estimate group
                Bootstrap bootstrap_beat(T, N, BeatEstimateGroup);
                bootstrap_beat.ImplementBoostrapping();
                AvgAAR_beat = bootstrap_beat.GetAveragedAAR();
                STDAAR_beat = bootstrap_beat.GetAARSTD();
                AvgCAAR_beat = bootstrap_beat.GetAveragedCAAR();
                STDCAAR_beat = bootstrap_beat.GetCAARSTD();
                // for meet estimate group
                Bootstrap bootstrap_meet(T, N, MeetEstimateGroup);
                bootstrap_meet.ImplementBoostrapping();
                AvgAAR_meet = bootstrap_meet.GetAveragedAAR();
                STDAAR_meet = bootstrap_meet.GetAARSTD();
                AvgCAAR_meet = bootstrap_meet.GetAveragedCAAR();
                STDCAAR_meet = bootstrap_meet.GetCAARSTD();
                // for miss estimate group
                Bootstrap bootstrap_miss(T, N, MissEstimateGroup);
                bootstrap_miss.ImplementBoostrapping();
                AvgAAR_miss = bootstrap_miss.GetAveragedAAR();
                STDAAR_miss = bootstrap_miss.GetAARSTD();
                AvgCAAR_miss = bootstrap_miss.GetAveragedCAAR();
                STDCAAR_miss = bootstrap_miss.GetCAARSTD();
                // create the final big matrix
                FinalMatrix["Beat"] = {AvgAAR_beat, STDAAR_beat, AvgCAAR_beat, STDCAAR_beat};
                FinalMatrix["Meet"] = {AvgAAR_meet, STDAAR_meet, AvgCAAR_meet, STDCAAR_meet};
                FinalMatrix["Miss"] = {AvgAAR_miss, STDAAR_miss, AvgCAAR_miss, STDCAAR_miss};
                // set pull_data to true
                pull_data = true;
                // go back to menu
                cout << "Please enter continue..."; 
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cin.get();
                cout << endl;
                break;
            }
            case '2':
            {
                if (!pull_data) 
                {
                    cout << "Please retrieve historical price data for all stocks first." << endl;
                    break;
                }
                cout << "Enter Symbol for Detailed Information: ";
                cin >> stock_symbol;
                // get stock of the given symbol
                Stock* stock = fetch_stocks.GetStock(stock_symbol);
                while (stock == nullptr)
                {
                    cout << "Symbol is invalid; please re-enter." << endl;
                    cout << "Enter Symbol for Detailed Information: ";
                    cin >> stock_symbol;
                    stock = fetch_stocks.GetStock(stock_symbol);
                }
                // pull information for the stock
                cout << "Ticker: " << *stock->GetSymbol() << endl;
                cout << "Earning Announcement Date: " << *stock->GetDate() << endl;
                cout << "Earning Period Ending: " << *stock->GetPeriodEnding() << endl;
                cout << "Earning Estimate: $" << stock->GetEstimate() << endl;
                cout << "Reported Earning Per Share: $" << stock->GetReported() << endl;
                cout << "Earning Surprise $" << stock->GetSurprise() << endl;
                cout << "Earning Suprise Percentage: " << stock->GetSurprisePct() << "%" << endl;
                cout << "Group: " << GetStockGroup(stock, BeatEstimateGroup, MeetEstimateGroup, MissEstimateGroup) << endl << endl;
                cout << "Stock Daily Price Dates: " << endl << endl;
                print(*stock->GetDates());
                cout << endl << "Stock Cumulative Daily Prices: " << endl << endl;
                print(*stock->GetPrices(), 2, 10, 10);
                cout << endl << "Stock Cumulative Daily Returns: " << endl << endl;
                print(*stock->GetReturns(), 3, 10, 10);
                cout << endl << "Stock Abnormal Daily Returns: " << endl << endl;
                print(*stock->GetAbnReturns(), 3, 10, 10);
                cout << endl;
                // go back to menu
                cout << "Please enter continue..."; 
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cin.get();
                cout << endl;
                break;
            }
            case '3':
            {
                if (!pull_data) 
                {
                    cout << "Please retrieve historical price data for all stocks first." << endl << endl;
                    break;
                }
                
                do {
                    cout << "Enter Gronp (Beat, Meet, Miss) for Detailed Information: ";
                    cin >> group;
                    if (group == "Beat")
                    {
                        cout << endl << "Avg AARs for Group BEAT" << endl << endl;
                        print(FinalMatrix["Beat"][0]);
                        cout << endl << "AARs STD for Group BEAT" << endl << endl;
                        print(FinalMatrix["Beat"][1]);
                        cout << endl << "Avg CAARs for Group BEAT" << endl << endl;
                        print(FinalMatrix["Beat"][2]);
                        cout << endl << "CAARs STD for Group BEAT" << endl << endl;
                        print(FinalMatrix["Beat"][3]);
                        cout << endl;
                    }
                    else if (group == "Meet")
                    {
                        cout << endl << "Avg AARs for Group MEET" << endl << endl;
                        print(FinalMatrix["Meet"][0]);
                        cout << endl << "AARs STD for Group MEET" << endl << endl;
                        print(FinalMatrix["Meet"][1]);
                        cout << endl << "Avg CAARs for Group MEET" << endl << endl;
                        print(FinalMatrix["Meet"][2]);
                        cout << endl << "CAARs STD for Group MEET" << endl << endl;
                        print(FinalMatrix["Meet"][3]);
                        cout << endl;
                    }
                    else if (group == "Miss")
                    {
                        cout << endl << "Avg AARs for Group MISS" << endl;
                        print(FinalMatrix["Miss"][0]);
                        cout << endl << "AARs STD for Group MISS" << endl;
                        print(FinalMatrix["Miss"][1]);
                        cout << endl << "Avg CAARs for Group MISS" << endl;
                        print(FinalMatrix["Miss"][2]);
                        cout << endl << "CAARs STD for Group MISS" << endl;
                        print(FinalMatrix["Miss"][3]);
                        cout << endl;
                    }
                    else { cout << "Group is invalid; please re-enter." << endl; }
                } while((group != "Beat") & (group != "Meet") & (group != "Miss"));
                // go back to menu
                cout << "Please enter continue..."; 
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cin.get();
                cout << endl;
                break;
            }
            case '4':
            {
                if (!pull_data) 
                {
                    cout << "Please retrieve historical price data for all stocks first." << endl << endl;
                    break;
                }
                // plot results
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                Gnuplot gnuplot(N, FinalMatrix["Beat"][2], FinalMatrix["Meet"][2], FinalMatrix["Miss"][2]);
                gnuplot.PlotResults("Averaged CAARs For 3 Groups", "Avg CAAR(%)", true);
                cout << endl;
                break;
            }
            case '5':
            {
                if (!pull_data) 
                {
                    cout << "Please retrieve historical price data for all stocks first." << endl << endl;
                    break;
                }
                // plot results
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                Gnuplot gnuplot(N, FinalMatrix["Beat"][3], FinalMatrix["Meet"][3], FinalMatrix["Miss"][3]);
                gnuplot.PlotResults("CAARs STD For 3 Groups", "CAAR STD", false);
                cout << endl;
                break;
            }
            case '6':
            {
                if (!pull_data) 
                {
                    cout << "Please retrieve historical price data for all stocks first." << endl << endl;
                    break;
                }
                // plot results
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                Gnuplot gnuplot(N, FinalMatrix["Beat"][0], FinalMatrix["Meet"][0], FinalMatrix["Miss"][0]);
                gnuplot.PlotResults("Averaged AARs For 3 Groups", "Avg AAR(%)", true);
                cout << endl;
                break;
            }
            case '7':
            {
                if (!pull_data) 
                {
                    cout << "Please retrieve historical price data for all stocks first." << endl << endl;
                    break;
                }
                // plot results
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                Gnuplot gnuplot(N, FinalMatrix["Beat"][1], FinalMatrix["Meet"][1], FinalMatrix["Miss"][1]);
                gnuplot.PlotResults("AARs STD For 3 Groups", "AAR STD", false);
                cout << endl;
                break;
            }
            default:
            {
                cout << "Invalid choice. Please re-enter.\n" << endl;
            }
        }
    } while(choice != '8');
}