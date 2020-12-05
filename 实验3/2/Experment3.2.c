#include<stdio.h>
typedef int ElemType;
typedef struct Data{
	int r,c; // 迷宫的行列
	ElemType e;  // 上一个可通过迷宫在三元组中的位置
}SElemType,QElemType; 
#include<stdio.h>
#include"Stack.h" // 栈的头文件
#include"Queue.h" // 队列的头文件
#include<stdlib.h>
#include<time.h>

ElemType** createPuzzle(int ,int ); //  随机产生迷宫
Status rand1(ElemType **,int ,int );// 随机产生迷宫障碍物
Status showPuzzle(ElemType **, int , int ); // 输出迷宫
Status printPuzzle(ElemType **,SqStack *, int , int ); // 打印迷宫
ElemType findPath(ElemType **,ElemType **,QNode *,int i,int j,int d[][2]);  // 判断8个方向是否可以通行，并入队列
Status PushData(QNode ,SqStack *);  // ?将通过的路径放进栈
int main(){ // 主函数
	int r,c; // 随机产生迷宫的大小
	int flag; // 判断是否走出了迷宫
	int Directrion[8][2]={{1,1},{0,1},{-1,1},{-1,0},{-1,-1},{0,-1},{1,-1},{1,0}}; // 逆时针方向寻找路径
	ElemType **m=NULL,**mark=NULL;
	SqStack *s,s1;
	QNode *Q,q;
	Q=&q;s=&s1;
	InitQueue(Q); // 初始化
	InitStack(s);
	printf("请输入迷宫的大小!\n");
	scanf("%d%d",&r,&c);
	r=r+2;c=c+2; // 迷宫外部需要加上墙，所以数组大小加2（上下，左右）
	m=createPuzzle(r,c); // 动态产生迷宫 
	mark=createPuzzle(r,c); // 标记走过的位置

	int i,j;
	for( i=0;i<r;i++)
		for( j=0;j<c;j++)
			mark[i][j]=false;  //false 表示没有走过的位置
	
	rand1(m,r,c); // 随机产生迷宫障碍物

	flag=findPath(m,mark,Q,r,c,Directrion); // 寻找路径
	if(flag==1){ // 可以走出迷宫
		PushData(q,s);//队列里的路径压入栈 
		printPuzzle(m,s,r,c); // 打印迷宫
		StackTraverse(s1); // 输出坐标
	}
	else{
		showPuzzle(m,r,c);
		printf("No Path!\n");
	}
}

ElemType** createPuzzle(int row,int column){ // 实现创建矩阵函数
	ElemType **a;
	a = (int **)malloc(sizeof(int *) * row);//分配指针数组
	int i;
	for(i=0; i<row; i++)
		a[i] = (int *)malloc(sizeof(int) * column);//分配每个指针所指向的数组
	return a;
}
	
Status rand1(ElemType **p,int row,int column){ // 随机产生迷宫
	srand((time(NULL)));
	int r,c;
	for(r=0;r<row;r++) 
		for(c=0;c<column;c++)
			if(r==0||c==0||r==row-1||c==column-1)  // 数组的第一行最后一行第一列最后一列均为墙
				p[r][c]=1;	
			else{
				p[r][c]=rand()%100;//可以调整墙和路的比例 
				if(p[r][c]>=40)
					p[r][c]=0; // 0 表示课通过，路为60 
				else
					p[r][c]=1;
				}
		
		p[1][1]=0; //起点
		p[row-2][column-2]=0; // 终点
		return OK;
}
	
Status printPuzzle(ElemType **m,SqStack *s, int row, int column){ // 打印迷宫
	SElemType *data,data1;
	int k=s->top; // 记录栈元素的总个数
	int flag=1,i,j;
	data=&data1;
	for( i=0;i<row;i++){
		for( j=0;j<column;j++){
			if(i==0||j==0||i==row-1||j==column-1||m[i][j]==1)  //输出迷宫墙
				printf("田");//■
			else{
				data->r=i;
				data->c=j;
				if(searchStackData(s,data1))//是否与栈中元素相等 
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
	
//当前地点的下一步不为1或true，当前元素则可入队	
ElemType findPath(ElemType **m,ElemType **mark,QNode *Q,int row,int column,int d[][2]){ //寻找路径
	SElemType *data,data1,data2;  //data2用于记录向不同方向探索的坐标
	int flag=0; // 判断是否走出迷宫
	data=&data1;//data也指向data1
	//第一个元素入队 
	data->c=1; // 起点纵坐标
	data->r=1; // 起点横坐标
	data->e=-1; // 代表没有前一个元素
	EnQueue(Q,data1); // 起点入队列
	while(Q->front!=Q->rear){  // 队列非空
		int i,j; 
		DeQueue(Q,data);//出队元素赋值给data 
		i=data->r; // 将行列赋给i j 便于加上方向判断是否有路径
		j=data->c;
		mark[i][j]=true; // 表示已经走过
		data2=data1;
		data2.e=Q->front;  // 记录上个开始探索方向的初始位置
		if((i==row-2)&&(j==column-2))  // 走出迷宫
		{ 
			flag=1;
			break;
		}
		int k;
		for( k=0;k<8;k++){  // 搜索八个方向
			i=data->r;
			j=data->c;
			i+=d[k][0];//第一个数字 
			j+=d[k][1];//第二个数字 
			if(m[i][j]==1||mark[i][j]==true)  // 遇见路障或者已在队列里
				continue;
			else{
				data2.r=i;// 
				data2.c=j;
				mark[i][j]=true;
				EnQueue(Q,data2); // 找到通路，入队
				}
		} // for
		Q->front++;// 
	} //while
	return flag;
}
	
Status PushData(QNode q,SqStack *s){ // 将通过的路径放进栈
	SElemType data1;
	int i;
	i=q.front; // 上一个元素的位置
	while(i!=-1){  // 起点的值为 -1
		data1=q.base[i];//从队列中取出 
		Push(s,data1); // 坐标入栈
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
			if(i==0||j==0||i==row-1||j==column-1||m[i][j]==1) // 输出迷宫墙
				printf("田");
			else
				printf("  ");
		}
		printf("\n"); 
	}
	return OK;
}
