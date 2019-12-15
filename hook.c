#define _GNU_SOURCE
#include <stdio.h>
#include <stdint.h>
#include <dlfcn.h>

int puts(const char* s) {
    int i;
    char *pt;

    // Variable to store the original puts function. just incase we need it.
    static void* (*my_puts)(const char*s) = NULL;

    if (!my_puts){
        // Store the original puts function.
        my_puts = dlsym(RTLD_NEXT, "puts");
    }
    for (int i = 0x8048402;i<0x80484ff;i++)
    {
        pt = (char*)i;
        printf("%c", *pt);
    }
    // Display our hooked
    printf("Hooked-%s", s);

    return 0;
 
}

