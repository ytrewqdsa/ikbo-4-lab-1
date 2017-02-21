#include <stdio.h>
#include <stdlib.h>


struct pack {
	int chislo;
	char stroka[255];
	float dot;
};

int main(int argc, char *argv[])
{
	FILE *f1;
	long size;

	struct pack pp;
	if ((argc == 1) || (!(fopen(argv[1], "rb")))) {
		printf("Try to open: %s <filename>\n", argv[0]);
		return 1;
	}
	f1 = fopen(argv[1], "rb");
	while (fread(&pp, sizeof(struct pack), 1, f1)) {
		printf("%d,%s,%f\n", pp.chislo, pp.stroka, pp.dot);
	}
	fseek(f1, 0, SEEK_END);
	size = ftell(f1);
	printf("Size: %d%s", size, " bytes\n");
	fclose(f1);
	return 0;
}