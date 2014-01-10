/*
ID: wxx54331
PROG: pprime
LANG: C++
*/
/*
100,000,000以内的回文数数量显然要比质数的数量要少的多，
因此比较合理的做法是首先生成回文数，然后再判断该回文数是否为质数
这里有一个优化的地方：
位数为偶数的回文数必然能被11整除，因此位数为偶数的回文数只有11是质数。 
所以在生成回文数的时候只需要生成位数为奇数的 
*/
#include<iostream>
#include<fstream>
#include<string>
#include<sstream>
#include<stdlib.h>
using namespace std;
int a, b;
ofstream fout("pprime.out");

bool isPrime(int num);
string intToString(int num);
void solve();
void generatePal(int min, int max);
string duplicate(string str);

int main()
{
	ifstream fin("pprime.in");
	fin >> a >> b;
	solve();
	fin.close();
	fout.close();
	return 0;
}

void solve()
{
	generatePal(1,9);
	if(a<=11 && b>=11)
		fout << 11 << endl;
	generatePal(10,9999);
}
/*
生成回文数，并判断是否为质数，如果是则输出
生成方法， ab -> aba,   aabb-> aabbbaa
即只生成奇数位的回文数 
*/
void generatePal(int min, int max)
{
	string base;
	string pal;
	int num;
	for(int i = min; i <= max; ++i)
	{
		base = intToString(i);
		pal = duplicate(base);
		num = atoi(pal.c_str());
		if( num >= a && num <= b && isPrime(num) )
			fout << pal << endl;
	}
}
//生成方法， ab -> aba,   aabb-> aabbbaa
string duplicate(string str)
{
	int len = str.length();
	for(int i = 1; i < len; ++i)
		str += str[len-1-i];
	return str;
}

string intToString(int num)
{
	stringstream ss;
	string str;
	ss << num;
	ss >> str;
	return str;
}

bool isPrime(int num)
{
	if(num == 2)
		return true;
	if(num % 2 == 0)
		return false;
	for(int i = 3; i*i <= num; i+=2)
		if(num % i == 0)
			return false;
	return true;
}
