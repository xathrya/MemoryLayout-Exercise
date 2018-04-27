/*
Find out the memory layout of a class
If a class one or more static variables, where do they located?

Compile:
    (GCC)  
    $ g++ static.cpp -std=c++11 -o static
    
    (LLVM) 
    $ clang++ static.cpp -o static

    (MSVC)
    $ cl static.cpp

Run:
    $ static
*/
#include "util.hpp"

/*
Observe the address of each of them.
Question:
    Variables
    - Are the address of variables each instance same?
    - In what section do each variables reside?    

Conclusion:
    An object can have a static data. All instance of object will refer to the same
    static data, which shall be implemented as global data.
*/

//======== Type Definitions =========================================
class Example
{
    static int x;
    int y;
    int z;
public:
    Example() 
    {
        x = 135;
        y = 182;
        z = 15;
    }
    void printVars()
    {
        printf("Location x: [%p] | Value: %d\n", &x, x);
        printf("Location y: [%p] | Value: %d\n", &y, y);
        printf("Location z: [%p] | Value: %d\n", &z, z);
    }
    void printFuncs()
    {
        printf("Location of printVars   : [%p]\n", &printVars);
        printf("Location of printFuncs  : [%p]\n", &printFuncs);
    }
};
int Example::x;

//======== Helper Functions =========================================

//======== Main Function ============================================
int main()
{
    Example obj1;
    Example obj2;

    dump_instance("Instance of obj1", obj1);
    obj1.printVars();
    obj1.printFuncs();

    printf("\n");
    
    dump_instance("Instance of obj2", obj2);
    obj2.printVars();
    obj2.printFuncs();


    return 0;
}

//======== Implementations ==========================================