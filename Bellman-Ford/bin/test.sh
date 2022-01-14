cd ..
make clean
make all
cd bin
valgrind --leak-check=full ./programa < ../input/1.in
