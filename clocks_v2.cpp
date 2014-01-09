/*
ID: wxx54331
PROG: clocks
LANG: C++
*/
/*
转动的顺序和最后的结果无关，且每个操作进行4次就会回到原始状态，
因此搜索空间是4*9，使用dfs搜索 
*/
#include<iostream>
#include<fstream>
#include<climits>

using namespace std; 

int clocks[10];
int back[10];   //用来存储clocks的原始状态，以便重置 
int result[10];   //记录最终结果 
int rec[10];     //记录每个操作进行的次数 
int minimum = INT_MAX;
int move[10][10] = {{0},
	                    {0,1,1,0,1,1,0,0,0,0},
	                    {0,1,1,1,0,0,0,0,0,0},
	                    {0,0,1,1,0,1,1,0,0,0},
	                    {0,1,0,0,1,0,0,1,0,0},
	                    {0,0,1,0,1,1,1,0,1,0},
	                    {0,0,0,1,0,0,1,0,0,1},
	                    {0,0,0,0,1,1,0,1,1,0},
	                    {0,0,0,0,0,0,0,1,1,1},
	                    {0,0,0,0,0,1,1,0,1,1}};


void dfs(int depth);
void spin();
bool isComplete();
void reset();
int mod(int num);
int main()
{
	ifstream fin("clocks.in");
	ofstream fout("clocks.out");
	int num;
	for(int i = 1; i <= 9; ++i)
	{
		fin >> num;
		clocks[i] = (num%12) / 3;  //3,6,9,12分别转化到1,2,3,0 
		back[i] = clocks[i];
	}

	dfs(1);
	bool flag = true;
	for(int i = 1; i <= 9; ++i)
		for(int j = 0; j < result[i]; ++j)
		{
			if(flag)
			{
				fout << i;
				flag = false;
			}
			else
				fout << " " << i;
		}
	fout << endl;
	
	fin.close();
	fout.close();
	return 0;
}

void dfs(int depth)
{
	if(depth == 10)
	{
		spin();    //按照rec对clock进行操作，并检查是否符合 
		reset();   //重置回最初的状态 
		return;
	} 
	else
	{
		for(int i = 0; i <= 3; ++i)   //搜索所有的组合情况 
		{
			rec[depth] = i;
			dfs(depth+1);
		}
			
	}
}

void spin()
{
	for(int i = 1; i <= 9; ++i)
		for(int k = 1; k <=9; ++k)
				clocks[k] = mod(clocks[k]+rec[i]*move[i][k]);
			
	if(isComplete())
	{
		int sum = 0;
		for(int i =1; i <=9; ++i)
			sum += rec[i];
		if(sum < minimum)
		{
			minimum = sum;
			for(int i = 1; i < 10; ++i)
				result[i] = rec[i];
		}
	}
}

bool isComplete()
{
	for(int i = 0; i <= 9; ++i)
		if(clocks[i]!= 0)
			return false;
	return true;
}

void reset()
{
	for(int i = 1; i <= 9; ++i)
		clocks[i] = back[i];
}

int mod(int num)
{
	if(num % 4 == 0)
		return 0;
	else
		return (num % 4);
}
