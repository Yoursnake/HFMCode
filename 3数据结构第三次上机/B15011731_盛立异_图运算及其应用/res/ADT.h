#include <malloc.h>
#include <stdio.h>

#define FALSE 0
#define TRUE 1
#define MaxSize 30

typedef int T;
typedef int BOOL;

typedef struct enode{
	int AdjVex;
	T W;
	struct enode* NextArc;
}ENode;
typedef struct graph{
	int Vertices;
	ENode** A;
}Graph;

void CreateGraph(Graph* g, int n){
	int i;
	g->Vertices = n;
	g->A = (ENode**)malloc(n*sizeof(ENode*));
	for (i = 0; i<n; i++) g->A[i] = NULL;
}

/*新建节点*/
ENode* NewENode(int vex, T weight, ENode* nextarc){
	ENode* p;
	p = (ENode*)malloc(sizeof(ENode));
	p->AdjVex = vex;
	p->W = weight;
	p->NextArc = nextarc;
	return p;
}
/*u与v之间是否有链接*/
BOOL Exist(Graph g, int u, int v){
	int n;
	ENode* p;
	n = g.Vertices;
	if (u<0 || u>n - 1) return FALSE;
	for (p = g.A[u]; p&&p->AdjVex != v;)p = p->NextArc;		//图从u节点开始遍历，当p不存在或p的邻节点是v时跳出循环
	if (!p) return FALSE;				//如果跳出循环时 p 为空，则u和v之间无链接 
	return TRUE;
}
/*在图中添加u和v节点两者权重为w*/
BOOL Add(Graph *g, int u, int v, T w){
	int n;
	ENode* p;
	n = g->Vertices;
	if (u<0 || v<0 || u>n - 1 || v>n - 1 || u == v || Exist(*g, u, v)){
		printf("BadInput\n"); return FALSE;
	}
	p = NewENode(v, w, g->A[u]); 
	g->A[u] = p;		//新建一个节点指向图表头u，然后让原来的表头指向新建节点,A[u]代表一个表头的地址
	return TRUE;
}

BOOL Delete(Graph* g, int u, int v){
	int n = g->Vertices;
	ENode *p, *q;
	if (u>-1 && u<n){
		p = g->A[u]; q = NULL;
		while (p&&p->AdjVex != v){
			q = p; p = p->NextArc;
		}
		if (p){
			if (q)q->NextArc = p->NextArc;
			else g->A[u] = p->NextArc;
			free(p); return TRUE;
		}
	}
	printf("BadInput\n"); return FALSE;
}
/*使用递归实现深度遍历*/
void DFS(Graph g, int v, BOOL *visited){
	ENode *w = (ENode*)malloc(sizeof(ENode));
	visited[v] = TRUE; 
	//printf("%d  ", v);		//每次递归都将结点打印
	for (w = g.A[v]; w; w = w->NextArc){		//直到表头所对应的链表为空，即指针指到最后的时候跳出循环
		printf("<u=%d,v=%d,w=%d>\n", v, w->AdjVex,w->W);

		if (!visited[w->AdjVex])
			DFS(g, w->AdjVex, visited);	//使用递归，每次将下一个结点作为表头遍历
	}
}
/*深度遍历*/
void Traversal_DFS(Graph g){
	BOOL visited[MaxSize]; int i, n = g.Vertices;
	for (i = 0; i < n; i++)visited[i] = FALSE;	//初始化，如果结点已被遍历则为TRUE,否则为FALSE
	for (i = 0; i < n; i++)		//一共遍历 g.Vertices 次，保证每个表头都被遍历到
		if (!visited[i])DFS(g, i, visited);		
}


int count[10][10];
int z = 0;
void PathAll1(Graph *g, int u, int v, int path[], int i, BOOL *visited) /*输出图G中从顶点u到v的所有简单路径*/
{
	ENode *p;
	int j, n;
	int a, b;
	visited[u] = TRUE;
	p = g->A[u]; 	/*p指向顶点m的第一条弧的弧头结点*/
	for (a = 0; a < 10; a++){
		for (b = 0; b < 10; b++){
			count[a][b] = -1;
		}
	}
	while (p != NULL)
	{
		n = p->AdjVex;	/*n为 p 的邻接顶点*/
		if (n == v)
		{
			path[i + 1] = v;
			for (j = 0; j <= i + 1; j++){
				printf("%3d", path[j]);
				count[z][j] = path[j];
			}
			z++;
			printf("\n");
		}
		else if (visited[n] == FALSE) 	/*若该顶点未标记访问,则递归访问之*/
		{
			path[i + 1] = n;
			PathAll1(g, n, v, path, i + 1, visited);
		}
		p = p->NextArc;	/*找u的下一个邻接顶点*/
	}
	visited[u] = FALSE;		//每次找到一条路径后，将路径中的点全部设为未访问，以便能寻找下一条路径
}

void PathAll(Graph* g, int u,int v){
	BOOL visited[MaxSize]; int n = g->Vertices; int i = 0; int j;
	int path[MaxSize];
	path[0] = u;
	for (j = 0; j < n; j++)visited[j] = FALSE;	//初始化，如果结点已被遍历则为TRUE,否则为FALSE
	PathAll1(g, u, v, path, i, visited);
}

int minTranfer(){
	int a, b = 0;
	int c = 0;
	int min;
	static int num[10];
	for (a = 0; a < z; a++){
		while (count[a][b] != -1){
			num[a]++;
			b++;
		}
		b = 0;
	}
	min = num[0];
	for (a = 0; a < z; a++){
		if (num[a] < min){
			min = num[a];
			c = a;
		}
	}
	printf("\n");
	printf("最小换乘次数为%d\n", min);
	printf("路线为：");
	for (b = 0; count[c][b] != -1; b++){
		printf("%3d", count[c][b]);
	}
	printf("\n");
}

