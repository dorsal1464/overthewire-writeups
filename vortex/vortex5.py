import hashlib
base = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789"
passwd = '155fb95d04287b757c996d77b5ea51f7'
m = hashlib.md5()
name = "fillme"

# generator
fp = open(name, 'w')
for a in base:
	for b in base:
		for c in base:
			for d in base:
				for e in base:
					fp.write(a+b+c+d+e+'\n')
fp.close()

# checker

fp = open(name, 'r')

for pwd in fp.readlines():
	m.update(pwd.encode('utf-8'))
	if m.hexdigest() == passwd:
		print(pwd)
		break
fp.close()

	



					
