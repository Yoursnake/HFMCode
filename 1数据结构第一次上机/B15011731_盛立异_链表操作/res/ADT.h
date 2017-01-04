#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

#define SIZE 5
#define IS_FULL(ptr) (!(ptr))

typedef char T;

typedef struct node
{
	T Element[SIZE];
	struct node* Link;
}Node;


void PrintElement(T *x)
{
	printf("%s  ", x);
}

Node* NewNode()
{
	Node* p = (Node*)malloc(sizeof(Node));
	if (IS_FULL(p)){
		fprintf(stderr, "The memery is full\n");
		exit(1);
	}
	p->Link = NULL;
	return p;
}

Node* NewNode1()
{
	char a[5];
	Node* p = (Node*)malloc(sizeof(Node));
	if (IS_FULL(p)){
		fprintf(stderr, "The memery is full\n");
		exit(1);
	}
	getchar();
	strcpy(p->Element, gets(a));
	p->Link = NULL;
	return p;
}

Node* NewNode2(T *x)
{
	Node* p = (Node*)malloc(sizeof(Node));
	if (IS_FULL(p)){
		fprintf(stderr, "The memery is full\n");
		exit(1);
	}
	strcpy(p->Element, x);
	p->Link = NULL;
	return p;
}