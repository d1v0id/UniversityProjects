#define MAXCOLORTC
#include "wingraph.h"

#define FUEL_READY 0
#define FUEL_UPLOADED 1

const int cc = RGB(255, 40, 8);
const int cb = RGB(56, 56, 56);
const int ck = RGB(0, 0, 0);
const int cr = RGB(176, 30, 0);
const int cu = RGB(111, 111, 111);
const int cw = RGB(255, 255, 255);

struct LongMsg {
    int volume;
    int cmd;
};

void FuelProducer()
{
    HANDLE chan;
    LongMsg m;
    unsigned long foo;
    chan = CreateNamedPipe("\\\\.\\pipe\\lab2p", PIPE_ACCESS_DUPLEX,
            PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE, 1, sizeof(m), 4, 0, 0);

    ConnectNamedPipe(chan, 0);

    randomize();
    int valStep = 20;
    int valBotXCoord = 200;

    while (1) {
        int volumeVal = random(9) + 1;
        int delayVal = volumeVal * 50;
        
        int valTopXCoord = (valBotXCoord - valStep * volumeVal);

        for (int i = valBotXCoord; i >= valTopXCoord; i -= valStep) {
            setfillstyle(1, ck);
            bar(20, i, 60, i + 19);
            delay(delayVal);
        }

        m.cmd = FUEL_READY;
        TransactNamedPipe(chan, &m, sizeof(m), &foo, 4, &foo, 0);

        for (int i = valTopXCoord; i <= valBotXCoord; i += valStep) {
            setfillstyle(1, cw);
            bar(20, i, 60, i + 19);
            delay(150);
        }

        m.volume = volumeVal;
        m.cmd = FUEL_UPLOADED;
        TransactNamedPipe(chan, &m, sizeof(m), &foo, 4, &foo, 0);
    }
}

void mainx()
{
    resize(400, 300);
    setfillstyle(1, cu);
    bar(20, 240, 370, 250);
    setfillstyle(1, cb);
    bar(20, 220, 60, 239);

    FuelProducer();
    ExitProcess(0);
}
