//---------------------------------------------------------------------------
#define MAXCOLORTC
#include "wingraph.h"

#define BUFSIZE 4098

struct head {
        short bftype;
        long  bfsize;
        short rez1, rez2;
        long  bfoffbits;
        long  bisize;
        long  biwidth;
        long  biheight;
        short biplanes;
        short bibitcount;
        long  bicompression;
        long  bisizeimage;
        long  bix;
        long  biy;
        long  biclrused;
        long  biclrimp;
} head_file;

unsigned char palette[256][4];
FILE *f;

void Draw16Image()
{
        unsigned char buffer[BUFSIZE];
        long size;
        long lineSize = head_file.biwidth / 2; // нужно по границе 32
        long modDiff = lineSize % 32;
        if (modDiff != 0) {
                lineSize += 32 - modDiff;
        }

        long lineNum = 0;

        while (size = fread(buffer, 1, lineSize, f)) {
                for (long colNum = 0, i = 0; colNum < size; colNum++, i += 2) {
                        unsigned char colorNumChar = buffer[colNum];
                        unsigned char colorNum1 = colorNumChar & 0xf;
                        unsigned char colorNum2 = colorNumChar & 0x0f;
                        int iColorNum1 = (int) colorNum1;
                        int iColorNum2 = (int) colorNum2;
                        int color1 = RGB(palette[iColorNum1][2], palette[iColorNum1][1], palette[iColorNum1][0]);
                        int color2 = RGB(palette[iColorNum2][2], palette[iColorNum2][1], palette[iColorNum2][0]);
                        putpixel(i, head_file.biheight - lineNum, color1);
                        putpixel(i + 1, head_file.biheight - lineNum, color1);
                }
                lineNum++;
        }
}

void Draw256Image()
{
        unsigned char buffer[BUFSIZE];
        long size;
        long lineSize = head_file.biwidth; // нужно по границе 32
        long modDiff = lineSize % 32;
        if (modDiff != 0) {
                lineSize += 32 - modDiff;
        }

        long lineNum = 0;

        while (size = fread(buffer, 1, lineSize, f)) {
                for (long colNum = 0; colNum < size; colNum++) {
                        unsigned char colorNumChar = buffer[colNum];
                        int colorNum = (int) colorNumChar;
                        int color = RGB(palette[colorNum][2], palette[colorNum][1], palette[colorNum][0]);
                        putpixel(colNum, head_file.biheight - lineNum, color);
                }
                lineNum++;
        }
}

void DrawTCImage()
{
        char buffer[BUFSIZE];
        long size;
        long lineSize = 3 * head_file.biwidth; // нужно по границе 32
        long modDiff = lineSize % 32;
        if (modDiff != 0) {
                lineSize += 32 - modDiff;
        }

        long lineNum = 0;

        while (size = fread(buffer, 1, lineSize, f)) {
                for (long i = 0, colNum = 0; i < size; i += 3, colNum++) {
                        int color = RGB(buffer[i + 2], buffer[i + 1], buffer[i]);
                        putpixel(colNum, head_file.biheight - lineNum, color);
                }
                lineNum++;
        }
}
//---------------------------------------------------------------------------
int main()
{
        f = fopen("image_tc.bmp", "rb");

        if (f != NULL) {
                fread(&head_file, sizeof(head_file), 1, f);
                resize(head_file.biwidth, head_file.biheight);
                size_t paletteSize = (head_file.bfoffbits - 54) / 4;

                switch (head_file.bibitcount) {
                case 4:
                        for (unsigned int i = 0; i < paletteSize; i++) {
                                fread(palette[i], 4, 1, f);
                        }

                        Draw16Image();
                        break;

                case 8:
                        for (unsigned int i = 0; i < paletteSize; i++) {
                                fread(palette[i], 4, 1, f);
                        }

                        Draw256Image();
                        break;

                case 24:
                        DrawTCImage();
                        break;

                default:
                        printf("Unsupported image color type.");
                }

                fcloseall();
        }

        return 0;
}
//---------------------------------------------------------------------------
