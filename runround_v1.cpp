/*
ID: wxx54331
PROG: runround
LANG: C++
*/
/*
直接枚举就可以了，不过要注意有几个地方可以优化
如果有某一位数值等于数字的长度，则它一定会回到自己，所以不可能是runaround数
此外，每一位都不能是0且不能是之前出现过的数字
*/
#include<iostream>
#include<fstream>
#include<stack>
using namespace std;
int convertToArray(unsigned long num, int* numArray);
unsigned long find(unsigned int N);
bool isRunaround(const int* numArray, int len);
int main()
{
	ifstream fin("runround.in");
	ofstream fout("runround.out");
	unsigned long N;
	fin >> N;
	fout << find(N) << endl;
	fout.close();
	return 0;
}

unsigned long find(unsigned int N)
{
	int len;
	int numArray[10];
	for(int num = N+1; ; ++num)  //枚举大于N的数字 
	{
		len = convertToArray(num, numArray);   //将数字转化为数组方便处理 
		if(isRunaround(numArray, len))   //判断是否满足条件 
			return num;
	}
}
/*将数字转化为数组方便处理 */
int convertToArray(unsigned long num, int* numArray)
{
	stack<int> tmpStack;
	int len = 0;
	while(num != 0)
	{
		tmpStack.push(num%10);
		num /= 10;
		len++;
	}
	for(int i = 0; i < len; ++i)
	{
		numArray[i] = tmpStack.top();
		tmpStack.pop();
	}
	return len;
}

bool isRunaround(const int* numArray, int len)
{
	int digitCount[10] = {0};
	/*枚举的优化，先检查是否有某位的数字为len或者0，以及检查是否有重复数字*/ 
	for(int i = 0; i < len; ++i)  
	{
		if(numArray[i] == len || numArray[i] == 0 || digitCount[numArray[i]] != 0)
			return false;
		digitCount[numArray[i]]++;
	}
	int index = 0;
	for(int count = 0; count < len; ++count)
	{
		index += numArray[index];
		while(index >= len)
			index -= len;
		digitCount[numArray[index]]++;
	}
	for(int i = 1; i <= 9; ++i)
	{
		if(digitCount[i] != 0 && digitCount[i] != 2)
			return false;
	}
	return true;
}
