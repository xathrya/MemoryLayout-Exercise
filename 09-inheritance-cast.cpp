/*
Find out the memory layout of a class
In object-oriented world, a derived class and base class has a certain relationship.
Upcasting is converting a derived-class reference or pointer to a base-class.
Downcasting is converting a base class reference or pointer to a derived-class.

Compile:
    (GCC)  
    $ g++ inheritance-cast.cpp -std=c++11 -o inheritance-cast
    
    (LLVM) 
    $ clang++ inheritance-cast.cpp -o inheritance-cast

    (MSVC)
    $ cl inheritance-cast.cpp

Run:
    $ inheritance-cast
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
        x = 0x87;
        y = 0xB6;
    }

    void function(uint32_t a)
    {
        x = a;
        y = a + 45;
        printf("[%p] Hello Base1! %x %x\n", &Base1::function, x, y);
    }
};

struct Base2
{
    uint32_t z;

    Base2()
    {
        z = 0xEA;
    }
    
    void function(uint32_t a)
    {
        z = a;
        printf("[%p] Hello Base2! %x\n", &Base2::function, z);
    }
};

struct Derivate : public Base1, public Base2 
{
    uint32_t w;

    Derivate()
    {
        w = 0;
    }

    void function(uint32_t a)
    {
        w = a;
        printf("[%p] Hello Derivate! %x %x %x %x\n", &Derivate::function, x, y, z, w);
    }
};

//======== Helper Functions =========================================

//======== Main Function ============================================
int main()
{
    Base1    base1;
    Derivate derivate;

    printf("[-] base1 is at    %p (size %d)\n", &base1, sizeof(base1));
    printf("[-] derivate is at %p (size %d)\n", &derivate, sizeof(derivate));
    derivate.function(0xFF);
    base1.function(0x87);

    printf("\n");

    printf("[+] Upcast derivate to parent\n");
    printf("[-] to Base1...\n");
    Base1* pbase1 = &derivate;
    printf("[-] I'm located at: %p\n", pbase1);
    pbase1->function(1);
    printf("\n");
    printf("[-] to Base2...\n");
    Base2* pbase2 = &derivate;
    printf("[-] I'm located at: %p\n", pbase2);
    pbase2->function(2);

    printf("\n\n");
    
    printf("[+] Downcast base to child\n");
    Derivate* pderivate = (Derivate*) &base1;
    printf("[-] I'm located at: %p\n", pderivate);
    pderivate->function(3);


    return 0;
}

//======== Implementations ==========================================