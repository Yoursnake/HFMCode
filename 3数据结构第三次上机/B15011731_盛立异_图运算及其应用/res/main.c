#include <stdio.h>
#include <stdlib.h>
#include "ADT.h"

int main(){
	int i;
	int u, v, w;
	char choice;
	Graph *g = (Graph*)malloc(sizeof(Graph));
	//g->Vertices = 4;

	printf("������һ���Ľ������");
	scanf_s("%d", &g->Vertices);
	g->A = (ENode*)malloc(g->Vertices*sizeof(ENode));
	/*��ʼ��*/
	for (i = 0; i < g->Vertices; i++){
		g->A[i] = NULL;			//��ʼ�����б�ͷ�ÿ�
	}
	
	printf("��������Ͷ�ӦȨֵ��\n");
	printf("u=");
	scanf_s("%d", &u);
	printf("v=");
	scanf_s("%d", &v);
	printf("w=");
	scanf_s("%d", &w);
	getchar();
	Add(g,u,v,w);
	while(1){
		printf("�Ƿ��������(y/n)\n");
		choice = getchar();
		getchar();
		if (choice == 'n' || choice == 'N') break;
		printf("��������Ͷ�ӦȨֵ��\n");
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
	printf("�ڽӱ�ṹΪ��\n");
	Traversal_DFS(*g);

	//PathAll(g,2,0);
	printf("\n");
	printf("����u��v�õ�u��v�����м�·��\n");
	printf("u=");
	scanf_s("%d", &u);
	printf("v=");
	scanf_s("%d", &v);
	PathAll(g, u, v);

	minTranfer();

	system("pause");
	return 0;
}