#include<stdio.h>
typedef int ElemType;
typedef struct Data{
	int r,c; // �Թ�������
	ElemType e;  // ��һ����ͨ���Թ�����Ԫ���е�λ��
}SElemType,QElemType; 
#include<stdio.h>
#include"Stack.h" // ջ��ͷ�ļ�
#include"Queue.h" // ���е�ͷ�ļ�
#include<stdlib.h>
#include<time.h>

ElemType** createPuzzle(int ,int ); //  ��������Թ�
Status rand1(ElemType **,int ,int );// ��������Թ��ϰ���
Status showPuzzle(ElemType **, int , int ); // ����Թ�
Status printPuzzle(ElemType **,SqStack *, int , int ); // ��ӡ�Թ�
ElemType findPath(ElemType **,ElemType **,QNode *,int i,int j,int d[][2]);  // �ж�8�������Ƿ����ͨ�У��������
Status PushData(QNode ,SqStack *);  // ?��ͨ����·���Ž�ջ
int main(){ // ������
	int r,c; // ��������Թ��Ĵ�С
	int flag; // �ж��Ƿ��߳����Թ�
	int Directrion[8][2]={{1,1},{0,1},{-1,1},{-1,0},{-1,-1},{0,-1},{1,-1},{1,0}}; // ��ʱ�뷽��Ѱ��·��
	ElemType **m=NULL,**mark=NULL;
	SqStack *s,s1;
	QNode *Q,q;
	Q=&q;s=&s1;
	InitQueue(Q); // ��ʼ��
	InitStack(s);
	printf("�������Թ��Ĵ�С!\n");
	scanf("%d%d",&r,&c);
	r=r+2;c=c+2; // �Թ��ⲿ��Ҫ����ǽ�����������С��2�����£����ң�
	m=createPuzzle(r,c); // ��̬�����Թ� 
	mark=createPuzzle(r,c); // ����߹���λ��

	int i,j;
	for( i=0;i<r;i++)
		for( j=0;j<c;j++)
			mark[i][j]=false;  //false ��ʾû���߹���λ��
	
	rand1(m,r,c); // ��������Թ��ϰ���

	flag=findPath(m,mark,Q,r,c,Directrion); // Ѱ��·��
	if(flag==1){ // �����߳��Թ�
		PushData(q,s);//�������·��ѹ��ջ 
		printPuzzle(m,s,r,c); // ��ӡ�Թ�
		StackTraverse(s1); // �������
	}
	else{
		showPuzzle(m,r,c);
		printf("No Path!\n");
	}
}

ElemType** createPuzzle(int row,int column){ // ʵ�ִ���������
	ElemType **a;
	a = (int **)malloc(sizeof(int *) * row);//����ָ������
	int i;
	for(i=0; i<row; i++)
		a[i] = (int *)malloc(sizeof(int) * column);//����ÿ��ָ����ָ�������
	return a;
}
	
Status rand1(ElemType **p,int row,int column){ // ��������Թ�
	srand((time(NULL)));
	int r,c;
	for(r=0;r<row;r++) 
		for(c=0;c<column;c++)
			if(r==0||c==0||r==row-1||c==column-1)  // ����ĵ�һ�����һ�е�һ�����һ�о�Ϊǽ
				p[r][c]=1;	
			else{
				p[r][c]=rand()%100;//���Ե���ǽ��·�ı��� 
				if(p[r][c]>=40)
					p[r][c]=0; // 0 ��ʾ��ͨ����·Ϊ60 
				else
					p[r][c]=1;
				}
		
		p[1][1]=0; //���
		p[row-2][column-2]=0; // �յ�
		return OK;
}
	
Status printPuzzle(ElemType **m,SqStack *s, int row, int column){ // ��ӡ�Թ�
	SElemType *data,data1;
	int k=s->top; // ��¼ջԪ�ص��ܸ���
	int flag=1,i,j;
	data=&data1;
	for( i=0;i<row;i++){
		for( j=0;j<column;j++){
			if(i==0||j==0||i==row-1||j==column-1||m[i][j]==1)  //����Թ�ǽ
				printf("��");//��
			else{
				data->r=i;
				data->c=j;
				if(searchStackData(s,data1))//�Ƿ���ջ��Ԫ����� 
					printf(" *"); 
				else
					printf("  ");
					s->top=k;
				}
		}	
		printf("\n"); 
	}
	return OK;
}
	
//��ǰ�ص����һ����Ϊ1��true����ǰԪ��������	
ElemType findPath(ElemType **m,ElemType **mark,QNode *Q,int row,int column,int d[][2]){ //Ѱ��·��
	SElemType *data,data1,data2;  //data2���ڼ�¼��ͬ����̽��������
	int flag=0; // �ж��Ƿ��߳��Թ�
	data=&data1;//dataҲָ��data1
	//��һ��Ԫ����� 
	data->c=1; // ���������
	data->r=1; // ��������
	data->e=-1; // ����û��ǰһ��Ԫ��
	EnQueue(Q,data1); // ��������
	while(Q->front!=Q->rear){  // ���зǿ�
		int i,j; 
		DeQueue(Q,data);//����Ԫ�ظ�ֵ��data 
		i=data->r; // �����и���i j ���ڼ��Ϸ����ж��Ƿ���·��
		j=data->c;
		mark[i][j]=true; // ��ʾ�Ѿ��߹�
		data2=data1;
		data2.e=Q->front;  // ��¼�ϸ���ʼ̽������ĳ�ʼλ��
		if((i==row-2)&&(j==column-2))  // �߳��Թ�
		{ 
			flag=1;
			break;
		}
		int k;
		for( k=0;k<8;k++){  // �����˸�����
			i=data->r;
			j=data->c;
			i+=d[k][0];//��һ������ 
			j+=d[k][1];//�ڶ������� 
			if(m[i][j]==1||mark[i][j]==true)  // ����·�ϻ������ڶ�����
				continue;
			else{
				data2.r=i;// 
				data2.c=j;
				mark[i][j]=true;
				EnQueue(Q,data2); // �ҵ�ͨ·�����
				}
		} // for
		Q->front++;// 
	} //while
	return flag;
}
	
Status PushData(QNode q,SqStack *s){ // ��ͨ����·���Ž�ջ
	SElemType data1;
	int i;
	i=q.front; // ��һ��Ԫ�ص�λ��
	while(i!=-1){  // ����ֵΪ -1
		data1=q.base[i];//�Ӷ�����ȡ�� 
		Push(s,data1); // ������ջ
		i=q.base[i].e;
	}
	return OK;
}

showPuzzle(ElemType **m, int row, int column){
	SElemType *data,data1;
	data=&data1;
	int j,i;
	for(i=0;i<row;i++){
		for(j=0;j<column;j++){
			if(i==0||j==0||i==row-1||j==column-1||m[i][j]==1) // ����Թ�ǽ
				printf("��");
			else
				printf("  ");
		}
		printf("\n"); 
	}
	return OK;
}
