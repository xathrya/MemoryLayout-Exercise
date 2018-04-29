/*
Find out the memory layout of a class
If a class is inherited from another class, how it is built?

Compile:
    (GCC)  
    $ g++ inheritance-instance-order.cpp -std=c++11 -o inheritance-instance-order
    
    (LLVM) 
    $ clang++ inheritance-instance-order.cpp -o inheritance-instance-order

    (MSVC)
    $ cl inheritance-instance-order.cpp

Run:
    $ inheritance-instance-order
*/
#include "util.hpp"

/*
Observe the order of instantiation.

Conclusion:
    - when instantiating, the constructor is called from parent to child.
    - when destructing, the destructor is called from child to parent. 
*/

//======== Type Definitions =========================================
struct Base
{
    Base() 
    {
        printf("Hello from Base\n");
    }
    ~Base()
    {
        printf("Bye from Base\n");
    }
};

struct Derivate : public Base 
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

struct DerivateMore : public Derivate
{
    DerivateMore()
    {
        printf("Hello from DerivateMore\n");
    }
    ~DerivateMore()
    {
        printf("Bye from DerivateMore\n");
    }
};

//======== Helper Functions =========================================

//======== Main Function ============================================
int main()
{
    // Spawn Base in a scope
    {
        printf("[+] Spawning Base...\n");
        Base base;
    }

    printf("\n");

    // Spawn Derivate in a scope
    {
        printf("[+] Spawning Derivate...\n");
        Derivate derivate;
    }
    
    printf("\n");

    // Spawn DerivateMore in a scope
    {
        printf("[+] Spawning DerivateMore...\n");
        DerivateMore derivate_more;
    }

    return 0;
}

//======== Implementations ==========================================