CC=g++
CFLAGS=-c -Wall
LDFLAGS=

SOURCES=BinomialTreeModel02.cpp Homework04.cpp Option05.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=Homework04

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f $(OBJECTS) $(EXECUTABLE)
