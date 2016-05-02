//---------------------------------------------------------------------------
#pragma hdrstop
#include <stdio.h>
#include <windows.h>

#define BUFSIZE 1024

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
//---------------------------------------------------------------------------
#pragma argsused
int main(int argc, char* argv[])
{
        if (argc != 3) {
                printf("Usage lab1 <src-bmp-file> <dst-bmp-file>");
                return 0;
        }

        FILE *f1;
        FILE *f2;
        int n;
        char buffer[BUFSIZE];
        f1 = fopen(argv[1], "rb");
        f2 = fopen(argv[2], "wb");

        if (f1 != NULL) {
                fread(&head_file, sizeof(head_file), 1, f1);
                fwrite(&head_file, sizeof(head_file), 1, f2);
                size_t paletteSize = (head_file.bfoffbits - 54) / 4;
                printf("Width: %d\n", head_file.biwidth);
                printf("Height: %d\n", head_file.biheight);
                printf("SizeImage: %d\n", head_file.bisizeimage);
                printf("ClrUsed: %d\n", head_file.biclrused);

                for (unsigned int i = 0; i < paletteSize; i++) {
                        fread(palette[i], 4, 1, f1);

                        byte redVal = palette[i][0];
                        byte greenVal = palette[i][1];
                        byte blueVal = palette[i][2];
                        byte value = (redVal + greenVal + blueVal) / 3;

                        palette[i][0] = value;
                        palette[i][1] = value;
                        palette[i][2] = value;

                        fwrite(palette[i], 4, 1, f2);
                }

                size_t size;
                while (size = fread(buffer, 1, BUFSIZE, f1)) {
                        fwrite(buffer, 1, size, f2);
                }

                fcloseall();
        }

        return 0;
}
//---------------------------------------------------------------------------
