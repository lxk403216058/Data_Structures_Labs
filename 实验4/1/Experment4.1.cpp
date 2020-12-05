# include<stdio.h>
# include<stdlib.h>
# include<time.h> 

#define OK 1
#define ERROR 0
#define TURE 1
#define OVERFLOW -2
#define MAXSIZE 100 

typedef int Status;
typedef int ElemType;

typedef struct{
	int i,j;
	ElemType e;
}Triple;

typedef struct {
	Triple data[MAXSIZE+1];
	int mu,nu,tu;
}TSMatrix;

Status Init_TSMatrix(int ***,int ,int );
Status Create_TSMatrix(int **,int ,int );
Status TSMatrix_Transform_Triad(TSMatrix *,int **,int, int );
Status FastTransposeSMatrix(TSMatrix,TSMatrix *);
Status Triad_Transform_TSMatrix(TSMatrix ,int **);
Status Triad_Add(TSMatrix ,TSMatrix ,TSMatrix *);
Status Printf_Triad(TSMatrix );
Status Printf_TSMatrix(int **,int ,int );
Status Destory_TSMatrix(int ***);

int main(){
	srand((int)time(0));
	int **a,**b,**c,**d;
	int row,col;
	TSMatrix triad1;
	TSMatrix FTtriad1;
	TSMatrix triad2;
	TSMatrix triad3;
	
	printf("请输入矩阵行数：");
	scanf("%d",&row);
	printf("请输入矩阵的列:");
	scanf("%d",&col);
	Init_TSMatrix(&a,row,col);
	Init_TSMatrix(&b,row,col);
	Create_TSMatrix(a,row,col);
	Create_TSMatrix(b,row,col);
	printf("a:\n");
	Printf_TSMatrix(a,row,col);
	printf("三元组A：\n");
	TSMatrix_Transform_Triad(&triad1,a,row,col);
	Printf_Triad(triad1);
	printf("快速转置后的矩阵：\n");
	FastTransposeSMatrix(triad1,&FTtriad1);
	Init_TSMatrix(&d,row,col);
	Triad_Transform_TSMatrix(FTtriad1,d);
	Printf_TSMatrix(d,row,col);
	printf("快速转置后的三元组：\n");
	Printf_Triad(FTtriad1);
	printf("b；\n");
	Printf_TSMatrix(b,row,col);
	printf("三元组B：\n");
	TSMatrix_Transform_Triad(&triad2,b,row,col);
	Printf_Triad(triad2);
	printf("相加后的矩阵：\n"); 
	Triad_Add(triad1,triad2,&triad3);
	Init_TSMatrix(&c,triad3.mu,triad3.nu);
	Triad_Transform_TSMatrix(triad3,c);
	Printf_TSMatrix(c,triad1.mu,triad1.nu);
	printf("相加后的三元组：\n"); 
	Printf_Triad(triad3);
	Destory_TSMatrix(&a);
	Destory_TSMatrix(&b);
	Destory_TSMatrix(&c);
	Destory_TSMatrix(&d);
	return 0;
}

Status Init_TSMatrix(int ***tsmatrix,int row,int col){//初始化矩阵 
	int i;
	*tsmatrix = (int**) malloc(sizeof(int*)*row);//动态分配内存 
	for(i =0; i<row;i++)
	 (*tsmatrix)[i] = (int *)malloc(sizeof(int)*col);
	 
	 return OK;
}

Status Create_TSMatrix(int **tsmatrix,int row,int col){//创建稀疏矩阵 
	int i,j,falg;
	
	for (i=0;i<row;i++){ 
		for (j=0;j<col;j++){
			falg = rand()%20;
			if (falg == 0)
		        tsmatrix[i][j] = rand()%99+1;
		    else
		        tsmatrix[i][j] = 0;
		}
	}
	
	return OK;
}

Status TSMatrix_Transform_Triad(TSMatrix *triad,int **tsmatrix,int row, int col){//稀疏矩阵转换为三元组 
	int i,j;
	int n=1;
	triad -> mu = row;
	triad -> nu = col;
	
	for (i=0;i<row;i++){
		for (j =0;j<col;j++){
			if (tsmatrix[i][j]!=0){
			  triad->data[n].e=tsmatrix[i][j];
			  triad->data[n].i=i+1;
			  triad->data[n].j=j+1;
			  n++;
			}
			  
		}
	}
	triad->tu=n;
	
	return OK;
}

Status FastTransposeSMatrix(TSMatrix triad1,TSMatrix *FTtriad1){//快速转置 
	int col,t,p,q;
	int num[20], cpot[20];
	
	FTtriad1->mu=triad1.nu;
	FTtriad1->nu=triad1.mu;
	FTtriad1->tu=triad1.tu;
	
	if (FTtriad1->tu){
		for (col=1;col<=triad1.nu;++col)
		    num[col]=0;
		for (t=1;t<=triad1.tu;++t)
		    ++num[triad1.data[t].j];
		cpot[1]=1;
		for (col=2;col<=triad1.nu;++col)
		cpot[col]=cpot[col-1]+num[col-1];
		for (p=1;p<=triad1.tu;++p){
			col=triad1.data[p].j;
			q=cpot[col];
			FTtriad1->data[q].i=triad1.data[p].j;
			FTtriad1->data[q].j=triad1.data[p].i;
			FTtriad1->data[q].e=triad1.data[p].e;
			++cpot[col];
		}
	}
	
	return OK;
}

Status Triad_Transform_TSMatrix(TSMatrix triad,int **tsmatrix){//三元组转换为矩阵 
	
	int i,j;
	
	for (i=0;i<triad.mu;i++){
		for (j=0;j<triad.nu;j++)
			tsmatrix[i][j]=0;
	}
	
	for (i=1;i<triad.tu;i++)
		tsmatrix[triad.data[i].i-1][triad.data[i].j-1]=triad.data[i].e;
		
	
	return OK;
}

Status Triad_Add(TSMatrix a,TSMatrix b,TSMatrix *c){//稀疏矩阵的三元组相加 
	int i=1,j=1,k=1;
	int n,value;
	
	if (a.mu!=b.mu||a.nu!=b.nu)
	   return ERROR;
	c->mu=a.mu;
	c->nu=a.nu;
	
	while (i<a.tu&&j<b.tu){
		if (a.data[i].i==b.data[j].i){
			if (a.data[i].j<b.data[j].j){//将a元素添加到C中 
				c->data[k].i=a.data[i].i;
				c->data[k].j=a.data[i].j;
				c->data[k].e=a.data[i].e;
				k++;
				i++;
			}else if(a.data[i].j>b.data[j].j){//将b元素添加C中 
				c->data[k].i=b.data[j].i;
				c->data[k].j=b.data[j].j;
				c->data[k].e=b.data[j].e;
				k++;
				j++;
			}else{//a元素的列号等于b元素的列号 
				value=a.data[i].e+b.data[j].e;
				if (value!=0){
					c->data[k].i=a.data[i].i;
					c->data[k].j=a.data[i].j;
					c->data[k].e=value;
					k++;
				}
				i++;
				j++;
			}
		}else if(a.data[i].i<b.data[j].i){//将a元素添加到C中 
				c->data[k].i=a.data[i].i;
				c->data[k].j=a.data[i].j;
				c->data[k].e=a.data[i].e;
				k++;
				i++;
		}else{//将b元素添加到C 
		        c->data[k].i=b.data[j].i;
				c->data[k].j=b.data[j].j;
				c->data[k].e=b.data[j].e;
				k++;
				j++;
		}
	}
	
	while (i<a.tu){//a中有剩余元素 
		c->data[k].i=a.data[i].i;
		c->data[k].j=a.data[i].j;
		c->data[k].e=a.data[i].e;
		k++;
		i++;
	}
	while (j<b.tu){//b中有剩余元素 
		c->data[k].i=b.data[j].i;
		c->data[k].j=b.data[j].j;
		c->data[k].e=b.data[j].e;
		k++;
		j++;
	}
	c->tu=k;
	
	return OK;
}

Status Printf_Triad(TSMatrix triad){//打印三元组 
	int i;
	printf("行  列  值\n");
	for (i=1;i<triad.tu;i++){
		printf("%d  %d  %d\n",triad.data[i].i,triad.data[i].j,triad.data[i].e);
	}
	
	return OK;
}

Status Printf_TSMatrix(int **tsmatrix,int row,int col){//打印矩阵 
	int i,j;
	
	for (i=0;i<row;i++){
		for (j=0;j<col;j++)
		    printf("%6d",tsmatrix[i][j]);
		printf("\n");
	}
	
	return OK;
}

Status Destory_TSMatrix(int ***tsmatrix){//销毁矩阵 
	free(**tsmatrix);
	
	return OK;	
}
