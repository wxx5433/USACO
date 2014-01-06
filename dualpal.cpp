/*
ID: wxx54331
PROG: dualpal
LANG: C++
*/

/*
回文数实际上是比较常见的，因此数据量不会太大，可以直接暴力搜索
直接借用了前一个程序palsquare的两个函数 isPalindrome 与 convert 
*/

#include<iostream>
#include<fstream>
#include<string>

using namespace std;

bool isPalindrome(string num);
string convert(int num, int base);

int main()
{
	ifstream fin("dualpal.in");
	ofstream fout("dualpal.out");
	
	int N, S; 
	fin >> N >> S;
	int count;  //记录有几个数字满足条件了，只要找到N个就可以了 
	int flag;  //记录有几个base满足条件 
	
	for(int i = S+1; count < N; ++i)  //找出严格大于S的满足条件的答案 
	{
		flag = 0;
		for(int base = 2; base <= 10; ++base)   //遍历2-10的base 
		{
			if(isPalindrome(convert(i,base)))
				flag++;
			if(flag == 2)   //已经找到两个了就不用再继续找了 
				break;
		}
		if(flag == 2)   
		{
			count++;
			fout << i << endl;
		}
	}
	
	fin.close();
	fout.close();
	return 0;
}

bool isPalindrome(string num)
{
	int len = num.length();
	for(int i = 0, j = len-1; i < j; ++i, --j)
	{
		if(num[i] != num[j])
			return false;
	}
	return true;
}

string convert(int num, int base)
{
	const char ch[10] = {'0','1','2','3','4','5','6','7','8','9'}; 
	string result="";
	int tmp;
	while(num!=0)
	{
		tmp = num%base;
		result = ch[tmp] + result;
		num /= base;
	}
	return result;
}
