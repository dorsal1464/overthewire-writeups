this time around, we cant use any disassembly programs, because the code has no symbol table.
perhaps we can load one menually...

upon run, we get: ./level4 ev0lcmds!

workaround:
run info file --> get entry point 0x8048060
run x/64i 0x8048060:
```assembly
   0x8048060 <_start>:		pop    eax			#has num. of env
   0x8048061 <_start+1>:	dec    eax			#decrease it...
   0x8048062 <_start+2>:	jne    0x8048096 <fine>		#jump if num. of env != 1... to fine
   0x8048064 <_start+4>:	call   0x804807d <_start+29>
   0x8048069 <_start+9>:	cs das 
   0x804806b <_start+11>:	ins    BYTE PTR es:[edi],dx
   0x804806c <_start+12>:	gs jbe 0x80480d4 <d1+9>
   0x804806f <_start+15>:	ins    BYTE PTR es:[edi],dx
   0x8048070 <_start+16>:	xor    al,0x20
   0x8048072 <_start+18>:	gs jbe 0x80480a5 <fine+15>
   0x8048075 <_start+21>:	ins    BYTE PTR es:[edi],dx
   0x8048076 <_start+22>:	arpl   WORD PTR [ebp+0x64],bp
   0x8048079 <_start+25>:	jae    0x804809c <fine+6>
   0x804807b <_start+27>:	or     al,BYTE PTR [eax]
   0x804807d <_start+29>:	mov    eax,0x4
   0x8048082 <_start+34>:	mov    ebx,0x1
   0x8048087 <_start+39>:	pop    ecx
   0x8048088 <_start+40>:	mov    edx,0x14
   0x804808d <_start+45>:	int    0x80
   0x804808f <_start+47>:	mov    eax,0x1
   0x8048094 <_start+52>:	int    0x80
```
fine label:
```assembly
   0x8048096 <fine>:	pop    eax				#eax = env[0]
   0x8048097 <fine+1>:	mov    eax,0x7d				#eax = 125
   0x804809c <fine+6>:	mov    ebx,0x8048060			#addr of _start
   0x80480a1 <fine+11>:	and    ebx,0xfffff000			#some addr
   0x80480a7 <fine+17>:	mov    ecx,0x97
   0x80480ac <fine+22>:	mov    edx,0x7
   0x80480b1 <fine+27>:	int    0x80				#interrupt 0x80
   0x80480b3 <fine+29>:	lea    esi,ds:0x80480cb			#addr of d1+4 label
   0x80480b9 <fine+35>:	mov    edi,esi				#same
   0x80480bb <fine+37>:	mov    ecx,0x2c				
   0x80480c0 <fine+42>:	mov    edx,0x12345678
```
l1 label:
```assembly
   0x80480c5 <l1>:	lods   eax,DWORD PTR ds:[esi]		#load from memory *d1 & esi+=4
   0x80480c6 <l1+1>:	xor    eax,edx				#xor -> decrypt with 12345678
   0x80480c8 <l1+3>:	stos   DWORD PTR es:[edi],eax		#writes to *d1 eax & edi+=4
   0x80480c9 <l1+4>:	loop   0x80480c5 <l1>			#should loop 44 times, ecx = 44
```
d1 label:
```assembly
   0x80480cb <d1>:	and    bh,dl				#all of this is encrypted shit
   0x80480cd <d1+2>:	or     al,0xcc				
   0x80480cf <d1+4>:	mov    eax,0x61672761			
   0x80480d4 <d1+9>:	addr16 hlt 
   0x80480d6 <d1+11>:	inc    edx
   0x80480d7 <d1+12>:	adc    BYTE PTR [ecx+0x1b],bh
   0x80480da <d1+15>:	popa   
   0x80480db <d1+16>:	adc    BYTE PTR [esi],bh
   0x80480dd <d1+18>:	sbb    esi,DWORD PTR [eax+0x11]
   0x80480e0 <d1+21>:	cmp    BYTE PTR [ebp-0x42fad70f],bh
   0x80480e6 <d1+27>:	repz dec ecx
   0x80480e8 <d1+29>:	test   BYTE PTR [ecx+ebx*1+0x138cd6b5],al
   0x80480ef <d1+36>:	js     0x8048147
   0x80480f1 <d1+38>:	xor    al,0x23
   0x80480f3 <d1+40>:	.byte 0xa3
   0x80480f4 <d1+41>:	.byte 0x15
   0x80480f5 <d1+42>:	stc    
   0x80480f6 <d1+43>:	xchg   edx,eax
```


l1 decrypts all d1 label instructions! then d1 is activated...

l1 decrypted:
```assembly
   0x80480cb <d1>:	pop    eax				#pointer to env[0]
   0x80480cc <d1+1>:	cmp    DWORD PTR [eax],0x1337c0de	#cmp env[0] to this
   0x80480d2 <d1+7>:	jne    0x80480ed <d1+34>		#if not equal, jump to what i guess is exit
   0x80480d4 <d1+9>:	xor    eax,eax				#else, call /bin/sh...
   0x80480d6 <d1+11>:	push   eax
   0x80480d7 <d1+12>:	push   0x68732f2f
   0x80480dc <d1+17>:	push   0x6e69622f
   0x80480e1 <d1+22>:	mov    ebx,esp
   0x80480e3 <d1+24>:	push   eax
   0x80480e4 <d1+25>:	push   ebx
   0x80480e5 <d1+26>:	mov    ecx,esp
   0x80480e7 <d1+28>:	xor    edx,edx
   0x80480e9 <d1+30>:	mov    al,0xb
   0x80480eb <d1+32>:	int    0x80
   0x80480ed <d1+34>:	mov    eax,0x1
   0x80480f2 <d1+39>:	xor    ebx,ebx
   0x80480f4 <d1+41>:	inc    ebx
   0x80480f5 <d1+42>:	int    0x80
```

looking at this line tells it all: cmp    DWORD PTR [eax],0x1337c0de
so we change our variable...
r $(python -c 'print "\x13\x37\xc0\xde"')

 indeed we get: (shell)
$ exit

recall that we are in little indian:
./maze3 $(python -c 'print "\xde\xc0\x37\x13"')
$ cat /etc/maze_pass/maze4
deekaihiek

we get: 
deekaihiek



