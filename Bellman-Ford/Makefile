Dijkstra:
	g++ src/dijkstra.cpp -c -o bin/dijkstra.o -Wall
Bellman-Ford:
	g++ src/bellmanford.cpp -c -o bin/bellmanford.o -Wall
Main:
	g++ src/principal.cpp -c -o bin/principal.o -Wall
Compile:
	g++ bin/dijkstra.o  bin/bellmanford.o bin/principal.o -o bin/programa -Wall
clean:
	rm bin/*.o bin/programa
all: Dijkstra Bellman-Ford Main Compile
test: all
	sh execution.sh --no-compile
clean-test:
	rm output/*-result.out
	rm output/*-diff.out
zip-task:
	zip -j BellmanFord-task.zip src/*.hpp src/*.cpp -x src/dijkstra_copy.cpp