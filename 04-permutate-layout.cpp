/*
Find out the memory layout of a class
Do the order affect the class?

Compile:
    (GCC)  
    $ g++ permutate-layout.cpp -std=c++11 -o permutate-layout
*/
#include "util.hpp"
#include <cstddef>

/*
Observe the address of each of them.    

Conclusion:
    Placing variables in certain orders will affect the size. Each members variable of struct or class
    should be always aligned therefore compiler will give a padding if neessary 
*/

//======== Type Definitions =========================================
// Size: 16 = 4 + 10 + 2
struct Example1
{
    int32_t x;
    int8_t  y[10];
    int16_t z;
};

// Size: 16 = 4 + 2 + 10
struct Example2
{
    int32_t x;
    int16_t y;
    int8_t  z[10];
};

// Size: 20 = 10 (+2 padding) + 4 + 2, the first 10 is forced to rount to multiple of 4
struct Example3
{
    int8_t  x[10];
    int32_t y;
    int16_t z;
};

// Size: 16 = 1 + 8 then round to multiple of 8
struct Example4
{
    int8_t x;
    int64_t y;
};

// Size: 8 = 4 + 1 then round to multiple of 4
struct Example5
{
    int32_t x;
    int8_t  y;
};

//======== Helper Functions =========================================
template<typename T>
void dump_variables(T &t);

//======== Main Function ============================================
int main()
{
    Example1 ex1;
    Example2 ex2;
    Example3 ex3;

    // A trick to print offset:
    // (int) offsetof(ClassName,field)

    dump_instance("Instance of Example1", ex1);
    dump_variables(ex1);

    printf("\n");

    dump_instance("Instance of Example2", ex2);
    dump_variables(ex2);

    printf("\n");
    
    dump_instance("Instance of Example3", ex3);
    dump_variables(ex3);

    printf("\n");

    printf("Sizeof(Example4) = %d\n", sizeof(Example4));
    printf("Sizeof(Example5) = %d\n", sizeof(Example5));

    return 0;
}

//======== Implementations ==========================================
template<typename T>
void dump_variables(T &t)
{
    printf("Address of x: [%p] +%d\n", &t.x, (size_t)offsetof(T,x));
    printf("Address of y: [%p] +%d\n", &t.y, (size_t)offsetof(T,y));
    printf("Address of z: [%p] +%d\n", &t.z, (size_t)offsetof(T,z));
}