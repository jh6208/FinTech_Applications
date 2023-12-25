CC = g++
CFLAGS = -Wall -ggdb3 -std=c++11 -lcurl -lpthread

main: main.o Stock.o FetchStocks.o Benchmark.o Matrix.o Bootstrap.o Gnuplot.o
	$(CC) $(CFLAGS) -o main main.o Stock.o FetchStocks.o Benchmark.o Matrix.o Bootstrap.o Gnuplot.o
	
main.o: Benchmark.h FetchStocks.h Stock.h main.cpp
	$(CC) $(CFLAGS) -c main.cpp

Gnuplot.o: Matrix.h Gnuplot.h Gnuplot.cpp
	$(CC) $(CFLAGS) -c Gnuplot.cpp

Bootstrap.o: Matrix.h Bootstrap.h Bootstrap.cpp
	$(CC) $(CFLAGS) -c Bootstrap.cpp

Matrix.o: Matrix.h Matrix.cpp
	$(CC) $(CFLAGS) -c Matrix.cpp

Benchmark.o: Stock.h Benchmark.h Benchmark.cpp
	$(CC) $(CFLAGS) -c Benchmark.cpp

FetchStocks.o: Stock.h FetchStocks.h FetchStocks.cpp 
	$(CC) $(CFLAGS) -c FetchStocks.cpp

Stock.o: Stock.h Stock.cpp
	$(CC) $(CFLAGS) -c Stock.cpp

clean:
	rm -rf main *.o