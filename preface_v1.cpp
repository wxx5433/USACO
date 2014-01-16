/*
ID: wxx54331
PROG: preface
LANG: C++
*/
/*
直接枚举
但是需要一点技巧，先开一个数组把个十百千的罗马数字表示存储起来
然后就能按照阿拉伯数字的习惯去处理了 
*/ 
#include<fstream>
#include<iostream>
#include<string>
#include<sstream>
using namespace std;
string mark[4][9] = { {"I","II","III","IV","V","VI","VII","VIII","IX"},   //个 
				      {"X","XX","XXX","XL","L","LX","LXX","LXXX","XC"},   //十 
				      {"C","CC","CCC","CD","D","DC","DCC","DCCC","CM"},   //百 
				      {"M","MM","MMM"} };   //千
int count[100];
string convert(int num);	
void sum(string roman);	  
void output();
int main()
{
	int N;
	ifstream fin("preface.in");
	fin >> N;
	fin.close();
	for(int i = 1; i <= N; ++i)
	{
		sum(convert(i));
	}
	output();
	return 0;
} 

string convert(int num)
{
	stringstream ss;
	string number;
	ss << num;
	ss >> number;
	string result = "";
	int len = number.length();
	for(int i = 0; i < len; ++i)
	{
		if(number[i]-48 == 0)
			continue;
		result += mark[len-1-i][number[i]-49];
	}
	return result;
}

void sum(string roman)
{
	int len = roman.length();
	for(int i = 0; i < len; ++i)
		count[roman[i]]++;
}

void output()
{
	ofstream fout("preface.out");
	if(count['I'] != 0)
		fout << "I " << count['I'] << endl;
	if(count['V'] != 0)
		fout << "V " << count['V'] << endl;
	if(count['X'] != 0)
		fout << "X " << count['X'] << endl;
	if(count['L'] != 0)
		fout << "L " << count['L'] << endl;
	if(count['C'] != 0)
		fout << "C " << count['C'] << endl;
	if(count['D'] != 0)
		fout << "D " << count['D'] << endl;
	if(count['M'] != 0)
		fout << "M " << count['M'] << endl;
	fout.close();
}
