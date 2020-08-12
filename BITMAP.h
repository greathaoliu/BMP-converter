typedef unsigned char	BYTE;	/*1 byte*/
typedef unsigned short	WORD;	/*2 bytes*/
typedef unsigned int	DWORD;	/*4 bytes*/

#pragma pack(2)
typedef struct tagBITMAPFILEHEADER
{
	WORD	bfType;		/*文件标识 BM*/
	DWORD	bfSize;		/*文件总长度*/
	WORD	bfReserved1;/*保留，总为0*/
	WORD	bfReserved2;/*保留，总为0*/
	DWORD	bfOffBits;	/*偏移量*/
}
BITMAPFILEHEADER;
/*
typedef struct tagBITMAPINFO
{
	BITMAPINFOHEADER	bmiHeader;
	RGBQUAD				bmiColors[1];
}BITMAPINFO;
*/
#pragma pack(2)
typedef struct tagBITMAPINFOHEADER
{
	DWORD biSize;	/*BITMAPINFOHEADER的大小*/
	DWORD biWidth;	/*位图宽度*/
	DWORD biHeight;	/*位图高度*/
	WORD  biPlanes;	/*颜色位面数，总为1*/
	WORD  biBitCount;	/*每象数颜色位（1，2，4，8，24）*/
	DWORD bmCompression;/*压缩模式（0=无）*/
	DWORD biSizelmage;	/*位图大小*/
	DWORD biXPelsPerMeter;	/*水平分辨率*/
	DWORD biYPelsPerMeter;	/*垂直分辨率*/
	DWORD biClrUsed;		/*所使用的颜色数*/
	DWORD beClrlmportant;	/*重要颜色数*/
}
BITMAPINFOHEADER;

#pragma pack(2)
typedef struct tagRGBQUAD
{
	BYTE	rgbBlue;
	BYTE	rgbGreen;
	BYTE	rgbRed;
	BYTE	rgbReserved;
}
RGBQUAD;
