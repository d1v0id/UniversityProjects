/*
 * Реализация алгоритма Дейкстры.
 * Находит кратчайшее расстояние от одной из вершин графа до всех остальных.
 * Пример графа взят из Википедии http://ru.wikipedia.org/wiki/Алгоритм_Дейкстры
 */
#include <iostream>
#include <fstream>
#include <stdlib.h>
using namespace std;

#define SEQUENCE_SIZE 6
#define INT_MAX 0x7fff

struct dijkstraDesc {
	unsigned int *s;
	unsigned int w;
	unsigned int d;
	unsigned int *other_d;
	unsigned short int flag;
};

void print_dijkstra_in_table(dijkstraDesc *d, int size) {
	int i;
	int j;

	cout << "S\tw\tD(w)\t";
	for (j = 0; j < size - 1; j++) {
		cout << "D(" << j + 2 << ")\t";
	}
	cout << endl;
	for (i = 0; i < size; i++) {
		for (j = 0; j < size; j++) {
			if (d[i].s[j] != 0 ) {
				cout << d[i].s[j];
			}
		}
		cout << "\t";

		cout << d[i].w << "\t";

		cout << d[i].d << "\t";

		for (j = 1; j < size; j++) {
			if ((d[i].other_d[j] != 0) && (d[i].other_d[j] != INT_MAX)) {
				cout << d[i].other_d[j] << "\t";
			}
			else {
				cout << "-\t";
			}
		}

		cout << endl;
	}
	cout << endl;
}

void find_path_by_dijkstra(int **graph, int start, int size)
{
    int i;
    int j;

    dijkstraDesc d[size]; // исправить на список, стек или на динамический массив
    unsigned int parent[size]; // исправить на корректную запись пути

    for (i = 0; i < size; i++) {
    	d[i].s = new unsigned int[size];
    	for (j = 0; j < size; j++) {
    		d[i].s[j] = start;
    	}

    	d[i].w = 0;

    	d[i].d = graph[start][i];

    	d[i].other_d = new unsigned int[size];
    	for (j = 0; j < size; j++) {
    		d[i].other_d[j] = graph[i][j];
    	}

    	d[i].flag = 0;

    	parent[i] = start;
    }
    d[0].s[size - 1] = 1;

    // Пока известно только одно расстояние: от вершины start до нее же, равное 0
    parent[start] = 0;
    d[start].flag = 1;

    for (i = 0; i < size - 1; i++) {
        int k = 0;
        unsigned int minDistance = INT_MAX;

        // Находим минимальное расстояние до непомеченных вершин
        for (j = 0; j < size; j++) {
            if (!d[j].flag && minDistance > d[j].d) {
                minDistance = d[j].d;
                k = j;
            }
        }

        // Вершина k помечается просмотренной
        d[k].flag = 1;

        for (j = 0; j < size; j++) {
            // Если для вершины j еще не найдено кратчайшее расстояние от
            // нач. и из вершины k по дуге graph[k][j] путь в j короче
            // чем найденное ранее, то запоминаем его
            if (!d[j].flag && d[j].d > d[k].d + graph[k][j]) {
                d[j].d = d[k].d + graph[k][j];
                parent[j] = k;
            }
        }
    }

    // Запись маршрутов в структуру для таблицы
    int m = size - 1;
    for (i = size; i > start + 1; i--) {
    	int r = size - 1;
		for (j = i - 1; j > start; ) {
			d[m].s[r] = j + 1;
			r--;
			j = parent[j];
		}
		d[m].s[r] = start + 1;
		d[m].w = d[m].s[size - 1];
		m--;
	}

	print_dijkstra_in_table(d, size);
}

int load_graph_from_file(char *filename, int ***a)
{
	ifstream in(filename);
	if(!in) {
		cout << "Cannot open file.\n";
		return 0;
	}

	int d;
	int cnt = 0;

	while (!in.eof()) {
		in >> d;
		cnt++;
	}

	char buf[256];
	int rows_cnt = 0;

	in.close();
	in.clear();
	in.open(filename);

	while(!in.eof()) {
	in.getline(buf, 255);
		rows_cnt++;
	}
	in.close();
	in.clear();

	cnt--;
	rows_cnt--;
	int cols_cnt = cnt / rows_cnt;

	(*a) = new int*[rows_cnt];
	for(int i = 0; i < rows_cnt; i++) {
		(*a)[i] = new int[cols_cnt];
	}

	in.open(filename);
	for(int i = 0; i < rows_cnt; i++) {
		for(int j = 0; j < cols_cnt; j++) {
			in >> (*a)[i][j];
			cout << (*a)[i][j] << "\t";
		}
		cout << endl;
	}
	cout << endl;

	return rows_cnt;
}

int main(int argc, char **argv)
{
    /*int **graph = new int [SEQUENCE_SIZE][SEQUENCE_SIZE];
    graph = {
         { 0, 7, 9, 14, INT_MAX, INT_MAX },
         { 7, 0, 10, INT_MAX, INT_MAX, 15 },
         { 9, 10, 0, 2, INT_MAX, 11 },
         { 14, INT_MAX, 2, 0, 9, INT_MAX },
         { INT_MAX, INT_MAX, INT_MAX, 9, 0, 6 },
         { INT_MAX, 15, 11, INT_MAX, 6, 0 }
    };*/

	if (argc > 1) {
		int **graph = 0;
		int size = load_graph_from_file(argv[1], &graph);
		find_path_by_dijkstra(graph, 0, size);
	}
	else {
		cout << "Run: dijkstra filename.txt" << endl;
	}

    return 0;
}
