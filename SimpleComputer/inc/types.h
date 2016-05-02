#ifndef _TYPES_H
#define _TYPES_H

#define MEMSZ  100  /* количество ячеек ОП */
#define COLCNT 10   /* количество столбцов */
#define CMDCNT 100  /* количество команд   */
 
/* флаги */
#define FULL 1 /* переполнение */
#define ZERO 2 /* делеине на 0*/
#define OUTO 3 /* выход за границы ОП */
#define IGNR 4 /* игнорирование тактов */
#define BCMD 5 /* неверная команда */
 
int memory[100];	/* оперативная память */
int flag;			/* регистр флагов */
int ax;				/* аккумулятор */
int ip;				/* счетчик команд */
int operand;			/* операнд */
int command;			/* команда */

int cmds[CMDCNT];	/* поддерживаемые команды */

/* размер консоли */
#define TERM_ROW 30 /* строки */
#define TERM_COL 80 /* столбцы */

/* цвета для консоли */
enum colors { clBlack, clRed, clGreen, clYellow, clBlue, clPurple, clAqua, clWhite };

/* массив для хранения символа в псевдографике */
int mas[2];

/* режимы работы клавиатуры */
#define CAN 0
#define ECH 1
#define CUR 2

int can; /* canonical */
int ech; /* echo */
int cur; /* cursor */

/* поддерживаемые клавиши */
/*enum keys { kLeft, kRight, kUp, kDown, kL, kS, kR, kT, kI, kF5, kF6 };*/
enum keys { K_UNKNOWN, K_UP, K_DOWN, K_LEFT, K_RIGHT, K_F5, K_F6, K_ESC, K_ENTER, K_MAX };
#define KEY_MAX_LEN 20
#define MY_CLRSCR "\033[H\033[J"
#define MY_GOTOXY "\033[%u;%uH"
#define MY_BGCOLOR "\033[4%um"
#define MY_FGCOLOR "\033[3%um"

/* максимальная длинна имени файла программы */
#define MAX_FNAME_LEN 12

#endif