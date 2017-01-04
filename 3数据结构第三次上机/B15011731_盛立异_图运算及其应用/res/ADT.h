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

/*�½��ڵ�*/
ENode* NewENode(int vex, T weight, ENode* nextarc){
	ENode* p;
	p = (ENode*)malloc(sizeof(ENode));
	p->AdjVex = vex;
	p->W = weight;
	p->NextArc = nextarc;
	return p;
}
/*u��v֮���Ƿ�������*/
BOOL Exist(Graph g, int u, int v){
	int n;
	ENode* p;
	n = g.Vertices;
	if (u<0 || u>n - 1) return FALSE;
	for (p = g.A[u]; p&&p->AdjVex != v;)p = p->NextArc;		//ͼ��u�ڵ㿪ʼ��������p�����ڻ�p���ڽڵ���vʱ����ѭ��
	if (!p) return FALSE;				//�������ѭ��ʱ p Ϊ�գ���u��v֮�������� 
	return TRUE;
}
/*��ͼ�����u��v�ڵ�����Ȩ��Ϊw*/
BOOL Add(Graph *g, int u, int v, T w){
	int n;
	ENode* p;
	n = g->Vertices;
	if (u<0 || v<0 || u>n - 1 || v>n - 1 || u == v || Exist(*g, u, v)){
		printf("BadInput\n"); return FALSE;
	}
	p = NewENode(v, w, g->A[u]); 
	g->A[u] = p;		//�½�һ���ڵ�ָ��ͼ��ͷu��Ȼ����ԭ���ı�ͷָ���½��ڵ�,A[u]����һ����ͷ�ĵ�ַ
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
/*ʹ�õݹ�ʵ����ȱ���*/
void DFS(Graph g, int v, BOOL *visited){
	ENode *w = (ENode*)malloc(sizeof(ENode));
	visited[v] = TRUE; 
	//printf("%d  ", v);		//ÿ�εݹ鶼������ӡ
	for (w = g.A[v]; w; w = w->NextArc){		//ֱ����ͷ����Ӧ������Ϊ�գ���ָ��ָ������ʱ������ѭ��
		printf("<u=%d,v=%d,w=%d>\n", v, w->AdjVex,w->W);

		if (!visited[w->AdjVex])
			DFS(g, w->AdjVex, visited);	//ʹ�õݹ飬ÿ�ν���һ�������Ϊ��ͷ����
	}
}
/*��ȱ���*/
void Traversal_DFS(Graph g){
	BOOL visited[MaxSize]; int i, n = g.Vertices;
	for (i = 0; i < n; i++)visited[i] = FALSE;	//��ʼ�����������ѱ�������ΪTRUE,����ΪFALSE
	for (i = 0; i < n; i++)		//һ������ g.Vertices �Σ���֤ÿ����ͷ����������
		if (!visited[i])DFS(g, i, visited);		
}


int count[10][10];
int z = 0;
void PathAll1(Graph *g, int u, int v, int path[], int i, BOOL *visited) /*���ͼG�дӶ���u��v�����м�·��*/
{
	ENode *p;
	int j, n;
	int a, b;
	visited[u] = TRUE;
	p = g->A[u]; 	/*pָ�򶥵�m�ĵ�һ�����Ļ�ͷ���*/
	for (a = 0; a < 10; a++){
		for (b = 0; b < 10; b++){
			count[a][b] = -1;
		}
	}
	while (p != NULL)
	{
		n = p->AdjVex;	/*nΪ p ���ڽӶ���*/
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
		else if (visited[n] == FALSE) 	/*���ö���δ��Ƿ���,��ݹ����֮*/
		{
			path[i + 1] = n;
			PathAll1(g, n, v, path, i + 1, visited);
		}
		p = p->NextArc;	/*��u����һ���ڽӶ���*/
	}
	visited[u] = FALSE;		//ÿ���ҵ�һ��·���󣬽�·���еĵ�ȫ����Ϊδ���ʣ��Ա���Ѱ����һ��·��
}

void PathAll(Graph* g, int u,int v){
	BOOL visited[MaxSize]; int n = g->Vertices; int i = 0; int j;
	int path[MaxSize];
	path[0] = u;
	for (j = 0; j < n; j++)visited[j] = FALSE;	//��ʼ�����������ѱ�������ΪTRUE,����ΪFALSE
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
	printf("��С���˴���Ϊ%d\n", min);
	printf("·��Ϊ��");
	for (b = 0; count[c][b] != -1; b++){
		printf("%3d", count[c][b]);
	}
	printf("\n");
}

