/*
Virtual Table or Virtual Method Table
In object-oriented world, a polymorphism makes Derivate clas
can override the behavior of functions inherited from base.

testing on:
    - TDM GCC 5.1.0

ps: Assuming x64

Compile:
    $ g++ vtable-inheritance.cpp -std=c++11 -o vtable-inheritance

Run:
    $ vtable-inheritance

We can also ask compiler to emit the vtable and other structure, see the difference.
    (GCC)
    $ g++ -g -fdump-class-hierarchy -std=c++11 vtable-inheritance.cpp

    (MSVC)
    $ cl.exe /d1 reportAllClassLayout vtable-inheritance.cpp

*/
#include <iostream>
#include "util.hpp"


//======== Type Definitions =========================================
/*
Order of vtable is similar to the order of declared virtual function in code.
The order is also base on the relationship of inheritance. 
It means the base vtable will be placed before the vtable of Derivate (unless overridden)
However when more than one base present, the layout become more complex.

But in most simple explanation:
    - Base1 vtable entries (with some replaced by Derivate)
    - Derivate vtable entries
    - for each other Bases, it have entries here. 
        Each of them separated by an "off the top" entry
        It is used by polymorphism to reach the Derivate object quickly.
*/

/*
Memory layout:
    - Base1::vtable  (pointer to vtable of Base)
    - Base1::id

The vtable layout:
    - Base1::~Base1()     (base object destructor)
    - Base1::~Base1()     (deleting destructor)
    - Base1::B()
    - Base1::C()
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
    - Base2::B()
    - Base2::D()
*/
class Base2 
{
public:
    void A()                { std::cout << "-  Base2::A" << std::endl; }

    virtual void B()        { std::cout << "-  Base2::B" << std::endl; }
    virtual void D()        { std::cout << "-  Base2::D" << std::endl; }
};

/*
Memory layout:
    - Derivate::vtable (pointer to vtable of Derivate)
    - Base::id
    - Data for Base2

The vtable layout:
    - Derivate::~Derivate()       (base object destructor)
    - Derivate::~Derivate()       (deleting destructor)
    - Base1::B()
    - Derivate::C()
    - Derivate::D()
    ---- "off to the top" (from Base2)
    - Base2::B()

Try to uncomment B()
*/
class Derivate final : public Base1, public Base2
{
public:
    Derivate(int id) : Base1(id) { }
    ~Derivate()                  { }

    // void B() override           { std::cout << "-  Derivate[" << id << "]::B" << std::endl; } 
    void C() override           { std::cout << "-  Derivate[" << id << "]::C" << std::endl; }
    void D() override           { std::cout << "-  Derivate[" << id << "]::D" << std::endl; }
};

//======== Helper Functions =========================================

//======== Main Function ============================================
int main()
{
    Base1 base1(1);
    Base2 base2;
    Derivate derivate(2);
    Base2 *pbase = new Derivate(3);

    dump_instance("instance of base1", base1, 4);
    dump_instance("instance of base2", base2, 2);
    dump_instance("instance of Derivate", derivate, 7);
    dump_instance("instance of pbase as Base2", *pbase, 2);
    dump_instance("instance of pbase as Derivate", *dynamic_cast<Derivate*>(pbase), 7);

    // Try to call B() of each instance!

    return 0;
}