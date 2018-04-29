/*
Find out the memory layout of a class
Each C++ object need to hold its instance data. But if there is none, what happen?

Compile:
    (GCC)  
    $ g++ empty.cpp -std=c++11 -o empty
    
    (LLVM) 
    $ clang++ empty.cpp -o empty

    (MSVC)
    $ cl empty.cpp

Run:
    $ empty
*/
#include "util.hpp"

//======== Type Definitions =========================================
class Example { };

//======== Helper Functions =========================================

//======== Main Function ============================================
int main()
{
    Example kelas;
    dump_instance("Empty class", kelas);
    return 0;
}

//======== Implementations ==========================================