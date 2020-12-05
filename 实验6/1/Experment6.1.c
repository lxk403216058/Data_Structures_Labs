#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
typedef int QElemType;
#include "queue.h"
#define MAX_VERTEX_NUM 20  //最大顶点数
#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0

typedef int ElemType;
typedef int Status;
typedef int VRType;
typedef int InfoType;
typedef int VertexType;
typedef enum{
	DG,
	DN,
	AG,
	AN
}Graphkind;
typedef struct ArcCell{
	VRType adj;
	InfoType *info;
}ArcCell,AdjMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];

typedef struct MGraph
{
	VertexType Vertex[MAX_VERTEX_NUM];			// 储存图的顶点
	AdjMatrix arcs;
		//顶点的关系矩阵 1表示相连接，0表示无连接
	int vexnum,arcnum;
	Graphkind kind;
} MGraph;
int book[MAX_VERTEX_NUM]={0};
int visited[MAX_VERTEX_NUM];


int local(MGraph g,int n){//值为n的点在定点向量中的下标 
	int i;
	for( i=0;i<g.vexnum;i++){
		if(g.Vertex[i]==n||g.Vertex[i]==0)
			return i;
		else if(i==g.vexnum-1){
			return g.vexnum;
		}
	}
}

//创建图
void CreateGraph(MGraph * G)
{
	int vex1,vex2;
	int i,j,k;
	printf("\n请输入有向图的顶点名称：\n");
	for(i=0;i<G->vexnum;++i)
		scanf("\n%d",&G->Vertex[i]);
	// 初始化关系矩阵为 0
	for(i=0;i<G->vexnum;++i)
		for(j=0;j<G->vexnum;++j)
			G->arcs[i][j].adj=0;
	printf("\n请输入无向图的边(弧尾->弧头)：\n");
	//建立关系矩阵 如果有弧连接则设为 1
	for(k=1;k<=G->arcnum;++k)
	{
		scanf("%d%d",&vex1,&vex2);
		i=local(*G,vex1);
		j=local(*G,vex2);
		if(	G->arcs[i][j].adj)
		{
			printf("\n请不要输入重复的弧: < %d,%d > \n",G->Vertex[i],G->Vertex[j]);
			printf("\n程序已停止运行...\n");
			exit(1);
		}
		else
		{
				G->arcs[i][j].adj=1;
		}
	}
}


//广度优先遍历
void BFS(MGraph* G)
{
	QNode Q;
	InitQueue(&Q); 
	int i,j;
	for( i=0;i< G->vexnum;++i)
		visited[i]=0;
	for( i=0;i< G->vexnum;++i)
	{
		if(!visited[i])
		{
			printf("%d ",G->Vertex[i]);
			visited[i]=1;
			EnQueue(&Q,i);		
		}
		while(!QueueEmpty(&Q))
		{
			int k=Q.front,temp;
			DeQueue(&Q,&temp);		
			for( j=0;j< G->vexnum;++j)
			{
				if(	G->arcs[i][j].adj==1 && !visited[j])
				{
					printf("%d ",G->Vertex[j]);
					visited[j]=1;			
					EnQueue(&Q,i);
				}
			}
		}
	}
}


void initGragh(MGraph *g){
	int i,j;
	g->vexnum=0;
	g->arcnum=0; 
	for(i=0;i<MAX_VERTEX_NUM;i++){
		g->Vertex[i]=0;
		for( j=0;j<MAX_VERTEX_NUM;j++){
			g->arcs[i][j].adj=0;
		}
	}
}


void createGragh(MGraph *g){
	printf("请分别输入无向图的顶点个数，边数：\n");
	int n,m,a,b,i;
	scanf("%d %d",&(g->vexnum),&(g->arcnum));
	printf("\n请输入无向图的顶点名称：\n");
	for(i=0;i<g->vexnum;++i)
		scanf("%d",&g->Vertex[i]);
		printf("请输入无向图的边(弧尾->弧头)：\n");
	for( i=0;i<g->arcnum;i++){
		scanf("%d %d",&a,&b);
		g->arcs[local(*g,a)][local(*g,b)].adj=1;//无向图 
		g->arcs[local(*g,b)][local(*g,a)].adj=1;
	}
} 



/*深度优先遍历*/ 
void dfs(MGraph g,int n,int a){
	int m=local(g,a);//a是存的数 
	int i;	
	printf("%d ",g.Vertex[m]);
	book[m]=1;
	if(n==g.vexnum+1) return;
	for( i=1;i<=g.vexnum;i++){
		if(book[i]==0&&g.arcs[m][i].adj==1){
			book[i]=1;
			dfs(g,++n,g.Vertex[i]);
		}
	}
}
 

int main()
{
	MGraph g;
	initGragh(&g);
	createGragh(&g);
	printf("\n无向图深度优先遍历：\n");
	dfs(g,1,1);// g：图 1：第一步  1：从顶点值为1的地方开始遍历 
	
	MGraph G;
	printf("\n\n请分别输入有向图的顶点数,边数：\n");
	scanf("%d%d",&G.vexnum,&G.arcnum);
	CreateGraph(&G);
	printf("有向图广度优先遍历：\n");
	BFS(&G);
	printf("\n");
	return 0;
}

