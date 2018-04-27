/*
Find out the memory layout of a class
If a class is inherited from another class, how is it represented?

Compile:
    (GCC)  
    $ g++ inheritance-layout.cpp -std=c++11 -o inheritance-layout
    
    (LLVM) 
    $ clang++ inheritance-layout.cpp -o inheritance-layout

    (MSVC)
    $ cl inheritance-layout.cpp

Run:
    $ inheritance-layout
*/
#include "util.hpp"

/*
Observe the address of each of them.

Conclusion: 
    A class derivate from other class will have parent data in conjunction to
    it's own data.
*/

//======== Type Definitions =========================================
struct Base
{
    uint32_t x, y, z;

    Base() 
    {
        x = 135;
        y = 182;
    }
    void printVars()
    {
        printf("Location x: [%p]\n", &x);
        printf("Location y: [%p]\n", &y);
        printf("Location z: [%p]\n", &z);
    }
};

struct Derivate : public Base 
{
    uint32_t a;

    Derivate()
    {
        a = 234;
    }
    void printVars()
    {
        printf("Location x: [%p]\n", &x);
        printf("Location y: [%p]\n", &y);
        printf("Location z: [%p]\n", &z);
        printf("Location a: [%p]\n", &a);
    }
};

//======== Helper Functions =========================================

//======== Main Function ============================================
int main()
{
    printf("[+] Spawn base...\n");
    Base base;
    dump_instance("Instance of base", base);
    base.printVars();

    printf("\n");

    printf("[+] Spawn derivate...\n");
    Derivate derivate;
    dump_instance("Instance of derivate", derivate);
    derivate.printVars();

    return 0;
}

//======== Implementations ==========================================