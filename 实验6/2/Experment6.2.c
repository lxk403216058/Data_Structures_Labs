#include <stdio.h>  
#include <stdlib.h>  
#include<conio.h>
#define MAX_VERTEX_NUM 20 
#define OK 1
#define ERROR 0
#define OVERFLOW 0 
#include "Queue.h"

typedef int InfoType;
typedef int VertexType;
typedef struct ArcNode{  
    int adjvex;  
    struct ArcNode *nextarc;  
    InfoType *info;
}ArcNode;  
  
typedef struct{  
    VertexType data;  
    ArcNode *firstarc;  
}VNode,AdjList[MAX_VERTEX_NUM];  
  
typedef struct{  
    AdjList vertices;  
    int vexnum;  
    int arcnum;
	int kind;  
}ALGraph;  

int LocateVex(ALGraph G,char v)  
{//查找顶点v在图G中的位置  
	int i;
    for( i=0;i<G.vexnum;i++)  
        if(G.vertices[i].data==v)  
            return i;  
    return -1;  
}  
  
void CreateAdjList(ALGraph *G)  
{//建立无向图的邻接表  
    int v,i,j,k;  
    int v1,v2;  
    ArcNode *p,*s;  
    printf("输入无向图的顶点数和边数：\n");  
    scanf("%d%d",&G->vexnum,&G->arcnum);  
    getchar();  
    printf("输入图的顶点信息：\n");  
    for(v=0;v<G->vexnum;v++){  
        scanf("%d",&G->vertices[v].data);getchar();  
        G->vertices[v].firstarc=NULL;  
    }  
    printf("输入弧的信息(弧尾-弧头),以及权值：\n");  
    for(k=0;k<G->arcnum;k++){ 
		int h; 
        scanf("%d%d%d",&v1,&v2,&h);  
        getchar();  
        i=LocateVex(*G,v1);  
        j=LocateVex(*G,v2);  
        s=(ArcNode*)malloc(sizeof(ArcNode));  
        s->adjvex=j;  
        s->nextarc=NULL;  
        s->info=&h;
        if(!G->vertices[i].firstarc)  
            G->vertices[i].firstarc=s;  
        else{  
            p=G->vertices[i].firstarc;  
            while(p->nextarc)  
                p=p->nextarc;  
            p->nextarc=s;  
        }  
        s=(ArcNode*)malloc(sizeof(ArcNode));  
        s->adjvex=i;  
        s->nextarc=NULL;  
        if(!G->vertices[j].firstarc)  
            G->vertices[j].firstarc=s;  
        else{  
            p=G->vertices[j].firstarc;  
            while(p->nextarc)  
                p=p->nextarc;  
            p->nextarc=s;  
        }  
    }  
}  
  
int visited[MAX_VERTEX_NUM];  
  
void BFSTraverse(ALGraph G)  
{//对用邻接表存储的无向图G进行深度优先遍历  
    int *u,v;  
    QNode Q;  
    ArcNode *p;  
    for(v=0;v<G.vexnum;v++)  
        visited[v]=0;  
    InitQueue(&Q);  
    for(v=0;v<G.vexnum;v++)  
        if(!visited[v]){  
            printf("%3d",G.vertices[v].data);  
            visited[v]=1;  
            EnQueue(&Q,v);  
            while(!QueueEmpty(&Q)){  
                DeQueue(&Q,u);  
                for(p=G.vertices[*u].firstarc;p;p=p->nextarc)  
                    if(!visited[p->adjvex]){  
                        printf("%3d",G.vertices[p->adjvex].data);  
                        visited[p->adjvex]=1;  
                        EnQueue(&Q,p->adjvex);  
                    }  
            }  
        }  
}  
  

int FirstAdjVex(ALGraph G,char v)//返回v的第一个邻接顶点的序号
{
	int i;
	ArcNode *p;
	i=LocateVex(G,v);		//i为顶点v在图G中的序号
	if(i==-1)
		return -1;
	p=G.vertices[i].firstarc;
	if(p)
		return p->adjvex;
	else
		return -1;
}

int NextAdjVex(ALGraph G,char v,char w)//返回v的(相对于w)的下一个邻接顶点的序号
{
	int i,j;
	ArcNode *p,*q;
	i=LocateVex(G,v);
	j=LocateVex(G,w);
	if(i==-1||j==-1||i==j)
		return -1;
	p=G.vertices[i].firstarc;          //p指向v的邻接顶点链表中的第一个邻接顶点
	while(p->nextarc&&p->adjvex!=j)		//找到邻接顶点w
		p=p->nextarc;
	if(p->nextarc)				//找到邻接顶点w，且w非v的最后一个邻接顶点
	{
		q=p->nextarc;
		return q->adjvex;	//返回v的(相对于w)的下一个邻接顶点的序号
	}
	else 
		return -1;		//没有找到w或w是v的最后一个邻接顶点
}

int Visit(char v)
{
	printf("%d ",v);
	return OK;
}

int CreateDG(ALGraph *G)			//采用邻接表表示，构造有向图G
{
	int v,e,i,j,t;
	ArcNode *p,*q;
	int tail,head;
	printf("输入有向图的顶点数,边数:\n");
	scanf("%d%d",&v,&e);
	if(v<0)
		return ERROR;
	G->vexnum=v;

	if(e<0)
		return	ERROR;
	G->arcnum=e;
	printf("输入有向图的顶点信息:\n");
	for(t=0;t<G->vexnum;t++)				//建立头结点顺序表
	{
	
		scanf("%d",&G->vertices[t].data);
		G->vertices[t].firstarc=NULL;	//初始化该头结点指针域
	}
		printf("输入弧的信息(弧尾-弧头),以及权值：\n");
	for(t=0;t<G->arcnum;t++)				//建立表结点链表(每个顶点的邻接顶点链表)
	{
		//fflush(stdin);
		int h;
		scanf("%d%d%d",&tail,&head,&h);
		i=LocateVex(*G,tail);
		j=LocateVex(*G,head);
		if(i==-1||j==-1||i==j)
			return ERROR;
		p=(ArcNode *)malloc(sizeof(ArcNode));
		p->adjvex=j;
		p->info=NULL;
		p->nextarc=NULL;
		p->info=&h;
		if(!G->vertices[i].firstarc)
			G->vertices[i].firstarc=p;
		else
		{//找尾结点
			for(q=G->vertices[i].firstarc;q->nextarc;q=q->nextarc);
				q->nextarc=p;			//插入到链表尾
		}
	}
}

int DFS(ALGraph G,int v)		//从第v个顶点出发，递归的深度优先遍历有向图G
{
	int w;
	visited[v]=-1;
	printf("%d ",G.vertices[v].data);
	w=FirstAdjVex(G,G.vertices[v].data);
	for(;w>=0;w=NextAdjVex(G,G.vertices[v].data,G.vertices[w].data))
		if(!visited[w])
			DFS(G,w);		//对v的尚未访问的邻接顶点w递归调用DFS()
		return OK;
}

int DFSTraverse(ALGraph G)  //深度优先搜索遍历图G
{
	int i;
	for(i=0;i<G.vexnum;i++)
		visited[i]=0;
	for(i=0;i<G.vexnum;i++)
		if(!visited[i])
			DFS(G,i);
		return OK;
}


int main(){  
    ALGraph G;  
    printf("建立无向图的邻接表：\n");  
    CreateAdjList(&G);  
    printf("无向图的广度优先遍历：\n");  
    BFSTraverse(G); 
    printf("\n\n\n");
	 
	ALGraph g;
	printf("建立有向图的邻接表：\n");
	if(CreateDG(&g))
	{
		printf("有向图的深度优先遍历:\n");
		DFSTraverse(g);
		printf("\n");
	}
	printf("\n"); 
    return 0;  
}  
