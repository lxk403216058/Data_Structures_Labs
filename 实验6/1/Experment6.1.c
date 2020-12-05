#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
typedef int QElemType;
#include "queue.h"
#define MAX_VERTEX_NUM 20  //��󶥵���
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
	VertexType Vertex[MAX_VERTEX_NUM];			// ����ͼ�Ķ���
	AdjMatrix arcs;
		//����Ĺ�ϵ���� 1��ʾ�����ӣ�0��ʾ������
	int vexnum,arcnum;
	Graphkind kind;
} MGraph;
int book[MAX_VERTEX_NUM]={0};
int visited[MAX_VERTEX_NUM];


int local(MGraph g,int n){//ֵΪn�ĵ��ڶ��������е��±� 
	int i;
	for( i=0;i<g.vexnum;i++){
		if(g.Vertex[i]==n||g.Vertex[i]==0)
			return i;
		else if(i==g.vexnum-1){
			return g.vexnum;
		}
	}
}

//����ͼ
void CreateGraph(MGraph * G)
{
	int vex1,vex2;
	int i,j,k;
	printf("\n����������ͼ�Ķ������ƣ�\n");
	for(i=0;i<G->vexnum;++i)
		scanf("\n%d",&G->Vertex[i]);
	// ��ʼ����ϵ����Ϊ 0
	for(i=0;i<G->vexnum;++i)
		for(j=0;j<G->vexnum;++j)
			G->arcs[i][j].adj=0;
	printf("\n����������ͼ�ı�(��β->��ͷ)��\n");
	//������ϵ���� ����л���������Ϊ 1
	for(k=1;k<=G->arcnum;++k)
	{
		scanf("%d%d",&vex1,&vex2);
		i=local(*G,vex1);
		j=local(*G,vex2);
		if(	G->arcs[i][j].adj)
		{
			printf("\n�벻Ҫ�����ظ��Ļ�: < %d,%d > \n",G->Vertex[i],G->Vertex[j]);
			printf("\n������ֹͣ����...\n");
			exit(1);
		}
		else
		{
				G->arcs[i][j].adj=1;
		}
	}
}


//������ȱ���
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
	printf("��ֱ���������ͼ�Ķ��������������\n");
	int n,m,a,b,i;
	scanf("%d %d",&(g->vexnum),&(g->arcnum));
	printf("\n����������ͼ�Ķ������ƣ�\n");
	for(i=0;i<g->vexnum;++i)
		scanf("%d",&g->Vertex[i]);
		printf("����������ͼ�ı�(��β->��ͷ)��\n");
	for( i=0;i<g->arcnum;i++){
		scanf("%d %d",&a,&b);
		g->arcs[local(*g,a)][local(*g,b)].adj=1;//����ͼ 
		g->arcs[local(*g,b)][local(*g,a)].adj=1;
	}
} 



/*������ȱ���*/ 
void dfs(MGraph g,int n,int a){
	int m=local(g,a);//a�Ǵ���� 
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
	printf("\n����ͼ������ȱ�����\n");
	dfs(g,1,1);// g��ͼ 1����һ��  1���Ӷ���ֵΪ1�ĵط���ʼ���� 
	
	MGraph G;
	printf("\n\n��ֱ���������ͼ�Ķ�����,������\n");
	scanf("%d%d",&G.vexnum,&G.arcnum);
	CreateGraph(&G);
	printf("����ͼ������ȱ�����\n");
	BFS(&G);
	printf("\n");
	return 0;
}

