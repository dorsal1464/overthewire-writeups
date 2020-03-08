#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>


#define e(); if(((unsigned int)ptr & 0xff000000)==0xca000000) { setresuid(geteuid(), geteuid(), geteuid()); execlp("/bin/sh", "sh", "-i", NULL); }
// this activates shell, we want to call e()
//we need ptr to be equal to 0xca<--anything-->

void print(unsigned char *buf, int len)
{
	//hexdump memory...
        int i;

        printf("[ ");
        for(i=0; i < len; i++) printf("%x ", buf[i]); 
        printf(" ]\n");
}

int main()
{
        unsigned char buf[512];
        unsigned char *ptr = buf + (sizeof(buf)/2);
        unsigned int x;

        while((x = getchar()) != EOF) {
                switch(x) {
			//print the buffer
                        case '\n': print(buf, sizeof(buf)); continue; break;
			// use backslash to decrease ptr
                        case '\\': ptr--; break;
			//if ptr isnt at end of buffer, it writes our char and ptr moves on...
                        default: e(); if(ptr > buf + sizeof(buf)) continue; ptr++[0] = x;break;
                }
        }
        printf("All done\n");
}
