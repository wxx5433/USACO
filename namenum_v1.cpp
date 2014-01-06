/*
ID: wxx54331
PROG: namenum
LANG: C++
*/

/*
首先把字典中的所有单词都转化为数字的形式，存储这样一份单词对应数字的字典
然后再查找字典，这样的方法适合于不止一次查询的情况 
实际上还可以效率更高，可以考虑建立一颗字典树，节点为数字，并设立string数组存储经过这条路径的单词。
例如4->7->3->4, 这条路径上，在最后'4'这个节点上可以存储"GREG"这个单词。 
*/

#include<iostream>
#include<fstream>
#include<string>

using namespace std;
const int MAX = 5000;
struct Dict{
	string name[MAX];
	string num[MAX];
	int size;
};

char convert(char ch);
Dict readDict();
int main()
{
	ifstream fin("namenum.in");
	ofstream fout("namenum.out");
	Dict dict;
	dict = readDict();
	
	string number;
	fin >> number;
	bool flag = false;
	for(int i = 0; i < dict.size; ++i)
	{
		if(number.length() != dict.name[i].length())
			continue; 
		if(number == dict.num[i])
		{
			fout << dict.name[i] << endl;
			flag = true;
		}
	}
	if(!flag)
		fout << "NONE" << endl;
	fin.close();
	fout.close();
	return 0;
}

Dict readDict()
{
	ifstream fdict("dict.txt");
	string name, number;
	Dict dict;
	int len;
	char tmp;
	int size = 0;
	while(fdict >> name)
	{
		len = name.length();
		number = "";
		for(int i = 0; i < len; ++i)
		{
			tmp = convert(name[i]);
			if(tmp == '0')
				break;
			number += tmp;
		}
		if(number.length() == len)
		{
			dict.name[size] = name;
			dict.num[size] = number;
			dict.size = ++size;
		}
	}
	fdict.close();
	return dict;
}

char convert(char ch)
{
	if(ch == 'A' || ch == 'B' || ch == 'C')
		return '2';
	else if(ch == 'D' || ch == 'E' || ch == 'F')
		return '3';
	else if(ch == 'G' || ch == 'H' || ch == 'I')
		return '4';
	else if(ch == 'J' || ch == 'K' || ch == 'L')
		return '5';
	else if(ch == 'M' || ch == 'N' || ch == 'O')
		return '6';
	else if(ch == 'P' || ch == 'R' || ch == 'S')
		return '7';
	else if(ch == 'T' || ch == 'U' || ch == 'V')
		return '8';
	else if(ch == 'W' || ch == 'X' || ch == 'Y')
		return '9';
	else
		return '0';
}
