/*
ID: wxx54331
PROG: milk3
LANG: C++
*/
/*
使用DFS搜索所有情况，对于已经出现过的状态进行剪枝
用一个bool数组pattern来记录三个桶的状态
再用一个bool数组result来记录当a桶为空时，c桶内牛奶的数量
最后结果主要扫描一遍result输出就可以了。 
*/
#include<iostream>
#include<fstream>
using namespace std;

int a, b, c;
const int MAX = 21;
bool pattern[MAX][MAX];  //只要确定了两个桶就能确定整个状态 
bool result[MAX];
void DFS(int A, int B, int C);
int main()
{
	ifstream fin("milk3.in");
	ofstream fout("milk3.out");
	
	fin >> a >> b >> c;
	
	DFS(0,0,c);
	int flag = true;
	for(int i = 0; i < MAX; ++i)
		if(result[i])
		{
			if(flag)
			{
				flag = false;
				fout << i;
			}
			else
				fout << " " << i;
		}
	fout << endl;
			
	fin.close();
	fout.close();
	return 0;
} 

void DFS(int A, int B, int C)
{
	if(pattern[A][B])   //对于已经出现过的状态进行剪枝 
		return;
	pattern[A][B] = true;   
	if(A == 0)
	{
		if(!result[C])
			result[C] = true;
	}
	//a->b
	if(A+B<=b)
		DFS(0,A+B,C);
	else
		DFS(A-(b-B),b,C);
	//a->c
	if(A+C<=c)
		DFS(0,B,A+C);
	else
		DFS(A-(c-C),B,c);
	//b->a
	if(A+B<=a)
		DFS(A+B,0,C);
	else
		DFS(a,B-(a-A),C);
	//b->c
	if(B+C<=c)
		DFS(A,0,B+C);
	else
		DFS(A,B-(c-C),c);
	//c->a
	if(A+C<=a)
		DFS(A+C,B,0);
	else
		DFS(a,B,C-(a-A));
	//c->b
	if(B+C<=b)
		DFS(A,B+C,0);
	else
		DFS(A,b,C-(b-B));
}

