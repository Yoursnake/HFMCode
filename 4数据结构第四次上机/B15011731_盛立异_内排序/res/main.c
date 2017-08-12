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
		printf("请输入要生成多少个随机数。(0~100000)\n");
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

		printf("\n1.直接插入排序\n2.冒泡排序\n3.改进的冒泡排序\n4.选择排序\n5.快速排序\n6.改进的快速排序\n使用哪种排序方式。");

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

			printf("该排序算法使用时间为 %f second\n", (end - start) / CLOCKS_PER_SEC);
			printf("\n是否使用其他排序方式(y/n)\n");
			isContinue = getchar();
			getchar();
			if (isContinue == 'N' || isContinue == 'n') break;
			else printf("使用哪种方式。");
		} while (1);
		
		printf("\n");
		printf("是否继续测试(y/n)\n");
		isContinue = getchar();
		getchar();
		if (isContinue == 'N' || isContinue == 'n') break;
	} while (1);
	
	printf("\n");
	
	system("pause");
	return 0;
}