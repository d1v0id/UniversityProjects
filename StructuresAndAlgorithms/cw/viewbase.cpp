/* VIEWBASE - просмотр/запись БД */
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <windows.h>

#define NAMESIZE 32     /* размер поля ФИО */
#define DPSIZE 3 	/* количество цифр в номере отдела */
#define POSTSIZE 22 	/* размер поля для должности */
#define BDATESIZE 10    /* размер поля дата рождения */
#define INDM 100        /* максимальное количество индексов БД */
#define LSIZE 20        /* размер очереди для поиска по ключу в БД */

/* DEBUG начало описания тестовой эмуляции БД из файла DEBUG */
typedef char char_str32[NAMESIZE+1];
typedef char char_str22[POSTSIZE+1];
typedef char char_str10[BDATESIZE+1];

#define MAXBD 14
const char_str32 names[MAXBD] = {"Petrov_Ivan_Ivanovich___________", "Ivanov_Petr_Petrovich___________",
                                "Ivanov_Petr_Petrovic1___________", "Ivanov_Petr_Petrovic2___________",
                                "Ivanov_Petr_Petrovic3___________", "Ivanov_Petr_Petrovic4___________",
                                "Ivanov_Petr_Petrovic5___________", "Ivanov_Petr_Petrovic6___________",
                                "Ivanov_Petr_Petrovic7___________", "Ivanov_Petr_Petrovic8___________",
                                "Ivanov_Petr_Petrovic9___________", "Ivanov_Petr_Petrovi10___________",
                                "Ivanov_Petr_Petrovi11___________", "Ivanov_Petr_Petrovi12___________"};
const int deps[MAXBD] = {130, 120, 140, 400, 101, 100, 110, 131, 122, 143, 404, 152, 106, 117};
const char_str22 posts[MAXBD] = {"team_leader___________", "manager_______________",
                                "manage1_______________", "manage2_______________", "manage3_______________",
                                "manage4_______________", "manage5_______________", "team_leade1___________",
                                "manag10_______________", "manag11_______________", "manag12_______________",
                                "manag13_______________", "manag14_______________", "manag15_______________"};
const char_str10 bdates[MAXBD] = {"30-12-1993", "05-10-1991", "15-12-1990", "06-11-1991",
                                "30-12-1992", "12-03-1976", "07-12-1991", "20-01-2001",
                                "01-01-1991", "07-08-1990", "04-06-1991", "03-04-1991",
                                "22-11-1976", "02-03-1991"};
/* DEBUG конец описания тестовой эмуляции БД из файла DEBUG */

struct orgDBase {
	char name[NAMESIZE];		/* ФИО */
	int depnum;			/* номер отдела */
	char post[POSTSIZE];		/* должность */
	char bdate[BDATESIZE];		/* дата рождения */
	struct orgDBase *ptr_next;	/* указатель на следующий элемент */
};

char oem_str[255];

/* ф-ция загрузки БД из констант в оперативную память */
orgDBase* dbase_loadToMem(char *fname)
{
    orgDBase *ptr_dbPointer;    /* указатель на начало массива */
    orgDBase *ptr_dbElem;       /* указатель на запись */
    orgDBase *ptr_dbPred;       /* указатель на предыдущий элемент */

    int i = 0;
    ptr_dbPointer = ptr_dbElem = (orgDBase*)malloc(sizeof(orgDBase));

    ptr_dbElem->depnum = deps[0];               /* получаем номер отдела из БД */
    for (int j = 0; j < NAMESIZE; j++)
        ptr_dbElem->name[j] = names[i][j];      /* получаем ФИО из БД */
    for (int j = 0; j < POSTSIZE; j++)
        ptr_dbElem->post[j] = posts[i][j];      /* получаем должность из БД */
    for (int j = 0; j < BDATESIZE; j++)
        ptr_dbElem->bdate[j] = bdates[i][j];    /* получаем дату рождения из БД */

    ptr_dbPred = ptr_dbElem;
    i++;

    while (i < MAXBD) {
        ptr_dbElem = (orgDBase*)malloc(sizeof(orgDBase));

        ptr_dbElem->depnum = deps[i];               /* получаем номер отдела из БД */
        for (int j = 0; j < NAMESIZE; j++)
            ptr_dbElem->name[j] = names[i][j];      /* получаем ФИО из БД */
        for (int j = 0; j < POSTSIZE; j++)
            ptr_dbElem->post[j] = posts[i][j];      /* получаем должность из БД */
        for (int j = 0; j < BDATESIZE; j++)
            ptr_dbElem->bdate[j] = bdates[i][j];    /* получаем дату рождения из БД */

        ptr_dbPred->ptr_next = ptr_dbElem;
        ptr_dbPred = ptr_dbElem;
        i++;
    }

    return ptr_dbPointer;   /* возвращаем указатель на динамический список */
}

/* процедура вывода БД из памяти на экран */
template <class printElem>
void dbase_printToScreen(printElem *ptr_dbPointer)
{
    printf(".");	/* рисуем верх таблички */
    for (int i = 0; i < NAMESIZE+DPSIZE+POSTSIZE+BDATESIZE+9; i++)
	printf("-");
    printf(".\n");
    /* рисуем табличку и в ней поля БД */
    while (ptr_dbPointer != NULL) {
	printf("|");
	for (int i = 0; i < NAMESIZE; i++)
	    printf("%c", ptr_dbPointer->name[i]);
	printf(" | ");
        printf("%d | ", ptr_dbPointer->depnum);
	for (int i = 0; i < POSTSIZE; i++)
	    printf("%c", ptr_dbPointer->post[i]);
	printf(" | ");
        for (int i = 0; i < BDATESIZE; i++)
	    printf("%c", ptr_dbPointer->bdate[i]);
        printf("|\n");
        ptr_dbPointer = ptr_dbPointer->ptr_next;
    }
    printf("'");	/* рисуем низ таблички */
    for (int i = 0; i < NAMESIZE+DPSIZE+POSTSIZE+BDATESIZE+9; i++)
	printf("-");
    printf("'\n");
}

/* запись БД из памяти в файл */
int dbase_saveToFile(orgDBase *ptr_dbPointer, char *fname, int n) {
	FILE *binFile = NULL;
	binFile = fopen(fname, "wb+");

	/* запись заголовка БД */
	char dbSeg[3] = {'K', 'D' , 'A'};
	fwrite(&dbSeg, sizeof(char[3]), 1, binFile);
	fwrite(&n, sizeof(int), 1, binFile);

	while (ptr_dbPointer != NULL) {
		/* запись одной строки БД */
		fwrite(&ptr_dbPointer->name, NAMESIZE, 1, binFile);
		fwrite(&ptr_dbPointer->depnum, DPSIZE, 1, binFile);
		fwrite(&ptr_dbPointer->post, POSTSIZE, 1, binFile);
		fwrite(&ptr_dbPointer->bdate, BDATESIZE, 1, binFile);
		ptr_dbPointer = ptr_dbPointer->ptr_next;
	}

	fclose(binFile);
	return 0;
}

/* ф-ция загрузки БД из файла в оперативную память */
orgDBase* dbase_loadFromFile(char *fname) {
	orgDBase *ptr_dbPointer;    /* указатель на начало памяти для БД */
	orgDBase *ptr_dbElem;       /* указатель на запись */
	orgDBase *ptr_dbPred;       /* указатель на предыдущий элемент */

	FILE *binFile = NULL;
	binFile = fopen(fname, "rb");
	if (binFile == NULL) {
                CharToOem("Ошибка! Файл недоступен!", oem_str);
		printf("%s\n", oem_str);
		exit(1);
	}

	/* чтение заголовка БД */
	char dbSeg[3];
	fread(&dbSeg, sizeof(char[3]), 1, binFile);
	if ((dbSeg[0] != 'K') && (dbSeg[1] != 'D') && (dbSeg[2] != 'A')) {
                CharToOem("Ошибка! Это не файл БД!", oem_str);
		printf("%s", oem_str);
		exit(1);
	}
	int n; /* количество элементов в БД */
	fread(&n, sizeof(int), 1, binFile);

	/* считываем все остальное из файла в память */
	ptr_dbPointer = ptr_dbElem = (orgDBase*)malloc(sizeof(orgDBase));
	fread(&ptr_dbElem->name, NAMESIZE, 1, binFile);		/* получаем ФИО из файла БД */
	fread(&ptr_dbElem->depnum, DPSIZE, 1, binFile);		/* получаем номер отдела из файла БД */
	fread(&ptr_dbElem->post, POSTSIZE, 1, binFile);		/* получаем должность из файла БД */
	fread(&ptr_dbElem->bdate, BDATESIZE, 1, binFile);	/* получаем дату рождения из файла БД */
	ptr_dbPred = ptr_dbElem;

	for (int i = 1; i < n; i++) {
		ptr_dbElem = (orgDBase*)malloc(sizeof(orgDBase));
		fread(&ptr_dbElem->name, NAMESIZE, 1, binFile);		/* получаем ФИО из файла БД */
		fread(&ptr_dbElem->depnum, DPSIZE, 1, binFile);		/* получаем номер отдела из файла БД */
		fread(&ptr_dbElem->post, POSTSIZE, 1, binFile);		/* получаем должность из файла БД */
		fread(&ptr_dbElem->bdate, BDATESIZE, 1, binFile);	/* получаем дату рождения из файла БД */
		ptr_dbPred->ptr_next = ptr_dbElem;
		ptr_dbPred = ptr_dbElem;
	}

	fclose(binFile);
	return ptr_dbPointer;	/* возвращаем указатель на динамический список */
}

int main (int argc, char **argv) {
	char *fname = (char*)"base2.dat";   /* имя файла БД */
        int c;
	orgDBase *ptr_dbHead;	/* указатель на начало массива записей из БД */
        while(1) {
                CharToOem("Меню", oem_str);
                printf("%s\n", oem_str);
                CharToOem("1) Создать БД и сохранить в файл", oem_str);
                printf("%s\n", oem_str);
                CharToOem("2) Вывести содержимое БД из файла", oem_str);
                printf("%s\n", oem_str);
                CharToOem("3) Выход", oem_str);
                printf("%s\n> ", oem_str);
                scanf("%d", &c);
                switch(c) {
                case 1: /* создание БД из шаблона */
                	/* загрузка данных для БД из констант */
                	ptr_dbHead = dbase_loadToMem(fname);
                	/* вывод БД из памяти на экран */
                        CharToOem("База нанных успешно записана в файл ", oem_str);
                	printf("%s%s\n", oem_str, fname);
                        CharToOem("Просмотр БД:", oem_str);
                        printf("%s\n", oem_str);
                	dbase_printToScreen<orgDBase>(ptr_dbHead);
                	/* записываем содержимое БД в файл */
                	dbase_saveToFile(ptr_dbHead, fname, 14);
                        break;
                case 2: /* вывод БД из файла */
                	/* читаем содержимое файла */
                	ptr_dbHead = dbase_loadFromFile(fname);
                	/* вывод БД из памяти на экран */
                        CharToOem("Просмотр БД", oem_str);
                	printf("%s(%s):\n", oem_str, fname);
                	if (ptr_dbHead != NULL) dbase_printToScreen<orgDBase>(ptr_dbHead);
                        break;
                case 3: return 0;
                }
        }
}

