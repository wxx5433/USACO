/*
ID: wxx54331
PROG: milk2
LANG: C++
*/

/*
首先根据所有时间区间的开始时间，对这些区间进行排序
然后再遍历排序之后的所有区间，如果两个区间有交集，则将他们合并 
*/ 

#include<iostream>
#include<fstream>
#include<stdlib.h>

using namespace std;

struct Milking{
	int begin;
	int end;
};

int cmp(const void * a, const void * b);

int main()
{
	ifstream fin("milk2.in");
	ofstream fout("milk2.out");
	const int MAX = 5000;
	Milking milking[MAX];
	int n;
	fin >> n;
	
	for(int i = 0; i < n; ++i)
		fin >>  milking[i].begin >> milking[i].end;
	qsort(milking, n, sizeof(milking[0]), cmp);   //按开始时间对区间进行排序 

	int longestMilkTime = 0, longestNoMilkTime = 0;
	int milkTime, noMilkTime; 
	Milking cur = milking[0];
	   
	for(int i = 1; i < n; ++i)   //遍历所有区间 
	{
		if(milking[i].begin > cur.end)   //两段区间没有相交
		{
			noMilkTime = milking[i].begin - cur.end;    //无人喂奶的时间 
			if(noMilkTime > longestNoMilkTime)
				longestNoMilkTime = noMilkTime;
				
			milkTime = cur.end - cur.begin;    //有人喂奶的时间 
			if(milkTime > longestMilkTime)
				longestMilkTime = milkTime;
			
			cur = milking[i];
		} 
		else
			if(milking[i].end > cur.end)
				cur.end = milking[i].end;
	}
	
	//检查最后一段区间 
	milkTime = cur.end - cur.begin;
	if(milkTime > longestMilkTime)
		longestMilkTime = milkTime;
	
	fout << longestMilkTime << " " << longestNoMilkTime << endl;
	
	fin.close();
	fout.close();
	return 0;
}

int cmp(const void * a, const void * b)
{
	Milking *x = (Milking *)a;
	Milking *y = (Milking *)b;
	return (x->begin - y->begin);
}
