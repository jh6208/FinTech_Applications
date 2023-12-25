CC=g++
CFLAGS=-c -Wall
LDFLAGS=

SOURCES=BinomialTreeModel.cpp Homework02.cpp Option02.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=Homework02

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f $(OBJECTS) $(EXECUTABLE)



