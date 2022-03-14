#include <stdio.h>

char * utoa_s(int);
int atou_s(char* string);

int main(int argc, char **argv) {
	
	int toConvert = atou_s(argv[1]);
	char * stringInt = utoa_s(toConvert);
	printf("%s\n", stringInt);
	return 0;
}

