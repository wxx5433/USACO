/*
ID: wxx54331
PROG: milk
LANG: C++
*/
/*
对每个提供商的价格进行排序，然后使用贪心算法，每次都取尽价格最便宜的，
直到满足需求为止。 
*/
#include<iostream>
#include<fstream>
#include<stdlib.h>

using namespace std;

struct Farmer{
	int P;
	int A;
};
int cmp(const void *a, const void *b);
int main()
{
	ifstream fin("milk.in");
	ofstream fout("milk.out");
	int N, M;
	fin >> N >> M;
	Farmer farmer[M];
	for(int i = 0; i < M; ++i)
		fin >> farmer[i].P >> farmer[i].A;
	qsort(farmer, M, sizeof(farmer[0]),cmp);
	int totalPrice = 0;
	for(int i = 0; i < M && N > 0; ++i)
	{
		if(N > farmer[i].A)
		{
			totalPrice += farmer[i].P * farmer[i].A;
			N -= farmer[i].A;
		}
		else
		{
			totalPrice += farmer[i].P * N;
			N = 0;
		}
	}
	fout << totalPrice << endl;
		
	fin.close();
	fout.close();
	return 0; 
} 

int cmp(const void *a, const void *b)
{
	return (*(int *)a - *(int *)b);
}

