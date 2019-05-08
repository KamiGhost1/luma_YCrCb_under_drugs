#include "head.h"


int main(int C, char **V){
    FILE *image;
    COLOR **RGB;
    YCbCr *YCC;
    BMPFILEHEADER fh;
    BMPINFOHEADER ih;

    testParam(C, V);

    image = IOpen(V[2]);
    fh = readFH(image);
    ih = readIH(image);

    RGB = createColor(ih.bi_Height, ih.bi_Width);
    YCC = createYCC(ih.bi_Height, ih.bi_Width);
    #ifdef debug
    printf("all okey\n");
    #endif

    fseek(image, fh.bfOffBits, SEEK_SET);
    IRead(image, RGB, ih.bi_Height, ih.bi_Width);
    fseek(image, fh.bfOffBits, SEEK_SET);
    #ifdef debug
    printf("all okey\n");
    #endif

    RGBtoYCC(RGB, YCC, ih.bi_Height, ih.bi_Width);
    chgYP(YCC, ih.bi_Height, ih.bi_Width);
    YCCtoRGB(YCC, RGB, ih.bi_Height, ih.bi_Width);
    #ifdef debug
    printf("all okey\n");
    #endif

    IWrite(image, RGB, ih.bi_Height, ih.bi_Width);
    #ifdef debug
    printf("all okey\n");
    #endif

    fclose(image);
    free(RGB);
    free(YCC);
    printf("image change!\n");
    return 0;
}