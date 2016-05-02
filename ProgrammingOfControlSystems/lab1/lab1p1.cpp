/*
 * Движение фигур реализовывается отдельными нитями.
 * Работа нити завершается, когда фигура достигает границы окна.
 *
 * Рисовать одновременно движущиеся фигуры:
 * • окружность (движение сверху вниз, скорость 10 точек/с);
 * • окружность (движение сверху вниз, скорость 20 точек/с);
 * • квадрат (движение слева направо, скорость 20 точек/с);
 * • квадрат (движение справа налево, скорость 20 точек/с).
 *
 * Когда любая из окружностей пересекает линию у = 200,
 * размер квадратов изменяется.
 */
#define MAXCOLORTC

#include "wingraph.h"
#include "shared.h"

#define LTRMOVE 2
#define RTLMOVE 3
#define LINE_Y_COORD 200
#define THREADS_CNT 4
#define CIRCLE_RADIUS 30
#define BLACK_COLOR RGB(0, 0, 0)
#define GREEN_COLOR RGB(0, 200, 0)
#define WHITE_COLOR RGB(255, 255, 255)

SharedData *shrData;
bool bThRunning[THREADS_CNT];
bool bThReset[THREADS_CNT];
bool bRecSizeChanges[THREADS_CNT];
bool bRecSizeChanged;

struct DrawData {
    int nThread;
    int x;
    int y;
    int speed;
    int direction;
};

void DrawSpecificLine()
{
    line(0, LINE_Y_COORD, shrData->nWidth, LINE_Y_COORD, BLACK_COLOR);
}

void MovingCircle(DrawData *dData)
{
    int moveDelta = 1;

    while ((shrData->nHeight - dData->y - CIRCLE_RADIUS - 10) > moveDelta) {
        if (shrData->stop) {
            break;
        }

        if (bThReset[dData->nThread]) {
            bThReset[dData->nThread] = false;
            moveDelta = 1;
        }

        int newYCoord = dData->y + moveDelta;

        if ((newYCoord + CIRCLE_RADIUS) == LINE_Y_COORD) {
            bRecSizeChanged = true;
        }

        if (((newYCoord + CIRCLE_RADIUS) >= LINE_Y_COORD) && ((newYCoord - CIRCLE_RADIUS - 1) <= LINE_Y_COORD)) {
            DrawSpecificLine();
        }

        bool colorChanged = shrData->chColor[dData->nThread];
        circle(dData->x, newYCoord, CIRCLE_RADIUS, colorChanged ? BLACK_COLOR : GREEN_COLOR);
        delay(dData->speed);
        circle(dData->x, newYCoord, CIRCLE_RADIUS, WHITE_COLOR);
        moveDelta++;
    }

    bThRunning[dData->nThread] = false;
}

void MovingRectangle(DrawData *dData)
{
    int nRectWidth = 50;
    int nRectHeight = 50;
    int recSizeType = 0;
    int moveDelta = 1;

    while (1) {
        if (((dData->direction == LTRMOVE) && ((dData->x + nRectWidth + moveDelta + 10) >= shrData->nWidth)) ||
                ((dData->direction == RTLMOVE) && (dData->x <= moveDelta)) || shrData->stop) {
            break;
        }

        if (bThReset[dData->nThread]) {
            bThReset[dData->nThread] = false;
            moveDelta = 1;
        }

        if (bRecSizeChanged) {
            if (recSizeType == 0) {
                nRectWidth -= 20;
                nRectHeight -= 20;
                recSizeType = 1;
            }
            else if (recSizeType == 1) {
                nRectWidth += 20;
                nRectHeight += 20;
                recSizeType = 0;
            }
            
            bRecSizeChanges[dData->nThread] = true;
        }

        int newX1Coord;
        int newX2Coord;

        switch (dData->direction) {
            case LTRMOVE:
                newX1Coord = dData->x + moveDelta;
                newX2Coord = dData->x + nRectWidth + moveDelta;
                break;

            case RTLMOVE:
                newX1Coord = dData->x - moveDelta; 
                newX2Coord = dData->x + nRectWidth - moveDelta;
        }

        bool colorChanged = shrData->chColor[dData->nThread];
        rectangle(newX1Coord, dData->y, newX2Coord, dData->y + nRectHeight, colorChanged ? BLACK_COLOR : GREEN_COLOR);
        delay(dData->speed);
        rectangle(newX1Coord, dData->y, newX2Coord, dData->y + nRectHeight, WHITE_COLOR);
        moveDelta++;
    }

    bThRunning[dData->nThread] = false;
    bRecSizeChanges[dData->nThread] = true;
}

void StartMovingFigure(int thrd, int startX, int startY, int moveSpeed, int moveDirection, LPTHREAD_START_ROUTINE func)
{
    DrawData *dData = new DrawData;
    dData->nThread = thrd;
    dData->x = startX;
    dData->y = startY;
    dData->speed = moveSpeed;
    dData->direction = moveDirection;
    CreateThread(0, 0, func, (LPVOID) dData, 0, 0);
}

void mainx()
{
    char envVarBuf[40];
    HANDLE hMap;

    if (GetEnvironmentVariable("hMap", envVarBuf, 40)) {
        hMap = (HANDLE) atoi(envVarBuf);
    }
    else {
        ExitProcess(1);
    }

    shrData = (SharedData *) MapViewOfFile(hMap, FILE_MAP_WRITE, 0, 0, sizeof(SharedData));

    if (shrData == 0) {
        ExitProcess(2);
    }

    resize(shrData->nWidth, shrData->nHeight);
    DrawSpecificLine();

    for (int i = 0; i < THREADS_CNT; i++) {
        bThRunning[i] = true;
        bThReset[i] = false;
        bRecSizeChanges[i] = false;
    }

    bRecSizeChanged = false;

    StartMovingFigure(0, 100, 100, 100, NULL, (LPTHREAD_START_ROUTINE) MovingCircle); // 10 pixels/sec
    StartMovingFigure(1, 200, 100, 50, NULL, (LPTHREAD_START_ROUTINE) MovingCircle); // 20 pixels/sec
    StartMovingFigure(2, 300, 0, 50, LTRMOVE, (LPTHREAD_START_ROUTINE) MovingRectangle); // 20 pixels/sec
    StartMovingFigure(3, 300, 100, 50, RTLMOVE, (LPTHREAD_START_ROUTINE) MovingRectangle); // 20 pixels/sec

    while (1) {
        if (!bThRunning[0] && !bThRunning[1] && !bThRunning[2] && !bThRunning[3]) {
            break;
        }

        if (bRecSizeChanges[2] && bRecSizeChanges[3]) {
            bRecSizeChanged = false;

            if (bThRunning[2]) {
                bRecSizeChanges[2] = false;
            }

            if (bThRunning[3]) {
                bRecSizeChanges[3] = false;
            }
        }

        if (shrData->reset) {
            shrData->reset = false;

            for (int i = 0; i < THREADS_CNT; i++) {
                bThReset[i] = true;
            }
        }
    }

    UnmapViewOfFile(shrData);
    CloseHandle(hMap);
    ExitProcess(0);
}
