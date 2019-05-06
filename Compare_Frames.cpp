#include <stdio.h>
#include <malloc.h>
#include <string.h>
#pragma warning(disable:4996)


char filename[256] = "";
int width = 3840;
int height = 2160;



int compare(short *dest, short *source, int size) {
	for (int i = 0; i < size; i++) {
		if (dest[i] != source[i])
			return 0;
	}
	return 1;
}

int main(int argc, char **argv) {

	FILE *fp;
	int iter = 0;
	int size = width * height;
	size += size / 2;
	short *img = (short*)malloc(sizeof(short)*(size));
	short *temp = (short*)malloc(sizeof(short)*(size));
	if (argc != 2) {
		printf("Enter Filename!\n");
		return 0;
	}
	strcpy(filename ,argv[1]);
	fp = fopen(filename, "rb");
	if (fp == NULL)
		printf("Can not open file!\n");
	while (feof(fp) == 0) {
		fread(img, sizeof(short), size, fp);
		
		if (iter == 0) {
			iter++;
			memcpy(temp, img, size * sizeof(short));
			continue;
		}
		if (compare(img, temp, size))
			printf("POC %d, POC %d is same\n", iter - 1, iter);
		else
			printf("POC %d, POC %d is not same\n", iter - 1, iter);
		memcpy(temp, img, size * sizeof(short));
		iter++;
	}

	return 0;

}