
cmpl 0x0, 0x8(%ebp) --> checks if argc == 0, argc is the number of arguments  
usually its 1 --> filename is argv[0]  

so we need a c program to run with argc = 0:  

using: execve("/utumno/utumno2", {0x0}, <--envp-->);  

so we write a program: execve.c...  
at first, we try to see how many arguments we need to write with strcpy to $esp...  
try from 1 envp {"AAAA"} we try increasing the "", e.g. {"" * X, "AAAA"}  
we try: char* envp = {"","","","","","","","", "aaaa", "AAAA"};  
it writes: (using ltrace) strcpy(0xffffde6c(==$ebp+12), "AAAA")  

so we try to add A's until we get a seg. fault - for me it was 20  
from now on, it's stack overflow attack...  

using gdb, we read from memory adresses until we find aaaa / AAAA...  
then we replace aaaa with shellcode, and pad it with nops (0x90)  

again, reading from memory until we find the shellcode...  
write 0xffffdfb0 instead of AAAA...  

run it: we got shell  
zuudafiine


