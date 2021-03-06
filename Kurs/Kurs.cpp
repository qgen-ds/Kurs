// Kurs.cpp: ���������� ����� ����� ��� ����������� ����������.
//

#include "stdafx.h"
#include "locale.h"
#include "time.h"
#include "stdlib.h"
#include "conio.h"
#include "GraphColoring.h"



int _tmain(int argc, _TCHAR* argv[])
{
	setlocale(LC_ALL, "Rus");
	srand(time(NULL));
	unsigned int size = 0; // ����� ������ �����
	int** G = NULL; // ������� ���������
	int* color = NULL; // ������ ������

	/* ���� ����� */
	char in = 0;
	char FName[260] = {0};
	FILE* File = NULL;
	while(1) {
		static vector<int> buf;
		printf("\n������ ���� �� �����? (Y/N): ");
		in = _getche();
		fflush(stdin);
		switch(in) {
			case 'Y':
			case 'y':
				printf("\n������� ��� �����: ");
				if( !(File = fopen(strcat(gets(FName), ".txt"), "rt")) ) {
					printf("\n�� ������� ������� ����. ��������� �������.");
					strncpy(FName, "", strlen(FName));
					in = 0;
					continue;
				}
				fseek(File, 0, SEEK_END);
				size = ftell(File);
				rewind(File);
				if(!size) {
					printf("\n���� ����. ��������� �������");
					continue;
				}
				else 
					size = 0;
				 do {
					static int b = 0;
					fscanf(File, "%d", &b);
					buf.push_back(b);
					size++;
				} while(!feof(File));
				fclose(File); File = NULL;
				size = sqrt((float)size);
				if( !(G = (int**)malloc(size * sizeof(int*))) )
					exit(EXIT_FAILURE);
				for(unsigned int i = 0; i < size; i++) {
					if( !(G[i] = (int*)malloc(size * sizeof(int))) )
						exit(EXIT_FAILURE);
				}

				for(unsigned int i = 0; i < size; i++) {
					for(unsigned int j = 0; j < size; j++) {
						G[i][j] = buf[i * size + j];
					}
				}
				break;
			case 'N':
			case 'n':
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
				break;
			default:
				in = 0;
				continue;
		};
		buf.clear();
		break;
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
	
	/* ����� � ���� */
	in = 0;
	strncpy(FName, "", strlen(FName));
	while(1) {
		printf("\n��������� ��������� � ����? (Y/N): ");
		in = _getche();
		fflush(stdin);
		switch(in) {
			case 'Y':
			case 'y':
				printf("\n������� ��� �����: ");
				if( !(File = fopen(strcat(gets(FName), ".txt"), "w+t")) ) {
					printf("\n�� ������� ������� ����. ��������� �������.");
					strncpy(FName, "", strlen(FName));
					in = 0;
					continue;
				}
				fprintf(File, "�������: ");
				for(unsigned int j = 0; j < size; j++) {
					fprintf(File, "%d ", j);
				}
				fprintf(File, "\n�����: ");
				for(unsigned int j = 0; j < size; j++) {
					fprintf(File, "%d ", color[j]);
				}
				fclose(File);
			case 'N':
			case 'n':
				free(color); color = NULL;
				for(unsigned int i = 0; i < size; i++) {
					free(G[i]);
					G[i] = NULL;
				}
				free(G); G = NULL;
				exit(EXIT_SUCCESS);
			default:
				in = 0;
				continue;
		};
	}
}