//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
//           INSTITUTO POLITÉCNICO DO CÁVADO E DO AVE
//                          2016/2017
//             ENGENHARIA DE SISTEMAS INFORMÁTICOS
//                    VISÃO POR COMPUTADOR
//                       CÓDIGO AULAS
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

#define VC_DEBUG
#define MAX(a,b)(a>b?a:b)

//Estrutura para representar cor, assume por defeito 3 canais e 255 niveis
//Também possui um campo chamado gray que converte automaticamente de rgb para grayscale
typedef struct {
	unsigned char r, g, b;
	unsigned char gray;
}COLOR;

typedef enum
{
	UNDEFINED = 0, SQUARE = 1, CIRCLE = 2 
} Shape;

typedef enum
{
	ARROWLEFT, ARROWRIGHT, ARROWUP, CAR, FORBIDDEN, HIGHTWAY, STOP
} Signal;

int drawBoundingBox(IVC *imagem, OVC *blobs, int *nlabels, COLOR *color);
COLOR* newColor(int r, int g, int b);
int paintPixel(IVC *imagem, int position, COLOR *cor);
int meanBlur(IVC *src, IVC *dst, int kernel);
int drawGravityCentre(IVC *imagem, OVC *blobs, int *nlabels, COLOR *color);
IVC *vc_image_copy(IVC *src);
int blueSignalsToBinary(IVC *src, IVC *dst);
int redSignalsToBinary(IVC *src, IVC *dst);

int vc_rgb_to_hsv(IVC *srcdst);
int value100To255(int value);
int value255To100(int value);

int vc_binary_dilate(IVC *src, IVC *dst, int size);
int vc_binary_erode(IVC *src, IVC *dst, int size);
int vc_binary_open(IVC *src, IVC *dst, int sizeErode, int sizeDilate);
int vc_binary_close(IVC *src, IVC *dst, int sizeErode, int sizeDilate);

int vc_gray_dilate(IVC *src, IVC *dst, int size);
int vc_gray_erode(IVC *src, IVC *dst, int size);
int vc_gray_open(IVC *src, IVC *dst, int sizeErode, int sizeDilate);
int vc_gray_close(IVC *src, IVC *dst, int sizeErode, int sizeDilate);

int vc_gray_to_binary_mean(IVC *srcdst);
int vc_gray_to_binary_midpoint(IVC *src, IVC *dst, int kernel);
int vc_gray_to_binary(IVC *srcdst, int threshold);
int vc_gray_to_binary_bernsen(IVC *src, IVC *dst, int kernel);
int vc_gray_to_binary_adapt(IVC *src, IVC *dst, int kernel);

int vc_gray_negative(IVC *srcdst);
int vc_rgb_negative(IVC *srcdst);
int vc_red_filter(IVC *srcdst);
int vc_remove_red(IVC *srcdst);
int vc_rgb_to_gray(IVC *src, IVC *dst);

int vc_rgb_to_gray(IVC *src, IVC *dst);
int vc_rgb_to_gray_mean(IVC *src, IVC *dst);




