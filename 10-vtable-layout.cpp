/*
Virtual Table or Virtual Method Table
In OO (object-oriented) world, a polymorphism makes Derivate class
can override the behavior of functions inherited from Base.
C++ use virtual table to implement this.

How is the vtable layout in memory?

verified on:
    - TDM GCC 5.1.0 (assuming x64)

Compile:
    $ g++ vtable-layout.cpp -std=c++11 -o vtable-layout

Run:
    $ vtable-layout

We can also ask compiler to emit the vtable and other structure, see the difference.
    (GCC)
    $ g++ -g -fdump-class-hierarchy -std=c++11 vtable-layout.cpp

    (MSVC)
    $ cl.exe /d1 reportAllClassLayout vtable-layout.cpp

*/
#include <iostream>
#include "util.hpp"

/*
Observe the address of each of them.
Questions:
    - Compare the vtable layout of ClassA and ClassB, what's the difference?
    - Why not all functions are in vtable?
    - Is there any two or more entry in vtable that has same address? 
        - Why?
    - Do the two classes share the same address in their vtable entry?
        - Why?

Conclusion:
    The order of vtable entry is similar to the order of declared virtual function in code.
*/

//======== Type Definitions =========================================
/*
Memory layout:
    - ClassA::vtable  (pointer to vtable of ClassA)
    - ClassA::id

The vtable layout:
    - ClassA::~ClassA()     (base object destructor)
    - ClassA::~ClassA()     (deleting destructor)
    - ClassA::B()
*/
class ClassA 
{
    int id;
public:
    ClassA(int id) : id(id) { }
    virtual ~ClassA()       { }

    void A()                { std::cout << "-  ClassA[" << id << "]::A" << std::endl; }
    virtual void B()        { std::cout << "-  ClassA[" << id << "]::B" << std::endl; }
};

/*
Memory layout:
    - ClassB::vtable (pointer to vtable of ClassB)
    - ClassB::id

The vtable layout:
    - ClassB::A()
    - ClassB::B()
*/
class ClassB
{
    int id;
public:
    ClassB(int id) : id(id) { }
    ~ClassB()       { }

    virtual void A()        { std::cout << "-  ClassB[" << id << "]::A" << std::endl; } 
    virtual void B()        { std::cout << "-  ClassB[" << id << "]::B" << std::endl; }
};

//======== Helper Functions =========================================

//======== Main Function ============================================
int main()
{
    ClassA InstanceA(1);
    ClassB InstanceB(2);

    dump_instance("instance of ClassA", InstanceA, 3);    
    dump_instance("instance of ClassB", InstanceB, 2);

    return 0;
}