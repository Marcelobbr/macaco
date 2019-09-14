g++ -std=c++17 -I /usr/include/python3.6 -fpic -c -o dfbuild.o dfbuild.cpp
g++ -o dfbuild.so -shared dfbuild.o -lboost_python3
