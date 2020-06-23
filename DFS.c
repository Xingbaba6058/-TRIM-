//自动机的TRIM算法 ,结果为邻接矩阵，行节点为起点 ，列节点为终点
//0表示无连接，1表示有连接 
#include<stdio.h>
#include<math.h>
int map[100][100]={0};
char event[100][100];
int trimap[100][100]={0};
int stack[120],pathstack[120],v[100]={0},top=0,m,n,start,end,l=0;
void dfs(int b,int c)
{
	int i,p;
	if(b==end){
		if(c==1)
		{
			trimap[end][stack[0]]=1;
		}
		trimap[stack[top-1]][end]=1;
		for(i=0;i<top;i++)
		{
			if(i<top-1)
			{
				trimap[stack[i]][stack[i+1]]=1;
			}
			int q=0;
			for(p=0;p<=l;p++)
			{
				if(pathstack[p]==stack[i])
				{
					q=1;
				}
			}
			if(q!=1)
			{
				pathstack[l]=stack[i];
				l++;
			}	
			printf("%d ",stack[i]);
		}
		printf("%d\n",end);
		return;
	}
	v[b]=1;
	stack[top++]=b;
	for(i=0;i<n;i++){
		if(!v[i]&&map[b][i])
			dfs(i,c);
	}
	v[b]=0;
	top--;	
}
void circle(int a,int n)
{
	int j;
	for(j=0;j<n;j++)
	{	
		if(j==a&&map[a][a]==1)
		{
			trimap[a][a]=1;
			printf("%d %d\n",a,a);
		}
		else if(map[a][j]==1)
		{
			end=a;
			dfs(j,1);
		}
	}
}
int main()
{
    int i,j,x,y,z,b;
    char k1;
    printf("Please enter the number of nodes and edges:");
    scanf("%d %d",&n,&m);
    printf("Please enter the event and the couples of nodes with directed edges:\n");
    for(i=0; i<m; i++) {
        scanf("%d %d %c", &x,&y,&k1);
        map[x][y] = 1; 
		event[x][y]=k1;
    }
    printf("Initial（adjacency matrix representation）:\n");
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
			printf("%d ",map[i][j]);
		printf("\n");
	}
    printf("Please enter the initial node and the marked node:");
    scanf("%d %d", &start,&end);
    printf("The paths of trim (without circles):\n");
    dfs(start,0);
    printf("Circles on the paths: \n");
    pathstack[l]=end;
    l++;
	for(b=0;b<=l;b++)
		circle(pathstack[b],n);
	printf("TRIM:\n");
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
			{
				if(trimap[i][j]==1)
				{
					printf("%d----%c---->%d \n",i,event[i][j],j);
				}
			}
	}
	fflush(stdin);
	getchar();
    return 0;
}

