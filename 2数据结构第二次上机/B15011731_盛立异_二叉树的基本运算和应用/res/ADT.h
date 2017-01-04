#define IS_FULL(ptr) (!(ptr))

typedef char T;

typedef struct btnode{
	T Element;
	struct btnode* Lchild, *Rchild;
}BTNode;

typedef struct btree{
	struct btnode* Root;
}BTree;

struct queueRecord{
	int Capacity;
	int Front;
	int Rear;
	int Size;
	BTNode *Array;
};
typedef struct queueRecord Queue;

//����������
BTNode* NewNode();
void CreateBT(BTree* Bt);
void MakeBT(BTree* Bt, T x, BTree *Lt, BTree *Rt);
void BreakBT(BTree* Bt, T x, BTree *Lt, BTree *Rt);
void Visit(BTNode* p);
void PreOrd(void(*Visit)(BTNode* u), BTNode *t);
void InOrd(void(*Visit)(BTNode* u), BTNode *t);
void PostOrd(void(*Visit)(BTNode* u), BTNode *t);
void PreOrder(BTree Bt, void(*Visit)(BTNode* u));
void InOrder(BTree Bt, void(*Visit)(BTNode* u));
void PostOrder(BTree Bt, void(*Visit)(BTNode* u));
int Size(BTNode* p);
int SizeofBT(BTree Bt);
int Depth(BTNode* p);
int DepthofBT(BTree Bt);
BTNode* Copy(BTNode* p);
BTree CopyofBT(BTree Bt);
void ExChangeBT(BTree* Bt);
void SuccOrd(void(*Visit)(BTNode* u), BTNode *t, Queue *q);//�������
void SuccOrder(BTree Bt, void(*Visit)(BTNode* u));

//���в���
int IsEmpty(Queue* Q);
int IsFull(Queue* Q);
Queue *CreateQueue(int MaxElements);
void DisposeQueue(Queue Q);
void MakeEmpty(Queue* Q);
void inQueue(BTNode *x, Queue* Q);
BTNode outQueue(Queue *Q);
T Front(Queue Q);
void Dequeue(Queue Q);
T FrontAndDequeue(Queue Q);


BTNode* NewNode(){
	BTNode* p = (BTNode*)malloc(sizeof(BTNode));
	if (IS_FULL(p)){
		fprintf(stderr, "The memery is full\n");
		exit(1);
	}
	return p;
}

void CreateBT(BTree* Bt){
	Bt->Root = NULL;
}

void MakeBT(BTree* Bt, T x, BTree *Lt, BTree *Rt){
	BTNode* p = NewNode();
	p->Element = x;
	p->Lchild = Lt->Root;
	p->Rchild = Rt->Root;
	Lt->Root = Rt->Root = NULL;
	Bt->Root = p;
}
/*ɾ��һ����*/
void BreakBT(BTree* Bt, T x, BTree *Lt, BTree *Rt){
	BTNode* p = Bt->Root;
	if (p){
		x = p->Element;			//���洫�����ĸ��ڵ������
		Lt->Root = p->Lchild;	//�����������������ö����� Lt ����
		Rt->Root = p->Rchild;	//�����������������ö����� Rt ����
		Bt->Root = NULL;		//���������ĸ��ڵ��ÿ�����ɶ�������ɾ��
		free(p);
	}
}
/*��ӡһ��������Ԫ�ص�����*/
void Visit(BTNode* p){
	printf("%c", p->Element);	
}
/*ǰ�����*/
void PreOrd(void(*Visit)(BTNode* u), BTNode *t){
	if (t){
		(*Visit)(t);
		PreOrd(Visit, t->Lchild);
		PreOrd(Visit, t->Rchild);
	}
}
/*�������*/
void InOrd(void(*Visit)(BTNode* u), BTNode *t){
	if (t){
		InOrd(Visit, t->Lchild);
		(*Visit)(t);
		InOrd(Visit, t->Rchild);
	}
}
/*�������*/
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
/*����һ������µ�Ҷ����*/
int Size(BTNode* p){
	int s, s1, s2;
	if (!p)return 0;
	else{
		s1 = Size(p->Lchild);
		s2 = Size(p->Rchild);
		s = s1 + s2 + 1;
		return s;
	}
}
/*����һ�ö�������Ҷ����*/
int SizeofBT(BTree Bt){
	return Size(Bt.Root);
}
/*����һ��������ڸ߶�*/
int Depth(BTNode* p){
	if (!p)return 0;
	else return 1 + max(Depth(p->Lchild), Depth(p->Rchild));
}
/*����һ�ζ��������ڸ߶�*/
int DepthofBT(BTree Bt){
	return Depth(Bt.Root);
}

BTNode* Copy(BTNode* p){
	BTNode* q;
	if (!p)return NULL;
	q = NewNode();
	q->Element = p->Element;
	q->Lchild = Copy(p->Lchild);
	q->Rchild = Copy(p->Rchild);
	return q;
}
/*����һ�ö�����*/
BTree CopyofBT(BTree Bt){
	BTree a;
	a.Root = Copy(Bt.Root);
	return a;
}
/*����һ�ö���������������*/
void ExChangeBT(BTree* Bt){
	BTNode *p = NewNode();
	p = Bt->Root->Lchild;
	Bt->Root->Lchild = Bt->Root->Rchild;
	Bt->Root->Rchild = p;
}

/*�������*/
void SuccOrd(void(*Visit)(BTNode* u), BTNode *t, Queue *q){
	BTNode *a = NewNode();

	inQueue(t, q);
	while (q->Size){				//��������û��Ԫ��ʱ��ֹѭ��
		*a = outQueue(q);			//ÿ��ѭ��������һ��Ԫ��
		(*Visit)(a);
		if (a->Lchild != NULL){
			inQueue(a->Lchild,q);	//ÿ��ѭ�����ѳ��ӵ�Ԫ�ص��������Ľ����������Ľ�����
		}
		if (a->Rchild != NULL){
			inQueue(a->Rchild, q);
		}
	}
}

void SuccOrder(BTree Bt, void(*Visit)(BTNode* u)){
	Queue *q = CreateQueue(20);
	SuccOrd(Visit, Bt.Root, q);
}


//���в���
/*�ж϶����Ƿ�Ϊ��*/
int IsEmpty(Queue* Q){
	return Q->Size == 0;
}
/*�ж϶����Ƿ�����*/
int IsFull(Queue* Q){
	return Q->Size == Q->Capacity;
}
/*��һ���б��ÿ�*/
void MakeEmpty(Queue* Q){
	Q->Size = 0;
	Q->Front = 1;
	Q->Rear = 0;
}
/*����һ�����У��������������г���*/
Queue *CreateQueue(int capacity){
	Queue *Q = (Queue*)malloc(sizeof(Queue));
	Q->Capacity = capacity;
	Q->Front = Q->Rear = 0;
	Q->Size = 0;
	Q->Array = (BTNode*)malloc(sizeof(BTNode)*capacity);
	return Q;
}
/*���*/
void inQueue(BTNode *x, Queue* Q){
	if (IsFull(Q)){
		printf("Queue is full\n");
		exit(1);
	}
	Q->Size++;
	Q->Array[Q->Rear++] = *x;
	if (Q->Rear == Q->Capacity)
		Q->Rear = 0;
}
/*����*/
BTNode outQueue(Queue *Q){
	BTNode temp;
	if (IsEmpty(Q)){
		printf("Queue is empty\n");
		exit(1);
	}
	temp = Q->Array[Q->Front];
	Q->Size--;
	Q->Front++;
	if (Q->Front == Q->Capacity)
		Q->Front = 0;
	return temp;
}
/*�ͷ��ڴ�*/
void deleteQueue(Queue *Q){
	if (Q != NULL){
		free(Q->Array);
		free(Q);
	}
}