/*
ID: wxx54331
PROG: numtri
LANG: C++
*/
/*
这题可以使用动态规划自底向上的做，上层的a[i-1][j]+=max(a[i][j],a[i][j+1])
最后只要输出最顶上的值即可。
我在这里采用的是自顶向下的解法，解法是类似的。 
*/
#include<iostream>
#include<fstream>
#include<stdlib.h>
using namespace std;

int main()
{
	ifstream fin("numtri.in");
	ofstream fout("numtri.out");
	int line;
	fin >> line;
	int result[1001],lastLine[1001];
	for(int i = 0; i < 1001; ++i)
	{
		result[i] = 0;
		lastLine[i] = 0;
	}
	int number;
	for(int i = 1; i <= line; ++i)
	{
		for(int k = 0; k <= i-1; ++k)
			lastLine[k] = result[k]; 
		for(int j = 1; j <= i; ++j)
		{
			fin >> number;
			result[j] = number + max(lastLine[j-1],lastLine[j]);
		}			
	}
	int ans = 0;
	for(int i = 1; i <= line; ++i)
		ans = max(ans,result[i]);
	fout << ans << endl;
	
	fin.close();
	fout.close();
	return 0;
}
