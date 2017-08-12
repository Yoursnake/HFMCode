#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <math.h>
#include "ADT.h"

int main(){
	BTree a, x, y, z; T e; Queue *q;
	int height; int nodeNum;
	BTree copyBt;
	CreateBT(&a); CreateBT(&x); CreateBT(&y); CreateBT(&z);
	MakeBT(&y, 'E', &a, &a);
	MakeBT(&z, 'F', &a, &a);
	MakeBT(&x, 'C', &y, &z);
	MakeBT(&y, 'D', &a, &a);
	MakeBT(&z, 'B', &y, &x);
	printf("先序排列：");
	PreOrder(z, Visit); printf("\n");
	printf("中序排列：");
	InOrder(z, Visit); printf("\n");
	printf("层序遍历：");
	SuccOrder(z, Visit); printf("\n\n");

	height = DepthofBT(z);
	nodeNum = SizeofBT(z);
	printf("二叉树的高度为%d\n",height);
	printf("二叉树的叶子节点数为%d\n\n", nodeNum);

	printf("复制后\n");
	copyBt = CopyofBT(z);
	printf("先序排列：");
	PreOrder(copyBt, Visit); printf("\n");
	printf("中序排列：");
	InOrder(copyBt, Visit); printf("\n");
	printf("层序遍历：");
	SuccOrder(z, Visit); printf("\n\n");

	printf("交换后\n");
	ExChangeBT(&z);
	printf("先序排列：");
	PreOrder(z, Visit); printf("\n");
	printf("中序排列：");
	InOrder(z, Visit); printf("\n");
	printf("层序遍历：");
	SuccOrder(z, Visit); printf("\n\n");

	printf("删除后\n");
	BreakBT(&z, &e, &y, &x);
	printf("先序排列：");
	PreOrder(z, Visit); printf("\n");
	printf("中序排列：");
	InOrder(z, Visit); printf("\n");

	
	system("pause");

	return 0;
}



