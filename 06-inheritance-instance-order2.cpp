/*
Find out the memory layout of a class
If a class is inherited from another class, how it is built?
What if it inherit from more than 1 class?

Compile:
    (GCC)  
    $ g++ inheritance-instance-order2.cpp -std=c++11 -o inheritance-instance-order2
    
    (LLVM) 
    $ clang++ inheritance-instance-order2.cpp -o inheritance-instance-order2

    (MSVC)
    $ cl inheritance-instance-order2.cpp

Run:
    $ inheritance-instance-order2
*/
#include "util.hpp"

/*
Observe the order of instantiation.

Conclusion:
    When instantiating a class with two or more base, 
    the base will be instantiate in order of declaration.

*/

//======== Type Definitions =========================================
struct Base1
{
    Base1() 
    {
        printf("Hello from Base1\n");
    }
    ~Base1()
    {
        printf("Bye from Base1\n");
    }
};

struct Base2
{
    Base2()
    {
        printf("Hello from Base2\n");
    }
    ~Base2()
    {
        printf("Bye from Base2\n");
    }
};

struct Derivate : public Base1, public Base2 
{
    Derivate()
    {
        printf("Hello from Derivate\n");
    }
    ~Derivate()
    {
        printf("Bye from Derivate\n");
    }
};

//======== Helper Functions =========================================

//======== Main Function ============================================
int main()
{
    // Spawn Derivate in a scope
    {
        printf("[+] Spawning Derivate...\n");
        Derivate derivate;
    }

    return 0;
}

//======== Implementations ==========================================