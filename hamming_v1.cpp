/*
ID: wxx54331
PROG: hamming
LANG: C++
*/
/*
由于数据量比较小，可以直接从小到大枚举是否满足条件
满足的话直接输出就可以了 
*/
#include<iostream>
#include<fstream>
#include<vector>
using namespace std;

int amount, len, hammingDist;
vector<int> result;

void search();
bool checkDistance(int num);
int computeDistance(int num);
void output(ofstream &fout, int num, int count);
int main()
{
	ifstream fin("hamming.in");
	fin >> amount >> len >> hammingDist;
	fin.close();
	search();
	return 0;
}
/*从小到大枚举每一个数字，并检查与之前生成的数字是否符合Hamming Distance的条件*/ 
void search()
{
	ofstream fout("hamming.out");
	int count = 0;  //记录已经生成的数量 
	result.push_back(0);
	count++;
	output(fout, 0,count);
	int upperBound = 1 << (len+1);	
	for(int num = 1; num < upperBound; ++num)  //从小到大枚举 
	{
		if(checkDistance(num))  //如果满足Hamming Distance条件则记录下来并输出 
		{
			result.push_back(num);
			count++;
			output(fout, num, count);
		}
		if(count == amount)
			return;
	}
	fout.close();
}
/*检查新生成的数字是否和已经满足条件的每一个数字都满足Hamming Distance的条件*/ 
bool checkDistance(int num)
{
	int dist;
	for(int i = 0; i < result.size(); ++i)
	{
		dist = computeDistance(result[i] xor num); //使用异或操作就能知道有几位数字不同了 
		if(dist < hammingDist)
			return false;
	}
	return true;
}
/*计算海明码距离*/
int computeDistance(int num)
{
	int dist = 0;
	while(num)
	{
		if(num & 1)
			++dist;
		num >>= 1;
	}
	return dist;
}

void output(ofstream &fout, int num, int count)
{
	if(count %10 == 1)
		fout << num;
	else if(count % 10 == 0 || count == amount)  //10个则换行，输出最后一个时候也换行 
		fout << " " << num << endl;
	else
		fout << " " << num;
}
