#include <iostream>
using namespace std;

extern "C" {
    int SampleAddInt42(int i1, int i2)    {        return i1 + i2;     }
    int SampleAddInt(int i1, int i2)    {         return i1 + i2;    }
 
    // A function doing nothing ;)
    void SampleFunction1()    {    }
 
    // A function always returning one
    int SampleFunction2()    {        return 1;    }
    
    void hello() {cout << "Hello World!" << endl;}
}