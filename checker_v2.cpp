/*
ID: wxx54331
PROG: checker
LANG: C++
*/
/*
较checker_v1.cpp改进之处：
在判断是否和之前棋子冲突的时候，并不是遍历之前的棋子再去判断，
而是直接设立了两个数组来记录冲突情况，如下所示：
	1.b!=j  不在同一行上    
		==>   设立rowFlag[i]表示第i行不能放置 
	2.b-j != a-i   不在正对角线上'\'  
		==> a-b != i-j   
	  由于在正对角线上的棋子col-row是固定值，因此只要设立一个数组rightDown,
	  其下标i-j即可表示该对角线是否可以放置（实际使用j-i+N是为了防止j-i<0而越界） 
	3.j-b != a-i   不在反对角线上'/'  
		==> a+b = j+i
	  处于反对角线上的棋子col+row是固定值， 因此只要设立一个数组leftDown,
	  其下标i+j表示该该反对角线是否可以放置 
*/ 

#include<iostream>
#include<fstream>
using namespace std;
ofstream fout("checker.out");
const int MAX = 14;
unsigned int rowFlag[MAX];       // (i, j) -> j 
unsigned int leftDown[2*MAX];    // (i, j) -> i+j 
unsigned int rightDown[2*MAX];   // (i, j) -> i-j + N 
unsigned int checkerBoard[MAX];  //记录第i列的棋子放在哪一行上 
unsigned int firstThree[3][MAX];  //记录前三种情况(题目要求输出前3种) 
unsigned int N;
unsigned int index=1;  //索引当前需要放置第几列的棋子 
unsigned int count;    //由对称性，count只需要记录前一半的情况 
unsigned int flag;    //用来记录当N为奇数的时候，第1列放在第(N+1)/2行上有多少种 
void dfs(int r, int dep);
bool isConflict(int curRow, int preNum);
void output();
int celling(int n);
int getResultNum();
int main()
{
	ifstream fin("checker.in");
	fin >> N;
	dfs(0,1);
	output();
	fin.close();
	fout.close();
	return 0;
} 

void dfs(int r, int dep)
{
	if((dep == 2) && (r>celling(N)))
	{

		return;
	}
		
	if(dep > N)
	{
		count++;
		if(count <= 3)
			for(int i = 1; i <= N; ++i)
				firstThree[count-1][i] = checkerBoard[i];
		if(N%2 != 0 && checkerBoard[1]==celling(N))  
			flag++;	 //记录当N为奇数的时候处于中间的个数 
		return ;
	}
	for(int row = 1; row <= N; ++row)
	{
		if(isConflict(row, dep))
			continue;
		checkerBoard[index++] = row;
		/*记录冲突*/
		rowFlag[row]++;  
		leftDown[row+dep]++;
		rightDown[row-dep+N]++;
		/*继续搜索*/ 
		dfs(row, dep+1);
		/*恢复原样*/
		rowFlag[row]--;
		leftDown[row+dep]--;
		rightDown[row-dep+N]--;
		index--;
	}
} 

bool isConflict(int curRow, int colNum)
{
	if(rowFlag[curRow] || leftDown[curRow+colNum] || rightDown[curRow-colNum+N])
		return true;
	return false;
}

void output()
{
	for(int i = 0; i < 2; ++i)
	{
		fout << firstThree[i][1];
		for(int j = 2; j <= N; ++j)
			fout << " " << firstThree[i][j];
		fout << endl;
	}
	if(count == 2)
	{
		fout << firstThree[1][N];
		for(int j = N-1; j >= 1; --j)
			fout << " " << firstThree[1][j];
		fout << endl;
	}
	else
	{
		fout << firstThree[2][1];
		for(int j = 2; j <= N; ++j)
			fout << " " << firstThree[2][j];
		fout << endl;
	}
	fout << getResultNum() << endl;
}

int celling(int n)
{
	if(n%2 == 0)
		return n/2;
	else
		return (n/2+1);
}

int getResultNum()
{
	if(N%2 == 0)
		return count*2;
	else
		return (count*2-flag);
}
