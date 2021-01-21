#include "stdafx.h"
#include "GraphColoring.h"
#include <iostream>
#include <vector>



int* GraphColoring(int** Matrix, const unsigned int size)
{
	int* ColorArray = NULL; // возвращаемый массив цветов, индексы - номера вершин, значения - присвоенный цвет
	if( !(ColorArray = (int*)calloc(size, sizeof(int))) )
			exit(EXIT_FAILURE);

	ColorArray[0] = 1;
	/*
	Проходим по матрице смежности и смотрим, есть ли из i-ой вершины путь в k-ю, после чего составляем
	локальный массив-буфер, в который записываем цвета всех смежных i-ой вершин, после чего красим
	текущую в минимальный доступный цвет и заносим этот цвет в ColorArray.
	   В цикле:
			i - вершина, которую нужно покрасить.
	*/
	for(unsigned int i = 1; i < size; i++) {
		static vector<int> buf; // локальный вектор-буфер

		/* Каждую итерацию этот цикл составляет вектор цветов всех вершин, смежных i-ой */
		for(unsigned int k = 0; k < size; k++) {
			if(Matrix[i][k]) {
				buf.push_back(ColorArray[k]);
			}
		}

		if(!buf.empty()) { // если буфер пустой, то вершина изолирована
			
			/* Сортируем буфер по возрастанию цветов */
			while (1) { // проходим по массиву, пока не отсортирован
				int b = 0;
				bool operated = false; // показывает, была ли проведена операция над массивом
				for(unsigned int j = 1; j < buf.size(); j++) {
					if (buf[j] < buf[j - 1]) {
						b = buf[j];
						buf[j] = buf[j - 1];
						buf[j - 1] = b;
						operated = true;
					}
				}
				if(!operated) break;
			}

			/* Проверка на разрыв между 0 (отсутствие цвета) и минимальным элементом буфера.
			   Если есть разрыв хотя бы в единицу, красим i-ю вершину в цвет 1. */
			if(buf[0] >= 2) {
				ColorArray[i] = 1;
				buf.clear();
				continue;
			}

			/* Этот цикл находит минимальный неиспользованный цвет в буфере */
			int TargetColor = 0; // Собственно искомый цвет
			for(unsigned int j = 1; j < buf.size(); j++) {
				if((buf[j] - buf[j - 1]) >= 2) {
					TargetColor = buf[j - 1]  + 1;
					break;
				}
			}
			if(!TargetColor) // если такого цвета нет в буфере, то создаём новый цвет и красим в него i-ю вершину
				TargetColor = buf[buf.size() - 1] + 1;
			ColorArray[i] = TargetColor;
		}
		else {
			ColorArray[i] = 1; // красим все изолированные вершины в цвет 1
		}
		buf.clear();
	}

	return ColorArray;
}