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
	printf("�������У�");
	PreOrder(z, Visit); printf("\n");
	printf("�������У�");
	InOrder(z, Visit); printf("\n");
	printf("���������");
	SuccOrder(z, Visit); printf("\n\n");

	height = DepthofBT(z);
	nodeNum = SizeofBT(z);
	printf("�������ĸ߶�Ϊ%d\n",height);
	printf("��������Ҷ�ӽڵ���Ϊ%d\n\n", nodeNum);

	printf("���ƺ�\n");
	copyBt = CopyofBT(z);
	printf("�������У�");
	PreOrder(copyBt, Visit); printf("\n");
	printf("�������У�");
	InOrder(copyBt, Visit); printf("\n");
	printf("���������");
	SuccOrder(z, Visit); printf("\n\n");

	printf("������\n");
	ExChangeBT(&z);
	printf("�������У�");
	PreOrder(z, Visit); printf("\n");
	printf("�������У�");
	InOrder(z, Visit); printf("\n");
	printf("���������");
	SuccOrder(z, Visit); printf("\n\n");

	printf("ɾ����\n");
	BreakBT(&z, &e, &y, &x);
	printf("�������У�");
	PreOrder(z, Visit); printf("\n");
	printf("�������У�");
	InOrder(z, Visit); printf("\n");

	
	system("pause");

	return 0;
}



