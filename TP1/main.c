#include <stdio.h>
#include "vc.h"
#include "labelling.h"
#include "ca.h"

int main(void) {

	analiza("Imagens/Sinais1/ArrowRight1.ppm");
	log(INFO, "Feito!");
	return 1;
}

//int main2(void) {
//
//	IVC *coins = vc_read_image("Imagens/Aulas/coins.pgm");
//	IVC *coins1 = vc_read_image("Imagens/Aulas/coins.pgm");
//	IVC *coins2 = vc_image_new(coins->width, coins->height, coins->channels, coins->levels);
//	IVC *coins3 = vc_image_new(coins->width, coins->height, coins->channels, coins->levels);
//	IVC *coinsLabel = vc_image_new(coins->width, coins->height, 1, coins->levels);
//	OVC *labels;
//	int nlabels;
//
//	vc_gray_negative(coins);
//
//	vc_gray_to_binary_mean(coins);
//
//	vc_write_image("Resultados/CoinsBinary.pgm", coins);
//
//	vc_binary_open(coins, coins2, 3, 3);
//
//	vc_binary_close(coins2, coins3, 3, 3);
//
//	vc_write_image("Resultados/CoinsClosedOpened.pgm", coins3);
//
//	labels = vc_binary_blob_labelling(coins3, coinsLabel, &nlabels);
//	vc_binary_blob_info(coinsLabel, labels, nlabels);
//
//	vc_write_image("Resultados/CoinsLabel.pgm", coinsLabel);
//
//	drawBoundingBox(coins1, labels, &nlabels, newColor(0,0,0));
//	drawGravityCentre(coins1, labels, &nlabels, newColor(0, 0, 0));
//
//	vc_write_image("Resultados/CoinsBox.pgm", coins1);
//
//	vc_image_free(coins);
//	vc_image_free(coins2);
//
//	printf("Tem %d blobs!\n", nlabels);
//
//	getchar();
//	return 0;
//}