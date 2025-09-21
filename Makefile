CC=g++
CFLAGS=-g -Wall -Werror

OBJECTS =

random: $(OBJECTS) ./build/RandomGraphs.o
	g++ -o ./build/RandomGraphs ./build/RandomGraphs.o $(OBJECTS) -g

randomGraphDegree: $(OBJECTS) ./build/RandomGraphDegree.o
	g++ -o ./build/RandomGraphDegree ./build/RandomGraphDegree.o $(OBJECTS) -g

build: $(OBJECTS) ./build/ShannonSwitching.o
	g++ -o ./build/ShannonSwitching ./build/ShannonSwitching.o $(OBJECTS) -g

./build/ShannonSwitching.o: ./src/ShannonSwitching.cpp
	mkdir -p build
	g++ -o $@ -c $(CFLAGS) $<

./build/RandomGraphs.o: ./src/RandomGraph.cpp
	mkdir -p build
	g++ -o $@ -c $(CFLAGS) $<

./build/RandomGraphDegree.o: ./src/RandomGraphDegree.cpp
	mkdir -p build
	g++ -o $@ -c $(CFLAGS) $<

./build/%.o: ./src/Graphs/%.cpp
	mkdir -p build
	${CC} -o $@ -c ${CFLAGS} $<

clean:
	rm -rf ./build