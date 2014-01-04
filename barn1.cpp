/*
ID: wxx54331
PROG: barn1
LANG: C++
*/
/*
要使得木板覆盖的牛棚数尽可能少，只要让空牛棚数不被覆盖的尽可能多就可以了
使用贪心算法，例如有牛的牛棚编号为1，5，7，那么假设只有一块木板，那么需要覆盖1-7这个区间，
假设有两块木板，那么由于1和5之间的空隙大于5和7之间的，那么只要覆盖1，5-7这两个区间
每增加一块木板都保证当前最大的空隙不被覆盖，这样就可以获得最优解。 
因此在这题中，首先要计算出有牛的牛棚之间的空隙，然后从大到小对这些空隙排序。
这样每增加一块木板就取最大的空隙，记录下未被覆盖的空隙的总大小，
然后再加上最开始和最后阶段的空牛棚（例如共有10个牛棚，则3，5，8的情况下，1-2，9-10也是空牛棚） 
*/ 

#include<iostream>
#include<fstream>
#include<stdlib.h>
using namespace std;
int enc(const void *a, const void *b);
int dec(const void *a, const void *b);
int solve(int intervals[], int count, int M, int S, int min, int max);
int main()
{
	ifstream fin("barn1.in");
	ofstream fout("barn1.out");
	int M, S, C;   //M为板的数量， S为总的牛棚数， C为有牛的牛棚数 
	fin >> M >> S >> C;
	int filled[C];  //记录所有有牛的牛棚编号 
	for(int i = 0; i < C; ++i)
		fin >> filled[i];
	qsort(filled,C,sizeof(filled[0]),enc);  //按编号从小到大排序 
	int intervals[C-1];   //记录有牛的牛棚之间的空牛棚数目。 
	int interval, count = 0;
	for(int i = 0; i < C-1; ++i)
	{
		interval = filled[i+1] - filled[i] - 1;
		if(interval != 0)
			intervals[count++] = interval;
	}
	qsort(intervals,count,sizeof(intervals[0]),dec);  //从大到小排序 

	fout << solve(intervals,count,M,S,filled[0],filled[C-1]) << endl;
	
	fin.close();
	fout.close();
	return 0;
}

int dec(const void *a, const void *b)
{
	return (*(int *)b - *(int *)a);
}

int enc(const void *a, const void *b)
{
	return (*(int *)a - *(int *)b);
}

int solve(int intervals[], int count, int M, int S, int min, int max)
{
	int uncovered = 0;
	/*贪心算法，每次都取最大的间隔数*/
	for(int i = 0; i < M-1 && i < count; ++i)
		uncovered += intervals[i];   
	uncovered += (S-max) + (min-1);   //加上最开始和最末尾的空牛棚数也不用覆盖 
	return (S-uncovered);   //牛棚总数减去未覆盖的牛棚数即为覆盖的牛棚数。 
}
