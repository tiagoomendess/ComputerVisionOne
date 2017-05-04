#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <malloc.h>
#include "vc.h"
#include "labelling.h"
#include "ca.h"

//FUNÇÔES FEITAS NA AULA ==============================================
#pragma region TRABALHO

//Extrai apenas os sinais azuis para binario
int blueSignalsToBinary(IVC *src, IVC *dst) {

	int x, y, i, pos, posBinary;
	vc_write_image("Resultados/src.ppm", src);
	vc_write_image("Resultados/dst.pgm", dst);

	IVC *hsvImage = vc_image_copy(src);
	vc_write_image("Resultados/srcCopied.pgm", hsvImage);
	
	vc_rgb_to_hsv(hsvImage);
	vc_write_image("Resultados/hsvImage.pgm", hsvImage);

	int hue, sat, value;

	if (dst->channels != 1)
		return 0;

	for (y = 0; y < hsvImage->height; y++)
	{
		for (x = 0; x < hsvImage->width; x++)
		{

			posBinary = y * dst->bytesperline + x * dst->channels;
			pos = y * hsvImage->bytesperline + x * hsvImage->channels;

			hue = hsvImage->data[pos];
			sat = hsvImage->data[pos + 1];
			value = hsvImage->data[pos + 2];

			if ((hue >= hue360To255(218) && hue <= hue360To255(264)) && (value >= value100To255(13) && value <= value100To255(60)))
				dst->data[posBinary] = 255;
			else
				dst->data[posBinary] = 0;

		}
	}

	free(hsvImage);
	return 1;
}

//Extrai apenas os sinais vermelhos para binario
int redSignalsToBinary(IVC *src, IVC *dst) {

	int x, y, i, pos, posBinary;
	vc_write_image("Resultados/src.ppm", src);
	vc_write_image("Resultados/dst.pgm", dst);

	IVC *hsvImage = vc_image_copy(src);
	vc_write_image("Resultados/srcCopied.pgm", hsvImage);

	vc_rgb_to_hsv(hsvImage);
	vc_write_image("Resultados/hsvImage.pgm", hsvImage);

	int hue, sat, value;

	if (dst->channels != 1)
		return 0;

	for (y = 0; y < hsvImage->height; y++)
	{
		for (x = 0; x < hsvImage->width; x++)
		{

			posBinary = y * dst->bytesperline + x * dst->channels;
			pos = y * hsvImage->bytesperline + x * hsvImage->channels;

			hue = hsvImage->data[pos];
			sat = hsvImage->data[pos + 1];
			value = hsvImage->data[pos + 2];

			if ((hue >= hue360To255(350) && hue <= hue360To255(360)) && (sat >= value100To255(60) && sat <= value100To255(100)) && (value >= value100To255(31) && value <= value100To255(71)))
				dst->data[posBinary] = 255;
			else if((hue >= hue360To255(0) && hue <= hue360To255(7)) && (sat >= value100To255(60) && sat <= value100To255(100)) && (value >= value100To255(31) && value <= value100To255(71))) //O vermelho ocupa as duas pontas do cone
				dst->data[posBinary] = 255;
			else
				dst->data[posBinary] = 0; //Se calhar há uma versão mais rapida de processar com menos condições nos if's, ver mais tarde

		}
	}

	free(hsvImage);
	return 1;
}

//Diz que formato tem o blob
Shape getBlobShape(OVC blob) {

	int boxArea, blobArea, blobPerimeter;
	Shape formato = UNDEFINED;

	boxArea = blob.width * blob.height;
	blobArea = blob.area;
	blobPerimeter = blob.perimeter;

	if ((boxArea - blobArea) < boxArea * 0.10f) //Se a diferença da area for menos que 10% da imagem é porque e um quadrado
		formato = SQUARE;

	if ((boxArea - blobArea) > boxArea * 0.10f)
		formato = CIRCLE;

	return ;
}

//Faz blobs apenas nos sinais de transito
int blobSignals(IVC *src, IVC *dst) {

	int x, y, i;
	IVC *hsv = vc_image_new(src->width, src->height, 3, 255);
	vc_rgb_to_hsv(src);

	//Verificações de erros
	if (dst->channels != 1 || src->channels != 3)
		return 0;
	if (src->width != dst->width || src->height != dst->height)
		return 0;

	for (y = 0; y < src->height; y++)
	{
		for (x = 0; x < src->width; x++)
		{

		}
	}

}

int hue360To255(int hue) {
	return (int) (hue / 360.0f * 255.0f);
}

int hue255To360(int hue) {
	return (int) (hue / 255.0f * 360.0f);
}

int value100To255(int value) {
	return (int)(value / 100.0f * 255.0f);
}

int value255To100(int value) {
	return (int)(value / 255.0f * 100.0f);
}

int countBluePixels(IVC *imagem) {

	IVC *hsvImage = vc_image_copy(imagem);
	int i, x, y, position, contador = 0;
	int hue, sat, value;

	vc_rgb_to_hsv(hsvImage);

	for (y = 0; y < hsvImage->height; y++)
	{
		for (x = 0; x < hsvImage->width; x++)
		{
			position = y * hsvImage->bytesperline + x * hsvImage->channels;

			hue = hsvImage->data[position];
			sat = hsvImage->data[position + 1];
			value = hsvImage->data[position + 2];

			//Caso o pixel seja azul incrementa o contador
			if ((hue >= hue360To255(218) && hue <= hue360To255(264)) && (value >= value100To255(13) && value <= value100To255(60))) { //Vai buscar so a componente H de HSV
				contador++;
			}
		}
	}

	vc_image_free(hsvImage);
	return contador;

}

int countRedPixels(IVC *imagem) {

	IVC *hsvImage = vc_image_copy(imagem);
	int i, x, y, position, contador = 0;
	int hue, sat, value;

	vc_rgb_to_hsv(hsvImage);

	for (y = 0; y < hsvImage->height; y++)
	{
		for (x = 0; x < hsvImage->width; x++)
		{
			position = y * hsvImage->bytesperline + x * hsvImage->channels;

			hue = hsvImage->data[position];
			sat = hsvImage->data[position + 1];
			value = hsvImage->data[position + 2];

			//Caso o pixel seja azul incrementa o contador
			if ((hue >= hue360To255(350) && hue <= hue360To255(360)) && (sat >= value100To255(60) && sat <= value100To255(100)) && (value >= value100To255(31) && value <= value100To255(71)))//Vai buscar so a componente H de HSV
				contador++;
			else if ((hue >= hue360To255(0) && hue <= hue360To255(7)) && (sat >= value100To255(60) && sat <= value100To255(100)) && (value >= value100To255(31) && value <= value100To255(71)))
				contador++;

		}
	}

	vc_image_free(hsvImage);
	return contador;

}

//Copia duas imagens
IVC *vc_image_copy(IVC *src) {

	int x, y, i;
	IVC *dst = (IVC *)malloc(sizeof(IVC));

	dst->width = src->width;
	dst->height = src->height;
	dst->bytesperline = src->bytesperline;
	dst->channels = src->channels;
	dst->levels = src->levels;
	dst->data = (unsigned char *)malloc(dst->width * dst->height * dst->channels * sizeof(char));

	for (y = 0; y < src->height; y++)
	{
		for (x = 0; x < src->width; x++)
		{
			for (i = 0; i < src->channels; i++)
			{
				dst->data[(y * src->bytesperline + x * src->channels) + i] = src->data[(y * src->bytesperline + x * src->channels) + i];
			}
		}
	}
	
	return dst;
}

//Blur pela média
int meanBlur(IVC *src, IVC *dst, int kernel) { //Implementa o requisito de remoção de ruido de uma imagem

	int x, y, kx, ky, delta, soma, posK, position, i;
	int channels = src->channels;
	int *somas = malloc(sizeof(int) * channels);

	delta = (kernel - 1) / 2;

	for (y = 0; y < src->height; y++)
	{
		for (x = 0; x < src->width; x++)
		{
			//Limpar soma do pixel anterior
			for (i = 0; i < channels; i++)
			{
				somas[i] = 0;
			}

			position = y * src->bytesperline + x * src->channels;

			for (ky = -delta; ky <= delta; ky++)
			{
				for (kx = -delta; kx <= delta; kx++)
				{
					if (kx + x >= 0 && ky + y >= 0 && kx + x < src->width && ky + y < src->height) {

						posK = (y + ky) * src->bytesperline + (x + kx) * src->channels;

						for (int i = 0; i < channels; i++)
						{
							somas[i] += src->data[posK + i];
						}
						
					}
				}
			}

			//Faz a média e atribui valor
			for (i = 0; i < channels; i++)
			{
				dst->data[position + i] = somas[i] / (kernel * kernel);
			}

		}
	}

	return 1;
}

//Procura por sinais de transito numa imagem
//Retorna o numero de sinais encontrados
int checkForSignals(IVC *imagem, IVC **sinais) {

	int encontrados = 0;
	return encontrados;
}

//Desenha uma caixa a volta de cada blob
int drawBoundingBox(IVC *imagem, OVC *blobs, int *nlabels, COLOR *color) {

	int x, y, width, height, i, position;
	width = imagem->width;
	height = imagem->height;

	for (y = 0; y < height; y++)
	{
		for (x = 0; x < width; x++)
		{
			position = y * imagem->bytesperline + x * imagem->channels;

			for (i = 0; i < *nlabels; i++)
			{
				if ( ((x >= blobs[i].x) && (x < (blobs[i].x + blobs[i].width))) && y == blobs[i].y) { //Pinta a parte de cima da caixa
					paintPixel(imagem, position, color);
				}

				if (((x >= blobs[i].x) && (x <= (blobs[i].x + blobs[i].width))) && y == blobs[i].y + blobs[i].height ) { //Pinta a parte de baixo da caixa
					paintPixel(imagem, position, color);
				}

				if (((y >= blobs[i].y) && (y < (blobs[i].y + blobs[i].height))) && x == blobs[i].x) { //Pinta a parte esquerda da caixa
					paintPixel(imagem, position, color);
				}

				if (((y >= blobs[i].y) && (y <= (blobs[i].y + blobs[i].height))) && x == blobs[i].x + blobs[i].width) { //Pinta a parte direita da caixa
					paintPixel(imagem, position, color);
				}

			}
		}
	}

	return 1;
}

//Coloca 1 pixel da cor desejada no centro de cada blob
int drawGravityCentre(IVC *imagem, OVC *blobs, int *nlabels, COLOR *color) {

	int x, y, i, position;

	for (y = 0; y < imagem->height; y++)
	{
		for (x = 0; x < imagem->width; x++)
		{
			position = y * imagem->bytesperline + x * imagem->channels;

			for (i = 0; i < *nlabels; i++)
			{
				if (x == blobs[i].xc && y == blobs[i].yc)
					paintPixel(imagem, position, color);
			}
		}
	}

	return 1;
}

//Conforme os channels e os levels que a imagem tem, ele pinta de acordo
int paintPixel(IVC *imagem, int position, COLOR *cor) {

	int i;

	if (imagem->channels == 1)
		imagem->data[position] = cor->gray;
	else if (imagem->channels == 3)
	{
		imagem->data[position] = cor->r;
		imagem->data[position + 1] = cor->g;
		imagem->data[position + 2] = cor->b;
	}
	else { //No caso de isto ter mais channels(Improvavel)

		imagem->data[position] = imagem->levels;

		for (i = 1; i < imagem->channels; i++)
		{
			imagem->data[position + i] = 0;
		}
	}

	return 1;
}

//Função para procurar sinal de stop em uma imagem
int temStop() {
	return 0;
}
#pragma endregion

#pragma region MORFOLOGICOS_BINARY


//Dilatação de uma imagem binária
int vc_binary_dilate(IVC *src, IVC *dst, int size) {

	int x, y, xk, yk, pos, w, h, painel, posk;
	h = src->height;
	w = src->width;
	int centro;

	painel = (size - 1) / 2;

	for (y = 0; y < h; y++)
	{
		for (x = 0; x < w; x++)
		{
			pos = y * src->bytesperline + x * src->channels;
			centro = 0;

			for (yk = -painel; yk <= painel; yk++)
			{
				for (xk = -painel; xk < painel; xk++)
				{

					if ((y + yk >= 0) && (y + yk < src->height) && (x + xk >= 0) && (x + xk < src->width))
					{
						posk = (y + yk) * w + (x + xk);

						if (src->data[posk] == 255)
						{
							centro = 255;
							xk = 1000;
							yk = 1000;
						}
					}

				}
			}

			dst->data[pos] = centro;
		}
	}

	return 1;
}

//erosão de uma imagem binária
int vc_binary_erode(IVC *src, IVC *dst, int size) {

	int x, y, xk, yk, pos, w, h, painel, posk;
	h = src->height;
	w = src->width;
	int centro;

	painel = (size - 1) / 2;

	for (y = 0; y < h; y++)
	{
		for (x = 0; x < w; x++)
		{
			pos = y * src->bytesperline + x * src->channels;
			centro = 255;

			for (yk = -painel; yk <= painel; yk++)
			{
				for (xk = -painel; xk < painel; xk++)
				{

					if ((y + yk >= 0) && (y + yk < src->height) && (x + xk >= 0) && (x + xk < src->width))
					{
						posk = (y + yk) * w + (x + xk);

						if (src->data[posk] == 0)
						{
							centro = 0;
							xk = 1000;
							yk = 1000;
						}
					}

				}
			}

			dst->data[pos] = centro;
		}
	}
	return 1;
}

//abertura binaria
int vc_binary_open(IVC *src, IVC *dst, int sizeErode, int sizeDilate) {

	int ret = 1;
	IVC *tmp = vc_image_new(src->width, src->height, src->channels, src->levels);

	ret &= vc_binary_erode(src, tmp, sizeErode);
	ret &= vc_binary_dilate(tmp, dst, sizeDilate);

	vc_image_free(tmp);

	return ret;
}

//Fecho binario
int vc_binary_close(IVC *src, IVC *dst, int sizeErode, int sizeDilate) {

	int ret = 1;
	IVC *tmp = vc_image_new(src->width, src->height, src->channels, src->levels);

	ret &= vc_binary_dilate(src, tmp, sizeDilate);
	ret &= vc_binary_erode(tmp, dst, sizeErode);

	vc_image_free(tmp);

	return ret;
}

#pragma endregion

#pragma region MORFOLOGICOS_GRAY
//dilatação grayscale
int vc_gray_dilate(IVC *src, IVC *dst, int size) {

	int x, y, xk, yk, pos, w, h, painel, posk;
	h = src->height;
	w = src->width;
	int max;

	painel = (size - 1) / 2;

	for (y = 0; y < h; y++)
	{
		for (x = 0; x < w; x++)
		{
			pos = y * src->bytesperline + x * src->channels;
			max = 0;

			for (yk = -painel; yk <= painel; yk++)
			{
				for (xk = -painel; xk < painel; xk++)
				{

					if ((y + yk >= 0) && (y + yk < src->height) && (x + xk >= 0) && (x + xk < src->width))
					{
						posk = (y + yk) * w + (x + xk);

						if (src->data[posk] > max)
							max = src->data[posk];
					}

				}
			}

			dst->data[pos] = max;
		}
	}

	return 1;
}

//erosao grayscale
int vc_gray_erode(IVC *src, IVC *dst, int size) {

	int x, y, xk, yk, pos, w, h, painel, posk;
	h = src->height;
	w = src->width;
	int min;

	painel = (size - 1) / 2;

	for (y = 0; y < h; y++)
	{
		for (x = 0; x < w; x++)
		{
			pos = y * src->bytesperline + x * src->channels;
			min = src->levels + 1;

			for (yk = -painel; yk <= painel; yk++)
			{
				for (xk = -painel; xk < painel; xk++)
				{

					if ((y + yk >= 0) && (y + yk < src->height) && (x + xk >= 0) && (x + xk < src->width))
					{
						posk = (y + yk) * w + (x + xk);

						if (src->data[posk] < min)
							min = src->data[posk];
					}

				}
			}

			dst->data[pos] = min;
		}
	}

	return 1;
}

//abertura gray
int vc_gray_open(IVC *src, IVC *dst, int sizeErode, int sizeDilate) {

	int ret = 1;
	IVC *tmp = vc_image_new(src->width, src->height, src->channels, src->levels);

	ret &= vc_gray_erode(src, tmp, sizeErode);
	ret &= vc_gray_dilate(tmp, dst, sizeDilate);

	vc_image_free(tmp);

	return ret;
}

//Fecho gray
int vc_gray_close(IVC *src, IVC *dst, int sizeErode, int sizeDilate) {

	int ret = 1;
	IVC *tmp = vc_image_new(src->width, src->height, src->channels, src->levels);

	ret &= vc_gray_dilate(src, tmp, sizeDilate);
	ret &= vc_gray_erode(tmp, dst, sizeErode);

	vc_image_free(tmp);

	return ret;
}

#pragma endregion

#pragma region GRAY_TO_BINARY

// Calcula o threshold a usar pela media total
int vc_gray_to_binary_mean(IVC *srcdst)
{
	unsigned char *data = (unsigned char *)srcdst->data;
	int width = srcdst->width;
	int height = srcdst->height;
	int bytesperline = srcdst->width * srcdst->channels;
	int channels = srcdst->channels;
	int i, size;
	float media = 0;

	size = width * height * channels;

	if ((width <= 0) || (height <= 0) || (data == NULL)) return 0;
	if (channels != 1) return 0;

	for (i = 0; i < size; i++)
	{
		media += data[i];
	}
	media = (float)media / size;

	for (i = 0; i < size; i++)
	{
		if (data[i] > media) data[i] = 255;
		else data[i] = 0;
	}

	return 1;
}

//Gray to binary midpoint
int vc_gray_to_binary_midpoint(IVC *src, IVC *dst, int kernel)
{
	int x, y, z, a;
	int painel, posk;
	int min, max;
	float thershold;

	painel = (kernel - 1) / 2;

	for (y = 0; y < src->height; y++)
	{
		for (x = 0; x < src->width; x++)
		{
			min = src->levels + 1;
			max = -1;

			for (z = -painel; z <= painel; z++)
			{
				for (a = -painel; a <= painel; a++)
				{
					if (y + z >= 0 && x + a >= 0 && y + z < src->height && x + a < src->width)
					{
						posk = (y + z) * src->width + (x + a);

						if (src->data[posk] <= min)
							min = src->data[posk];

						if (src->data[posk] >= max)
							max = src->data[posk];
					}
				}
			}

			thershold = ((float)(min + max) * 0.5f);

			if (src->data[y * src->width + x] > thershold)
			{
				dst->data[y * src->width + x] = 255;
			}
			else
			{
				dst->data[y * src->width + x] = 0;
			}

		}
	}

	return 1;
}

//Gray to binary
int vc_gray_to_binary(IVC *srcdst, int threshold) {

	int i;
	unsigned char *data;
	int width = srcdst->width;
	int height = srcdst->height;
	int channels = srcdst->channels;
	int bytesperline = srcdst->bytesperline;
	int size;

	data = (unsigned char *)srcdst->data;
	size = width * height * channels;

	for (i = 0; i < size; i++)
	{
		if (data[i] < threshold)
			data[i] = 0;
		else
			data[i] = 255;
	}

}

//Gray to binary pelo metodo Bernsen
int vc_gray_to_binary_bernsen(IVC *src, IVC *dst, int kernel) 
{
	unsigned char *data_src = (unsigned char *)src->data, *data_dst = (unsigned char *)dst->data;
	int width = src->width;
	int height = src->height;
	int bytesperline = src->width * src->channels;
	int channels = src->channels;
	int x, y, xX, yY, vmin = src->levels, vmax = 0, delta, pos, pox;
	float treshold = 0;

	delta = (kernel - 1) / 2;


	//verificar imagem
	if ((width <= 0) || (height <= 0) || (data_src == NULL)) return 0;
	if (channels != 1) return 0;
	if ((width != dst->width) || (height != dst->height) || (dst->data == NULL)) return 0;
	if (dst->channels != 1) return 0;

	for (x = 0; x < width; x++)
	{
		for (y = 0; y < height; y++)
		{
			vmin = src->levels;
			vmax = 0;
			for (xX = -delta; xX <= delta; xX++)
			{
				for (yY = -delta; yY <= delta; yY++)
				{
					if (xX + x >= 0 && yY + y >= 0 && xX + x < width && yY + y < height)
					{
						pox = (yY + y)  * bytesperline + (xX + x) * channels;
						if (data_src[pox] < vmin) vmin = data_src[pox];
						if (data_src[pox] > vmax) vmax = data_src[pox];
					}
				}
			}
			pos = y * bytesperline + x * channels;

			if (vmax - vmin < 15) treshold = src->levels / 2;
			else treshold = (vmin + vmax) / 2;

			if (data_src[pos] > treshold) data_dst[pos] = 255;
			else data_dst[pos] = 0;
		}
	}
}

//Gray to binary pelo metodo adaptativo
int vc_gray_to_binary_adapt(IVC *src, IVC *dst, int kernel)
{
	unsigned char *data_src = (unsigned char *)src->data, *data_dst = (unsigned char *)dst->data;
	int width = src->width;
	int height = src->height;
	int bytesperline = src->width * src->channels;
	int channels = src->channels;
	int x, y, xX, yY, vmin = src->levels, vmax = 0, delta, pos, pox, soma = 0, n;
	float treshold = 0, media = 0, desvio = 0;

	delta = (kernel - 1) / 2;
	n = kernel * kernel;

	if ((width <= 0) || (height <= 0) || (data_src == NULL)) return 0;
	if (channels != 1) return 0;
	if ((width != dst->width) || (height != dst->height) || (dst->data == NULL)) return 0;
	if (dst->channels != 1) return 0;

	for (x = 0; x < width; x++)
	{
		for (y = 0; y < height; y++)
		{
			for (xX = -delta; xX <= delta; xX++)
			{
				for (yY = -delta; yY <= delta; yY++)
				{
					if (xX + x >= 0 && yY + y >= 0 && xX + x < width && yY + y < height)
					{
						pox = (yY + y)  * bytesperline + (xX + x) * channels;
						soma += data_src[pox];
					}
				}
			}

			media = (float)soma / n;
			soma = 0;

			for (xX = -delta; xX <= delta; xX++)
			{
				for (yY = -delta; yY <= delta; yY++)
				{
					if (xX + x >= 0 && yY + y >= 0 && xX + x < width && yY + y < height)
					{
						pox = (yY + y)  * bytesperline + (xX + x) * channels;
						soma += pow((data_src[pox] - media), 2);
					}
				}
			}
			soma = soma / (n - 1);
			desvio = (float)sqrt(soma);

			treshold = media - 0.2 * desvio;

			pos = y * bytesperline + x * channels;

			if (data_src[pos] > treshold) data_dst[pos] = 255;
			else data_dst[pos] = 0;
		}
	} return 1;
}

#pragma endregion

#pragma region RGB_TO_HSV

//RGB para HSV
int vc_rgb_to_hsv(IVC *srcdst)
{
	unsigned char *data = (unsigned char *)srcdst->data;
	int width = srcdst->width;
	int height = srcdst->height;
	int bytesperline = srcdst->bytesperline;
	int channels = srcdst->channels;
	float r, g, b, hue, saturation, value;
	float rgb_max, rgb_min;
	int i, size;

	// Verifica��o de erros
	if ((width <= 0) || (height <= 0) || (data == NULL)) return 0;
	if (channels != 3) return 0;

	size = width * height * channels;

	for (i = 0; i<size; i = i + channels)
	{
		r = (float)data[i];
		g = (float)data[i + 1];
		b = (float)data[i + 2];

		// Calcula valores m�ximo e m�nimo dos canais de cor R, G e B
		rgb_max = (r > g ? (r > b ? r : b) : (g > b ? g : b));
		rgb_min = (r < g ? (r < b ? r : b) : (g < b ? g : b));

		// Value toma valores entre [0,255]
		value = rgb_max;
		if (value == 0.0f)
		{
			hue = 0.0f;
			saturation = 0.0f;
		}
		else
		{
			// Saturation toma valores entre [0,255]
			saturation = ((rgb_max - rgb_min) / rgb_max) * 255.0f;

			if (saturation == 0.0f)
			{
				hue = 0.0f;
			}
			else
			{
				// Hue toma valores entre [0,360]
				if ((rgb_max == r) && (g >= b))
				{
					hue = 60.0f * (g - b) / (rgb_max - rgb_min);
				}
				else if ((rgb_max == r) && (b > g))
				{
					hue = 360.0f + 60.0f * (g - b) / (rgb_max - rgb_min);
				}
				else if (rgb_max == g)
				{
					hue = 120.0f + 60.0f * (b - r) / (rgb_max - rgb_min);
				}
				else /* rgb_max == b*/
				{
					hue = 240.0f + 60.0f * (r - g) / (rgb_max - rgb_min);
				}
			}
		}

		// Atribui valores entre [0,255]
		data[i] = (unsigned char)(hue / 360.0f * 255.0f);
		data[i + 1] = (unsigned char)(saturation);
		data[i + 2] = (unsigned char)(value);
	}

	return 1;
}

#pragma endregion

#pragma region RGB_GRAY

// Calculado pela formula
int vc_rgb_to_gray(IVC * src, IVC *dst) 
{
	unsigned char *data_src = (unsigned char *)src->data, *data_dst = (unsigned char *)dst->data;
	int width = src->width;
	int height = src->height;
	int bytesperline_src = src->width * src->channels, bytesperline_dst = dst->width * dst->channels;
	int channels_src = src->channels, channels_dst = dst->channels;
	int x, y;
	long int pos_src, pos_dst;
	float r, g, b;


	//verificar imagem
	if ((width <= 0) || (height <= 0) || (data_src == NULL)) return 0;
	if (channels_src != 3) return 0;
	if ((width != dst->width) || (height != dst->height) || (data_dst == NULL)) return 0;
	if (channels_dst != 1) return 0;

	//Inverter Imagem
	for (y = 0; y < height; y++)
	{
		for (x = 0; x < width; x++)
		{
			pos_src = y * bytesperline_src + x * channels_src;
			pos_dst = y * bytesperline_dst + x * channels_dst;

			r = data_src[pos_src];
			g = data_src[pos_src + 1];
			b = data_src[pos_src + 2];

			data_dst[pos_dst] = (unsigned char)((r *0.299) + (g*0.587) + (b *0.114));

		}
	}
	return 1;
}

// Calculado pela media
int vc_rgb_to_gray_mean(IVC * src, IVC *dst)
{
	unsigned char *data_src = (unsigned char *)src->data, *data_dst = (unsigned char *)dst->data;
	int width = src->width;
	int height = src->height;
	int bytesperline_src = src->width * src->channels, bytesperline_dst = dst->width * dst->channels;
	int channels_src = src->channels, channels_dst = dst->channels;
	int x, y;
	long int pos_src, pos_dst;
	int r, g, b;


	//verificar imagem
	if ((width <= 0) || (height <= 0) || (data_src == NULL)) return 0;
	if (channels_src != 3) return 0;
	if ((width != dst->width) || (height != dst->height) || (data_dst == NULL)) return 0;
	if (channels_dst != 1) return 0;

	//Inverter Imagem
	for (y = 0; y < height; y++)
	{
		for (x = 0; x < width; x++)
		{
			pos_src = y * bytesperline_src + x * channels_src;
			pos_dst = y * bytesperline_dst + x * channels_dst;

			r = data_src[pos_src];
			g = data_src[pos_src + 1];
			b = data_src[pos_src + 2];

			data_dst[pos_dst] = (unsigned char)((r + g + b) / 3);

		}
	}
	return 1;
}

#pragma endregion

#pragma region EQUALIZAÇÃO

int vc_gray_histogram_equalization(IVC *src, IVC *dst) {

	int width = src->width;
	int height = src->height;
	int channels = src->channels;
	int npixeis = width * height;
	double pdf[256] = { 0.0 };
	double cdf[256] = { 0.0 };
	double cdfmin;
	int hist[256] = { 0 };
	long int pos;
	int x, y, i;
	unsigned char k;

	//Percorre todos os pixeis da imagem
	for (pos = 0; pos < npixeis; pos++)
	{
		//Conta o numero de vezes que cada intensidade de cor ocorr
		hist[src->data[pos]++];
	}


	//Calcula pdf da imagem
	for (i = 0; i < 256; i++)
	{
		pdf[i] = (double)hist[i] / (double)npixeis;
	}

	//Calcula CDF da imagem

	return 1;
}
#pragma endregion


#pragma region OUTROS

COLOR* newColor(int r, int g, int b) {

	COLOR *cor = malloc(sizeof(COLOR));
	cor->r = (unsigned char)r;
	cor->g = (unsigned char)g;
	cor->b = (unsigned char)b;

	cor->gray = (unsigned char)((r *0.299) + (g*0.587) + (b *0.114));

	return cor;

}

int vc_gray_negative(IVC *srcdst)
{
	unsigned char *data = (unsigned char *)srcdst->data;
	int width = srcdst->width;
	int height = srcdst->height;
	int bytesperline = srcdst->width * srcdst->channels;
	int channels = srcdst->channels;
	int x, y;
	long int pos;

	//verificar imagem
	if ((width <= 0) || (height <= 0) || (srcdst->data == NULL)) return 0;
	if (channels != 1) return 0;

	//Inverter Imagem
	for (y = 0; y < height; y++)
	{
		for (x = 0; x < width; x++)
		{
			pos = y * bytesperline + x * channels;

			data[pos] = 255 - data[pos];
		}
	}
	return 1;
}

int vc_rgb_negative(IVC *srcdst)
{
	unsigned char *data = (unsigned char *)srcdst->data;
	int width = srcdst->width;
	int height = srcdst->height;
	int bytesperline = srcdst->width * srcdst->channels;
	int channels = srcdst->channels;
	int x, y;
	long int pos;

	//verificar imagem
	if ((width <= 0) || (height <= 0) || (data == NULL)) return 0;
	if (channels != 3) return 0;

	//Inverter Imagem
	for (y = 0; y < height; y++)
	{
		for (x = 0; x < width; x++)
		{
			pos = y * bytesperline + x * channels;

			data[pos] = 255 - data[pos];
			data[pos + 1] = 255 - data[pos + 1];
			data[pos + 2] = 255 - data[pos + 2];
		}
	}
	return 1;
}

int vc_red_filter(IVC *srcdst)
{
	unsigned char *data = (unsigned char *)srcdst->data;
	int width = srcdst->width;
	int height = srcdst->height;
	int bytesperline = srcdst->width * srcdst->channels;
	int channels = srcdst->channels;
	int x, y;
	long int pos;

	//verificar imagem
	if ((width <= 0) || (height <= 0) || (data == NULL)) return 0;
	if (channels != 3) return 0;

	//Inverter Imagem
	for (y = 0; y < height; y++)
	{
		for (x = 0; x < width; x++)
		{
			pos = y * bytesperline + x * channels;

			data[pos + 1] = 0;
			data[pos + 2] = 0;
		}
	}
	return 1;
}

int vc_remove_red(IVC * srcdst)
{
	unsigned char *data = (unsigned char *)srcdst->data;
	int width = srcdst->width;
	int height = srcdst->height;
	int bytesperline = srcdst->width * srcdst->channels;
	int channels = srcdst->channels;
	int x, y;
	long int pos;

	//verificar imagem
	if ((width <= 0) || (height <= 0) || (data == NULL)) return 0;
	if (channels != 3) return 0;

	//Inverter Imagem
	for (y = 0; y < height; y++)
	{
		for (x = 0; x < width; x++)
		{
			pos = y * bytesperline + x * channels;

			data[pos] = 0;
		}
	}
	return 1;
}

#pragma endregion

//FIM DE FUNÇÔES FEITAS NA AULA