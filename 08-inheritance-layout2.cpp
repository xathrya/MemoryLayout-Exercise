/*
Find out the memory layout of a class
If a class is inherited from another class, how it is built?

Compile:
    (GCC)  
    $ g++ inheritance-layout2.cpp -std=c++11 -o inheritance-layout2
    
    (LLVM) 
    $ clang++ inheritance-layout2.cpp -o inheritance-layout2

    (MSVC)
    $ cl inheritance-layout2.cpp

Run:
    $ inheritance-layout2
*/
#include "util.hpp"

/*
Observe the address of each of them.

Conclusion:
    When instantiating a class with two or more base, 
    the derived class will have base variables and put in order of declaration.
*/

//======== Type Definitions =========================================
struct Base1
{
    uint32_t x, y;

    Base1() 
    {
        x = 135;
        y = 182;
    }
};

struct Base2
{
    uint32_t z;

    Base2()
    {
        z = 234;
    }
};

struct Derivate : public Base1, public Base2 
{
    uint32_t w;

    void printVars()
    {
        printf("Location w: [%p]\n", &w);
        printf("Location x: [%p]\n", &x);
        printf("Location y: [%p]\n", &y);
        printf("Location z: [%p]\n", &z);
    }
};

//======== Helper Functions =========================================

//======== Main Function ============================================
int main()
{
    printf("[+] Spawn derivate...\n");
    Derivate derivate;
    
    printf("Size of derivate: %d\n", sizeof(derivate));
    printf("Size of Base1: %d\n", sizeof(Base1));
    printf("Size of Base2: %d\n", sizeof(Base2));
    derivate.printVars();

    return 0;
}

//======== Implementations ==========================================