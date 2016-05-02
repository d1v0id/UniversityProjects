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
unsigned char newPalette[16][4] = {
        { 0x0, 0x0, 0x0, 0x0 },
        { 0xff, 0xff, 0xff, 0x0 },
        { 0xff, 0x0, 0x0, 0x0 },
        { 0x0, 0xff, 0x0, 0x0 },
        { 0x0, 0x0, 0xff, 0x0 },
        { 0xff, 0xff, 0x0, 0x0 },
        { 0x0, 0xff, 0xff, 0x0 },
        { 0xff, 0x0, 0xff, 0x0 },
        { 0xc0, 0xc0, 0xc0, 0x0 },
        { 0x80, 0x80, 0x80, 0x0 },
        { 0x80, 0x0, 0x0, 0x0 },
        { 0x80, 0x80, 0x0, 0x0 },
        { 0x0, 0x80, 0x0, 0x0 },
        { 0x80, 0x0, 0x80, 0x0 },
        { 0x0, 0x80, 0x80, 0x0 },
        { 0x0, 0x0, 0x80, 0x0 }
};

typedef struct StPaletteFreq {
        unsigned int num;
        unsigned long count;
} TPaletteFreq;

TPaletteFreq paletteFreq[256];

FILE *f1;
FILE *f2;
//---------------------------------------------------------------------------
int main()
{
        f1 = fopen("image_256.bmp", "rb");
        f2 = fopen("image_16res.bmp", "wb");

        if (f1 != NULL) {
                fread(&head_file, sizeof(head_file), 1, f1);
                resize(head_file.biwidth * 2, head_file.biheight);
                long paletteSize = (head_file.bfoffbits - 54) / 4;

                if (head_file.bibitcount == 8) {
                        for (unsigned int i = 0; i < paletteSize; i++) {
                                fread(palette[i], 4, 1, f1);
                        }

                        char buffer[BUFSIZE];
                        long size;
                        long lineSize = head_file.biwidth; // нужно по границе 32
                        long modDiff = lineSize % 32;
                        if (modDiff != 0) {
                                lineSize += 32 - modDiff;
                        }

                        head_file.bibitcount = 4;
                        head_file.biclrused = 16;
                        head_file.biclrimp = 16;
                        head_file.bfoffbits = 16 * 4 + 54;

                        fwrite(&head_file, sizeof(head_file), 1, f2);

                        for (unsigned int i = 0; i < 16; i++) {
                                fwrite(newPalette[i], 4, 1, f2);
                        }

                        long lineNum = 0;
                        bool firstPart = true;
                        char part;
                        long sizeImage = 0;

                        while (size = fread(buffer, 1, lineSize, f1)) {
                                for (long colNum = 0; colNum < size; colNum++) {
                                        unsigned char colorNumChar = buffer[colNum];
                                        int colorNum = (int) colorNumChar;

                                        // find closest color from 16 bit table
                                        int red1 = palette[colorNum][2];
                                        int green1 = palette[colorNum][1];
                                        int blue1 = palette[colorNum][0];
                                        putpixel(colNum, head_file.biheight - lineNum, RGB(red1, green1, blue1));

                                        long delta = 10000000;
                                        int closestColorNum = -1;

                                        for (int i = 0; i < 16; i++) {
                                                int red2 = newPalette[i][2];
                                                int green2 = newPalette[i][1];
                                                int blue2 = newPalette[i][0];

                                                long tmpDelta = pow(red1 - red2, 2) + pow(green1 - green2, 2) + pow(blue1 - blue2, 2);

                                                if (tmpDelta < delta) {
                                                        delta = tmpDelta;
                                                        closestColorNum = i;
                                                }
                                        }

                                        if (closestColorNum != -1) {
                                                int red2 = newPalette[closestColorNum][2];
                                                int green2 = newPalette[closestColorNum][1];
                                                int blue2 = newPalette[closestColorNum][0];

                                                putpixel(colNum + head_file.biwidth, head_file.biheight - lineNum, RGB(red2, green2, blue2));

                                                if (firstPart) {
                                                        char t1 = closestColorNum << 4;
                                                        part = t1;
                                                }
                                                else {
                                                        char t2 = closestColorNum;
                                                        part = part | t2;
                                                        fwrite(&part, 1, 1, f2);
                                                        sizeImage++;
                                                }

                                                firstPart = !firstPart;
                                        }
                                }

                                lineNum++;
                        }

                        long fileSize = ftell(f2);
                        head_file.bfsize = fileSize;
                        head_file.bisizeimage = sizeImage;

                        fseek(f2, 0, SEEK_SET);
                        fwrite(&head_file, sizeof(head_file), 1, f2);
                }

                fcloseall();
        }

        return 0;
}
//---------------------------------------------------------------------------
