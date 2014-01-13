/*
ID: wxx54331
PROG: frac1
LANG: C++
*/
/*
以分母为1到N分别生成分数，并判断该分数是否为真分数，
如果是真分数的话则存储起来，不是的话则忽略（因为约分后一定分其中一个真分数） 
最后对所有真分数排序后输出 
*/ 
#include<iostream>
#include<fstream>
#include<stdlib.h>
using namespace std;
struct Fraction{
	int n;  //分子 
	int d;  //分母 
};
const int MAX = 160*160;
int count = 0;
Fraction fractions[MAX];

int fractionCmp(const void *a, const void *b);
//Fraction simplify(Fraction a);
bool isSimple(Fraction a);
Fraction* generate(int N);
int main()
{
	ifstream fin("frac1.in");
	ofstream fout("frac1.out");
	int N;
	fin >> N;
	generate(N);
	qsort(fractions, count, sizeof(fractions[0]),fractionCmp);   
	for(int i = 0; i < count; ++i)
		fout << fractions[i].n <<"/"<<fractions[i].d<< endl;
	fin.close();
	fout.close();
	return 0;
}

int fractionCmp(const void *a, const void *b)
{
	Fraction *fa = (Fraction *)a;
	Fraction *fb = (Fraction *)b;
	return (fa->n*fb->d - fb->n*fa->d);
}
/*生成分母为1到N之间的所有真分数*/ 
Fraction* generate(int N)
{
	Fraction a;
	a.n = 0;
	a.d = 1;
	fractions[count++] = a;
	for(int d = 1; d <= N; ++d)  //分母
		for(int n = 1; n <= d; ++n)  //分子
		{
			a.n = n;
			a.d = d;
			if(isSimple(a))
				fractions[count++] = a;
		}
}
/*
原来是将分数化简，其实没有必要，只需要判断分数是否可以化简就可以了
因为可以化简的话，其化简后的形式一定存在于真分数的集合中。 
Fraction simplify(Fraction a)
{
	if(a.n == 0)
	{
		a.d = 1;
		return a;
	}
	for(int i = a.n; i >= 0; --i)
		if(a.n%i==0 && a.d%i==0)
		{
			a.n /= i;
			a.d /= i;
			return a;
		}
} */
//判断是否为真分数 
bool isSimple(Fraction a)
{
	if(a.n == 1)
		return true;
	for(int i = a.n; i >= 2; --i)
		if(a.n%i==0 && a.d%i==0)
			return false;
	return true;
}
