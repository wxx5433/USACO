/*
ID: wxx54331
PROG: ariprog
LANG: C++
*/
/*
枚举所有的可能解，但是由于数据量比较大，因此需要剪枝，否则会超时
预处理把所有的biSquare算出来，记录到biSqr数组中 ，并从小到大排序 
于此同时，用一个布尔数组isBiSqr[i]记录数字i是否为biSquare
设置布尔数组的目的是为了之后判断某个数是否为biSquare的时候能直接获得，而无需再搜索
搜索策略：
从第一个biSquare开始枚举其与之后的biSquare的差，以这个差为等差，验证之后的数字是否为biSquare 
剪枝策略：
假设需要获取长度为len的等差序列，假设第一个数字为a0,第二个数字是a1，则等差为diff=a1-a0
那么便可求出该序列的最后一个数字=a0+diff*(len-1),如果这个数值比biSquare数组中最大的值还大，
那么这个序列一定是无法满足条件的，便无需再往后枚举比a1更大的数字了，因为diff必然更大
于是可以直接更新a0的值继续枚举 
*/
#include<iostream>
#include<fstream>
#include<stdlib.h>
using namespace std; 

struct Result
{
	int a0;
	int difference;
};

const int MAX = 125001;  //最大的biSquare为250^2+250^2=125000 
bool isBiSqr[MAX];
int biSqr[MAX];

int generateBiSquare(int upperLimit);
int cmp(const void *a, const void *b);
int resultCmp(const void *a, const void *b);
int main()
{
	ifstream fin("ariprog.in");
	ofstream fout("ariprog.out");
	int len, upperLimit;
	fin >> len >> upperLimit;
	
	int count = generateBiSquare(upperLimit);
	int diff;   //等差 
	Result result[10000];  
	int flag;
	int index = 0;
	for(int i = 0; i < count-1; ++i)   //枚举a0 
		for(int j = i+1; j < count; ++j)   //枚举a1 
		{
			flag = true;
			diff = biSqr[j] - biSqr[i];   //根据a1-a0求得等差diff 
			/*如果根据上面求得的diff算出的该序列的最大数字比最大的biSqr还要大
			那么可以直接剪枝，不需要枚举之后的a1了，直接更新a0*/
			if( (biSqr[i]+diff*(len-1)) > biSqr[count-1])  
				break;
			for(int k = 2; k < len; ++k)   /*验证根据此diff得到的序列是否都为biSqr*/
				if(!isBiSqr[biSqr[i]+k*diff])
				{
					flag = false;
					break;
				}
			if(flag)
			{
				result[index].a0 = biSqr[i];
				result[index++].difference = diff; 
			}
		}
	qsort(result,index,sizeof(result[0]),resultCmp);
	if(index == 0)
		fout << "NONE" << endl;
	else
		for(int i = 0; i < index; ++i)
			fout << result[i].a0 << " " << result[i].difference << endl;
	fin.close();
	fout.close();
	return 0;
}
/*预处理生成所有的biSqr，并根据从小到大排序*/
int generateBiSquare(int upperLimit)
{
	int number;
	int count = 0;
	for(int i = 0; i <= upperLimit; ++i)
		for(int j =0; j <= upperLimit; ++j)
		{
			number = i*i + j*j;
			if(!isBiSqr[number])   //如果该数已经存在，不要重复存储 
				biSqr[count++] = number;
			isBiSqr[number] = true;
		}
	qsort(biSqr, count, sizeof(biSqr[0]), cmp);
	return count;
}

int cmp(const void *a, const void *b)
{
	return (*(int*)a - *(int*)b);
}

int resultCmp(const void *a, const void *b)
{
	Result *ra = (Result*)a;
	Result *rb = (Result*)b;
	if(ra->difference != rb->difference)
		return (ra->difference - rb->difference);
	else
		return (ra->a0 - rb->a0);
} 
