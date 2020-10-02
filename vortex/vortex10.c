//i used this to bruteforce the seed...
//must run in 30 seconds after vortex10 has begun...
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char **argv) {
	unsigned int t = *(argv[1]);
	unsigned int match = *(argv[2]);
	for (int i = -128; i < 128; ++i)
	{
		srand(i+t);
		if (rand() == match)
			printf("%x\n", i+t);
	}
	printf("no match\n");
	return 0;
}