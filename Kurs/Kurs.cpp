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
	int* ColorArray = NULL; // ������������ ������ ������, ������� - ������ ������, �������� - ����������� ����
	if( !(ColorArray = (int*)calloc(size, sizeof(int))) )
			exit(EXIT_FAILURE);

	ColorArray[0] = 1;
	/*
	�������� �� ������� ��������� � �������, ���� �� �� i-�� ������� ���� � k-�, ����� ���� ����������
	��������� ������-�����, � ������� ���������� ����� ���� ������� i-�� ������, ����� ���� ������
	������� � ����������� ��������� ���� � ������� ���� ���� � ColorArray.
	   � �����:
			i - �������, ������� ����� ���������.
	*/
	for(unsigned int i = 1; i < size; i++) {
		static vector<int> buf; // ��������� ������-�����

		/* ������ �������� ���� ���� ���������� ������ ������ ���� ������, ������� i-�� */
		for(unsigned int k = 0; k < size; k++) {
			if(Matrix[i][k]) {
				buf.push_back(ColorArray[k]);
			}
		}

		if(buf.size()) { // ���� ������ ������ ����� 0, �� ������� �����������
			
			/* ��������� ����� �� ����������� ������ */
			while (1) { // �������� �� �������, ���� �� ������������
				int b = 0;
				bool operated = false; // ����������, ���� �� ��������� �������� ��� ��������
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

			/* �������� �� ������ ����� 0 (���������� �����) � ������ � ����������� ��������� ������.
			   ���� ���� ������ ���� �� � �������, ������ i-� ������� � ���� 1. */
			if(buf[0] >= 2) {
				ColorArray[i] = 1;
				buf.clear();
				continue;
			}

			/* ���� ���� ������� ����������� ���������������� ���� � ������ */
			int TargetColor = 0; // ���������� ������� ����
			for(int j = 1; j < buf.size(); j++) {
				if((buf[j] - buf[j - 1]) >= 2) {
					TargetColor = buf[j - 1]  + 1;
					break;
				}
			}
			if(!TargetColor) // ���� ������ ����� ��� � ������, �� ������ ����� ���� � ������ � ���� i-� �������
				TargetColor = buf[buf.size() - 1] + 1;
			ColorArray[i] = TargetColor;
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
	srand(time(NULL));
	unsigned int size = 0; // ����� ������ �����
	int** G = NULL; // ������� ���������
	int* color = NULL; // ������ ������

	/* ������ ����� ������ */
	printf("������� ���������� ������ �����: ");
	scanf("%d", &size);
	fflush(stdin);
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