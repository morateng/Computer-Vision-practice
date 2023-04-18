#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <windows.h>

void swap(BYTE* a, BYTE* b) {
	BYTE temp = *a;
	*a = *b;
	*b = temp;
}

void Sorting(BYTE* Arr, int Size) {
	for (int i = 0; i < Size - 1; i++) {
		for (int j = i + 1; j < Size; j++) {
			if (Arr[i] > Arr[j])
				swap(&Arr[i], &Arr[j]);
		}
	}
}

void main()
{
	BITMAPFILEHEADER hf;
	BITMAPINFOHEADER hinfo;
	RGBQUAD hRGB[256];
	FILE* fp;
	fp = fopen("salt.bmp", "rb");
	if (fp == NULL) {
		printf("File not found\n");
		return;
	}

	fread(&hf, sizeof(BITMAPFILEHEADER), 1, fp);
	fread(&hinfo, sizeof(BITMAPINFOHEADER), 1, fp);
	fread(hRGB, sizeof(RGBQUAD), 256, fp);

	int W, H, ImgSize;
	W = hinfo.biWidth;
	H = hinfo.biHeight;
	ImgSize = W * H;

	BYTE* Image = (BYTE*)malloc(ImgSize);
	BYTE* Output = (BYTE*)malloc(ImgSize);
	fread(Image, sizeof(BYTE), ImgSize, fp);
	fclose(fp);

	BYTE Temp[9];
	for (int i = 1; i < H - 1; i++) {
		for (int j = 1; j < W - 1; j++) {
			for (int m = -1; m <= 1; m++) {
				for (int n = -1; n <= 1; n++) {
					Temp[(m + 1) * 3 + (n + 1)] = Image[(i + m) * W + (j + n)];
				}
			}
			Sorting(Temp, 9);
			Output[i * W + j] = Temp[4];
		}

		fp = fopen("output.bmp", "wp");
		fwrite(&hf, sizeof(BYTE), sizeof(BITMAPFILEHEADER), fp);
		fwrite(&hinfo, sizeof(BYTE), sizeof(BITMAPINFOHEADER), fp);
		fwrite(&hRGB, sizeof(RGBQUAD), 256, fp);
		fwrite(Output, sizeof(BYTE), ImgSize, fp);
		fclose(fp);
		free(Image);
		free(Output);
		return;
	}
}