//---------------------------------------------------------------------------
#pragma hdrstop
#include <stdio.h>
#include <windows.h>

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

FILE *f1;
FILE *f2;
//---------------------------------------------------------------------------
char GenerateRandomColor()
{
        randomize();
        return (char) (random(255) + 1);
}

void drawBorder(int pixelSize)
{
        char color = GenerateRandomColor();
        char buffer[BUFSIZE];
        size_t size;
        long lineSize = pixelSize * head_file.biwidth; // нужно по границе 32
        long modDiff = lineSize % 32;
        if (modDiff != 0) {
                lineSize += 32 - modDiff;
        }

        long lineNum = 0;

        while (size = fread(buffer, 1, lineSize, f1)) {
                if (lineNum < 15) {
                        for (long i = 0; i < lineSize; i++) {
                                buffer[i] = color;
                        }
                }

                for (long i = 0; i < 15 * pixelSize; i++) {
                        buffer[i] = color;
                }

                long xSeek = pixelSize * head_file.biwidth;

                for (long i = xSeek - (pixelSize * 15); i < xSeek; i++) {
                        buffer[i] = color;
                }

                if (lineNum >= (head_file.biheight - 15)) {
                        for (long i = 0; i < lineSize; i++) {
                                buffer[i] = color;
                        }
                }

                fwrite(buffer, 1, size, f2);
                lineNum++;
        }
}

void drawBorder16Colors()
{
        char color = GenerateRandomColor();
        color = color & 0xf | ((color & 0xf) << 4);

        char buffer[BUFSIZE];
        long size;
        long lineSize = head_file.biwidth / 2; // нужно по границе 32 (внутри байта два пикселя)
        long modDiff = lineSize % 32;
        if (modDiff != 0) {
                lineSize += 32 - modDiff;
        }

        long lineNum = 0;

        while (size = fread(buffer, 1, lineSize, f1)) {
                if (lineNum < 15) {
                        for (long i = 0; i < lineSize; i++) {
                                buffer[i] = color; // 0x11
                        }
                }

                for (int i = 0; i < 7; i++) {
                        buffer[i] = color;
                }

                char t1 = (color & 0xf) << 4;
                char t2 = buffer[7] & 0x0f;
                buffer[7] = t1 | t2;

                long xSeek = head_file.biwidth / 2;

                t1 = (buffer[xSeek - 8] & 0xf) << 4;
                t2 = color & 0xf;
                buffer[xSeek - 8] = t1 | t2;

                for (long i = xSeek - 7; i < xSeek; i++) {
                        buffer[i] = color;
                }

                if (lineNum >= (head_file.biheight - 15)) {
                        for (long i = 0; i < lineSize; i++) {
                                buffer[i] = color;
                        }
                }

                fwrite(buffer, 1, size, f2);
                lineNum++;
        }
}

#pragma argsused
int main(int argc, char* argv[])
{
        if (argc != 3) {
                printf("Usage lab2 <src-bmp-file> <dst-bmp-file>");
                return 0;
        }

        int n;
        f1 = fopen(argv[1], "rb");
        f2 = fopen(argv[2], "wb");

        if (f1 != NULL) {
                fread(&head_file, sizeof(head_file), 1, f1);
                fwrite(&head_file, sizeof(head_file), 1, f2);
                size_t paletteSize = (head_file.bfoffbits - 54) / 4;

                if ((head_file.biwidth < 30) || (head_file.biheight < 30)) {
                        printf("Source image smaller than 30x30");
                        return 0;
                }

                switch (head_file.bibitcount) {
                case 4:
                        for (unsigned int i = 0; i < paletteSize; i++) {
                                fread(palette[i], 4, 1, f1);
                                fwrite(palette[i], 4, 1, f2);
                        }

                        drawBorder16Colors();
                        break;

                case 8:
                        for (unsigned int i = 0; i < paletteSize; i++) {
                                fread(palette[i], 4, 1, f1);
                                fwrite(palette[i], 4, 1, f2);
                        }

                        drawBorder(1);
                        break;

                case 16:
                        drawBorder(2);
                        break;

                case 24:
                        drawBorder(3);
                        break;
                   
                default:
                        printf("Unsupported image color type.");
                        return 0;
                }

                fcloseall();
        }

        return 0;
}
//---------------------------------------------------------------------------
 