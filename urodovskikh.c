#include <stdio.h>
#include <stdlib.h>
#define N 255

struct package {
	int x;
	char string[255];
	float y;
	};

int main(int argc, char *argv[]) {
	FILE *fp;
	if ((argc == 1) || (!(fopen(argv[1], "rb")))) {
		printf("Использование: %s <имя файла>\n", argv[0]);
		return 1;
	}
	fp = fopen(argv[1], "rb");
	struct package paquet;
	
	int i = 0;
	while(fread(&paquet, sizeof(struct package), 1, fp)) {
		printf("%d %s %f\n", paquet.x, paquet.string, paquet.y);
		i++;
	}
	printf("Размер файла: %d байт\n", i*sizeof(paquet));

	fclose(fp);
	return 0;
}
