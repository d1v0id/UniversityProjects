/*
 * Computer Emulator
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <limits.h>
#include <signal.h>
#include <sys/time.h>

#include "types.h"

int result, i, len, k;
int tty, value, isRunning = 1, j, col;
char str[20] = "";
char str2[20] = "";
int x = 0, y = 0; /* координаты для отображения больших символов */
int curPos = 0; /* текущая позиция курсора в ОП */
char filename[MAX_FNAME_LEN]; /* имя файла для открытия/сохранения программы */
struct itimerval nval, oval; /* определение системного таймера */

/* начальная отрисовка интерфейса */
void drawGui()
{
	/* Настройка внешнего вида терминала */
	mt_setfgcolor(clAqua);
	mt_setbgcolor(clBlack);
	mt_clrscr();

	/* Рамки */
	bc_box(0,  0,  12, 61); /* Memory */
	bc_box(0,  62, 3,  18);	/* Accumulator */
	bc_box(3,  62, 3,  18); /* InstrPointer */	
	bc_box(6,  62, 3,  18); /* Memory */	
	bc_box(9,  62, 3,  18); /* Flags */	
	bc_box(12, 48, 10, 32); /* Keys */	
	bc_box(12, 0,  10, 47); /* BigChar */
	bc_box(22, 0,  7,  79); /* Input/Output */

	/* Заголовки */
	mt_gotoXY(1, 31);
	write(tty, "Memory", 6);
	mt_gotoXY(13, 50);
	write(tty, "Keys:", 5);
	mt_gotoXY(10, 69);
	write(tty, "Flags", 5);
	mt_gotoXY(7, 67);
	write(tty, "Operation", 9);
	mt_gotoXY(1, 66);
	write(tty, "Accumulator", 11);    
	mt_gotoXY(4, 66);
	write(tty, "InstrCountr", 11);

	/* Инфо для управления */
	mt_gotoXY(14, 49);
	write(tty, "o - open", 8); /* 111 */
	mt_gotoXY(15, 49);
	write(tty, "s - safe", 8); /* 115 */
	mt_gotoXY(16, 49);
	write(tty, "r - run", 7); /* 114 */
	mt_gotoXY(17, 49);
	write(tty, "t - step", 8); /* 116 */
	mt_gotoXY(18, 49);
	write(tty, "i - reset", 9); /* 105 */
	mt_gotoXY(19, 49);
	write(tty, "a - accumulator", 15); /* 97 */
	mt_gotoXY(20, 49);
	write(tty, "p - instruction counter", 23); /* 112 */
	mt_gotoXY(21, 49);
	write(tty, "q - quit", 9);
}

/* перерисовка интерфейса */
void refreshGui()
{	
	mt_setfgcolor(clWhite);
	mt_setbgcolor(clBlack);

	/* аккумулятор */
	mt_gotoXY(2, 69);
	write(tty, "+0000", 5);
	if ((ax < 100) && (ax >= 16)) {
		mt_gotoXY(2, 72);
		sprintf(str, "%x", ax);
		write(tty, str, 2);
	} 
	else if (ax < 16) {
		mt_gotoXY(2, 73);
		sprintf(str, "%x", ax);
		write(tty, str, 1);
	}

	/* ip */
	mt_gotoXY(5, 69);
	write(tty, "+0000", 5);
	if ((ip < 100) && (ip >= 16)) {
		mt_gotoXY(5, 72);
		sprintf(str, "%x", ip);
		write(tty, str, 2);
	} 
	else if (ip < 16) {
		mt_gotoXY(5, 73);
		sprintf(str, "%x", ip);
		write(tty, str, 1);
	}

	/* операнд */
	mt_gotoXY(8, 69);
	write(tty, "+0000", 5);
	sprintf(str, "%x", operand);
	if (strlen(str) == 2) {
		mt_gotoXY(8, 72);
		write(tty, str, 2);
	} 
	else if (strlen(str) == 1) {
		mt_gotoXY(8, 73);
		write(tty, str, 1);
	}

	/* флаги */
	mt_gotoXY(11, 67);
	if (((flag >> 0) & 0x1) == 1) {
		write(tty, "F ", 2);
	}
	else {
		write(tty, "  ", 2);
	}
	if (((flag >> 1) & 0x1) == 1) {
		write(tty, "Z ", 2);
	}
	else {
		write(tty, "  ", 2);
	}
	if (((flag >> 2) & 0x1) == 1) {
		write(tty, "O ", 2);
	}
	else {
		write(tty, "  ", 2);
	}
	if (((flag >> 3) & 0x1) == 1) {
		write(tty, "I ", 2);
	}
	else {
		write(tty, "  ", 2);
	}
	if (((flag >> 4) & 0x1) == 1) {
		write(tty, "B ", 2);
	}
	else {
		write(tty, "  ", 2);
	}

	/* вывод содержимого ОП */
	mt_gotoXY(2, 2);
	col = 2;
	for (i = 0; i < MEMSZ; i++) {
		if (i == ip) {
			mt_setfgcolor(clBlack);
			mt_setbgcolor(clWhite);
		}
		else {
			mt_setfgcolor(clWhite);
			mt_setbgcolor(clBlack);
		}

		if ( (i == curPos) && (isRunning) ) {
			mt_setfgcolor(clBlack);
			mt_setbgcolor(clRed);
		}

		if (i % 10 == 0 && i != 0) {
			col++;
			mt_gotoXY(col, 2);
		}

		sc_memoryGet(i, &value);
		k = (value >> (14)) & 0x1;
		sprintf(str, "%c%x", (k == 0) ? '+':' ', value);
		switch (strlen(str)) {
			case 2:
				str[4] = str[1];
				str[3] = str[2] = str[1] = '0';
				break;
			case 3:
				str[4] = str[2];
				str[3] = str[1];
				str[2] = str[1] = '0';
				break;
			case 4:
				str[4] = str[3];
				str[3] = str[2];
				str[2] = str[1];
				str[1] = '0';
				break;
		}
		write(tty, str, 5);

		/* перевод курсора к следующей ячейке */
		sprintf(str2, "%s", "\E[1C");
		write(tty, str2, 20);
	}

	/* вывод больших символов */
	if (((memory[ip] >> (15)) & 0x1) == 0) {
		bc_setbigcharpos('+', 14, 3, 0);
	}
	else {
		bc_setbigcharpos(' ', 14, 3, 0);
	}

	/* команда */	
	sprintf(str, "%x", command);
	if (strlen(str) == 1) {
		str[1] = str[0];
		str[0] = '0';
	}
	bc_setbigcharpos(str[0], 14, 12, 0);
	bc_setbigcharpos(str[1], 14, 21, 0);

	/* операнд */
	sprintf(str, "%x", operand);
	if (strlen(str) == 1) {
		str[1] = str[0];
		str[0] = '0';
	}
	bc_setbigcharpos(str[0], 14, 30, 0);
	bc_setbigcharpos(str[1], 14, 39, 0);
}

void readToMemory()
{
	int c;
	mt_gotoXY(24, 2);
	mt_setfgcolor(clWhite);
	mt_setbgcolor(clBlack);
	for (i = 0; i < TERM_COL - 3; i++) {
		write(tty, " ", 1);
	}
	mt_gotoXY(24, 2);
	write(tty, "[0x10]: ", 8);
	sc_regSet(IGNR, 1);
	rk_showCursor();
	scanf("%d", &c);
	rk_hideCursor();
	memory[operand] = c;
	sc_regSet(IGNR, 0);
}

void writeFromMemory()
{
	int c;
	mt_gotoXY(25, 2);
	mt_setfgcolor(clWhite);
	mt_setbgcolor(clBlack);
	for (i = 0; i < TERM_COL - 3; i++) {
		write(tty, " ", 1);
	}
	mt_gotoXY(25, 2);
	write(tty, "[0x11]: ", 8);
	sprintf(str2, "%x", memory[operand]);
	write(tty, str2, 2);
}

void executeAlu()
{
	switch (command) {
		case 0x30: // add
			ax = memory[operand] + ax;
			if(ax > 0xffff) {
				ax = 0xffff;
				sc_regSet(FULL, 1);
			}
			break;

		case 0x31: // sub
			ax = ax - memory[operand];
			if(ax < -0xffff) {
				ax = -0xffff;
				sc_regSet(FULL, 1);
			}
			break;

		case 0x32: // div
			if(memory[operand] == 0) {
				sc_regSet(ZERO, 1);
			}
			else {
				ax = ax / memory[operand];
			}
			break;

		case 0x33: // mul
			ax = ax * memory[operand];
			if(ax > 0xffff) {
				ax = 0xffff;
				sc_regSet(FULL, 1);
			}
			if(ax < -0xffff){
				ax = -0xffff;
				sc_regSet(FULL, 1);
			}
			break;

		default:
			sc_regSet(BCMD, 1);
	}
}

void executeCmd()
{
	switch (command) {
		case 0x10: // read
			readToMemory();
			break;

		case 0x11: // write
			writeFromMemory();
			break;

		case 0x20: // load
			ax = memory[operand];
			break;

		case 0x21: // store
			memory[operand] = ax;
			break;

		case 0x40: // jump
			ip = operand - 1;
			break;

		case 0x41: // jng
			if(ax < 0) {
				ip = operand - 1;
			}
			break;

		case 0x42: // jz
			if(ax == 0) {
				ip = operand - 1;
			}
			break;

		case 0x43: // halt
			/* do nothing */
			sc_regSet(IGNR, 1);
			break;

		default:
			executeAlu();
	}
}

/* обработчик прерываний от системного таймера */
void signalhandler(int sig)
{
	sc_regGet(IGNR, &isRunning);
	if (isRunning == 0) {
		if (ip + 1 <= MEMSZ) {
			/* execute from ram */
			command = ((unsigned char *)(&memory[ip]))[1];
			operand = ((unsigned char *)(&memory[ip]))[0];
			executeCmd();

			ip++;			
			refreshGui();
		}
		else {
			/*ip = 0;*/
			sc_regSet(IGNR, 1);
		}
	}
}

void kr_open()
{
	mt_gotoXY(24, 2);
	mt_setfgcolor(clWhite);
	mt_setbgcolor(clBlack);
	for (i = 0; i < TERM_COL - 3; i++) {
		write(tty, " ", 1);
	}
	mt_gotoXY(24, 2);
	write(tty, "Open dump from file: ", 22);
	rk_showCursor();
	scanf("%s", filename);
	rk_hideCursor();
	sc_memoryLoad(filename);
}

void kr_save()
{
	mt_gotoXY(24, 2);
	mt_setfgcolor(clWhite);
	mt_setbgcolor(clBlack);
	for (i = 0; i < TERM_COL - 3; i++) {
		write(tty, " ", 1);
	}
	mt_gotoXY(24, 2);
	write(tty, "Save dump to file: ", 19);	
	rk_showCursor();
	scanf("%s", filename);	
	rk_hideCursor();
	sc_memorySave(filename);
}

void kr_run()
{
	if (isRunning) {
		mt_gotoXY(24, 2);
		mt_setfgcolor(clWhite);
		mt_setbgcolor(clBlack);
		for (i = 0; i < TERM_COL - 3; i++) {
			write(tty, " ", 1);
		}
		mt_gotoXY(24, 2);
		write(tty, "Run program...", 14);
		// инициализация системного таймера
		signal(SIGALRM, signalhandler);
		nval.it_interval.tv_sec = 1;
		nval.it_interval.tv_usec = 0;
		nval.it_value.tv_sec = 1;
		nval.it_value.tv_usec = 0;
		setitimer(ITIMER_REAL, &nval, &oval);						
		sc_regSet(IGNR, 0);
	}
}

void kr_step()
{
	if (isRunning) {
		if (ip + 1 <= MEMSZ) {
			/* execute from ram */
			command = ((unsigned char *)(&memory[ip]))[1];
			operand = ((unsigned char *)(&memory[ip]))[0];
			executeCmd();

			ip++;

			mt_gotoXY(24, 2);
			mt_setfgcolor(clWhite);
			mt_setbgcolor(clBlack);
			for (i = 0; i < TERM_COL - 3; i++) {
				write(tty, " ", 1);
			}
			mt_gotoXY(24, 2);
			write(tty, "Trace...", 8);
		}
		else {
			// some one else
		}
	}
}

void kr_reset()
{	
	ip = 0;	
	sc_regInit(); // установка значений флагов	
	mt_gotoXY(24, 2);
	mt_setfgcolor(clWhite);
	mt_setbgcolor(clBlack);
	for (i = 0; i < TERM_COL - 3; i++) {
		write(tty, " ", 1);
	}
	mt_gotoXY(24, 2);
	write(tty, "Program terminated.", 19);
}

void kr_accumulator()
{
	mt_gotoXY(24, 2);
	mt_setfgcolor(clWhite);
	mt_setbgcolor(clBlack);
	for (i = 0; i < TERM_COL - 3; i++) {
		write(tty, " ", 1);
	}
	mt_gotoXY(24, 2);
	write(tty, "Enter accumulator new value: ", 30);	
	rk_showCursor();
	scanf("%d", &ax);
	rk_hideCursor();
}

void kr_ip()
{
	mt_gotoXY(24, 2);
	mt_setfgcolor(clWhite);
	mt_setbgcolor(clBlack);
	for (i = 0; i < TERM_COL - 3; i++) {
		write(tty, " ", 1);
	}
	mt_gotoXY(24, 2);
	write(tty, "Enter instruction pointer new value: ", 38);
	rk_showCursor();
	scanf("%d", &ip);	
	rk_hideCursor();
}

int main(int argc, char **argv)
{
	/* заполняем ОП */
	sc_memoryInit();

	/* установка значений флагов */
	sc_regInit();

	ip = 0;
	ax = 0;
	command = 0;
	operand = 0;

	/* открытие дескриптора	*/
	tty = open("/dev/tty", O_RDWR);

	drawGui();
	rk_hideCursor();
		
  	char key = 0;

  	while (1) {

	while (1) {		  		
  		refreshGui();
  		sc_regGet(IGNR, &isRunning);
  		rk_readkey(&key);
		if (isRunning) {			
			switch (key) {        
				case 104: // h - left					
					if ((curPos-1 >= 0) && isRunning) curPos--;
					break;
				case 108: // l - right					
					if ((curPos+1 < 100) && isRunning) curPos++;
					break;
				case 106: // j - down					
					if ((curPos+10 < 100) && isRunning) curPos +=10;
					break;
				case 107: // k - up					
					if ((curPos-10 >= 0) && isRunning) curPos -=10;
					break;
				case 111: // o - open
					kr_open();
					break;	
				case 115: // s - save
					kr_save();
					break;				
				case 116: // t - step
					kr_step();
					break;
				case 97: // a - accumulator
					kr_accumulator();
					break;
				case 112: // p - ip
					kr_ip();
					break;
			}			
		}

		if (key == 114) { // r - run					
			kr_run();
			break;
		}

		if (key == 105) { // i - reset
			kr_reset();
			break;
		}

		if (key == 113)  { // q -exit
			rk_showCursor();
			mt_gotoXY(30, 0);
			close(tty);
			return 0;
		}
	}

	/* run */

	}
}