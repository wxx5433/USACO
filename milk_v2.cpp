/*
ID: wxx54331
PROG: milk
LANG: C++
*/
/*
实际上，可以不用对price进行qsort，
因为price的区间只是1-1000而已，直接创建一个数组来表示每个price即可
碰到有相同价格的，则直接将amount叠加。 
*/
#include<iostream>
#include<fstream>
using namespace std;

int main()
{
	ifstream fin("milk.in");
	ofstream fout("milk.out");
	int N, M;
	fin >> N >> M;
	const int MAX = 1001;
	int priceTable[MAX] = {};
	int price, amount;
	for(int i = 0; i < M; ++i)
	{
		fin >> price >> amount;
		priceTable[price] += amount;  //碰到有相同价格的，则直接将amount叠加
	}
	int totalPrice = 0;
	for(int i = 0; i < MAX && N > 0; ++i)
	{
		if(priceTable[i] != 0)
		{
			if(priceTable[i] < N)
			{
				totalPrice += i * priceTable[i];
				N -= priceTable[i]; 
			}
			else
			{
				totalPrice += i * N;
				N = 0;
			}
		}
	}
	fout << totalPrice << endl;
	
	fin.close();
	fout.close();
	return 0;
}
