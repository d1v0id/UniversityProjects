#include <stdio.h>
#include <malloc.h>
#include <locale.h>

#define volum_matr 100

int weight_matrix[volum_matr][volum_matr];	// массив для хранения весов ребер
int max_num_vertex = 0;			            // количество вершин в графе
int infinity = 1;		                    // начальное значение бесконечности, позже будет пересчитано

// Заполнение массива весов ребер
int enter_array_of_input_data(void)
{
	int	i = 0;
	int j = 0;
	int temp_X = 0;
	int temp_Y = 0;
	int temp_weight = 0;

	// Список для временного хранения весов ребер,
	// пока не будет сформирована матрица
	struct spis {
        int X;  			// координаты в матрице и номера вершин
        int Y;
        int weight;			// вес ребра
        struct spis *next;	// указатель на следующую структуру
    };

    // указатели на начало и конец списка
	struct spis *head;
    struct spis *tail;
	head = NULL;
	tail = NULL;
	printf("введите количество вершин в графе: ");
	scanf("%d", &max_num_vertex);

	struct spis *p;     //локальный указатель на элементы списка
	do {
        p = (struct spis*) malloc(sizeof(struct spis));   //выделение памяти элементу
        if (p != NULL) {
            printf("\n от какой вершины: ");
            scanf("%d", &temp_X);
            printf(" до какой вершины: ");
            scanf("%d", &temp_Y);
            printf(" вес ребра: ");
            scanf("%d", &temp_weight);
            // проверка ошибок ввода
            if ( (temp_X >= 0 && temp_X<max_num_vertex) &&
                 (temp_Y >= 0 && temp_Y<max_num_vertex) &&
                 temp_weight > 0 ) {
                p->X = temp_X;    // заполнение полей
                p->Y = temp_Y;    // данных для нового
                p->weight = temp_weight; // элемента
                p->next = NULL;
                if(head != NULL) {
                    tail->next = p;
                }
                else {
                    head = p;
                }
                tail = p;
                infinity += temp_weight + 1;
            }
            else {
                if (temp_X >= max_num_vertex || temp_Y >= max_num_vertex) {
                    printf("\n превышен максимально возможный номер вершины!");
                }
                else {
                    printf("\n некорректные данные,- вес ребра в данной программе");
                    printf("\n не может быть отрицательным или равным нулю!");
                    printf("\n также номер вершины не может быть отрицательным");
                }
                puts("\n повторите ввод данных.");
            }
        }
        else {
            puts("ошибка выделения памяти! обратитесь к разработчику.");
            return 1;
        }
        puts("\n закончили ввод? - <y/n>"); // ожидает нажатия клавиши
    } while (getchar() != 'y'); // если не нажата "у" - повтор цикла

	// заполнение всего массива значениями "бесконечность" и нулями
	for (i = 0; i < max_num_vertex; i++) {
        for (j = 0; j < max_num_vertex; j++) {
            if(i == j) {
                weight_matrix[i][j] = 0;
		    }
            else {
                weight_matrix[i][j] = infinity;
			}
	    }
    }

	// занесение весов ребер из очереди в матрицу
	while (head != NULL) {
        p = head;
        weight_matrix[p->X][p->Y] = p->weight;
        weight_matrix[p->Y][p->X] = p->weight;
        head = p->next;
        free(p);
	}

	return 0;
}

void clrscr(void)
{
    system("clear");
}

int main(int argc, char **argv)
{
	int i = 0;
    int j = 0;
    int a = 0;
    int min = 0;
    int temp = 0;
    int stabilization = 0;
    int minimum_cost_crossings[volum_matr]; // массивы для хранения значений
    int new_minimum_cost_crossings[volum_matr];	// минимальных путей к вершинам

	clrscr();
	if (enter_array_of_input_data() == 1) {
        return 1;
    }

	do {
        printf("от какой вершины считать? : ");
	    scanf("%d", &a);
    }  while(a >= max_num_vertex);
    
	// начальное заполнение массива минимальных путей
	for (i = 0; i < max_num_vertex; i++) {
        minimum_cost_crossings[i] = infinity;
	    new_minimum_cost_crossings[i] = infinity;
    }
	minimum_cost_crossings[a] = 0;

	stabilization = 0;
    
    // пока не наступила стабилизация
	while (!stabilization) {
        // перебор всех вершин
        for (i = 0; i < max_num_vertex; i++) {
            min = infinity;
            // поиск минимального пути
            for (j = 0; j < max_num_vertex; j++) {
                temp = minimum_cost_crossings[j] + weight_matrix[i][j];
                if (temp > infinity) {
                    temp = infinity;
                }
                if (temp < min) {
                    min = temp;
                    new_minimum_cost_crossings[i] = temp;
                }
            }
        }

        // определяем, не наступила ли стабилизация
        // сравнивая старые и новые показатели стоимости
        stabilization = 1;
        for (i = 0; i < max_num_vertex; i++) {
            if (minimum_cost_crossings[i] != new_minimum_cost_crossings[i]) {
                stabilization = 0;
            }
            minimum_cost_crossings[i] = new_minimum_cost_crossings[i];
        }
    }

	printf("вывод результатов:\n");
	for (i = 0; i < max_num_vertex; i++) {
        printf(" %d\t-", i);
        if (minimum_cost_crossings[i] >= infinity) {
            printf("\tбеск\n");
        }
        else {
            printf(" \t%d\n", minimum_cost_crossings[i]);
        }
    }

	printf("конец работы программы\n");
	return 0;
}

