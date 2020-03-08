import socket
# TCP socket
s = socket.socket()
s.connect(('176.9.9.172', 5842))

# int list to store the ints
ints = []
sum = 0

for i in range(0,4):
	ints.append(s.recv(4))
	# converting the recieved bytes to unsigned ints, according to little ind.
	sum += int.from_bytes(ints[i], byteorder='little', signed=False)
print(sum)
# sending the sum, as bytes from int
s.send(sum.to_bytes(8, 'little'))
msg = s.recv(128)
# recv and display
print(msg)
