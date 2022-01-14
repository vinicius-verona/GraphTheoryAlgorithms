BFS:
	g++ src/BFS.cpp -c -o bin/BFS.o -Wall
Main:
	g++ src/principal.cpp -c -o bin/principal.o -Wall
Compile:
	g++ bin/BFS.o bin/principal.o -o bin/programa -Wall
clean:
	rm bin/*.o bin/programa
all: BFS Main Compile
test: all
	sh execution.sh --no-compile
clean-test:
	rm output/*-result.out
	rm output/*-diff.out
zip-task:
	zip -j BFS-task.zip src/*.hpp src/*.cpp