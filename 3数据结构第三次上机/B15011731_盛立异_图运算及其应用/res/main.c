#include <stdio.h>
#include <stdlib.h>
#include "ADT.h"

int main(){
	int i;
	int u, v, w;
	char choice;
	Graph *g = (Graph*)malloc(sizeof(Graph));
	//g->Vertices = 4;

	printf("请输入一共的结点数：");
	scanf_s("%d", &g->Vertices);
	g->A = (ENode*)malloc(g->Vertices*sizeof(ENode));
	/*初始化*/
	for (i = 0; i < g->Vertices; i++){
		g->A[i] = NULL;			//开始将所有表头置空
	}
	
	printf("请输入结点和对应权值：\n");
	printf("u=");
	scanf_s("%d", &u);
	printf("v=");
	scanf_s("%d", &v);
	printf("w=");
	scanf_s("%d", &w);
	getchar();
	Add(g,u,v,w);
	while(1){
		printf("是否继续输入(y/n)\n");
		choice = getchar();
		getchar();
		if (choice == 'n' || choice == 'N') break;
		printf("请输入结点和对应权值：\n");
		printf("u=");
		scanf_s("%d", &u);
		printf("v=");
		scanf_s("%d", &v);
		printf("w=");
		scanf_s("%d", &w);
		getchar();
		Add(g, u, v, w);
	}
	/*Add(g, 1, 0, 4);
	Add(g, 1, 2, 5);
	Add(g, 2, 3, 3);
	Add(g, 3, 0, 1);
	Add(g, 3, 1, 1);*/
	printf("\n");
	printf("邻接表结构为：\n");
	Traversal_DFS(*g);

	//PathAll(g,2,0);
	printf("\n");
	printf("输入u和v得到u到v的所有简单路径\n");
	printf("u=");
	scanf_s("%d", &u);
	printf("v=");
	scanf_s("%d", &v);
	PathAll(g, u, v);

	minTranfer();

	system("pause");
	return 0;
}