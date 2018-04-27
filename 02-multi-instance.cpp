/*
Find out the memory layout of a class
If a class has two or more instance, where are they located?

Compile:
    (GCC)  
    $ g++ multi-instance.cpp -std=c++11 -o multi-instance
    
    (LLVM) 
    $ clang++ multi-instance.cpp -o multi-instance

    (MSVC)
    $ cl multi-instance.cpp

Run:
    $ multi-instance
*/
#include "util.hpp"

/*
Observe the address of each of them.
Question:
    Variables
    - Are the address of variables each instance same?
    
    Functions
    - Are the address of functions each instance same?    

Conclusion:
    When a class is having multiple instance, each class will have their instance data,
    but the functions (or methods) operating on them is not.

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
        printf("Location of printVars   : [%p]\n", &printVars);
        printf("Location of printFuncs  : [%p]\n", &printFuncs);
    }
};

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