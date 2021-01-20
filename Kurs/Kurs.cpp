// Kurs.cpp: ���������� ����� ����� ��� ����������� ����������.
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
		unsigned int n; // ����� �������
		unsigned int color; // ���� �������, 0 - �� ��������
	};
	int* ColorArray = NULL; // ������������ ������ ������, ������� - ������ ������, �������� - ����������� ����
	unsigned int r = 1; // ������� ������
	if( !(ColorArray = (int*)calloc(size, sizeof(int))) )
			exit(EXIT_FAILURE);

	ColorArray[0] = 1;
	/*
	�������� �� ������� ��������� � �������, ���� �� �� i-�� ������� ���� � k-�, ����� ���� ����������
	��������� ������-�����, � ������� ���������� ������ � ����� ���� ������� i-�� ������, ����� ���� ������
	������� � ����������� ��������� ���� � ������� ���� ���� � ColorArray.
	   � �����:
			i - �������, ������� ����� ���������;
			k - �������, ������� i-��;

	*/
	for(unsigned int i = 1; i < size; i++) {
		v b = {0}; // �������� �������
		vector<v> buf; // ��������� ������-�����

		/* ������ �������� ���� ���� ���������� ������ ���� ������, ������� i-�� */
		for(unsigned int k = 0; k < size; k++) {
			if(Matrix[i][k]) {
				b.n = k;
				b.color = ColorArray[k];
				buf.push_back(b);
			}
		}
		if(buf.size()) { // ���� ������ ������ ����� 0, �� ������� �����������
			
			/* ��������� ����� �� ����������� ������ */
			while (1) { // �������� �� �������, ���� �� ������������
				bool operated = false; // ����������, ���� �� ��������� �������� ��� ��������
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
			/* ���� ���� ������� ����������� ���������������� ���� � ������ */
			int CurrentColor = 0; // ���������� ������� ����

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
			ColorArray[i] = 1; // ������ ��� ������������� ������� � ���� 1
		}
		buf.clear();
	}

	return ColorArray;
}




int _tmain(int argc, _TCHAR* argv[])
{
	setlocale(LC_ALL, "Rus");
	//srand(time(NULL));
	unsigned int size = 0; // ����� ������ �����
	int** G = NULL; // ������� ���������
	int* color = NULL; // ������ ������

	/* ������ ����� ������ */
/*	printf("������� ���������� ������ �����: ");
	scanf("%d", &size);
	fflush(stdin); */
	size = 7; // TODO: Delete
	/* �������������� ������� ��������� */
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
	/* ������� ������� �� ����� */
	for(unsigned int i = 0; i < size; i++) {
		for(unsigned int j = 0; j < size; j++) {
			printf("%d ", G[i][j]);
		}
		printf("\n");
	}

	/* ������ ������ ������ */	
	color = GraphColoring(G, size);
	
	/* ������� ������ ������ �� ����� */
	printf("\nColors: ");
	for(unsigned int j = 0; j < size; j++) {
		printf("%d ", color[j]);
	}

	getch();
	return 0;
}

	/*					�������� �������
					  0, 0, 1, 1, 0, 1, 1,
					  0, 0, 1, 0, 0, 0, 1, 
					  1, 1, 0, 1, 1, 1, 1, 
					  1, 0, 1, 0, 0, 0, 0, 
					  0, 0, 1, 0, 0, 1, 1, 
					  1, 0, 1, 0, 1, 0, 1, 
					  1, 1, 1, 0, 1, 1, 0,
	*/
