CC=g++
CFLAGS=-c -Wall
LDFLAGS=

SOURCES=BinomialTreeModel02.cpp DoubleDigitOpt.cpp Homework05.cpp Option05.cpp SpreadOpt.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=Homework05

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f $(OBJECTS) $(EXECUTABLE)
