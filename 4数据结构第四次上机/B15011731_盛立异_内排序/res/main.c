#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <time.h>
#include "ADT.h"

int main(){
	int i;
	int size;
	int choice;
	char isContinue;
	double start, end;
	List *list = (List*)malloc(sizeof(List));
	T temp[MaxSize];
	list->MaxList = 100000;
	do{
		printf("������Ҫ���ɶ��ٸ��������(0~100000)\n");
		scanf_s("%d",&size);
		if (size > list->MaxList) 
			continue;
		else
			list->Size = size;

		for (i = 0; i<list->Size; i++){
			list->Elements[i] = rand() % 10;
		}

		for (i = 0; i<list->Size; i++){
			temp[i] = list->Elements[i];
		}

		printf("\n1.ֱ�Ӳ�������\n2.ð������\n3.�Ľ���ð������\n4.ѡ������\n5.��������\n6.�Ľ��Ŀ�������\nʹ����������ʽ��");

		do{
			for (i = 0; i<list->Size; i++){
				list->Elements[i] = temp[i];
			}
			scanf_s("%d", &choice);
			getchar();
			start = clock();
			switch (choice){
			case 1:InsertSort(list); break;
			case 2:BubbleSort(list); break;
			case 3:BubbleSort1(list); break;
			case 4:SelectSort(list); break;
			case 5:QuickSort(list); break;
			case 6:ImprovedSort(list); break;
			}
			end = clock();

			printf("�������㷨ʹ��ʱ��Ϊ %f second\n", (end - start) / CLOCKS_PER_SEC);
			printf("\n�Ƿ�ʹ����������ʽ(y/n)\n");
			isContinue = getchar();
			getchar();
			if (isContinue == 'N' || isContinue == 'n') break;
			else printf("ʹ�����ַ�ʽ��");
		} while (1);
		
		printf("\n");
		printf("�Ƿ��������(y/n)\n");
		isContinue = getchar();
		getchar();
		if (isContinue == 'N' || isContinue == 'n') break;
	} while (1);
	
	printf("\n");
	
	system("pause");
	return 0;
}