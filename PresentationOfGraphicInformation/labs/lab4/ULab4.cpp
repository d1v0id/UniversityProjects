//---------------------------------------------------------------------------
#pragma hdrstop
#include <stdio.h>
#include <windows.h>

#define BUFSIZE 4098
#define LOGOSIZE 64

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
} head_file, head_logo;

FILE *f1;
FILE *f2;
FILE *fLogo;

void drawTCLogo()
{
        char buffer[BUFSIZE];
        char logoBuffer[BUFSIZE];
        char logoBitmap[LOGOSIZE][LOGOSIZE * 3];
        long size;
        long logoSize;
        long lineSize = 3 * head_file.biwidth; // нужно по границе 32
        long logoLineSize = 3 * head_logo.biwidth;
        long modDiff = lineSize % 32;
        if (modDiff != 0) {
                lineSize += 32 - modDiff;
        }

        modDiff = logoLineSize % 32;
        if (modDiff != 0) {
                logoLineSize += 32 - modDiff;
        }

        long lineNum = 0;
        long logoLineNum = 0;

        while (logoSize = fread(logoBuffer, 1, logoLineSize, fLogo)) {
                for (long colNum = 0; colNum < (3 * head_logo.biwidth); colNum++) {
                        logoBitmap[logoLineNum][colNum] = logoBuffer[colNum];
                }

                logoLineNum++;
        }

        long lLineNum = 0;

        while (size = fread(buffer, 1, lineSize, f1)) {
                long lColNum = 0;

                if ((lineNum >= 0) && (lineNum < LOGOSIZE)) {
                        lLineNum++;
                }

                for (long colNum = 0; colNum < size; colNum++) {
                        if (((colNum >= 0) && (colNum <= (LOGOSIZE * 3))) &&
                                        ((lineNum >= 0) && (lineNum < LOGOSIZE))) {
                                buffer[colNum] = logoBitmap[lLineNum][lColNum];
                                lColNum++;
                        }
                }

                fwrite(buffer, 1, size, f2);
                lineNum++;
        }
}
//---------------------------------------------------------------------------
#pragma argsused
int main(int argc, char* argv[])
{
        f1 = fopen("image_tc.bmp", "rb");
        f2 = fopen("image_w_logo.bmp", "wb");
        fLogo = fopen("logo.bmp", "rb");

        if (f1 != NULL) {
                fread(&head_file, sizeof(head_file), 1, f1);
                fwrite(&head_file, sizeof(head_file), 1, f2);
                fread(&head_logo, sizeof(head_logo), 1, fLogo);

                if ((head_file.biwidth < 50) || (head_file.biheight < 50)) {
                        printf("Source image smaller than 50x50");
                        return 0;
                }

                switch (head_file.bibitcount) {
                case 24:
                        drawTCLogo();
                        break;
                default:
                        printf("Unsupported image color type.");
                }

                fcloseall();
        }

        return 0;
}
//---------------------------------------------------------------------------
 