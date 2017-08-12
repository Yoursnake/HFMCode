#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#define IS_FULL(ptr) (!(ptr))
#define MaxSize 20

typedef int T;

typedef struct btnode{
	int Element;
	char name;
	struct btnode* Lchild, *Rchild;
}BTNode;

typedef struct btree{
	struct btnode* Root;
}BTree;

typedef struct hfmCode{
	char code[10];
	char name;
}HFMCode;


void outputHMFNodeCode(BTNode *bt, int len, int a[]);

BTNode* NewNode(){
	BTNode* p = (BTNode*)malloc(sizeof(BTNode));
	char c;
	if (IS_FULL(p)){
		fprintf(stderr, "The memery is full\n");
		exit(1);
	}
	return p;
}


void CreateBT(BTree* Bt){
	Bt->Root = NULL;
}

void MakeBT(BTree* Bt, char na, int x, BTree *Lt, BTree *Rt){
	BTNode* p = NewNode();
	p->Element = x;
	p->name = na;
	p->Lchild = Lt->Root;
	p->Rchild = Rt->Root;
	Lt->Root = Rt->Root = NULL;
	Bt->Root = p;
}
//�Ҷ������Ȩֵ��С�����������±�
void Fmin(BTree *ht,int* k1,int* k2,int k){
	int i;
	*k1 = 0;
	for (i = 0; i < k; i++){
		if (ht[*k1].Root->Element > ht[i].Root->Element)
			*k1 = i;
	}
	if (*k1 != 0)*k2 = *k1 - 1;
	else *k2 = *k1 + 1;			//��֤ *k2 ������ *k1
	for (i = 0; i < k; i++){
		if (ht[*k2].Root->Element > ht[i].Root->Element && i != *k1)
			*k2 = i;
	}
}
//������������
BTree CreateHFMTree(char na[], int w[], int n){
	BTree zero, ht[MaxSize];
	int i, k, k1, k2;
	CreateBT(&zero);
	for (i = 0; i < n; i++)MakeBT(&ht[i], na[i], w[i], &zero, &zero);
	for (k = n - 1; k > 0; k--){
		Fmin(ht, &k1, &k2, k+1);
		MakeBT(&ht[k1],' ',ht[k1].Root->Element+ht[k2].Root->Element,&ht[k1],&ht[k2]);
		ht[k2] = ht[k];
	}
	return ht[0];
}

void Visit(BTNode* p){
	printf("%d  ", p->Element);
}

void PreOrd(void(*Visit)(BTNode* u), BTNode *t){
	if (t){
		(*Visit)(t);
		PreOrd(Visit, t->Lchild);
		PreOrd(Visit, t->Rchild);
	}
}

void InOrd(void(*Visit)(BTNode* u), BTNode *t){
	if (t){
		InOrd(Visit, t->Lchild);
		(*Visit)(t);
		InOrd(Visit, t->Rchild);
	}
}

void PostOrd(void(*Visit)(BTNode* u), BTNode *t){
	if (t){
		PostOrd(Visit, t->Lchild);
		PostOrd(Visit, t->Rchild);
		(*Visit)(t);
	}
}

void PreOrder(BTree Bt, void(*Visit)(BTNode* u)){
	PreOrd(Visit, Bt.Root);
}

void InOrder(BTree Bt, void(*Visit)(BTNode* u)){
	InOrd(Visit, Bt.Root);
}

void PostOrder(BTree Bt, void(*Visit)(BTNode* u)){
	PostOrd(Visit, Bt.Root);
}

void outputHMFTreeCode(BTree *bt){
	int a[10];
	outputHMFNodeCode(bt->Root, 0, a);
}


//���ɱ���
int j = 0;
static HFMCode hfmCode[10];
void outputHMFNodeCode(BTNode *bt, int len, char a[]){
	

	int i;
	if (bt != NULL){
		/*��Ҷ�ӽڵ�ʱ�ſ�ʼ��ӡ����ʱ����a[]�����˸ýڵ�ı���*/
		if (bt->Lchild == NULL && bt->Rchild == NULL){
			printf("�ڵ� %c ȨֵΪ %d  ����Ϊ��", bt->name, bt->Element);
			for (i = 0; i < len; i++){
				printf("%c", a[i]);			
				hfmCode[j].code[i] = a[i];
			}
			printf("\n");
			hfmCode[j].name = bt->name;
			j++;
		}
		else{
			a[len] = '0';		//��ڵ�Ϊ0
			outputHMFNodeCode(bt->Lchild, len + 1, a);	//�ݹ����õ�Ҷ�ӵı���
			a[len] = '1';		//�ҽڵ�Ϊ1
			outputHMFNodeCode(bt->Rchild, len + 1, a);
		}
	}
	
	
}

//��������ַ������б���
void Encode(FILE *textfile, FILE *codefile, char s[]){
	int i = 0, k = 0, x = 0;
	while (s[i] != '\0'){
		for (k = 0; k < j; k++){
			if (hfmCode[k].name == s[i]){
				/*����ַ����е��ַ��ʹ洢�ı���ṹ�е��ַ�һֱ��������ӡ*/
				while (hfmCode[k].code[x] != '\0'){
					//printf("%c", hfmCode[k].code[x]);
					fputc(hfmCode[k].code[x], codefile);
					x++;
				}
				x = 0;
				/*���ַ�����ӡ��textfile.txt�ļ���*/
				fputc(s[i], textfile);
				//fputc('\n',codefile);
			}	
		}
		i++;
	}
}
/*����*/
void Decode(FILE *codefile, FILE *resultfile,BTree HFMTree){
	char s[100];
	int i = 0;
	BTNode *p = HFMTree.Root;
	fscanf_s(codefile,"%s",&s,_countof(s));		//�Ƚ�������ļ��ж�����
	while (s[i-1] != '\0'){
		/*�������Ҷ�ӽڵ��жϱ��룬0����������1��������*/
		if (p->Lchild != NULL||p->Rchild != NULL){
			if (s[i] == '0'){
				p = p->Lchild;
			}
			else if (s[i] == '1'){
				p = p->Rchild;
			}
			i++;
		}
		/*�����Ҷ�ӽڵ㽫�����ַ���ӡ����*/
		else{
			fprintf_s(resultfile,"%c",p->name);		
			p = HFMTree.Root;
		}
		
	}
}