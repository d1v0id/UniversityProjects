/*
 * Консоль управления SimpleComputer. Клавиатура
 */
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <regex.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>

#include "types.h"

int can = 0;
int ech = 0;
int cur = 0;
/*
 * Sample solution
 */
/*char *key_sequences[K_MAX];

int is_probably_key(char *sequence, enum keys *key, int len)
{
  int i;

  if (sequence == NULL || key == NULL) {
    return -1;
  }

  key_sequences[K_UNKNOWN] = "";
  key_sequences[K_UP] = "\033[A";
  key_sequences[K_DOWN] = "\033[B";
  key_sequences[K_LEFT] = "\033[C";
  key_sequences[K_RIGHT] = "\033[D";
  key_sequences[K_F5] = "\033[15~";
  key_sequences[K_F6] = "\033[17~";
  key_sequences[K_ESC] = "\033\033";
  key_sequences[K_ENTER] = "\n";

  for (i = K_UNKNOWN; i < K_MAX; i++) {
    if (strlen(key_sequences[i]) < len) {
      continue;
    }
    if (!strncmp(sequence, key_sequences[i], len)) {
      if (len < strlen (key_sequences[i])) {
        return 1;
      }
      *key = i;
      return 0;
    }
  }

  *key = K_UNKNOWN;

  return 0;
}

int rk_readkey(enum keys *key)
{
  int len = 1;
  int res;
  char tmp_key[KEY_MAX_LEN];
  
  while (read(0, &(tmp_key[len - 1]), 1) > 0 && len <= KEY_MAX_LEN) {
    res = is_probably_key(tmp_key, key, len);
    if (res <= 0) {
      return res;
    }
    len ++;
  }
  return 0;
}*/

/* возвращает клавишу, нажатую пользователем */
int rk_readkey(int *key)
{
  /*int tty;
  char buff[50];
  ssize_t n;
  tty = open("/dev/tty", O_RDWR);
  if (tty == -1) {
    fprintf(stderr, "\nrk_readkey(int*)\n: Can not open tty\n");
    close(tty);
    return -1;
  } else {
    system("/dev/tty raw");
    n = fread(buff, 1, sizeof buff-1, stdin);
  }
  close(tty);*/

  /* переделать получение скан-кодов нажатых
  клавиш, чтобы была очередь, для работы f1-f12 и т.д. */

  int tty;
  char buf[50];
  ssize_t n;
  tty = open("/dev/tty", O_RDWR);
  if (tty == 01) {
    fprintf(stderr, "\nrk_readkey(int*)\n: Can not open tty\n");
    close(tty);
    return -1;
  }
  else {
    if (can) {
      system("/bin/stty raw");
      read(tty, buf, sizeof buf-1);
      *key = buf[0];
      system("/bin/stty cooked");
    }
    else {
      read(tty, buf, sizeof buf-1);
      *key = buf[0];
    }
  }
  close(tty);
  return 0;
}

/* сохраняет текущие параметры терминала */
int rk_mytermsave()
{
  FILE *f;
  f = fopen("myterm.cfg", "w+");
  fprintf(f, "Canonical=%d", can);
  fprintf(f, "Echo=%d", ech);
  fprintf(f, "Cursor=%d", cur);
  fclose(f);
  return 0;
}

/* сравнение по regexp */
int match(const char *string, char *pattern, regmatch_t *reg)
{ 
  int status; 
  regex_t re; 
  size_t s;

  (!reg) ? (s=0) : (s=1); 
  if (regcomp(&re, pattern, REG_EXTENDED) != 0) {
    return 0;
  }
  status = regexec(&re, string, s, reg, 0); 
  regfree(&re); 
  return !status; 
}

/* восстанавливает сохраненные параметры терминала */
int rk_mytermrestore()
{
  FILE *f;
  char str[50];
  regmatch_t reg;
  f = fopen("myterm.cfg", "a+");
  while ((fread(str, 50, 1, f)) != 0) {
    if (match(str, "Canonical=0", &reg)) {
      can = 0;
    }
    else {
      can = 1;
    }
    if (match(str, "Echo=0", &reg)) {
      ech = 0;
    }
    else {
      ech = 1;
    }
    if (match(str, "Echo=0", &reg)) {
      cur = 0;
    }
    else {
      cur = 1;
    }
  }
  fclose(f);
  return 0;
}

/* переключение терминала м/д режимами */
int rk_mytermregime(int cfg, int value)
{
  switch (cfg) {
    case 0:
      if ((value > -1) && (value < 2)) {
        can = value;
      }
      break;
    case 1:
      if ((value > -1) && (value < 2)) {
        ech = value;
      }
      if (ech) {
        system("/bin/stty -echo");
      }
      else {
        system("/bin/stty echo");
      }
      break;
    case 2:
      if ((value > -1) && (value < 2)) {
        cur = value;
      }
      if (cur) {
        system("tput civis");
      }
      else {
        system("tput cnorm");
      }
      break;
  }
  return 0;
}

void rk_hideCursor() {
  /*  
   *  0   - switch to canonical
   *  1   - echo off
   *  2   - hide cursor
   *  0/1 - enable/disable
   */
  rk_mytermregime(0, 1); /* переключение в канонический режим */
  rk_mytermregime(1, 1); /* выключение echo */
  rk_mytermregime(2, 1); /* скрытие курсора */
}

void rk_showCursor() {
  rk_mytermregime(0, 0);
  rk_mytermregime(1, 0);
  rk_mytermregime(2, 0);
}