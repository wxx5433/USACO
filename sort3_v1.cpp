/*
ID: wxx54331
PROG: sort3
LANG: C++
*/
/*
这题的原则是首先交换那些交换一次就能到最后位置上的数， 
count数组记录1，2，3的个数，那么就能得到应该是1，2，3各自的下标区间
例如2，2，1，3，3，3，2，3，1，那么1的区间是[0,2),2的区间是[2,5),3的区间是[5,9) 
然后遍历应该是1的区间，如果发现有不是1的数字，则到这个不是1的数的区间中去找有没有1，
如果有的话直接交换过来，那么这两个数就都到自己的位置上了。
用同样的方法遍历应该是2及3的区间。那么所有一次交换的情况就都获得了。
接下来不在自己应该在的区间上的数字只能通过两次交换才能到达自己的位置上
而这个时候没有必要再去交换了，只要把应该在1上而不是1的数字的个数统计出来*2就是需要交换的次数
因为如果这个数字不是1，那么必然可以通过两次交换使得1，2，3都在自己的位置上。 
*/
#include<iostream>
#include<fstream>
using namespace std;
int count[4];
const int MAX = 1000;
int number[MAX+1];
int total; 

void readData();
void swapOnce();
void swapTwice();
int swapNum;
int getBeginIndex(int k);
int main()
{
	ofstream fout("sort3.out");
	readData();
	swapOnce();
	swapTwice();
	fout << swapNum << endl;	
	fout.close();
	return 0;
}

void readData()
{
	ifstream fin("sort3.in");
	fin >> total;
	int num;
	for(int i = 0; i < total; ++i)
	{
		fin >> num;
		number[i] = num;
		count[num]++;
	}
	fin.close();
}

void swapOnce()
{
	for(int k = 1; k <= 3; ++k)   /*枚举1，2，3的情况*/ 
	{
		int begin1 = getBeginIndex(k);
		int end1 = begin1+count[k];
		for(int i = begin1; i < end1; ++i)  /*遍历1/2/3的区间*/
		{
			if(number[i] != k)  //如果在k的区间中有不是k的数字 
			{
				int begin2 = getBeginIndex(number[i]);  //则到这个数字x中的区间中去找k 
				int end2 = begin2+count[number[i]];
				for(int j = begin2; j < end2; ++j)
				{
					if(number[j] == k)   //找到k之后交换过来 
					{
						swap(number[i],number[j]);
						swapNum++;
						break;
					}
				}
			}
		}
	}
}
/*交换一次之后剩下的序列，如果应该在1的位置上还有不是1的数字，
那么通过两次交换也能使序列有序
假设此时序列是1312，那么可以交换一次得到1132，再交换一次得到1123*/
void swapTwice()
{
	for(int i = 0; i < count[1]; ++i)
	{
		if(number[i] != 1)
			swapNum += 2;
	}
}
/*应该是数字k的区间的开始位置*/
int getBeginIndex(int k)
{
	if(k == 1)
		return 0;
	else if(k == 2)
		return count[1];
	else if(k == 3)
		return count[1]+count[2];
}
