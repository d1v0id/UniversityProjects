#define MAXCOLORTC
#include "wingraph.h"

#define FUEL_READY WM_USER
#define VEH_ARRIVED_TO_FUEL WM_USER + 1
#define FUEL_UPLOADED WM_USER + 2
#define KETT_READY WM_USER + 3
#define VEH_ARRIVED_TO_KETT WM_USER + 4

const int cc = RGB(255, 40, 8);
const int cb = RGB(56, 56, 56);
const int ck = RGB(0, 0, 0);
const int cr = RGB(176, 30, 0);
const int cu = RGB(111, 111, 111);
const int cw = RGB(255, 255, 255);

int kettXCoords[4] = { 100, 150, 200, 250 };

unsigned long fpId;
unsigned long vhId;
unsigned long ktId[4];

void FuelProducer()
{
    MSG msg;
    PeekMessage(&msg, 0, 0, 0, PM_NOREMOVE);
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

        PostThreadMessage(vhId, FUEL_READY, 0, 0);
        GetMessage(&msg, 0, VEH_ARRIVED_TO_FUEL, VEH_ARRIVED_TO_FUEL);

        for (int i = valTopXCoord; i <= valBotXCoord; i += valStep) {
            setfillstyle(1, cw);
            bar(20, i, 60, i + 19);
            delay(150);
        }

        PostThreadMessage(vhId, FUEL_UPLOADED, volumeVal, 0);
    }
}

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
    MSG msg;
    PeekMessage(&msg, 0, 0, 0, PM_NOREMOVE);

    while (1) {
        GetMessage(&msg, 0, FUEL_READY, FUEL_READY);
        xCoord = MoveVehicleToLocation(-1, xCoord);
        PostThreadMessage(fpId, VEH_ARRIVED_TO_FUEL, 0, 0);

        GetMessage(&msg, 0, FUEL_UPLOADED, FUEL_UPLOADED);
        int volumeVal = msg.wParam;

        GetMessage(&msg, 0, KETT_READY, KETT_READY);
        int ktNum = msg.wParam;
        xCoord = MoveVehicleToLocation(ktNum, xCoord);
        PostThreadMessage(ktId[ktNum], VEH_ARRIVED_TO_KETT, volumeVal, 0);
    }
}

void Kettle(int num)
{
    MSG msg;
    PeekMessage(&msg, 0, 0, 0, PM_NOREMOVE);
    int valStep = 20;
    int valBotXCoord = 200;

    while (1) {
        PostThreadMessage(vhId, KETT_READY, num, 0);
        GetMessage(&msg, 0, VEH_ARRIVED_TO_KETT, VEH_ARRIVED_TO_KETT);
        int volumeVal = msg.wParam;
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
    }
}

void mainx()
{
    resize(400, 300);
    setfillstyle(1, cu);
    bar(20, 240, 370, 250);
    setfillstyle(1, cb);
    bar(20, 220, 60, 239);
    setfillstyle(1, cu);
    bar(330, 260, 370, 280);
    setfillstyle(1, cr);

    CreateThread(0, 0, (LPTHREAD_START_ROUTINE) FuelProducer, 0, 0, &fpId);
    CreateThread(0, 0, (LPTHREAD_START_ROUTINE) Vehicle, (LPVOID) 330, 0, &vhId);

    for (int i = 0; i < 4; i++) {
        bar(kettXCoords[i], 220, kettXCoords[i] + 40, 239);
        CreateThread(0, 0, (LPTHREAD_START_ROUTINE) Kettle, (LPVOID) i, 0, ktId + i);
    }
}
