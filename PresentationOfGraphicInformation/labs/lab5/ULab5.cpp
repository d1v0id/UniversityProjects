//---------------------------------------------------------------------------
#define MAXCOLORTC
#include "wingraph.h"

#define BUFSIZE 4098

typedef struct TPCXHeaderStruct {
        unsigned char ID;
        unsigned char Version;
        unsigned char Coding;
        unsigned char BitPerPixel;
        unsigned short XMin;
        unsigned short YMin;
        unsigned short XMax;
        unsigned short YMax;
        unsigned short HRes;
        unsigned short VRes;
        unsigned char Palette[48];
        unsigned char Reserved;
        unsigned char Planes;
        unsigned short BytePerLine;
        unsigned short PaletteInfo;
        unsigned short HScreenSize;
        unsigned short VScreenSize;
        unsigned char Filler[54];
} TPCXHeader;

typedef struct TPaletteStruct {
  unsigned char Red;
  unsigned char Green;
  unsigned char Blue;
} TPalette;

TPCXHeader PCXHeader;
TPalette PCXPalette[256];
FILE *f;
//---------------------------------------------------------------------------
int main()
{
        f = fopen("image256.pcx", "rb");
        unsigned char buffer;
        int runlen;

        if (f != NULL) {
                fread(&PCXHeader, sizeof(TPCXHeader), 1, f);
                unsigned short xSize = PCXHeader.XMax - PCXHeader.XMin + 1;
                unsigned short ySize = PCXHeader.YMax - PCXHeader.YMin + 1;
                resize(xSize, ySize);
                unsigned short totalBytes = PCXHeader.Planes * PCXHeader.BytePerLine;

                if (((int) PCXHeader.Version == 5) || ((int) PCXHeader.BitPerPixel == 8)) {
                        fseek(f, -769L, SEEK_END);
                        fread(&buffer, 1, 1, f);

                        if (buffer == 0x0c) {
                                fread(PCXPalette, sizeof(PCXPalette), 1, f);
                                unsigned short headSize = sizeof(PCXHeader);
                                fseek(f, headSize, SEEK_SET);

                                bool drawing = true;
                                int x = 0;
                                int y = 0;

                                while (drawing) {
                                        fread(&buffer, 1, 1, f);

                                        if ((buffer & 0xc0) == 0xc0) {
                                                runlen = (int) (buffer & 0x3f);
                                                fread(&buffer, 1, 1, f);
                                        }
                                        else {
                                                runlen = 1;
                                        }

                                        do {
                                                int colorNum = (int) buffer;
                                                int color = RGB(PCXPalette[colorNum].Red, PCXPalette[colorNum].Green, PCXPalette[colorNum].Blue);
                                                putpixel(x, y, color);

                                                if (++x >= totalBytes) {
                                                        x = 0;
                                                        y++;
                                                }

                                                if (y >= ySize) {
                                                        drawing = false;
                                                }
                                        } while (drawing && (--runlen > 0));
                                }
                        }
                }

                fcloseall();
        }

        return 0;
}
//---------------------------------------------------------------------------
