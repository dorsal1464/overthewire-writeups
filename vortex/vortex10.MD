we have an array of pseudo-random numbers, and we need to find the seed...  
it's pretty easy to extract the seed using gdb, but we need a method that doesnt envolve a debugger for the real solution...  
let's look at how the seed is generated:
```assembly
0x080486ad <+0>:     push   ebp
   0x080486ae <+1>:     mov    ebp,esp
   0x080486b0 <+3>:     push   esi
   0x080486b1 <+4>:     push   ebx
   0x080486b2 <+5>:     and    esp,0xfffffff0
   0x080486b5 <+8>:     add    esp,0xffffff80
   0x080486b8 <+11>:    lea    eax,[esp+0x20]
   0x080486bc <+15>:    mov    DWORD PTR [esp],eax
   0x080486bf <+18>:    call   0x80484e0 <times@plt>
   0x080486c4 <+23>:    mov    DWORD PTR [esp+0x18],eax
   0x080486c8 <+27>:    mov    edx,DWORD PTR [esp+0x20]
   0x080486cc <+31>:    mov    eax,DWORD PTR [esp+0x24]
   0x080486d0 <+35>:    add    edx,eax
   0x080486d2 <+37>:    mov    eax,DWORD PTR [esp+0x28]
   0x080486d6 <+41>:    add    edx,eax
   0x080486d8 <+43>:    mov    eax,DWORD PTR [esp+0x2c]
   0x080486dc <+47>:    add    eax,edx
   0x080486de <+49>:    add    DWORD PTR [esp+0x18],eax
   0x080486e2 <+53>:    call   0x8048540 <clock@plt>
   0x080486e7 <+58>:    add    DWORD PTR [esp+0x18],eax
   0x080486eb <+62>:    mov    DWORD PTR [esp],0x0
   0x080486f2 <+69>:    call   0x80484f0 <time@plt>
   0x080486f7 <+74>:    add    DWORD PTR [esp+0x18],eax
   0x080486fb <+78>:    mov    eax,DWORD PTR [esp+0x18]
   0x080486ff <+82>:    cdq    
   0x08048700 <+83>:    shr    edx,0x18
   0x08048703 <+86>:    add    eax,edx
   0x08048705 <+88>:    movzx  eax,al
   0x08048708 <+91>:    sub    eax,edx
   0x0804870a <+93>:    mov    edx,0x80
   0x0804870f <+98>:    sub    edx,eax
   0x08048711 <+100>:   mov    eax,edx
   0x08048713 <+102>:   mov    DWORD PTR [esp+0x18],eax
   0x08048717 <+106>:   mov    DWORD PTR [esp],0x0
   0x0804871e <+113>:   call   0x80484f0 <time@plt>
   0x08048723 <+118>:   mov    edx,DWORD PTR [esp+0x18]
   0x08048727 <+122>:   add    eax,edx
   0x08048729 <+124>:   mov    DWORD PTR [esp+0x1c],eax
   0x0804872d <+128>:   mov    eax,DWORD PTR [esp+0x1c]
   0x08048731 <+132>:   mov    DWORD PTR [esp],eax
   0x08048734 <+135>:   call   0x8048560 <srand@plt>
```
and when simplified:
```c
v0 = times(&tms)
v0 += (tms.utime + tms.stime + tms.cutime + tms.cstime)
v0 += clock();
v1 = time(NULL);
v0 += v1;
v0 = 0x80 - (v0 - (v0>>8)<<8);
srand(v0 + v1)
```
v1 = time(NULL) --> so if we check fast enough, it will be the same value as in the program...  
v0 is impossible to calculate, but lucky enough its in the range of -128 to 128 (0 <= (v0 - (v0>>8)<<8) <= 256 ==> -128, 128), 
so we can bruteforce v0...  
let's write a c program (test):
```c
#include<stdio.h>                                                         
#include<stdlib.h>                                                        
#include<time.h>                                                          
#include<unistd.h>                                                        
int main() {                                                              
    char* args = "/vortex/vortex10";                                      
    unsigned int v1 = time(NULL);  
    //printing time seed                                       
    printf("%08x\n",v1);                                                  
    execlp("/vortex/vortex10",args,NULL);                                                                                     
    return 0;                                                                 
}
```

the bruteforce c code (must run within 30 seconds of the command "python help.py | ./test"):
```c
//i used this to bruteforce the seed...                             
//must run in 30 seconds after vortex10 has begun...                
#include <string.h>                                                 
#include <stdio.h>                                                  
#include <stdlib.h>                                                 
#include <time.h>                                                   
                                                                    
int main(int argc, char **argv) {                                   
    int seed, match, i,j;     
    //insert the seed from test and a number from the random list                                      
    scanf("%x %x" ,&seed,&match);    
    //notice that i increased the range to be sure, this is not a neccesaty...                               
    for(i=-1024; i< 1024; i++) {                                    
        srand(seed+i);     
        //again, just to be sure, i increased the range, an exact range will be: j<i+1
        //we do this because the program activates rand() i (i=v0) times, and then prints 20 more rand()                                         
        for(j=0; j<512; j++) {                                      
            int r = rand();                                         
            if(r == match) {                                        
                int xx = seed+i;                                    
                printf("%08d\n", xx);                               
            }                                                       
        }                                                           
    }                                                               
} 
```

and a python script to help me write an int to the buffer (help.py):
```python
i = input()                                                               
i=int(i)                                                                  
s = chr(i&0xff) + chr((i>>8)&0xff) + chr((i>>16)&0xff) + chr((i>>24)&0xff$
print s                                                                   
print "whoami"                                                            
print "cat /etc/vortex_pass/vortex11"
print "exit"
```

put it all together we get:  
(I had to pipe the python script to convert the int to actual bytes ==> in little indian)
```bash
vortex10@vortex:/tmp/vt10$ python help.py | ./test
5e665ce0
[ 7af7aa05, 23decda6, 41e19bce, 6ef800f2, 6c3e68a4, 62bb7d9c, 62e02f9a, 015df289, 4f416f10, 633d6308, 4bafb42f, 2f91a427, 05420b8e, 2ede70ce, 19a90cd8, 7794954c, 5967ffc4, 1b309199, 4c3c5e9d, 71deebb3,]
1583767095
$ $ $ vortex11
$ %8sLEszy9
$ exit
```
we get:  
%8sLEszy9

