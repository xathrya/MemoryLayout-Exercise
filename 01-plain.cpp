/*
Find out the memory layout of a class
A class with three private variables and two functions.

Compile:
    (GCC)  
    $ g++ plain.cpp -std=c++11 -o plain
    
    (LLVM) 
    $ clang++ plain.cpp -o plain

    (MSVC)
    $ cl plain.cpp

Run:
    $ plain
*/
#include "util.hpp"

/*
Observe the address of each of them.
Question:
    Variables
    - Are the address of variables close to each other? See also their size.
    - Do the addresses come in certain order? In what order?
    - Are the variables close to the start of class?
    - In what segment do the variables reside?
    
    Functions
    - Are the address of functions close to each other?
    - Do the address come in certain order? In what order?
    - Are the functions close to the start of class?
    - Are the functions close to the variables?
    - In what segment do the functions reside?
*/

//======== Type Definitions =========================================
class Example
{
    int x;
    int y;
    int z;
public:
    Example() 
    {
        x = 135;
        y = 182;
    }
    void printVars()
    {
        printf("Location x: [%p] | Value: %d\n", &x, x);
        printf("Location y: [%p] | Value: %d\n", &y, y);
        printf("Location z: [%p] | Value: %d\n", &z, z);
    }
    void printFuncs()
    {
        printf("Location of printVars   : [%p]\n", &Example::printVars);
        printf("Location of printFuncs  : [%p]\n", &Example::printFuncs);
    }
};

//======== Helper Functions =========================================

//======== Main Function ============================================
int main()
{
    Example kelas;

    dump_instance("Plain Object without any decoration", kelas);
    kelas.printVars();

    printf("\n");
    kelas.printFuncs();

    return 0;
}

//======== Implementations ==========================================