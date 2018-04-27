/*
Virtual Table or Virtual Method Table
In object-oriented world, a polymorphism makes Derivate clas
can override the behavior of functions inherited from base.

testing on:
    - TDM GCC 5.1.0

ps: Assuming x64

Compile:
    $ g++ vtable-simple.cpp -std=c++11 -o vtable-simple

Run:
    $ vtable-simple

We can also ask compiler to emit the vtable and other structure, see the difference.
    (GCC)
    $ g++ -g -fdump-class-hierarchy -std=c++11 vtable-simple.cpp

    (MSVC)
    $ cl.exe /d1 reportAllClassLayout vtable-simple.cpp

*/
#include <iostream>
#include "util.hpp"


//======== Type Definitions =========================================
/*
Order of vtable is similar to the order of declared virtual function in code.
The order is also base on the relationship of inheritance. 
It means the base vtable will be placed before the vtable of Derivate (unless overridden)
*/

/*
Memory layout:
    - Base::vtable  (pointer to vtable of Base)
    - Base::id

The vtable layout:
    - Base::~Base()     (base object destructor)
    - Base::~Base()     (deleting destructor)
    - Base::B()
    - Base::C()
*/
class Base 
{
public:
    int id;

    Base(int id) : id(id)   { }
    virtual ~Base()         { }

    void A()                { std::cout << "-  Base[" << id << "]::A" << std::endl; }
    virtual void B()        { std::cout << "-  Base[" << id << "]::B" << std::endl; }
    virtual void C()        { std::cout << "-  Base[" << id << "]::C" << std::endl; }
};

/*
Memory layout:
    - Derivate::vtable (pointer to vtable of Derivate)
    - Base::id

The vtable layout:
    - Derivate::~Derivate()       (base object destructor)
    - Derivate::~Derivate()       (deleting destructor)
    - Base::B()
    - Derivate::C()

Try to uncomment B()
*/
class Derivate final : public Base 
{
public:
    Derivate(int id) : Base(id)  { }
    ~Derivate()                  { }

    // void B() override           { std::cout << "-  Derivate[" << id << "]::B" << std::endl; } 
    void C() override           { std::cout << "-  Derivate[" << id << "]::C" << std::endl; }
};

//======== Helper Functions =========================================

//======== Main Function ============================================
int main()
{
    Base base(1);
    Derivate derivate(2);
    Base *pbase = new Derivate(3);

    dump_instance("instance of base", base, 4);    
    dump_instance("instance of Derivate", derivate, 4);    
    dump_instance("instance of pointer to Derivate", *pbase, 4);

    // Try to call B() of each instance!

    return 0;
}