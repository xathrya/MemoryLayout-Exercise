/*
Common helper functions.
*/
#include <cstdio>
#include <cstdint>

// Dump memory on a region
// Needed by other functions
template<typename T>
void dump_memory(T &t, int n, int w)
{
    int counter = 16, padding;
    char *v = (char*)&t;

    while (n--) 
    {
        if (counter >= 16)
        {
            counter = 0;
            padding = w;
            printf("\n");
            while (padding--) printf(" ");
        }

        printf(" %02x", *v++ & 0xFF);
        counter ++;
    }
}

template<typename T>
void dump_vtable(T &t, int virtuals)
{
    // If a class have virtual functions, then
    // the first bytes of the instance is an address to vtable
    uintptr_t * vtable = (uintptr_t*) (*(uintptr_t*)&t);
    printf("\n\n");
    printf("vtable (%08x - %08x) %d entr%s\n", 
        vtable, vtable + virtuals - 1,
        virtuals, ((virtuals == 1) ? "y" : "ies"));

    for (int i = 0; i < virtuals; i++)
    {
        uintptr_t * fptr = ((uintptr_t**) vtable)[i];
        dump_memory(fptr, sizeof(uintptr_t*), 5);
    }
}

template<typename T>
void dump_instance(const char* header, T &t, int virtuals = 0)
{
    int n = sizeof(t);

    printf("%s\n", header);
    printf("[%p] -> instance (%d bytes)", &t, sizeof(t));
    
    dump_memory(t, n, 2);
    if (virtuals > 0)
        dump_vtable(t, virtuals);
    printf("\n\n");
}