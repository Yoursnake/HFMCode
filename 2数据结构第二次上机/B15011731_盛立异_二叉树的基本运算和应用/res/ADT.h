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

//二叉树操作
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
void SuccOrd(void(*Visit)(BTNode* u), BTNode *t, Queue *q);//层序遍历
void SuccOrder(BTree Bt, void(*Visit)(BTNode* u));

//队列操作
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
/*删除一棵树*/
void BreakBT(BTree* Bt, T x, BTree *Lt, BTree *Rt){
	BTNode* p = Bt->Root;
	if (p){
		x = p->Element;			//保存传入树的根节点的数据
		Lt->Root = p->Lchild;	//将传入树的左子树用二叉树 Lt 接收
		Rt->Root = p->Rchild;	//将传入树的右子树用二叉树 Rt 接收
		Bt->Root = NULL;		//将传入树的根节点置空以完成二叉树的删除
		free(p);
	}
}
/*打印一个二叉树元素的数据*/
void Visit(BTNode* p){
	printf("%c", p->Element);	
}
/*前序遍历*/
void PreOrd(void(*Visit)(BTNode* u), BTNode *t){
	if (t){
		(*Visit)(t);
		PreOrd(Visit, t->Lchild);
		PreOrd(Visit, t->Rchild);
	}
}
/*中序遍历*/
void InOrd(void(*Visit)(BTNode* u), BTNode *t){
	if (t){
		InOrd(Visit, t->Lchild);
		(*Visit)(t);
		InOrd(Visit, t->Rchild);
	}
}
/*后序遍历*/
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
/*计算一个结点下的叶子数*/
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
/*计算一棵二叉树的叶子数*/
int SizeofBT(BTree Bt){
	return Size(Bt.Root);
}
/*计算一个结点所在高度*/
int Depth(BTNode* p){
	if (!p)return 0;
	else return 1 + max(Depth(p->Lchild), Depth(p->Rchild));
}
/*计算一课二叉树所在高度*/
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
/*拷贝一棵二叉树*/
BTree CopyofBT(BTree Bt){
	BTree a;
	a.Root = Copy(Bt.Root);
	return a;
}
/*交换一棵二叉树的左右子树*/
void ExChangeBT(BTree* Bt){
	BTNode *p = NewNode();
	p = Bt->Root->Lchild;
	Bt->Root->Lchild = Bt->Root->Rchild;
	Bt->Root->Rchild = p;
}

/*层序遍历*/
void SuccOrd(void(*Visit)(BTNode* u), BTNode *t, Queue *q){
	BTNode *a = NewNode();

	inQueue(t, q);
	while (q->Size){				//当队列中没有元素时终止循环
		*a = outQueue(q);			//每次循环都出队一个元素
		(*Visit)(a);
		if (a->Lchild != NULL){
			inQueue(a->Lchild,q);	//每次循环都把出队的元素的左子树的结点和右子树的结点入队
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


//队列操作
/*判断队列是否为空*/
int IsEmpty(Queue* Q){
	return Q->Size == 0;
}
/*判断队列是否已满*/
int IsFull(Queue* Q){
	return Q->Size == Q->Capacity;
}
/*将一个列表置空*/
void MakeEmpty(Queue* Q){
	Q->Size = 0;
	Q->Front = 1;
	Q->Rear = 0;
}
/*创建一个队列，传入参数代表队列长度*/
Queue *CreateQueue(int capacity){
	Queue *Q = (Queue*)malloc(sizeof(Queue));
	Q->Capacity = capacity;
	Q->Front = Q->Rear = 0;
	Q->Size = 0;
	Q->Array = (BTNode*)malloc(sizeof(BTNode)*capacity);
	return Q;
}
/*入队*/
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
/*出队*/
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
/*释放内存*/
void deleteQueue(Queue *Q){
	if (Q != NULL){
		free(Q->Array);
		free(Q);
	}
}