/*
 * Структуры и алгоритмы обработки данных часть 2
 *
 * Лабораторная работа 1
 * */
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>

#define TRSIZE 6 /* количество элементов в дереве */

char oem_str[255];

int tr_pos[6] = {7, 2, 4, 3, 6, 5}; /* задание формы дерева по варианту */

struct sTree {
	int data; /* поле с данными */
	int gnum; /* уровень в дереве */
	sTree *left, *right; /* левая и правая часть дерева */
};

sTree *root; /* корень дерева */

/* запись в бинарное дерево */
int tr_push(sTree **t, int a) {
	if ((*t) == NULL) { /* если дерева не существует */
		(*t) = new sTree; /* выделяем память */
		(*t)->data = a; /* записываем в выделенное место aргумент a */
		(*t)->left = (*t)->right = NULL; /* очищаем память для следующего роста */
		return -1;
	}
	if (a > (*t)->data) tr_push(&(*t)->right, a); /* если аргумент больше текущего элемента то кладем вправо */
	else tr_push(&(*t)->left, a); /* иначе влево */
	return 0;
}

/* определение максимального из двух чисел */
int max(int a, int b) {
	return (a >= b) ? a : b;
}

/* размер дерева */
int tr_getSize(sTree *t) {
	return (t == NULL) ? 0 : 1+tr_getSize(t->left)+tr_getSize(t->right);
}

/* высота дерева */
int tr_getHeight(sTree *t) {
	return (t == NULL) ? 0 : 1+max(tr_getHeight(t->left), tr_getHeight(t->right));
}

/* средняя длинна пути */
int tr_sdp(sTree *t, int l) {
	return (t == NULL) ? 0 : l+tr_sdp(t->left, l+1)+tr_sdp(t->right, l+1);
}

/* средняя высота дерева */
float tr_getAverageHeight(sTree *t) {
	return ((float)tr_sdp(t, 1) / tr_getSize(t));
}

/* контрольная сумма дерева */
int tr_getSumm(sTree *t) {
	return (t == NULL) ? 0 : t->data+tr_getSumm(t->left)+tr_getSumm(t->right);
}

/* обход дерева слева направо */
int tr_print(sTree *t, int s) {
	if (t == NULL) return -1; /* если дерево пустое */
	tr_print(t->left, ++s); /* рекурсивно посещаем левое дерево */
	t->gnum = 0;
	for (int i = 0; i < s; ++i) {
		printf("|");
		t->gnum++;
	}
	printf("%d\n", t->data); /* выводим данные */
	s--;
	tr_print(t->right, ++s); /* рекурсивно посещаем правое дерево */
	return 0;
}

int main(int argc, char **argv) {
	/* для случайного дерева */
        CharToOem("[Случайное дерево]", oem_str);
	printf("%s\n", oem_str);
	root = NULL;
	srand(time(0)); /* рандомайз */
	for (int i = 0; i < TRSIZE; ++i) tr_push(&root, rand() % 100);
        CharToOem("Размер дерева: ", oem_str);
	printf("%s%d\n", oem_str, tr_getSize(root));
        CharToOem("Высота дерева: ", oem_str);
	printf("%s%d\n", oem_str, tr_getHeight(root));
        CharToOem("Средняя высота дерева: ", oem_str);
	printf("%s%5.2f\n", oem_str, tr_getAverageHeight(root));
        CharToOem("Контрольная сумма: ", oem_str);
	printf("%s%d\n", oem_str, tr_getSumm(root));
        CharToOem("Обход дерева слева на право:", oem_str);
	printf("%s\n", oem_str);
	tr_print(root, 0);
	printf("\n\n");

	/* для упорядоченного дерева */
        CharToOem("[Упорядоченное дерево]", oem_str);
	printf("%s\n", oem_str);
	root = NULL;
	for (int i = 0; i < TRSIZE; ++i) tr_push(&root, i+1);
        CharToOem("Размер дерева: ", oem_str);
	printf("%s%d\n", oem_str, tr_getSize(root));
        CharToOem("Высота дерева: ", oem_str);
	printf("%s%d\n", oem_str, tr_getHeight(root));
        CharToOem("Средняя высота дерева: ", oem_str);
	printf("%s%5.2f\n", oem_str, tr_getAverageHeight(root));
        CharToOem("Контрольная сумма: ", oem_str);
	printf("%s%d\n", oem_str, tr_getSumm(root));
        CharToOem("Обход дерева слева на право:", oem_str);
	printf("%s\n", oem_str);
	tr_print(root, 0);
	printf("\n\n");

	/* для дерева по варианту */
        CharToOem("[Дерево по варианту]", oem_str);
	printf("%s\n", oem_str);
	root = NULL;
	for (int i = 0; i < TRSIZE; ++i) tr_push(&root, tr_pos[i]);
        CharToOem("Размер дерева: ", oem_str);
	printf("%s%d\n", oem_str, tr_getSize(root));
        CharToOem("Высота дерева: ", oem_str);
	printf("%s%d\n", oem_str, tr_getHeight(root));
        CharToOem("Средняя высота дерева: ", oem_str);
	printf("%s%5.2f\n", oem_str, tr_getAverageHeight(root));
        CharToOem("Контрольная сумма: ", oem_str);
	printf("%s%d\n", oem_str, tr_getSumm(root));
        CharToOem("Обход дерева слева на право:", oem_str);
	printf("%s\n", oem_str);
	tr_print(root, 0);
	printf("\n");
        getch();
	return 0;
}
