/*
 * Консоль управления SimpleComputer. Псевдографика
 */
#include <stdio.h>
#include <fcntl.h>
#include <string.h>

#include "types.h"
 
/* вывод строки символов с использованием дополнительной таблицы кодировок */
int bc_printA(char *str)
{
  int tty;
  tty = open("/dev/tty", O_RDWR);
  if (tty == -1) {
    fprintf(stderr, "\nbc_printA(char *)\n: Can not open tty\n");
    close(tty);
    return -1;
  }
  else {
    write(tty, "\033(0", 3);
    write(tty, str, strlen(str));
    write(tty, "\033(B", 3);
  }
  close(tty);
  return 0;
}

/* рамка в псевдографике, координаты x1-y1, x2-y2 */
int bc_box(int x1, int y1, int x2, int y2)
{
  int tty, i, j;
  tty = open("/dev/tty", O_RDWR);
  if (tty == -1) {
    fprintf(stderr, "\nbc_box(int, int, int, int)\n: Can not open tty\n");
    close(tty);
    return -1;
  }
  else {
    for (i = 1; i < (x2 + 1); i++) {
      mt_gotoXY(x1 + i, y1);
      if (i == 1) {
        bc_printA("l");
        for (j = 2; j < y2; j++) {
          bc_printA("q");
        }
        bc_printA("k");
      }
      if (1 < i && i < x2) {
        bc_printA("x");
        for (j = 2; j < y2; j++) {
          bc_printA(" ");
        }
        bc_printA("x");
      }	
      if (i == x2) {
        bc_printA("m");
        for (j = 2; j < y2; j++) {
          bc_printA("q");
        }
        bc_printA("j");
      }
    }
    close(tty);
    return 0;
  }
}

/* вывод большого символа на экран */
int bc_printbigchar(int mas[], int x, int y, int fg, int bg)
{
  int tty, i, j;
  tty = open("/dev/tty", O_RDWR);
  if (tty == -1) {
    fprintf(stderr, "\nbc_printbigchar(int *, int, int, int, int)\n: Can not open tty\n");
    close(tty);
    return -1;
  }
  else {
    mt_setfgcolor(fg);
    mt_setbgcolor(bg);
    for (j = 1; j < 3; j++) {
      for (i = 32; i > 0; i--) {
        if (i == 32) mt_gotoXY(x + 3 + 4 * (j - 1), y);
        if (i == 24) mt_gotoXY(x + 2 + 4 * (j - 1), y);
        if (i == 16) mt_gotoXY(x + 1 + 4 * (j - 1), y);
        if (i ==  8) mt_gotoXY(x + 0 + 4 * (j - 1), y);
        if (mas[j] >> (i-1) & 0x1 == 1) {
          bc_printA("a");
        }
        else {
          bc_printA(" ");
        }
      }
    }
  }
  close(tty);
}

/* установить позицию большого символа */
int bc_setbigcharpos(char big, int x, int y, int *value)
{
  int tty, i, j;
  tty = open("/dev/tty", O_RDWR);
  if (tty == -1) {
    fprintf(stderr, "\nbc_setbigcharpos(int *, int, int, int *)\n: Can not open tty\n");
    close(tty);
    return -1;
  }
  else if (mt_gotoXY(x, y) != -1) {
      /* установить значение знакоместа "большого символа"
         в строке x и столбце y в значение value */
      switch(big) {
        case '+':
          mas[1] = 4279769112U;
          mas[2] = 404232447;
          break;
        case '0':
          mas[1] = 2172748287U;
          mas[2] = 4286677377U;
          break;
        case '1':
          mas[1] = 302646786;
          mas[2] = 33686018;
          break;
        case '2':
          mas[1] = /*134480639*/16843263U;
          mas[2] = /*4282392592U*/4286611711U;
          break;
        case '3':
          mas[1] = 4278256127U;
          mas[2] = 4278255873U;
          break;
        case '4':
          mas[1] = 4286677377U;
          mas[2] = 16843009;
          break;
        case '5':
          mas[1] = 2155905279U;
          mas[2] = 4278256127U;
          break;
        case '6':
          mas[1] = 2155905279U;
          mas[2] = 4286677503U;
          break;
        case '7':
          mas[1] = 134480639;
          mas[2] = 538976272;
          break;
        case '8':
          mas[1] = 4286677503U;
          mas[2] = 4286677377U;
          break;
        case '9':
          mas[1] = 4286677503U;
          mas[2] = 4278255873U;
          break;
        case 'a':
          mas[1] = 2172748158U;
          mas[2] = 2172748287U;
          break;
        case 'b':
          mas[1] = 4269900286U;
          mas[2] = 4269900286U;
          break;
        case 'c':
          mas[1] = 2155905279U;
          mas[2] = 4286611584U;
          break;
        case 'd':
          mas[1] = 2172748286U;
          mas[2] = 4269900161U;
          break;
        case 'e':
          mas[1] = 4286611711U;
          mas[2] = 4286611711U;
          break;
        case 'f':
          mas[1] = 4286611711U;
          mas[2] = 2155905152U;
          break;
        default:
          mas[1] = 0;
          mas[2] = 0;
          break;
      }
      bc_printbigchar(mas, x, y, clWhite, clBlack);
  }
  close(tty);
}

/* получить позицию большого символа */
int bc_getbigcharpos(int *big, int x, int y, int *value)
{
  int tty, i, j;
  tty = open("/dev/tty", O_RDWR);
  if (tty == -1) {
    fprintf(stderr, "\nbc_setbigcharpos(int *, int, int, int *)\n: Can not open tty\n");
    close(tty);
    return -1;
  }
  else {
    /* возвращает значение позиции в "большом символе"
    в строке x и столбце y */
  }
  close(tty);
}

/* запись больших символов в файл */
int bc_bigcharwrite(int fd, int *big, int count)
{
  /* записывает заданное число "больших символов" в файл.
  формат записи определяется пользователем */
}

/* считывает из файла большие символы */
int bc_bigcharread(int fd, int *big, int need_count, int *count)
{
  /* считывает из файла заданное количество "больших символов"
  третий параметр указывает адрес переменной, в которую помещается количество
  считанных символов или 0 в случае ошибки */
}