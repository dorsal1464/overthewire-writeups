Dump of assembler code for function main:
```assembly
   0x080485e7 <+0>:     push   ebp
   0x080485e8 <+1>:     mov    ebp,esp
   0x080485ea <+3>:     sub    esp,0x14
   0x080485ed <+6>:     push   0x8048760
   0x080485f2 <+11>:    call   0x80483c0 <puts@plt>		#display -------------
   0x080485f7 <+16>:    add    esp,0x4
   0x080485fa <+19>:    push   0x8048772
   0x080485ff <+24>:    call   0x80483b0 <printf@plt>		#print username:
   0x08048604 <+29>:    add    esp,0x4
   0x08048607 <+32>:    lea    eax,[ebp-0x9]			#load address of memory
   0x0804860a <+35>:    push   eax
   0x0804860b <+36>:    push   0x804877e
   0x08048610 <+41>:    call   0x8048410 <__isoc99_scanf@plt>	#scanf 8 bytes to str
   0x08048615 <+46>:    add    esp,0x8
   0x08048618 <+49>:    push   0x8048782
   0x0804861d <+54>:    call   0x80483b0 <printf@plt>		#print key:
   0x08048622 <+59>:    add    esp,0x4
   0x08048625 <+62>:    lea    eax,[ebp-0x12]
   0x08048628 <+65>:    push   eax
   0x08048629 <+66>:    push   0x804877e
   0x0804862e <+71>:    call   0x8048410 <__isoc99_scanf@plt>	#scanf 8 bytes to str
   0x08048633 <+76>:    add    esp,0x8
   0x08048636 <+79>:    lea    eax,[ebp-0x9]
   0x08048639 <+82>:    push   eax
   0x0804863a <+83>:    call   0x80483f0 <strlen@plt>		#strlen of username
   0x0804863f <+88>:    add    esp,0x4
   0x08048642 <+91>:    cmp    eax,0x8				#if len != 8
   0x08048645 <+94>:    jne    0x8048658 <main+113>		#exit...
   0x08048647 <+96>:    lea    eax,[ebp-0x12]
   0x0804864a <+99>:    push   eax
   0x0804864b <+100>:   call   0x80483f0 <strlen@plt>		#strlen of key
   0x08048650 <+105>:   add    esp,0x4
   0x08048653 <+108>:   cmp    eax,0x8				#if len != 8
   0x08048656 <+111>:   je     0x804866c <main+133>		#exit...
   0x08048658 <+113>:   push   0x804878e
   0x0804865d <+118>:   call   0x80483c0 <puts@plt>		#length not good
   0x08048662 <+123>:   add    esp,0x4
   0x08048665 <+126>:   push   0xffffffff
   0x08048667 <+128>:   call   0x80483e0 <exit@plt>		#exit
   0x0804866c <+133>:   push   0x0
   0x0804866e <+135>:   push   0x0
   0x08048670 <+137>:   push   0x0
   0x08048672 <+139>:   push   0x0
   0x08048674 <+141>:   call   0x8048420 <ptrace@plt>		#ptrace = checks the procces trace, who called him ==> anti debugging...
   0x08048679 <+146>:   add    esp,0x10
   0x0804867c <+149>:   test   eax,eax
   0x0804867e <+151>:   je     0x8048694 <main+173>
   0x08048680 <+153>:   push   0x80487a0
   0x08048685 <+158>:   call   0x80483c0 <puts@plt>		#puts "nahnah..."
   0x0804868a <+163>:   add    esp,0x4
   0x0804868d <+166>:   mov    eax,0x0
   0x08048692 <+171>:   jmp    0x80486d6 <main+239>		#exit
   0x08048694 <+173>:   lea    eax,[ebp-0x12]			#continue
   0x08048697 <+176>:   push   eax
   0x08048698 <+177>:   lea    eax,[ebp-0x9]
   0x0804869b <+180>:   push   eax
   0x0804869c <+181>:   call   0x804853b <foo>			#call foo(username, passwd)
   0x080486a1 <+186>:   add    esp,0x8
   0x080486a4 <+189>:   test   eax,eax				#if rt of foo is false
   0x080486a6 <+191>:   je     0x80486c4 <main+221>		#exit
   0x080486a8 <+193>:   push   0x80487ab
   0x080486ad <+198>:   call   0x80483c0 <puts@plt>
   0x080486b2 <+203>:   add    esp,0x4
   0x080486b5 <+206>:   push   0x80487c3
   0x080486ba <+211>:   call   0x80483d0 <system@plt>
   0x080486bf <+216>:   add    esp,0x4
   0x080486c2 <+219>:   jmp    0x80486d1 <main+234>
   0x080486c4 <+221>:   push   0x80487cb
   0x080486c9 <+226>:   call   0x80483c0 <puts@plt>
   0x080486ce <+231>:   add    esp,0x4
   0x080486d1 <+234>:   mov    eax,0x0
   0x080486d6 <+239>:   leave  
   0x080486d7 <+240>:   ret
```

Dump of assembler code for function foo:
```assembly
   0x0804853b <+0>:     push   ebp
   0x0804853c <+1>:     mov    ebp,esp
   0x0804853e <+3>:     sub    esp,0x14
   0x08048541 <+6>:     mov    DWORD PTR [ebp-0x11],0x6e697270	#prin
   0x08048548 <+13>:    mov    DWORD PTR [ebp-0xd],0x6c6f6c74	#tlol
   0x0804854f <+20>:    mov    BYTE PTR [ebp-0x9],0x0		#eos = 0
   0x08048553 <+24>:    mov    DWORD PTR [ebp-0x4],0x0
   0x0804855a <+31>:    jmp    0x804859c <foo+97>		#always jump
   0x0804855c <+33>:    mov    edx,DWORD PTR [ebp-0x4]		#probably will do 8 times
   0x0804855f <+36>:    mov    eax,DWORD PTR [ebp+0x8]		#username, edx = counter, starts with 0 --> lets symbol with i
   0x08048562 <+39>:    add    eax,edx
   0x08048564 <+41>:    movzx  eax,BYTE PTR [eax]		#eax = username[i]
   0x08048567 <+44>:    movsx  eax,al
   0x0804856a <+47>:    sub    eax,0x41				#eax -= 'A'
   0x0804856d <+50>:    mov    DWORD PTR [ebp-0x8],eax		#var = usr[i] - 'A'
   0x08048570 <+53>:    lea    edx,[ebp-0x11]			#"printlol"
   0x08048573 <+56>:    mov    eax,DWORD PTR [ebp-0x4]		#i
   0x08048576 <+59>:    add    eax,edx				
   0x08048578 <+61>:    movzx  eax,BYTE PTR [eax]		#eax = printlol[i]	
   0x0804857b <+64>:    mov    ecx,eax				#ecx = eax
   0x0804857d <+66>:    mov    eax,DWORD PTR [ebp-0x4]		#i
   0x08048580 <+69>:    lea    edx,[eax+eax*1]			#i
   0x08048583 <+72>:    mov    eax,DWORD PTR [ebp-0x8]		#username
   0x08048586 <+75>:    add    eax,edx				#i+=1
   0x08048588 <+77>:    sub    ecx,eax				
   0x0804858a <+79>:    mov    eax,ecx				
   0x0804858c <+81>:    mov    ecx,eax
   0x0804858e <+83>:    lea    edx,[ebp-0x11]			#printlol
   0x08048591 <+86>:    mov    eax,DWORD PTR [ebp-0x4]		#i
   0x08048594 <+89>:    add    eax,edx				#printlol[i]
   0x08048596 <+91>:    mov    BYTE PTR [eax],cl		#printlol[i] = printlol[i] + 'A' - username[i]
   0x08048598 <+93>:    add    DWORD PTR [ebp-0x4],0x1		
   0x0804859c <+97>:    push   DWORD PTR [ebp+0x8]		#continue:
   0x0804859f <+100>:   call   0x80483f0 <strlen@plt>		#strlen(username)
   0x080485a4 <+105>:   add    esp,0x4
   0x080485a7 <+108>:   mov    edx,eax				#edx = len(username)
   0x080485a9 <+110>:   mov    eax,DWORD PTR [ebp-0x4]		#eax = i
   0x080485ac <+113>:   cmp    edx,eax				#if edx > eax (unsigned)
   0x080485ae <+115>:   ja     0x804855c <foo+33>		#jmp to +33
   0x080485b0 <+117>:   jmp    0x80485d3 <foo+152>		#after 8 iter. we jmp
   0x080485b2 <+119>:   lea    edx,[ebp-0x11]			#jne here
   0x080485b5 <+122>:   mov    eax,DWORD PTR [ebp-0x4]		#i = 7
   0x080485b8 <+125>:   add    eax,edx				
   0x080485ba <+127>:   movzx  edx,BYTE PTR [eax]		#edx = printlol[i]
   0x080485bd <+130>:   mov    ecx,DWORD PTR [ebp-0x4]		#ecx = i
   0x080485c0 <+133>:   mov    eax,DWORD PTR [ebp+0xc]		#passwrd
   0x080485c3 <+136>:   add    eax,ecx				#passwrd[i]
   0x080485c5 <+138>:   movzx  eax,BYTE PTR [eax]		#eax = passwrd[i]
   0x080485c8 <+141>:   cmp    dl,al				
   0x080485ca <+143>:   je     0x80485d3 <foo+152>		#passwrd[i] == printlol[i]
   0x080485cc <+145>:   mov    eax,0x0
   0x080485d1 <+150>:   jmp    0x80485e5 <foo+170>
   0x080485d3 <+152>:   mov    eax,DWORD PTR [ebp-0x4]		#here, eax = i = 8
   0x080485d6 <+155>:   lea    edx,[eax-0x1]			# = i-1 = 7
   0x080485d9 <+158>:   mov    DWORD PTR [ebp-0x4],edx		# i -= 1
   0x080485dc <+161>:   test   eax,eax
   0x080485de <+163>:   jne    0x80485b2 <foo+119>		#if eax != 0
   0x080485e0 <+165>:   mov    eax,0x1
   0x080485e5 <+170>:   leave  
   0x080485e6 <+171>:   ret
```

ptrace(PTRACE_TRACEME, 0, 0):
looking at the documentation:
PTRACE_TRACEME
              Indicate that this process is to be traced by its parent.  A
              process probably shouldn't make this request if its parent
              isn't expecting to trace it.  (pid, addr, and data are
              ignored.)
              
so using this command, the program asks for its parent (debugging program) to trace it,
of course gdb doesnt expect that, so ptrace returns with error, then the program knows that
its being run by a debugging program... and exits!
so, we see that the program has anti-debugging feature: if it sees that its called by
another program, it stops itself, hence anti-debugging.
we find a solution online: https://gist.github.com/poxyran/71a993d292eee10e95b4ff87066ea8f2

```gdb
catch syscall ptrace
commands 1
set ($eax) = 0
continue
end
```

OK, it seems like the program encodes our username with some sort of increamental shifted alphabet code, which looks like this: cipher[i] = 'A' + key[i] - username[i] - 2i
where key = "printlol"

(EXTRA) notice that this code is symetric:
plaintext[i] = 'A' + key[i] - cipher[i] - 2i
cipher[i] = 'A' + key[i] - plaintext[i] - 2i

now for some technical details:
start code (=printlol):
(gdb) x/1s $ebp-0x11
0xffffd6b3:     "printlol"

iterator (=i):
$ebp-0x4 = iterator, namely i

inputs:
[ebp+0x8] --> username
[ebp+0xc] --> passwrd


OPTION 1: (calculate)
so I chose username = "AAAAAAAA", because it cancels the + 'A', so we are left with:
decoded[i] = printlol[i] - 2i --> 
calculations:

70 72 69 6e 74 6c 6f 6c
0  2  4  6  8  10 12 14
--------(minus)--------
70 70 65 68 6c 62 63 5e
we get: "ppehlbc^"

OPTION 2: (debug)
you can see that using gdb, if you break at foo+141 and use username "AAAAAAAA": "AAAAAAAA" becomes --> "ppehlbc^"
then the program compares the ciphered username with the password byte by byte...
so set "ppehlbc^" as the password!

it worked!

we get:
```sh
$ cat /etc/maze_pass/maze6
epheghuoli
```

that was a tough one...

