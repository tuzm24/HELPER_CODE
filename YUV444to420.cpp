#include <stdio.h>
#include <malloc.h>
#include <string.h>
#pragma warning(disable:4996)


char filename[256] = "";
int width = 3840;
int height = 2160;
int bitdepth = 10;
char addmessege[256] = "_3840x2160_30fps_10bit_420.yuv";

//YUV 444 to 420

void downSampling(short *dest, short *source, int cwidth, int cheight) {
	for(int i=0; i<cheight; i++)
		for (int j = 0; j < cwidth; j++) 
			dest[i*cwidth + j] = (source[(i << 1)*width + (j << 1)] + source[((i << 1) + 1)*width + (j << 1)] + 1) >> 1;
	return;
}


int main(int argc, char **argv) {
	if (argc != 2) {
		printf("Enter Filename!\n");
		return 0;
	}
	FILE *fp, *new_fp;
	short *yimg = (short*)malloc(sizeof(short)*width*height);
	short *uimg = (short*)malloc(sizeof(short)*((width*height)));
	short *vimg = (short*)malloc(sizeof(short)*((width*height)));
	short *nuimg = (short*)malloc(sizeof(short)*((width*height) >> 2));
	short *nvimg = (short*)malloc(sizeof(short)*((width*height) >> 2));
	int size = width * height;
	int csize = (width *height) >> 2;
	char newfilename[256];
	printf("Filename : %s", argv[1]);
	strcpy(filename, argv[1]);
	strcpy(newfilename, filename);
	newfilename[strlen(newfilename) - 4] = '\0';
	strcat(newfilename, addmessege);
	fp = fopen(filename, "rb");
	new_fp = fopen(newfilename, "wb");
	if (fp == NULL)
		printf("Can not open file!\n");
	while (feof(fp) == 0) {
		fread(yimg, sizeof(short), size, fp);
		fread(uimg, sizeof(short), size, fp);
		fread(vimg, sizeof(short), size, fp);
		downSampling(nuimg, uimg, width >> 1, height >> 1);
		downSampling(nvimg, vimg, width >> 1, height >> 1);
		fwrite(yimg, sizeof(short), size, new_fp);
		fwrite(nuimg, sizeof(short), size >> 2, new_fp);
		fwrite(nvimg, sizeof(short), size >> 2, new_fp);
	}
	fclose(fp);
	fclose(new_fp);
	free(yimg);
	free(uimg);
	free(vimg);
	free(nuimg);
	free(nvimg);


	return 0;




}