we are greeted with the message: You have mail
and we see there isnt a vortex9 executable...

so we need to search aroud and find a file...(kinda stupid if you ask me)
```bash
vortex9@vortex:/$ ls
README.txt  d    home   lib64   mnt   root  srv  usr
bin         dev  lib    libx32  opt   run   sys  var
boot        etc  lib32  media   proc  sbin  tmp  vortex
vortex9@vortex:/$ cd var
vortex9@vortex:/var$ ls
backups  cache  chroot  lib  local  lock  log  mail  opt  run  spool  tmp
vortex9@vortex:/var$ cd mail
vortex9@vortex:/var/mail$ ls
vortex9
vortex9@vortex:/var/mail$ cd vortex9
-bash: cd: vortex9: Not a directory
vortex9@vortex:/var/mail$ cat vortex9
5WT0}swdc
```
