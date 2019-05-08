#include "head.h"


int testParam(int C, char **V){
    if (C==1){
        printf("YCbCr + by GHost\nenjoy!\n");
        exit(0);
    }
    if(C==3){
        if (!strcmp(V[1],"-y")){
            return 0;
        }
    }
    if(C==2){
        if(!strcmp(V[1],"-h")){
            printf("\thelp menu!\n\nuse command '-y':\nprog.exe -y image.bmp\n");
            exit(0);
        }
    }
    printf("incorrect parameters!\nuse -h to more information!\n");
    exit(1);
}


void IRead(FILE *input, COLOR **image, int height,int width){
    int i,j;
    for (i=0;i<height;i++)
        for(j=0;j<width;j++)
            fread(&image[i][j], sizeof(COLOR),1,input);
}


void IWrite(FILE *output, COLOR **image,int height,int width){
    int i,j;
    for (i=0;i<height;i++)
        for(j=0;j<width;j++)
            fwrite(&image[i][j],sizeof(COLOR),1,output);
}


COLOR **createColor(int height,int width){
    int i;
    COLOR **RGB;
    RGB=(COLOR**)malloc(sizeof(COLOR*)*height);
    for(i=0;i<height;i++)
        RGB[i]=(COLOR*)malloc(sizeof(COLOR)*width);
    return RGB;
}

YCbCr **createYCC(int height,int width){
    int i;
    YCbCr **YCC;
    YCC=(YCbCr**)malloc(sizeof(YCbCr*)*height);
    for(i=0;i<height;i++)
        YCC[i]=(YCbCr*)malloc(sizeof(YCbCr)*width);
    return YCC;
}


FILE *IOpen(char *name){
    FILE *f;
    f = fopen(name, "rb+");
    if (!f){
        printf("file '%s' not found!\n",name);
        exit(2);
    }
    return f;
}


BMPFILEHEADER readFH(FILE *input){
    BMPFILEHEADER fh;
    fread(&fh,sizeof(BMPFILEHEADER),1,input);
    if(fh.bfType!=bmp){
        printf("file is not BMP!\n");
        exit(3);
    }
    return fh;
}


BMPINFOHEADER readIH(FILE *input){
    BMPINFOHEADER ih;
    fread(&ih, sizeof(BMPINFOHEADER),1,input);
    return ih;
}

void YCCtoRGB(YCbCr **YCC, COLOR **RGB, int height, int width){
    int i,j;
    for(i=0;i<height;i++)
        for (j=0;j<width;j++){
            RGB[i][j].R=(YCC[i][j].y + 1.402*(YCC[i][j].Cr-128));
            RGB[i][j].G=(YCC[i][j].y - 0.344*(YCC[i][j].Cb-128) - 0.714*(YCC[i][j].Cr - 128));
            RGB[i][j].B=(YCC[i][j].y + 1.772*(YCC[i][j].Cb-128));
        }
    #ifdef debug
    printf("YCC to RGB\n");
    #endif
}


void RGBtoYCC(COLOR **RGB, YCbCr **YCC, int height, int width){
    int i,j;
    for (i=0;i<height;i++)
        for (j=0;j<width;j++){
            YCC[i][j].y=0.299*RGB[i][j].R + 0.587*RGB[i][j].G + 0.114*RGB[i][j].B;
            YCC[i][j].Cb= 0.564*(RGB[i][j].B - YCC[i][j].y);
            YCC[i][j].Cr= 0.713*(RGB[i][j].R - YCC[i][j].y);
        }
    #ifdef debug
    printf("RBG to YCC\n");
    #endif
}
void chgYP(YCbCr **YCC, int height, int width){
    int i,j;
    for(i=0;i<height;i++)
        for(j=0;j<width;j++){
            YCC[i][j].y/=255;
            YCC[i][j].y+=0.001;
            YCC[i][j].y*=255;
        }
            
    #ifdef debug
    printf("YCC++ okey\n");
    #endif
}



/* 
super effect

void YCCtoRGB(YCbCr **YCC, COLOR **RGB, int height, int width){
    int i,j;
    for(i=0;i<height;i++)
        for (j=0;j<width;j++){
            RGB[i][j].R=(int)(YCC[i][j].y + 1.402*(YCC[i][j].Cr-128));
            RGB[i][j].G=(int)(YCC[i][j].y - 0.344*(YCC[i][j].Cb-128) - 0.714*(YCC[i][j].Cr - 128));
            RGB[i][j].B=(int)(YCC[i][j].y + 1.772*(YCC[i][j].Cb-128));
        }
    #ifdef debug
    printf("YCC to RGB\n");
    #endif
}


void RGBtoYCC(COLOR **RGB, YCbCr **YCC, int height, int width){
    int i,j;
    for (i=0;i<height;i++)
        for (j=0;j<width;j++){
            YCC[i][j].y=0.299*RGB[i][j].R + 0.587*RGB[i][j].G + 0.114*RGB[i][j].B;
            YCC[i][j].Cb= 0.564*(RGB[i][j].B - YCC[i][j].y);
            YCC[i][j].Cr= 0.713*(RGB[i][j].R - YCC[i][j].y);
        }
    #ifdef debug
    printf("RBG to YCC\n");
    #endif
}
void chgYP(YCbCr **YCC, int height, int width){
    int i,j;
    for(i=0;i<height;i++)
        for(j=0;j<width;j++)
            YCC[i][j].y-=0.001;
    #ifdef debug
    printf("YCC++ okey\n");
    #endif
}


*/