#define MAXCOLORTC
#include "wingraph.h"

#define FUEL_READY 0
#define FUEL_UPLOADED 1
#define KETT_READY 2
#define SYNC 3
#define KETT_CNT 4

const int cc = RGB(255, 40, 8);
const int cb = RGB(56, 56, 56);
const int ck = RGB(0, 0, 0);
const int cr = RGB(176, 30, 0);
const int cu = RGB(111, 111, 111);
const int cw = RGB(255, 255, 255);

const int kettXCoords[4] = { 100, 150, 200, 250 };

struct LongMsg {
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
    delay(50);

    return xCoord;
}

void Vehicle(int xCoord)
{
    LongMsg m;
    LongMsg ktM;
    unsigned long foo;
    HANDLE chan;
    chan = CreateFile("\\\\.\\pipe\\lab2p", GENERIC_READ | GENERIC_WRITE, 0, 0,
            OPEN_EXISTING, 0, 0);

    while (1) {
        ReadFile(chan, &m, sizeof(m), &foo, 0);

        if (m.cmd == FUEL_READY) {
            xCoord = MoveVehicleToLocation(-1, xCoord);
        }
        else {
            break;
        }

        WriteFile(chan, &foo, 4, &foo, 0);
        ReadFile(chan, &m, sizeof(m), &foo, 0);

        if (m.cmd == FUEL_UPLOADED) {
            WriteFile(chan, &foo, 4, &foo, 0);
            int ktNum = 0;

            while (1) {
                unsigned long s;
                char buf[20];
                char ktPipeName[100];
                char *numStrPres = itoa(ktNum, buf, 10);
                strcpy(ktPipeName, "\\\\.\\pipe\\lab2p2Kt");
                strcat(ktPipeName, numStrPres);
                HANDLE chanKt = CreateFile(ktPipeName, GENERIC_READ | GENERIC_WRITE,
                        0, 0, OPEN_EXISTING, 0, 0);
                ReadFile(chanKt, &ktM, sizeof(ktM), &s, 0);

                if (s > 0) {
                    if (ktM.cmd == KETT_READY) {
                        xCoord = MoveVehicleToLocation(ktNum, xCoord);
                        ktM.volume = m.volume;
                        WriteFile(chanKt, &ktM, sizeof(ktM), &foo, 0);
                        break;
                    }
                }

                ktNum++;

                if (ktNum == KETT_CNT) {
                    ktNum = 0;
                }
            }
        }
        else {
            break;
        }
    }

    ExitProcess(0);
}

void Kettle(int num)
{
    LongMsg ktM;
    unsigned long foo;
    int valStep = 20;
    int valBotXCoord = 200;
    char buf[20];

    while (1) {
        char buf[20];
        char ktPipeName[100];
        char *numStrPres = itoa(num, buf, 10);
        strcpy(ktPipeName, "\\\\.\\pipe\\lab2p2Kt");
        strcat(ktPipeName, numStrPres);
        HANDLE chan = CreateNamedPipe(ktPipeName, PIPE_ACCESS_DUPLEX,
                PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE, 1, sizeof(ktM), 4, 0, 0);

        ConnectNamedPipe(chan, 0);
        ktM.cmd = KETT_READY;
        WriteFile(chan, &ktM, sizeof(ktM), &foo, 0);
        ReadFile(chan, &ktM, sizeof(ktM), &foo, 0);
        CloseHandle(chan);

        int volumeVal = ktM.volume;
        int delayVal = volumeVal * 850;
        int valTopXCoord = (valBotXCoord - valStep * volumeVal);

        for (int i = valBotXCoord; i >= valTopXCoord; i -= valStep) {
            setfillstyle(1, cc);
            bar(kettXCoords[num], i, kettXCoords[num] + 40, i + 19);
            delay(150);
        }

        for (int i = valTopXCoord; i <= valBotXCoord; i += valStep) {
            delay(delayVal);
            setfillstyle(1, cw);
            bar(kettXCoords[num], i, kettXCoords[num] + 40, i + 19);
        }

        delay(50);
    }
}

void mainx()
{
    resize(500, 300);
    setfillstyle(1, cu);
    bar(20, 240, 370, 250);
    setfillstyle(1, cb);
    bar(20, 220, 60, 239);
    setfillstyle(1, cu);
    bar(330, 260, 370, 280);
    setfillstyle(1, cr);

    CreateThread(0, 0, (LPTHREAD_START_ROUTINE) Vehicle, (LPVOID) 330, 0, 0);

    for (int i = 0; i < KETT_CNT; i++) {
        bar(kettXCoords[i], 220, kettXCoords[i] + 40, 239);
        CreateThread(0, 0, (LPTHREAD_START_ROUTINE) Kettle, (LPVOID) i, 0, 0);
    }
}
