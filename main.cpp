#include <iostream>
#include <string>
#include "BITMAP.h"

using namespace std;
enum {
    to8bits, to4bits, to24bits, toGray, toBlackwhite
};

void loadInfo(char *name) {
    FILE *fp;
    BITMAPFILEHEADER bf;
    BITMAPINFOHEADER bi;
    if ((fp = fopen(name, "rb")) == NULL) {
        cout << "Open file failed." << endl;
    }
    fread(&bf, sizeof(bf), 1, fp);

    printf("bfType --> %c\n", bf.bfType);
    printf("bfSize --> %d\n", bf.bfSize);
    printf("bfOffsets --> %d\n", bf.bfOffBits);

    fread(&bi, sizeof(bi), 1, fp);
    printf("biSize:  %d\n", bi.biSize);
    printf("biWidth: %d\n", bi.biWidth);    //位图宽度
    printf("biHeight:%d\n", bi.biHeight);    //位图高度
    printf("biPlanes:%d\n", bi.biPlanes);    //颜色位面数，总为1
    printf("biBitCount:%d\n", bi.biBitCount);    //每象数颜色位（1，2，4，8，24）
    printf("bmCompression:  %d\n", bi.bmCompression);
}

RGBQUAD rgbquad[256] = {//用于转化为256色的调色板
        0, 0, 0, 0, 0, 0, 128, 0, 0, 128, 0, 0, 0, 128, 128, 0,
        128, 0, 0, 0, 128, 0, 128, 0, 128, 128, 0, 0, 192, 192, 192, 0,
        192, 220, 192, 0, 240, 202, 166, 0, 0, 32, 64, 0, 0, 32, 96, 0,
        0, 32, 128, 0, 0, 32, 160, 0, 0, 32, 192, 0, 0, 32, 224, 0,
        0, 64, 0, 0, 0, 64, 32, 0, 0, 64, 64, 0, 0, 64, 96, 0,
        0, 64, 128, 0, 0, 64, 160, 0, 0, 64, 192, 0, 0, 64, 224, 0,
        0, 96, 0, 0, 0, 96, 32, 0, 0, 96, 64, 0, 0, 96, 96, 0,
        0, 96, 128, 0, 0, 96, 160, 0, 0, 96, 192, 0, 0, 96, 224, 0,
        0, 128, 0, 0, 0, 128, 32, 0, 0, 128, 64, 0, 0, 128, 96, 0,
        0, 128, 128, 0, 0, 128, 160, 0, 0, 128, 192, 0, 0, 128, 224, 0,
        0, 160, 0, 0, 0, 160, 32, 0, 0, 160, 64, 0, 0, 160, 96, 0,
        0, 160, 128, 0, 0, 160, 160, 0, 0, 160, 192, 0, 0, 160, 224, 0,
        0, 192, 0, 0, 0, 192, 32, 0, 0, 192, 64, 0, 0, 192, 96, 0,
        0, 192, 128, 0, 0, 192, 160, 0, 0, 192, 192, 0, 0, 192, 224, 0,
        0, 224, 0, 0, 0, 224, 32, 0, 0, 224, 64, 0, 0, 224, 96, 0,
        0, 224, 128, 0, 0, 224, 160, 0, 0, 224, 192, 0, 0, 224, 224, 0,
        64, 0, 0, 0, 64, 0, 32, 0, 64, 0, 64, 0, 64, 0, 96, 0,
        64, 0, 128, 0, 64, 0, 160, 0, 64, 0, 192, 0, 64, 0, 224, 0,
        64, 32, 0, 0, 64, 32, 32, 0, 64, 32, 64, 0, 64, 32, 96, 0,
        64, 32, 128, 0, 64, 32, 160, 0, 64, 32, 192, 0, 64, 32, 224, 0,
        64, 64, 0, 0, 64, 64, 32, 0, 64, 64, 64, 0, 64, 64, 96, 0,
        64, 64, 128, 0, 64, 64, 160, 0, 64, 64, 192, 0, 64, 64, 224, 0,
        64, 96, 0, 0, 64, 96, 32, 0, 64, 96, 64, 0, 64, 96, 96, 0,
        64, 96, 128, 0, 64, 96, 160, 0, 64, 96, 192, 0, 64, 96, 224, 0,
        64, 128, 0, 0, 64, 128, 32, 0, 64, 128, 64, 0, 64, 128, 96, 0,
        64, 128, 128, 0, 64, 128, 160, 0, 64, 128, 192, 0, 64, 128, 224, 0,
        64, 160, 0, 0, 64, 160, 32, 0, 64, 160, 64, 0, 64, 160, 96, 0,
        64, 160, 128, 0, 64, 160, 160, 0, 64, 160, 192, 0, 64, 160, 224, 0,
        64, 192, 0, 0, 64, 192, 32, 0, 64, 192, 64, 0, 64, 192, 96, 0,
        64, 192, 128, 0, 64, 192, 160, 0, 64, 192, 192, 0, 64, 192, 224, 0,
        64, 224, 0, 0, 64, 224, 32, 0, 64, 224, 64, 0, 64, 224, 96, 0,
        64, 224, 128, 0, 64, 224, 160, 0, 64, 224, 192, 0, 64, 224, 224, 0,
        128, 0, 0, 0, 128, 0, 32, 0, 128, 0, 64, 0, 128, 0, 96, 0,
        128, 0, 128, 0, 128, 0, 160, 0, 128, 0, 192, 0, 128, 0, 224, 0,
        128, 32, 0, 0, 128, 32, 32, 0, 128, 32, 64, 0, 128, 32, 96, 0,
        128, 32, 128, 0, 128, 32, 160, 0, 128, 32, 192, 0, 128, 32, 224, 0,
        128, 64, 0, 0, 128, 64, 32, 0, 128, 64, 64, 0, 128, 64, 96, 0,
        128, 64, 128, 0, 128, 64, 160, 0, 128, 64, 192, 0, 128, 64, 224, 0,
        128, 96, 0, 0, 128, 96, 32, 0, 128, 96, 64, 0, 128, 96, 96, 0,
        128, 96, 128, 0, 128, 96, 160, 0, 128, 96, 192, 0, 128, 96, 224, 0,
        128, 128, 0, 0, 128, 128, 32, 0, 128, 128, 64, 0, 128, 128, 96, 0,
        128, 128, 128, 0, 128, 128, 160, 0, 128, 128, 192, 0, 128, 128, 224, 0,
        128, 160, 0, 0, 128, 160, 32, 0, 128, 160, 64, 0, 128, 160, 96, 0,
        128, 160, 128, 0, 128, 160, 160, 0, 128, 160, 192, 0, 128, 160, 224, 0,
        128, 192, 0, 0, 128, 192, 32, 0, 128, 192, 64, 0, 128, 192, 96, 0,
        128, 192, 128, 0, 128, 192, 160, 0, 128, 192, 192, 0, 128, 192, 224, 0,
        128, 224, 0, 0, 128, 224, 32, 0, 128, 224, 64, 0, 128, 224, 96, 0,
        128, 224, 128, 0, 128, 224, 160, 0, 128, 224, 192, 0, 128, 224, 224, 0,
        192, 0, 0, 0, 192, 0, 32, 0, 192, 0, 64, 0, 192, 0, 96, 0,
        192, 0, 128, 0, 192, 0, 160, 0, 192, 0, 192, 0, 192, 0, 224, 0,
        192, 32, 0, 0, 192, 32, 32, 0, 192, 32, 64, 0, 192, 32, 96, 0,
        192, 32, 128, 0, 192, 32, 160, 0, 192, 32, 192, 0, 192, 32, 224, 0,
        192, 64, 0, 0, 192, 64, 32, 0, 192, 64, 64, 0, 192, 64, 96, 0,
        192, 64, 128, 0, 192, 64, 160, 0, 192, 64, 192, 0, 192, 64, 224, 0,
        192, 96, 0, 0, 192, 96, 32, 0, 192, 96, 64, 0, 192, 96, 96, 0,
        192, 96, 128, 0, 192, 96, 160, 0, 192, 96, 192, 0, 192, 96, 224, 0,
        192, 128, 0, 0, 192, 128, 32, 0, 192, 128, 64, 0, 192, 128, 96, 0,
        192, 128, 128, 0, 192, 128, 160, 0, 192, 128, 192, 0, 192, 128, 224, 0,
        192, 160, 0, 0, 192, 160, 32, 0, 192, 160, 64, 0, 192, 160, 96, 0,
        192, 160, 128, 0, 192, 160, 160, 0, 192, 160, 192, 0, 192, 160, 224, 0,
        192, 192, 0, 0, 192, 192, 32, 0, 192, 192, 64, 0, 192, 192, 96, 0,
        192, 192, 128, 0, 192, 192, 160, 0, 240, 251, 255, 0, 164, 160, 160, 0,
        128, 128, 128, 0, 0, 0, 255, 0, 0, 255, 0, 0, 0, 255, 255, 0,
        255, 0, 0, 0, 255, 0, 255, 0, 255, 255, 0, 0, 255, 255, 255, 0};

RGBQUAD rgbquad16[16] = {
        0, 0, 0, 0,//黑
        128, 0, 0, 0,
        0, 128, 0, 0,
        128, 128, 0, 0,
        0, 0, 128, 0,
        128, 0, 128, 0,
        0, 128, 128, 0,
        128, 128, 128, 0,
        192, 192, 192, 0,
        255, 0, 0, 0,
        0, 255, 0, 0,
        255, 255, 0, 0,
        0, 0, 255, 0,
        255, 0, 255, 0,
        0, 255, 255, 0,
        255, 255, 255, 0//白
};

RGBQUAD rgbquadGray[16];//用函数初始化

int getIndex(BYTE R, BYTE G, BYTE B, RGBQUAD *rgbquad, int size) {//获得rgb在调色板中最接近颜色的索引
    int min_dist = 1000;
    int dist;
    int i;
    int min_index = 0;
    for (i = 0; i < size; i++) {
        dist = abs(rgbquad[i].rgbRed - R) + abs(rgbquad[i].rgbGreen - G) + abs(rgbquad[i].rgbBlue - B);
        if (dist < min_dist) {
            min_dist = dist;
            min_index = i;
        }
    }
    return min_index;
}

int getGrayIndex(BYTE R, BYTE G, BYTE B, RGBQUAD *rgbquad, int size) {//获得rgb在灰度调色板中最接近颜色的索引
    double gray = 0.299 * R + 0.587 * G + 0.114 * B;
    int index;
    index = int(gray / 17);
    return index;
}

void initGray() {
    int i;
    for (i = 0; i < 16; i++) {
        rgbquadGray[i].rgbRed = i * 17;
        rgbquadGray[i].rgbGreen = i * 17;
        rgbquadGray[i].rgbBlue = i * 17;
        rgbquadGray[i].rgbReserved = 0;
    }
}

//16色转24bits真彩色
void convert4bitsTo24bits(FILE* fp, FILE* fres){
    rewind(fp);

    RGBQUAD rgb[256];
    BITMAPFILEHEADER bf, bfr;
    BITMAPINFOHEADER bi, bir;
    int colors;
    int i, j, k;
    int colorIndex, colorIndex2;
    int Width, Height;
    BYTE pixel[4];

    fread(&bf, sizeof(bf), 1, fp);
    fread(&bi, sizeof(bi), 1, fp);
    colors = 1 << bi.biBitCount;
    fread(rgb, sizeof(RGBQUAD), colors, fp);
    Height = bi.biHeight;
    Width = bi.biWidth;

    bfr = bf;
    bir = bi;
    bir.biBitCount = 24;
    bfr.bfOffBits = 54;
    bfr.bfSize = Height * ((Width * 24 + 31) / 32 * 4) + 54;//4字节对齐后的size

    fwrite(&bfr, sizeof(bfr), 1, fres);
    fwrite(&bir, sizeof(bir), 1, fres);


    for (j = 0; j < Height; j++) {
        k = 0;
        for (i = 0; i < Width; i = i + 2) {
            fread(&colorIndex, 1, 1, fp);
            colorIndex2 = colorIndex & 0xf0 >> 4;
            colorIndex = colorIndex & 0xf;

            pixel[0] = rgb[colorIndex].rgbBlue;
            pixel[1] = rgb[colorIndex].rgbGreen;
            pixel[2] = rgb[colorIndex].rgbRed;
            fwrite(pixel, 3, 1, fres);

            pixel[0] = rgb[colorIndex2].rgbBlue;
            pixel[1] = rgb[colorIndex2].rgbGreen;
            pixel[2] = rgb[colorIndex2].rgbRed;
            fwrite(pixel, 3, 1, fres);
        }
        while ((i / 2) % 4 != 0) {//注意4字节对齐
            fread(&colorIndex, 1, 1, fp);
            i = i + 2;
        }
        while ((Width * 3 % 4) + k != 0) {//4字节对齐
            pixel[0] = 0;
            fwrite(pixel, 1, 1, fres);
            k++;
        }
    }
}

//256色转24bits真彩色
void convert8bitsTo24bits(FILE *fp, FILE *fres) {
    rewind(fp);

    RGBQUAD rgb[256];
    BITMAPFILEHEADER bf, bfr;
    BITMAPINFOHEADER bi, bir;
    int colors;
    int i, j, k;
    int colorIndex, colorIndex2;
    int Width, Height;
    BYTE pixel[4];
    fread(&bf, sizeof(bf), 1, fp);
    fread(&bi, sizeof(bi), 1, fp);
    colors = 1 << bi.biBitCount;
    fread(rgb, sizeof(RGBQUAD), colors, fp);
    Height = bi.biHeight;
    Width = bi.biWidth;

    bfr = bf;
    bir = bi;
    bir.biBitCount = 24;
    bfr.bfOffBits = 54;
    bfr.bfSize = Height * ((Width * 24 + 31) / 32 * 4) + 54;//4字节对齐后的size

    fwrite(&bfr, sizeof(bfr), 1, fres);
    fwrite(&bir, sizeof(bir), 1, fres);

    if (colors == 256) {//将256色转化成24bits真彩色
        for (j = 0; j < Height; j++) {
            k = 0;
            for (i = 0; i < Width; i++) {
                fread(&colorIndex, 1, 1, fp);
                pixel[0] = rgb[colorIndex].rgbBlue;
                pixel[1] = rgb[colorIndex].rgbGreen;
                pixel[2] = rgb[colorIndex].rgbRed;
                fwrite(pixel, 3, 1, fres);
            }
            while ((Width * 3 % 4) + k != 0) {//4字节对齐
                pixel[0] = 0;
                fwrite(pixel, 1, 1, fres);
                k++;
            }
        }
    }

}

//24bits真彩色转16色
void convert24bitsTo4bits(FILE* fp, FILE* fres){
    BITMAPFILEHEADER bf, bfr;
    BITMAPINFOHEADER bi, bir;
    int i, j;
    int Height, Width;
    BYTE pixel[4];
    int index, index2;
    fread(&bf, sizeof(bf), 1, fp);
    fread(&bi, sizeof(bi), 1, fp);
    bfr = bf;
    bir = bi;
    bfr.bfSize = 54 + 16 * 4 + Height * ((Width * 4 + 31) / 32 * 4);
    bfr.bfOffBits = 54 + 64;
    bir.biBitCount = 4;
    Height = bi.biHeight;
    Width = bi.biWidth;
    fwrite(&bfr, sizeof(bfr), 1, fres);
    fwrite(&bir, sizeof(bir), 1, fres);
    fwrite(&rgbquad16, sizeof(RGBQUAD), 16, fres);//写入调色板

    for (j = 0; j < Height; j++) {
        for (i = 0; i < Width; i = i + 2) {
            fread(&pixel, 3, 1, fp);
            index = getIndex(pixel[2], pixel[1], pixel[0], rgbquad16, 16);
            fread(&pixel, 3, 1, fp);
            index2 = getIndex(pixel[2], pixel[1], pixel[0], rgbquad16, 16);
            index = (index << 4) | index2;
            //cout << index2 << endl;
            fwrite(&index, 1, 1, fres);
        }
        while ((i / 2) % 4 != 0) {//4字节对齐
            index = 0;
            fwrite(&index, 1, 1, fres);
            i = i + 2;
        }
    }
    cout << "Convert to 4bits bmp success." << endl;
}

//24bits真彩色转256色
void convert24bitsTo8bits(FILE* fp, FILE* fres){
    BITMAPFILEHEADER bf, bfr;
    BITMAPINFOHEADER bi, bir;
    int i, j;
    int Height, Width;
    BYTE pixel[4];
    int index;

    fread(&bf, sizeof(bf), 1, fp);
    fread(&bi, sizeof(bi), 1, fp);
    bfr = bf;
    bir = bi;
    bfr.bfSize = 54 + 256 * 4 + Height * ((Width * 8 + 31) / 32 * 4);
    bfr.bfOffBits = 54 + 1024;
    bir.biBitCount = 8;
    Height = bi.biHeight;
    Width = bi.biWidth;
    fwrite(&bfr, sizeof(bfr), 1, fres);
    fwrite(&bir, sizeof(bir), 1, fres);
    fwrite(&rgbquad, sizeof(rgbquad), 1, fres);//写入调色板

    for (j = 0; j < Height; j++) {
        for (i = 0; i < Width; i++) {
            if (fread(&pixel, 3, 1, fp)) {
                index = getIndex(pixel[2], pixel[1], pixel[0], rgbquad, 256);
            } else {
                //cout << ftell(fp) << endl;
                break;
            }
            fwrite(&index, 1, 1, fres);
        }
    }
    cout << "Convert to 8bits bmp success." << endl;
}

//24bits真彩色转灰度
void convert24bitsToGray(FILE* fp, FILE* fres){
    BITMAPFILEHEADER bf, bfr;
    BITMAPINFOHEADER bi, bir;
    int i, j;
    int Height, Width;
    BYTE pixel[4];
    int index, index2;

    initGray();
    fread(&bf, sizeof(bf), 1, fp);
    fread(&bi, sizeof(bi), 1, fp);
    bfr = bf;
    bir = bi;
    bfr.bfSize = 54 + 16 * 4 + Height * ((Width * 4 + 31) / 32 * 4);
    bfr.bfOffBits = 54 + 64;
    bir.biBitCount = 4;
    Height = bi.biHeight;
    Width = bi.biWidth;
    fwrite(&bfr, sizeof(bfr), 1, fres);
    fwrite(&bir, sizeof(bir), 1, fres);
    fwrite(&rgbquadGray, sizeof(rgbquadGray), 1, fres);//写入调色板

    for (j = 0; j < Height; j++) {
        for (i = 0; i < Width; i = i + 2) {
            fread(&pixel, 3, 1, fp);
            index = getGrayIndex(pixel[2], pixel[1], pixel[0], rgbquad16, 16);
            fread(&pixel, 3, 1, fp);
            index2 = getGrayIndex(pixel[2], pixel[1], pixel[0], rgbquad16, 16);
            index = (index << 4) | index2;
            fwrite(&index, 1, 1, fres);
        }
        while ((i / 2) % 4 != 0) {//4字节对齐
            index = 0;
            fwrite(&index, 1, 1, fres);
            i = i + 2;
        }
    }
    cout << "Convert to gray bmp success." << endl;
}

//16阶灰度图像转抖动黑白图像
void convertGrayToBlackWhite(FILE *fp, FILE *fres) {
    BITMAPFILEHEADER bf, bfr;
    BITMAPINFOHEADER bi, bir;
    int i, j;
    int Height, Width;
    BYTE pixel[4];
    int M[4][4] = {{0,  8,  2,  10},
                   {12, 4,  14, 6},
                   {3,  11, 1,  9},
                   {15, 7,  13, 5}};//抖动矩阵
    initGray();
    fread(&bf, sizeof(bf), 1, fp);
    fread(&bi, sizeof(bi), 1, fp);
    bfr = bf;
    bir = bi;
    Height = bi.biHeight;
    Width = bi.biWidth;
    bfr.bfSize = 54 + 16 * 4 + Height * 4 * ((Width * 4 * 4 + 31) / 32 * 4);
    bfr.bfOffBits = 54 + 64;
    bir.biHeight = 4 * Height;
    bir.biWidth = 4 * Width;
    bir.biBitCount = 4;
    fwrite(&bfr, sizeof(bfr), 1, fres);
    fwrite(&bir, sizeof(bir), 1, fres);
    fwrite(&rgbquadGray, sizeof(rgbquadGray), 1, fres);//写入调色板
    BYTE BlackWhite[2000][2000];//储存黑白图像
    BYTE pixel0, pixel1;
    int k, l;
    fseek(fp, bf.bfOffBits, 0);//因为没有读灰度图像的调色板，所以把指针移动到图像信息开始位置，这里有点坑
    for (j = 0; j < Height; j++) {
        for (i = 0; i < Width; i = i + 2) {
            fread(&pixel, 1, 1, fp);
            pixel0 = pixel[0] & 0xf0 >> 4;
            pixel1 = pixel[0] & 0x0f;
            for (l = 0; l < 4; l++) {
                for (k = 0; k < 4; k++) {
                    if (pixel0 >= M[k][l]) {
                        BlackWhite[j * 4 + k][i * 4 + l] = 0xf;
                    } else {
                        BlackWhite[j * 4 + k][i * 4 + l] = 0;
                    }
                }
            }
            for (l = 0; l < 4; l++) {
                for (k = 0; k < 4; k++) {
                    if (pixel1 >= M[k][l]) {
                        BlackWhite[j * 4 + k][(i + 1) * 4 + l] = 0xf;
                    } else {
                        BlackWhite[j * 4 + k][(i + 1) * 4 + l] = 0;
                    }
                }
            }
        }
        while ((i / 2) % 4 != 0) {//注意读取时的4字节对齐！格外注意
            fread(&pixel, 1, 1, fp);
            i = i + 2;
        }
    }

    //将黑白图写入BMP
    int index;
    for (j = 0; j < Height*4; j++) {
        for (i = 0; i < Width*4; i = i + 2) {
            index = (BlackWhite[j][i]<<4) | BlackWhite[j][i+1];
            fwrite(&index, 1, 1, fres);
        }
        while ((i / 2) % 4 != 0) {//4字节对齐
            index = 0;
            fwrite(&index, 1, 1, fres);
            i = i + 2;
        }
    }
    cout << "Convert to black white bmp success." << endl;

}

int main() {
    FILE *fp, *fres;
    BITMAPFILEHEADER bf;
    BITMAPINFOHEADER bi;
    char originalFile[100], resultFile[100];
    cout<<"Please input the original filename"<<endl;
    cin>>originalFile;
    cout<<"Please input the result filename"<<endl;
    cin>>resultFile;

    if ((fp = fopen(originalFile, "rb")) == NULL) {
        cout << "Open file failed." << endl;
    }
    if ((fres = fopen("24bits.bmp", "wb")) == NULL) {
        cout << "Create file failed." << endl;
    }



    fread(&bf, sizeof(bf), 1, fp);
    fread(&bi, sizeof(bi), 1, fp);

    if (bi.biBitCount == 8) {//256色
        convert8bitsTo24bits(fp, fres);
        printf("This is a 8 bits BMP picture.\n");
    } else if (bi.biBitCount == 4) {//16色
        convert4bitsTo24bits(fp, fres);
        printf("This is a 4 bits BMP picture.\n");
    } else if (bi.biBitCount == 24) {//24位真彩色
        printf("This is a 24 bits BMP picture.\n");
    }

//-------------------此条线以上部分将256色和16色输入图像统一转化为24bits真彩BMP，储存到result.bmp中
    cout << "Please choose the target type" << endl;
    cout << "----to 8 bits BMP : 0" << endl;
    cout << "----to 4 bits BMP : 1" << endl;
    cout << "----to 24 bits BMP : 2" << endl;
    cout << "----to Gray BMP : 3" << endl;
    cout << "----to BlackWhite BMP : 4" << endl;

    int target;
    cin >> target;
    fclose(fp);
    fclose(fres);

    if ((fp = fopen("24bits.bmp", "rb")) == NULL) {//打开真彩文件
        cout << "Open 24bits file failed." << endl;
    }
    if ((fres = fopen(resultFile, "wb")) == NULL) {//创建最终的目标文件
        cout << "Create file failed." << endl;
    }

    switch (target) {
        case (to8bits): {//将24bits真彩色转换为256色
            convert24bitsTo8bits(fp, fres);
            break;
        }
        case (to4bits): {//将24bits真彩色转换为16色
            convert24bitsTo4bits(fp, fres);
            break;
        }
        case (to24bits): {
            cout << "Convert to 24bits bmp success." << endl;
            break;
        }
        case (toGray): {//将24bits真彩色转换为16色灰度图
            convert24bitsToGray(fp, fres);
            break;
        }
        case (toBlackwhite): {//将24bits真彩图转化为抖动黑白图像
            FILE* ftmp;
            ftmp = fopen("tmpGray.bmp", "wb+");
            convert24bitsToGray(fp, ftmp);//先将真彩图转化为灰度图
            rewind(ftmp);
            convertGrayToBlackWhite(ftmp, fres);
            fclose(ftmp);
            break;
        default:
            break;
        }
    }

    fclose(fp);
    fclose(fres);
    return 0;
}