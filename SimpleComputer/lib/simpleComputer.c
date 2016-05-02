/*
 * Функции по взаимодействию с оперативной памятью,
 * управлению регистром флагов и 
 * кодированию/декодированию команд
 */
#include <stdio.h>

#include "types.h"

/* коды команд */
int cmds[CMDCNT] = { 0x10, 0x11, 0x20, 0x21, 0x30, 0x31, 0x32,
                 0x33, 0x40, 0x41, 0x42, 0x43, 0x51, 0x52,
                 0x53, 0x54, 0x55, 0x56, 0x57, 0x58, 0x59,
                 0x60, 0x61, 0x63, 0x64, 0x65, 0x66, 0x67,
                 0x68, 0x69, 0x70, 0x71, 0x72, 0x73, 0x74,
                 0x02, 0x75, 0x02, 0x76 };

/* инициализация ОП, заполнение 0-ми */
void sc_memoryInit()
{
  int i;
  int *e = &memory[0];
  for (i = 0; i < MEMSZ; i++, e++) {
    *e = 0;
  }
}

/* записать в ячейку address значение value */
int sc_memorySet(int address, int value)
{
  if (address < MEMSZ && address > -1) {
    memory[address] = value;
  }
  else {
    flag = flag | (1 << (OUTO-1));
    fprintf(stderr, "\nsc_memorySet(int, int): Out of memory\n");
    return -1;
  }
  return 0;
}

/* возвращает в value содержимое ячейки address */
int sc_memoryGet(int address, int *value)
{
  if (address < MEMSZ && address > - 1) {
    *value = memory[address];
  }
  else {
    fprintf(stderr, "\nsc_memoryGet(int, int): Out of memory\n");
    return -1;
  }
  return 0;
}

/* сохраняет содержимое ОП в файл */
int sc_memorySave(char *filename)
{
  FILE *binfile;
  if ((binfile = fopen(filename, "wb")) == NULL) { 
    fprintf(stderr, "\nsc_memorySave(char*)\n: Cannot open file\n");
    return -1;
  }
  else {
    fwrite(memory, sizeof memory, 1, binfile);
  }
  fclose(binfile);
  return 0;
}

/* загружает в ОП содержимое из файла */
int sc_memoryLoad(char * filename)
{
  FILE *binfile;
  if ((binfile = fopen(filename, "rb")) == NULL) { 
    fprintf(stderr, "\nsc_memoryLoad(char*)\n: Cannot open file\n");
    return -1;
  }
  else {
    fread(memory, sizeof memory, 1, binfile);
  }
  fclose(binfile);
  return 0;
}

/* установка значения value в флаге reg (FULL, ZERO, OUTO, IGNR, BCMD) */
int sc_regSet(int reg, int value)
{
  if (6 < reg || reg < -1) {
    fprintf(stderr, "\nsc_regSet(int, int)\n: Incorrect flag address\n");
    return -1;
  }
  else if (2 < value || value < -1) {
    fprintf(stderr, "\nsc_regSet(int, int)\n: Incorrect flag value\n");
    return -1;
  }
  else { 
    if (value == 1)  {
      flag = flag | (value << (reg-1));
    }
    else if (value == 0) {
      flag = flag & (~(1 << (reg-1)));
    }
  }
  return 0;
}

/* возвращает значение флага reg */
int sc_regGet(int reg, int *value)
{
  if (6 > reg && reg > 0) {
    *value = (flag >> (reg - 1)) & 0x1;
  }
  else {
    fprintf(stderr, "\nsc_regGet()\n: Incorrect flag address\n");
    return -1;
  }
  return 0;
}

/* инициализация регистра флагов */
void sc_regInit()
{
  /*flag = 0;*/
  sc_regSet(FULL, 0);
  sc_regSet(ZERO, 0);
  sc_regSet(OUTO, 0);
  sc_regSet(IGNR, 1);
  sc_regSet(BCMD, 0);
}

/* кодирует команду */
int sc_commandEncode(int command, int operand, int *value)
{
  int i;
  int ex = 0;
  for (i = 0; i < CMDCNT; i++) {
    if (command == cmds[i]) {
      ex = 1;
      break;
    }
  }
  if (ex) {
    (*value) = ((command & 0x7F) << 7) | (operand & 0x7F);
    sc_regSet(BCMD, 0);
  }
  else {
    sc_regSet(BCMD, 1);
    return -1;
  }
  return 0;
}

/* декодирует команду */
int sc_commandDecode(int value, int *command, int *operand)
{
  if ((value < 0) || (value >> 14) || (command == NULL) || (operand == NULL)) {
    sc_regSet(BCMD, 1);
    return -1;
  }
  (*operand) = value & 0x7F;
  (*command) = (value >> 7) & 0x7F;
  return 0;
}

/* вывод регистра флагов */
void sc_printFlags()
{
  int i;
  printf("       F Z O I B\n");
  printf("Flags: ");
  for (i = 1; i < 6; i++) {
    printf("%d ", (flag >> (i - 1)) & 0x1);
  }
}

/* вывод содержимого ОП */
int sc_printMemory()
{
  int command = 0, operand = 0, value = 0;
  int i = 0, j = 0, len = 0;
  char ch[6] = { 0 };
  for(i = 0; i < 10; i++) {
    for(j = 0; j < 10; j++) {
      int k = 0;
      value = 0;
      if (sc_memoryGet(i * 10 + j, &value)) {
        return -1;
      }
      k = value >> 14;
      if (k) {
        value = value & 0x3FFF;
      }
      command = operand = 0;
      if (sc_commandDecode(value, &command, &operand)) {
        return -1;
      }
      len = sprintf(ch, "%c%02X%02X ", (k == 0) ? '+' : '-', command, operand);
      write(1, ch, len);
    }
    write(1, "\n", 1);
  }
  write(1, "\n", 1);
  return 0;
}