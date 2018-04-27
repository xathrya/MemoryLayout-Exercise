/*
Virtual Table or Virtual Method Table
In object-oriented world, a polymorphism makes derived clas
can override the behavior of functions inherited from base.

testing on:
    - TDM GCC 5.1.0

ps: Assuming x64

Compile:
    $ g++ vtable.cpp -std=c++11 -o vtable

Run:
    $ vtable
*/
#include <iostream>
#include "util.hpp"


//======== Type Definitions =========================================
/*
Order of vtable is similar to the order of declared virtual function in code.
The order is also base on the relationship of inheritance. 
It means the base vtable will be placed before the vtable of derived (unless overridden)
*/

/*
Memory layout:
    - Base::vtable  (pointer to vtable of Base)
    - Base::id

The vtable layout:
    - Base::~Base()
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
    - Derived::vtable (pointer to vtable of Derived)
    - Base::id

The vtable layout:
    - Derived::~Derived()
    - Base::B()
    - Derived::C()

Try to uncomment B()
*/
class Derived final : public Base 
{
public:
    Derived(int id) : Base(id)  { }
    ~Derived()                  { }

    // void B() override           { std::cout << "-  Derived[" << id << "]::B" << std::endl; } 
    void C() override           { std::cout << "-  Derived[" << id << "]::C" << std::endl; }
};

//======== Helper Functions =========================================

//======== Main Function ============================================
int main()
{
    Base base(1);
    Derived derived(2);
    Base *pbase = new Derived(3);

    dump_instance("instance of base", base, 4);    
    dump_instance("instance of derived", derived, 4);    
    dump_instance("instance of pointer to derived", *pbase, 4);

    // Try to call B() of each instance!

    return 0;
}