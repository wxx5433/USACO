/*
ID: wxx54331
PROG: crypt1
LANG: C++
*/
/*
只要乘数和被乘数固定了就可以获得整个等式，
因此一共需要进行9^5次尝试，可以满足时间限制 
*/ 
#include<iostream>
#include<fstream>
using namespace std;
bool isValid(int num[],int N, int m);
int solve(int num[],int N);
int main()
{
	ifstream fin("crypt1.in");
	ofstream fout("crypt1.out");
	int N;
	fin >> N;
	int *num = new int[N];
	for(int i = 0; i < N; ++i)
		fin >> num[i];

	fout << solve(num,N) << endl;
	
	delete[] num;
	fin.close();
	fout.close();
	return 0;
} 

int solve(int num[],int N)
{
	int count = 0;
	for(int a = 0; a < N; ++a)
		for(int b = 0; b < N; ++b)
			for(int c = 0; c < N; ++c)
			{
				int multiplicand = 100*num[a] + 10*num[b] +num[c];  //被乘数 
				for(int d = 0; d < N; ++d)
				{
					int x = multiplicand * num[d];
					if(x > 999 || !isValid(num,N,x))
						continue;
					for(int e = 0; e < N; ++e)
					{
						int y = multiplicand * num[e];
						int result = 10*x+y;
						if(y> 999 || result>9999 || !isValid(num,N,y) || !isValid(num,N,result))
							continue;
						count++;
					}
				}
			}
	return count;
} 

/*判断一个数字的每一个位数是否都在给定的数字集合中*/
bool isValid(int num[],int N, int number)
{
	int m;
	bool flag = true;;
	while(flag && number != 0)
	{
		flag = false;
		m = number % 10;
		number /= 10;
		for(int i = 0; i < N; ++i)
			if(num[i] == m)
			{
				flag = true;
				break;
			}
	}
	return flag;
}

