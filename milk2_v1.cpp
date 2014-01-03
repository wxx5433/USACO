/*
ID: wxx54331
PROG: milk2
LANG: C++
*/

/*
由于时间的范围是1e6次方，因此开了一个bool数组，来记录某个时间点是否有人喂奶。
然后遍历每一个区间，把这个区间内的时间点都置为有人喂奶。
最后只要统计这个bool数组，就能得到结果 
*/ 

#include<iostream>
#include<fstream>

using namespace std;

int main()
{
	ifstream fin("milk2.in");
	ofstream fout("milk2.out");

	const int MAX = 1000001;
	bool isMilk[MAX] = {};   /*记录某个时间点是否有人喂奶*/
	
	int N;
	fin >> N;
	
	int a,b;
	int begin = MAX, end = 0;    /*begin和end用来记录所有区间的头和尾*/
	int time;
	for(int i = 0; i < N; ++i)    /*遍历所有喂奶的区间*/ 
	{
		fin >> a >> b;
		if(a < begin)
			begin = a;
		if(b >end)
			end = b;
		for(time = a+1; time <= b; ++time)
			isMilk[time] = true;
	}
	
	int longestMilkTime = 0, longestNoMilkTime = 0;
	int tmp = 0;
	for(time = begin; time <= end+1; ++time)
	{
		if(isMilk[time] == true)
			tmp++;
		else 
		{
			if(tmp > longestMilkTime)
				longestMilkTime = tmp;
			tmp = 0;
		}
	}
	
	for(time = begin+1, tmp=0; time <= end; ++time)
	{
		if(isMilk[time] == false)
			tmp++;
		else 
		{
			if(tmp > longestNoMilkTime)
				longestNoMilkTime = tmp;
			tmp = 0;
		}
	}
	
	fout << longestMilkTime << " " << longestNoMilkTime << endl;
	
	fin.close();
	fout.close();
	return 0;	
}
