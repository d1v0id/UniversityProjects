/*
 * При запуске приложения в командной строке указывается размер окна,
 * который должен быть установлен в программе рисования.
 *
 * c = Изменение цвета для указанной пользователем фигуры;
 * r = Установка всех фигур в начальное положение.
 *
 * При завершении консольного приложения окно программы рисования закрывается.
 */
#include <windows.h>
#include <stdio.h>
#include "shared.h"

int main(int argc, char *argv[])
{
    if (argc != 3) {
        printf("Usage: lab1p2 <WIDTH> <HEIGHT>");
        return 1;
    }

    SECURITY_ATTRIBUTES sa;
    sa.nLength = sizeof(sa);
    sa.lpSecurityDescriptor = 0;
    sa.bInheritHandle = TRUE;

    HANDLE hMap = CreateFileMapping((HANDLE) -1, &sa, PAGE_READWRITE, 0, sizeof(SharedData), 0);
    char envVarBuf[40];
    sprintf(envVarBuf, "%d", hMap);
    SetEnvironmentVariable("hMap", envVarBuf);

    STARTUPINFO si;
    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    PROCESS_INFORMATION pi;
    CreateProcess("lab1p1.exe", 0, 0, 0, TRUE, 0, 0, 0, &si, &pi);
    SharedData *shrData = (SharedData *) MapViewOfFile(hMap, FILE_MAP_WRITE, 0, 0, sizeof(SharedData));
    shrData->stop = false;
    shrData->reset = false;
    shrData->nWidth = atoi(argv[1]);
    shrData->nHeight = atoi(argv[2]);
    char c;

    do {
        c = getchar();

        switch (c) {
            case 'r':
                shrData->reset = true;
                break;

            case 'c':
                printf("Change color:\n");
                printf("[1] Circle number one\n");
                printf("[2] Circle number two\n");
                printf("[3] Rectangle number one\n");
                printf("[4] Rectangle number two\n");

                int fNum = 0;
                scanf("%d", &fNum);
                shrData->chColor[fNum - 1] = !shrData->chColor[fNum - 1];
        }
    } while (c != 'q');

    shrData->stop = true;
    UnmapViewOfFile(shrData);
    CloseHandle(hMap);

    return 0;
}
