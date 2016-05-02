/*
 * Консоль управления SimpleComputer
 */
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <termios.h>
#include <sys/ioctl.h>

#include "types.h"

/* очистка и премещение курсора в левый верхний угол */
int mt_clrscr()
{
  int tty;
  tty = open("/dev/tty", O_RDWR); /* проверка, можно ли открыть терминал */
  if (tty == -1) {
    fprintf(stderr, "\nmt_clrscr()\n: Can not open tty\n");
    close(tty);
    return -1;
  }
  else {
    /* отправляем в терминал esc-последовательности */
    write(tty, "\E[2J", 4);
    write(tty, "\E[0;0H", 8);
    close(tty);
    return 0;
  }
}

/* перемещение курсора на позицию x, y */
int mt_gotoXY(int x, int y)
{
  int tty;
  tty = open("/dev/tty", O_RDWR);
  if (tty == -1) {
    fprintf(stderr, "\nmt_gotoXY(int, int)\n: Can not open tty\n");
    close(tty);
    return -1;
  }
  else if (x > -1 && x < (TERM_ROW + 1) && y > -1 && y < (TERM_COL + 1)) {
    /* составление esc-пос. "\E[X;YH", перемещающей курсор */
    char str1[10] = "\E[";
    char str2[10] = "";
    char str3[10] = ";";
    char str4[10] = "";
    char str5[10] = "H";
    char str[20] = "";
    /* перевод чисел в строки */
    sprintf(str2, "%d", x);
    sprintf(str4, "%d", y);
    /* объединение частей esc-пос. */
    strcat(str, str1);
    strcat(str, str2);
    strcat(str, str3);
    strcat(str, str4);
    strcat(str, str5);
    /* вывод esc-пос. */
    write(tty, str, 20);
    close(tty);
    return 0;
  }
  else {
    fprintf(stderr, "\nmt_gotoXY(int, int)\n: Incorrect row or column value\n");
    close (tty);
    return 1;
  }
}

/* возвращает размер экрана */
int mt_getscreensize(int *rows, int *cols)
{
  struct winsize ws;
  if (!ioctl(1, TIOCGWINSZ, &ws)) {
    *rows = ws.ws_row;
    *cols = ws.ws_col;
    return 0;
  }
  else {
    fprintf(stderr, "\nmt_getscreensize(int, int)\n: Can not get tty size\n");
    return -1;
  }
}

/* устанавливает цвет текста */
int mt_setfgcolor(int fg)
{
  int tty, fgColor;
  switch(fg) {
    case clBlack:  fgColor = 30; break;
    case clRed:    fgColor = 31; break;
    case clGreen:  fgColor = 32; break;
    case clYellow: fgColor = 33; break;
    case clBlue:   fgColor = 34; break;
    case clPurple: fgColor = 35; break;
    case clAqua:   fgColor = 36; break;
    case clWhite:  fgColor = 37; break;
    default:
      fprintf(stderr, "\nmt_setfgcolor(int)\n: Incorrect text color\n");
      return -1;
  }
  
  tty = open("/dev/tty", O_RDWR);
  if (tty == -1) {
    fprintf(stderr, "\nmt_setfgcolor(int)\n: Can not open TTY\n");
    close(tty);
    return -1;
  }
  else {
    /* составление esc-пос. "\E[34m" */
    char str1[10] = "\E[";
    char str2[10] = "";
    char str3[10] = "m";
    char str[20] = "";
    sprintf(str2, "%d", fgColor);
    strcat(str, str1);
    strcat(str, str2);
    strcat(str, str3);
    write(tty, str, 20);
    close(tty);
    return 0;
  }
}

/* устанавливает цвет фона */
int mt_setbgcolor (int bg)
{
  int tty, bgColor = 0;
  switch(bg) {
    case clBlack:  bgColor = 40; break;
    case clRed:    bgColor = 41; break;
    case clGreen:  bgColor = 42; break;
    case clYellow: bgColor = 43; break;
    case clBlue:   bgColor = 44; break;
    case clPurple: bgColor = 45; break;
    case clAqua:   bgColor = 46; break;
    case clWhite:  bgColor = 47; break;
    default:
      fprintf(stderr, "\nmt_setbgcolor(int)\n: Incorrect background color\n");
      return -1;
  }

  tty = open ("/dev/tty", O_RDWR);
  if (tty == -1) {
    fprintf(stderr, "\nmt_setfgcolor(int)\n: Can not open tty\n");
    close (tty);
    return -1;
  }
  else {
    /* составление esc-пос. "\E[34m" */
    char str1[10] = "\E[";
    char str2[10] = "";
    char str3[10] = "m";
    char str[20] = "";
    sprintf(str2, "%d", bgColor);
    strcat(str, str1);
    strcat(str, str2);
    strcat(str, str3);
    write(tty, str, 20);
    close(tty);
    return 0;
  }
}