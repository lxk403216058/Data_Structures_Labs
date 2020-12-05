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
{//���Ҷ���v��ͼG�е�λ��  
	int i;
    for( i=0;i<G.vexnum;i++)  
        if(G.vertices[i].data==v)  
            return i;  
    return -1;  
}  
  
void CreateAdjList(ALGraph *G)  
{//��������ͼ���ڽӱ�  
    int v,i,j,k;  
    int v1,v2;  
    ArcNode *p,*s;  
    printf("��������ͼ�Ķ������ͱ�����\n");  
    scanf("%d%d",&G->vexnum,&G->arcnum);  
    getchar();  
    printf("����ͼ�Ķ�����Ϣ��\n");  
    for(v=0;v<G->vexnum;v++){  
        scanf("%d",&G->vertices[v].data);getchar();  
        G->vertices[v].firstarc=NULL;  
    }  
    printf("���뻡����Ϣ(��β-��ͷ),�Լ�Ȩֵ��\n");  
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
{//�����ڽӱ�洢������ͼG����������ȱ���  
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
  

int FirstAdjVex(ALGraph G,char v)//����v�ĵ�һ���ڽӶ�������
{
	int i;
	ArcNode *p;
	i=LocateVex(G,v);		//iΪ����v��ͼG�е����
	if(i==-1)
		return -1;
	p=G.vertices[i].firstarc;
	if(p)
		return p->adjvex;
	else
		return -1;
}

int NextAdjVex(ALGraph G,char v,char w)//����v��(�����w)����һ���ڽӶ�������
{
	int i,j;
	ArcNode *p,*q;
	i=LocateVex(G,v);
	j=LocateVex(G,w);
	if(i==-1||j==-1||i==j)
		return -1;
	p=G.vertices[i].firstarc;          //pָ��v���ڽӶ��������еĵ�һ���ڽӶ���
	while(p->nextarc&&p->adjvex!=j)		//�ҵ��ڽӶ���w
		p=p->nextarc;
	if(p->nextarc)				//�ҵ��ڽӶ���w����w��v�����һ���ڽӶ���
	{
		q=p->nextarc;
		return q->adjvex;	//����v��(�����w)����һ���ڽӶ�������
	}
	else 
		return -1;		//û���ҵ�w��w��v�����һ���ڽӶ���
}

int Visit(char v)
{
	printf("%d ",v);
	return OK;
}

int CreateDG(ALGraph *G)			//�����ڽӱ��ʾ����������ͼG
{
	int v,e,i,j,t;
	ArcNode *p,*q;
	int tail,head;
	printf("��������ͼ�Ķ�����,����:\n");
	scanf("%d%d",&v,&e);
	if(v<0)
		return ERROR;
	G->vexnum=v;

	if(e<0)
		return	ERROR;
	G->arcnum=e;
	printf("��������ͼ�Ķ�����Ϣ:\n");
	for(t=0;t<G->vexnum;t++)				//����ͷ���˳���
	{
	
		scanf("%d",&G->vertices[t].data);
		G->vertices[t].firstarc=NULL;	//��ʼ����ͷ���ָ����
	}
		printf("���뻡����Ϣ(��β-��ͷ),�Լ�Ȩֵ��\n");
	for(t=0;t<G->arcnum;t++)				//������������(ÿ��������ڽӶ�������)
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
		{//��β���
			for(q=G->vertices[i].firstarc;q->nextarc;q=q->nextarc);
				q->nextarc=p;			//���뵽����β
		}
	}
}

int DFS(ALGraph G,int v)		//�ӵ�v������������ݹ��������ȱ�������ͼG
{
	int w;
	visited[v]=-1;
	printf("%d ",G.vertices[v].data);
	w=FirstAdjVex(G,G.vertices[v].data);
	for(;w>=0;w=NextAdjVex(G,G.vertices[v].data,G.vertices[w].data))
		if(!visited[w])
			DFS(G,w);		//��v����δ���ʵ��ڽӶ���w�ݹ����DFS()
		return OK;
}

int DFSTraverse(ALGraph G)  //���������������ͼG
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
    printf("��������ͼ���ڽӱ�\n");  
    CreateAdjList(&G);  
    printf("����ͼ�Ĺ�����ȱ�����\n");  
    BFSTraverse(G); 
    printf("\n\n\n");
	 
	ALGraph g;
	printf("��������ͼ���ڽӱ�\n");
	if(CreateDG(&g))
	{
		printf("����ͼ��������ȱ���:\n");
		DFSTraverse(g);
		printf("\n");
	}
	printf("\n"); 
    return 0;  
}  
