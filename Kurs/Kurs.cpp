// Kurs.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "locale.h"
#include "time.h"
#include "stdlib.h"
#include "conio.h"
#include <iostream>
#include <vector>

using namespace std;


int* GraphColoring(int** Matrix, const unsigned int size)
{
	struct v {
		unsigned int n; // номер вершины
		unsigned int color; // цвет вершины, 0 - не окрашена
	};
	int* ColorArray = NULL; // возвращаемый массив цветов, индексы - номера вершин, значения - присвоенный цвет
	unsigned int r = 1; // счётчик цветов
	if( !(ColorArray = (int*)calloc(size, sizeof(int))) )
			exit(EXIT_FAILURE);

	ColorArray[0] = 1;
	/*
	Проходим по матрице смежности и смотрим, есть ли из i-ой вершины путь в k-ю, после чего составляем
	локальный массив-буфер, в который записываем номера и цвета всех смежных i-ой вершин, после чего красим
	текущую в минимальный доступный цвет и заносим этот цвет в ColorArray.
	   В цикле:
			i - вершина, которую нужно покрасить;
			k - вершина, смежная i-ой;

	*/
	for(unsigned int i = 1; i < size; i++) {
		v b = {0}; // буферная вершина
		vector<v> buf; // локальный вектор-буфер

		/* Каждую итерацию этот цикл составляет вектор всех вершин, смежных i-ой */
		for(unsigned int k = 0; k < size; k++) {
			if(Matrix[i][k]) {
				b.n = k;
				b.color = ColorArray[k];
				buf.push_back(b);
			}
		}
		if(buf.size()) { // если размер буфера равен 0, то вершина изолирована
			
			/* Сортируем буфер по возрастанию цветов */
			while (1) { // проходим по массиву, пока не отсортирован
				bool operated = false; // показывает, была ли проведена операция над массивом
				for(unsigned int j = 1; j < buf.size(); j++) {
					if (buf[j].color < buf[j - 1].color) {
						b = buf[j];
						buf[j] = buf[j - 1];
						buf[j - 1] = b;
						operated = true;
					}
				}
				if(!operated) break;
			}

			printf("\nSorted buf:\n");
			for(int j = 0; j < buf.size(); j++) {
				printf("%d ", buf[j].n);
			}
			printf("\n\n");
			for(int j = 0; j < buf.size(); j++) {
				printf("%d ", buf[j].color);
			}
			/* Этот цикл находит минимальный неиспользованный цвет в буфере */
			int CurrentColor = 0; // Собственно искомый цвет

			for(int j = 1; j < buf.size(); j++) {
				if((buf[j].color - buf[j - 1].color) >= 2) {
					CurrentColor = buf[j - 1].color + 1;
					break;
				}
			}
			if(!CurrentColor) 
				CurrentColor = ++r;
			ColorArray[i] = CurrentColor;
			}
		else {
			ColorArray[i] = 1; // красим все изолированные вершины в цвет 1
		}
		buf.clear();
	}

	return ColorArray;
}




int _tmain(int argc, _TCHAR* argv[])
{
	setlocale(LC_ALL, "Rus");
	//srand(time(NULL));
	unsigned int size = 0; // число вершин графа
	int** G = NULL; // матрица смежности
	int* color = NULL; // массив цветов

	/* Вводим число вершин */
/*	printf("Введите количество вершин графа: ");
	scanf("%d", &size);
	fflush(stdin); */
	size = 7; // TODO: Delete
	/* Инициализируем матрицу смежности */
	if( !(G = (int**)malloc(size * sizeof(int*))) )
			exit(EXIT_FAILURE);
	for(unsigned int i = 0; i < size; i++) {
		if( !(G[i] = (int*)malloc(size * sizeof(int))) )
			exit(EXIT_FAILURE);
	}
	for(unsigned int i = 0; i < size; i++) {
		for(unsigned int j = 0; j < size; j++) {
			if(i != j) {
				G[i][j] = rand() % 2;
				G[j][i] = G[i][j];
			}
			else {
				G[i][j] = 0;
			}
		}
	}
	/* Выводим матрицу на экран */
	for(unsigned int i = 0; i < size; i++) {
		for(unsigned int j = 0; j < size; j++) {
			printf("%d ", G[i][j]);
		}
		printf("\n");
	}

	/* Создаём массив цветов */	
	color = GraphColoring(G, size);
	
	/* Выводим массив цветов на экран */
	printf("\nColors: ");
	for(unsigned int j = 0; j < size; j++) {
		printf("%d ", color[j]);
	}

	getch();
	return 0;
}

	/*					Тестовая Матрица
					  0, 0, 1, 1, 0, 1, 1,
					  0, 0, 1, 0, 0, 0, 1, 
					  1, 1, 0, 1, 1, 1, 1, 
					  1, 0, 1, 0, 0, 0, 0, 
					  0, 0, 1, 0, 0, 1, 1, 
					  1, 0, 1, 0, 1, 0, 1, 
					  1, 1, 1, 0, 1, 1, 0,
	*/
