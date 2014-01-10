/*
ID: wxx54331
PROG: sprime
LANG: C++
*/
/*
用dfs能很轻松的解决，由题目的要求可知，第一位数只能是2,3,5,7，
然后只要分别扩展它们到n位数即可，扩展的过程中如果碰到不是质数的则剪枝
e.g. 2可以拓展到21,23,27,29,由于21，27都不是质数，所以可以直接剪枝，
	只需要接着用｛1，3，7，9｝扩展23，29即可 
*/
#include<iostream>
#include<fstream>
using namespace std;
int len;
/*末尾不可能是偶数，否则能被2整除，也不可能是5，否则能被5整除*/
int tail[4] = {1,3,7,9};  
ofstream fout("sprime.out");

bool isPrime(int num);
void dfs(int num, int dep);
int main()
{
	ifstream fin("sprime.in");
	fin >> len;
	int dep = 1;
	dfs(2,dep);
	dfs(3,dep);
	dfs(5,dep);
	dfs(7,dep);
	fin.close();
	fout.close();
	return 0;
}

void dfs(int num, int dep)
{
	int newNum;
	if(dep == len)
	{
		if(isPrime(num))
			fout << num << endl;
		return;
	}
	for(int i = 0; i < 4; ++i)
	{
		newNum = num*10 + tail[i];
		if(isPrime(newNum)) //如果新生成的数不是质数，则剪枝 
			dfs(newNum, dep+1);
	}
}

bool isPrime(int num)
{
	if(num == 2)
		return true;
	if(num % 2 == 0)	
		return false;
	for(int i = 3; i*i<=num; i+=2)
		if(num%i == 0)
			return false;
	return true;
}
