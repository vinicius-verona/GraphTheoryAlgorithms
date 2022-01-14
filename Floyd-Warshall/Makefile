Floyd-Warshall:
	g++ src/floydwarshall.cpp -c -o bin/floydwarshall.o -Wall
Main:
	g++ src/principal.cpp -c -o bin/principal.o -Wall
Compile:
	g++ bin/floydwarshall.o bin/principal.o -o bin/programa -Wall
clean:
	rm bin/*.o bin/programa
all: Floyd-Warshall Main Compile
test: all
	sh execution.sh --no-compile
clean-test:
	rm output/*-result.out
	rm output/*-diff.out
zip-task:
	zip -j Floyd_Warshall-task.zip src/*.hpp src/*.cpp