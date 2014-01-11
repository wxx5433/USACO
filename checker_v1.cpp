/*
ID: wxx54331
PROG: checker
LANG: C++
*/
/*
这是经典的八皇后问题，采用dfs的方法能解决。
我采用的是针对每一列，棋子能放在哪一行的思考方式。
用数组checkerBoard来记录第i列的棋子放在哪一行上(假设为第j行)。
当放第a列的棋子时，假设其放在第b列上，则需要保证以下情况：
	b!=j  不在同一行上
	b-j != a-i   不在正对角线上'\'
	j-b != a-i   不在反对角线上'/' 
如果不满足以上限制条件的话则可以直接剪枝。 
但是由于时间的限制是一秒，如果不采取优化的话，当N较大的时候会超时。
这个程序里面有一个优化的地方： 
将棋盘旋转180度后会产生对称的图形，这也是满足题意的。 
因此由以上的对称性，我们只需要搜索一半的情况就可以了
然后由对称性能获得所有答案（实际上每转过90度就会产生新图形，但是不知道怎么写） 
*/
#include<iostream>
#include<fstream>
using namespace std;
ofstream fout("checker.out");
const int MAX = 14;
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
	if((dep == 2) && (r>celling(N)))  //对称性剪枝，只搜索前半部分 
		return;
	if(dep > N)
	{
		count++;
		if(count <= 3)   //记录下前三种方案，以便输出 
			for(int i = 1; i <= N; ++i)
				firstThree[count-1][i] = checkerBoard[i];
		if(N%2 != 0 && checkerBoard[1]==celling(N))  
			flag++;	 //记录当N为奇数的时，第一列放在第(N+1)/2时的方案数 
		return ;
	}
	for(int row = 1; row <= N; ++row)
	{
		if(isConflict(row, dep))
			continue;
		checkerBoard[index++] = row;
		dfs(row, dep+1);
		index--;
	}
} 

bool isConflict(int curRow, int colNum)
{
	for(int i = 1; i <= colNum-1; ++i)  //遍历之前所有列放置过的棋子 
	{
		if(curRow == checkerBoard[i])   //在同一行上
			return true;
		if(curRow-checkerBoard[i] == colNum-i)   //正斜线"\"
			return true;
		if(checkerBoard[i]-curRow == colNum-i)   //反斜线"/"
			return true; 
	}
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
	if(count == 2)  //当N=6的时候需要单独处理，因为前半部分只记录了两个方案 
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
/*由对称性获得最后的总方案数*/
int getResultNum()
{
	if(N%2 == 0)
		return count*2;
	else
		return (count*2-flag);
}
