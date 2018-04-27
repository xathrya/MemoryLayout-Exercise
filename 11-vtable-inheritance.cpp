/*
Virtual Table or Virtual Method Table
In OO (object-oriented) world, a polymorphism makes Derivate class
can override the behavior of functions inherited from Base.
C++ use virtual table to implement this.

How is the vtable layout in memory when inheritance happen?

verified on:
    - TDM GCC 5.1.0 (assuming x64)

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

/*
Observe the address of each of them.
Questions:
    - Is there any two or more entry in vtable that has same address? 
        - Why?
    - Do the classes share the same address in their vtable entry?
        - Why?
    - What if ClassC::A() is not defined as virtual?

Conclusion:
    When a class derived from another class, it will also inherit the vtable.
*/

//======== Type Definitions =========================================
/*
Memory layout:
    - ClassA::vtable  (pointer to vtable of ClassA)
    - ClassA::id

The vtable layout:
    - ClassA::~ClassA()     (base object destructor)
    - ClassA::~ClassA()     (deleting destructor)
    - ClassA::A()
*/
class ClassA 
{
protected:
    int id;
public:
    ClassA(int id) : id(id) { }
    virtual ~ClassA()       { }

    virtual void A()        { std::cout << "-  ClassA[" << id << "]::A" << std::endl; }
};

/*
Memory layout:
    - ClassB::vtable (pointer to vtable of ClassB)
    - ClassB::id

The vtable layout:
    - ClassB::B()
*/
class ClassB
{
protected:
    int id;
public:
    ClassB(int id) : id(id) { }
    ~ClassB()               { }

    virtual void B()        { std::cout << "-  ClassB[" << id << "]::B" << std::endl; }
};

/*
Memory layout:
    - ClassC::vtable  (pointer to vtable of ClassC)
    - ClassA::id

The vtable layout:
    - ClassC::~ClassC()     (base object destructor)
    - ClassC::~ClassC()     (deleting destructor)
    - ClassC::A()
*/
class ClassC : public ClassA
{
public:
    ClassC(int id) : ClassA(id) { }
    ~ClassC()                   { }
};

/*
Memory layout:
    - ClassD::vtable  (pointer to vtable of ClassD)
    - ClassA::id
    - ClassB::id

The vtable layout:
    - ClassD::~ClassD()     (base object destructor)
    - ClassD::~ClassD()     (deleting destructor)
    - ClassA::A()
    - offset to the top     (-16)
    - typeinfo
    - ClassB::B()
*/
class ClassD : public ClassA, public ClassB
{
public:
    ClassD(int id) : ClassA(id), ClassB(id) { }
    ~ClassD()           { }
};

//======== Helper Functions =========================================

//======== Main Function ============================================
int main()
{
    ClassA InstanceA(1);
    ClassB InstanceB(2);
    ClassC InstanceC(3);
    ClassD InstanceD(3);

    dump_instance("instance of ClassA", InstanceA, 3);    
    dump_instance("instance of ClassB", InstanceB, 1);   
    dump_instance("instance of ClassC", InstanceC, 3);  
    dump_instance("instance of ClassD", InstanceD, 6);

    InstanceC.A();
    InstanceD.B();

    return 0;
}