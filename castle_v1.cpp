/*
ID: wxx54331
PROG: castle
LANG: C++
*/
/*
首先使用floodFill算法得出这个图的所有连通块 
之后再按题目要求枚举可以拆掉的墙对房间的大小进行扩充，找到最大的扩充方案 
*/ 
#include<iostream>
#include<fstream>
using namespace std;

const int MAX = 50;
int row, column;     //整个图的大小 
int wall[MAX][MAX][5]; //0->west, 1->north, 2->east, 3->south, 4->group
bool visited[MAX][MAX];  //记录某个单元格是否已经被访问过 
int  dx[] = {-1, 0, 1, 0}; /*按←↑→↓的顺序移动*/
int  dy[] = {0, -1, 0, 1};
int group;    //记录房间数 
int roomSize[MAX*MAX];   //记录每个房间的大小 
int maxSize;
int r, c;  //记录要拆除的墙所在的单元格的行和列位置 
char dir;  //记录要拆除的墙的方位 

void readData();
void floodFill(int x, int y);
void merge(int x, int y);
int main()
{
	ofstream fout("castle.out");
	readData();
	/*floodFill算法找出房间的数量以及大小*/
	for(int i = 0; i < row; ++i)  
		for(int j = 0; j < column; ++j)
			if(!visited[i][j])
			{
				roomSize[group] = 0;
				floodFill(i, j);
				group++;
			}
	fout << group << endl;
	for(int i = 0; i < group; ++i)
		maxSize = max(maxSize, roomSize[i]);
	fout << maxSize << endl;
	/*从最西南边的墙开始枚举，拆除后面积是否为最大
	西边优先级最高，南边优先级次之，N墙优先级>E墙*/
	maxSize = 0;
	for(int i = 0; i < column; ++i)
		for(int j = row-1; j >= 0; --j)
			merge(j,i);
	fout << maxSize << endl;
	fout << r << " " << c << " " << dir << endl;
	fout.close();
	return 0;
}

void readData()
{
	ifstream fin("castle.in");
	int number;
	fin >> column >> row;
	for(int i = 0; i < row; ++i)
		for(int j = 0; j < column; ++j)
		{
			fin >> number;
			/*思考的时候将数字想为二进制，比如6是0110，每次从右边取出一位*/
			for(int k = 0; k <= 3; ++k) 
			{
				wall[i][j][k] = number % 2;
				number = number >> 1;
			}
			wall[i][j][4] = 0;
		}
	fin.close();
}

void floodFill(int y, int x)  /*按照坐标轴来考虑*/
{
	visited[y][x] = true;
	wall[y][x][4] = group;
	roomSize[group]++;
	for(int i = 0; i <= 3; ++i) //遍历4堵墙
	{
		int nx = x + dx[i];   //向上下左右的房间移动 
		int ny = y + dy[i]; 
		if(nx < 0 || ny < 0 || nx >= column || ny >= row)  //越界
			continue;
		if(visited[ny][nx] || wall[y][x][i])  //新的房间已经访问过，或者现在要移动到的方向有墙
			continue;
		floodFill(ny, nx); 
	} 
}

void merge(int y, int x)
{
	int sum = 0;
	if(y>=1 && wall[y][x][4]!=wall[y-1][x][4])  //拆除N边的墙 
	{
		sum = roomSize[wall[y][x][4]] + roomSize[wall[y-1][x][4]];
		if(sum > maxSize)
		{
			maxSize = sum;
			r = y+1;
			c = x+1;
			dir = 'N';
		}
	}
	if(x<column-1 && wall[y][x][4]!=wall[y][x+1][4])  //拆除E边的墙 
	{
		sum = roomSize[wall[y][x][4]] + roomSize[wall[y][x+1][4]];
		if(sum > maxSize)
		{
			maxSize = sum;
			r = y+1;
			c = x+1;
			dir = 'E';
		}
	}
}
