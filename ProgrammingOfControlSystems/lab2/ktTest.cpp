#define MAXCOLORTC
#include "wingraph.h"

const int cc = RGB(255, 40, 8);
const int cb = RGB(56, 56, 56);
const int ck = RGB(0, 0, 0);
const int cr = RGB(176, 30, 0);
const int cu = RGB(111, 111, 111);
const int cw = RGB(255, 255, 255);

const int kettXCoords[4] = { 100, 150, 200, 250 };

unsigned long ktId[2];

struct KtArg {
    HANDLE ktChan;
    int num;
};

struct LongMsg {
    int ktNum;
    int volume;
    int cmd;
};

int MoveVehicleToLocation(int locType, int xCoord)
{
    int vehStep = 20;
    int moveDelta = xCoord;
    bool moveToFuel = (locType == -1);

    while ( (moveToFuel && (moveDelta >= 20)) ||
            (!moveToFuel && (moveDelta <= kettXCoords[locType])) ) {

        setfillstyle(1, cu);
        bar(moveDelta, 260, moveDelta + 40, 280);
        delay(50);
        setfillstyle(1, cw);
        bar(moveDelta, 260, moveDelta + 40, 280);

        if (moveToFuel) {
            moveDelta -= vehStep;
        }
        else {
            moveDelta += vehStep;
        }
    }

    setfillstyle(1, cu);
    xCoord = moveToFuel ? 20 : kettXCoords[locType];
    bar(xCoord, 260, xCoord + 40, 280);

    return xCoord;
}

void Vehicle(int xCoord)
{
    HANDLE ktChan;
    LongMsg ktM;
    unsigned long foo;
    ktChan = CreateNamedPipe("\\\\.\\pipe\\lab2pKt",
            PIPE_ACCESS_DUPLEX,
            PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE,
            1, sizeof(ktM), 4, 0, 0);

    ConnectNamedPipe(ktChan, 0);
    outtextxy(0, 10, "conn", cw);

    while (1) {
        ReadFile(ktChan, &ktM, sizeof(ktM), &foo, 0);
        int num = ktM.ktNum;
        if (num == 0) {
            outtextxy(0, 40, "read0", cw);
        }
        else if (num == 1) {
            outtextxy(0, 70, "read1", cw);
        }
    }
}

void Kettle(KtArg *ktArg)
{
    LongMsg ktM;
    unsigned long foo;

    ktM.ktNum = ktArg->num;

    if (ktM.ktNum == 0) {
        outtextxy(0, 100, "kett0", cw);
    }
    else if (ktM.ktNum == 1) {
        outtextxy(0, 130, "kett1", cw);
    }

    WriteFile(ktArg->ktChan, &ktM, sizeof(ktM), &foo, 0);

    while (1) {
        delay(50);
    }
}

void mainx()
{
    resize(400, 300);
    setfillstyle(1, cu);
    bar(20, 240, 370, 250);
    setfillstyle(1, cb);
    bar(20, 220, 60, 239);
    setfillstyle(1, cr);

    CreateThread(0, 0, (LPTHREAD_START_ROUTINE) Vehicle, (LPVOID) 330, 0, 0);

    KtArg *ktArg1 = new KtArg;

    HANDLE ktChan;
    ktChan = CreateFile("\\\\.\\pipe\\lab2pKt",
            GENERIC_READ | GENERIC_WRITE,
            0, 0,
            OPEN_EXISTING,
            0, 0);

    ktArg1->ktChan = ktChan;
    ktArg1->num = 0;
    bar(kettXCoords[0], 220, kettXCoords[0] + 40, 239);
    CreateThread(0, 0, (LPTHREAD_START_ROUTINE) Kettle, (LPVOID) ktArg1, 0, 0);

    KtArg *ktArg2 = new KtArg;
    ktArg2->ktChan = ktChan;
    ktArg2->num = 1;
    bar(kettXCoords[1], 220, kettXCoords[1] + 40, 239);
    CreateThread(0, 0, (LPTHREAD_START_ROUTINE) Kettle, (LPVOID) ktArg2, 0, 0);
}
