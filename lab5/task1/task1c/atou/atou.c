#include <stdio.h>


int atou_s(char* number);

int main(int argc, char **argv) {
	
	int toConvert = atou_s(argv[1]);
	printf("%d\n", toConvert);
	return 0;
}

