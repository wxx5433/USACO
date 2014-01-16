/*
ID: wxx54331
PROG: subset
LANG: C++
*/
/*
这题是典型的动态规划题，可以归类到0/1背包问题
设a[i][j]表示前i个数中和为j的方案数目，
则a[i+1][j] = a[i][j](不取第i+1个数) + a[i][j-i](取第i+1个数) 
上式的条件是j-i>=0 
*/ 

#include<iostream>
#include<fstream>
using namespace std;
long long dp(int N);
int main()
{
	ifstream fin("subset.in");
	ofstream fout("subset.out");
	int N;
	fin >> N;
	fout << dp(N) << endl;
	fin.close();
	fout.close();
	return 0;
} 

long long dp(int N)
{
	int sum = (1+N)*N/2;
	if(sum%2 != 0)   //如果和不是偶数，一定不可能分成两个和相同的子集 
		return 0;
	int halfSum = sum/2;
	const int MAX = 40;
	long long a[MAX][(MAX+1)*MAX/2]={0};
	a[1][0] = 1;
	a[1][1] = 1;
	for(int i = 2; i <= N; i++)
		for(int j = 0; j <= halfSum; j++){
			if(j >= i) 
				a[i][j] = a[i-1][j] + a[i-1][j-i]; 
			else	
				a[i][j] = a[i-1][j];
		} 
	return a[N][halfSum]/2;
}
