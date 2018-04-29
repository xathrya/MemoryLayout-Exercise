/*
Virtual Table or Virtual Method Table
In OO (object-oriented) world, a polymorphism makes Derivate class
can override the behavior of functions inherited from Base.
C++ use virtual table to implement this.

What will happen in vtable if a class is derived from multiple classes?

testing on:
    - TDM GCC 5.1.0 (assuming x64)

Compile:
    $ g++ vtable-multi-base.cpp -std=c++11 -o vtable-multi-base

Run:
    $ vtable-multi-base

We can also ask compiler to emit the vtable and other structure, see the difference.
    (GCC)
    $ g++ -g -fdump-class-hierarchy -std=c++11 vtable-multi-base.cpp

    (MSVC)
    $ cl.exe /d1 reportAllClassLayout vtable-multi-base.cpp

*/
#include <iostream>
#include "util.hpp"

/*
Observe the address of each of them.
Questions:
    - Is there any two or more entry in vtable that has same address? 
        - Why?
    - Is there any two or more classes that has same address on vtable? 
        - Why?
    - What happen when you derived Base2 from Base1 and derive Derivate from Base2 ?

Conclusion:
    The entry will be similar unless overriding occurred.
*/

//======== Type Definitions =========================================
/*
Memory layout:
    - Base1::vtable  (pointer to vtable of Base)
    - Base1::id

The vtable layout:
    - Base1::~Base1()     (base object destructor)
    - Base1::~Base1()     (deleting destructor)
    - Base1::B()
*/
class Base1 
{
public:
    int id;

    Base1(int id) : id(id)  { }
    virtual ~Base1()        { }

    void A()                { std::cout << "-  Base[" << id << "]::A" << std::endl; }
    virtual void B()        { std::cout << "-  Base[" << id << "]::B" << std::endl; }
    virtual void C()        { std::cout << "-  Base[" << id << "]::C" << std::endl; }
};

/*
Memory layout:
    - Base2::vtable  (pointer to vtable of Base)

The vtable layout:
    - Base2::C()
*/
class Base2 
{
public:
    void A()                { std::cout << "-  Base2::A" << std::endl; }

    virtual void D()        { std::cout << "-  Base2::D" << std::endl; }
};

/*
Memory layout:
    - Derivate::vtable (pointer to vtable of Derivate)
    - Base::id
    - Base2::vtable    (pointer to vtable of Base2)

The vtable layout:
    - Derivate::~Derivate()     (base object destructor)
    - Derivate::~Derivate()     (deleting destructor)
    - Base1::B()
    - Derivate::C()
    - Derivate::D()
*/
class Derivate final : public Base1, public Base2
{
public:
    Derivate(int id) : Base1(id) { }
    ~Derivate()                  { }

    void C() override           { std::cout << "-  Derivate[" << id << "]::B" << std::endl; }
    void D() override           { std::cout << "-  Derivate[" << id << "]::C" << std::endl; }
};

//======== Helper Functions =========================================

//======== Main Function ============================================
int main()
{
    Base1 base1(1);
    Base2 base2;
    Derivate derivate(2);

    dump_instance("instance of base1", base1, 4);
    dump_instance("instance of base2", base2, 2);
    dump_instance("instance of Derivate", derivate, 5);

    // Try to call B() of each instance!

    return 0;
}