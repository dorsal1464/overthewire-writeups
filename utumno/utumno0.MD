we try to open using gdb, we have no permission to read...  
opening the exc, we get: Read me! :P  
so we need to read the file/string...  

we use shared library function hooking...  

using hook.c (in the directory)  

compile: gcc -m32 -fPIC -c hook.c  
link: ld -shared -m elf_i386 -o hook.so hook.o -ldl  
load library: LD_PRELOAD="./hook.so" /utumno/utumno0  

we had three stages:
1. read from the stack  
2. find relevant addresses  
3. snoop addresses, for me: 0x0x8048402 to 0x0x80484ff  
4. profit!  

password:  
aathaeyiew  
