/*
ID: wxx54331
PROG: calfflac
LANG: C++
*/
/*
求最长回文需要分奇数和偶数来讨论，
这里使用了一个很巧妙的方法，在输入串中插入特殊符号，即可统一成奇数的情况
e.g. aba -> #a#b#a#, abba -> #a#b#b#a#
然后枚举每一个字符作为最长回文子串的中心点，取其中的最大值即为答案。 
*/
 
#include<iostream>
#include<fstream>
using namespace std;
//记录最长回文子串的左右边界的结构 
struct Interval{
	int begin;
	int end;
};
Interval findLongestPal(const char str[], int len);
int main()
{
	ifstream fin("calfflac.in");
	ofstream fout("calfflac.out");
	const int MAX = 20000;
	/*orig为原始读入的字符串， character是经过处理后的字符串
	character中只存储有'#'和小写字母（大写统一转化为小写）*/
	char orig[MAX], character[2*MAX];
	/*map用来映射character中的小写字母到orig中的位置（'#'不映射）*/
	int map[MAX];
	char ch;
	int i = 0;  //记录orig数组的索引 
	int j = 1;  //记录character数组的索引 
	int k = 0;  //记录map数组的索引 
	
	character[0] = '#';
	while( (ch = fin.get()) != EOF)
	{
		orig[i] = ch;   //原始的换行符也要保留 
		if(ch != '\n')   
		{
			if(ch >= 'A' && ch <= 'Z')
			{
				map[k++] = i;   //character到orig的位置映射 
				character[j++] = ch+32;
				character[j++] = '#';
			}
			else if(ch >= 'a' && ch <= 'z')
			{
				map[k++] = i;
				character[j++] = ch;
				character[j++] = '#';
			}
		}
		i++;
	}
	
	Interval interval = findLongestPal(character,j);
	/*最长回文子串的长度（不包括其他符号）*/ 
	fout << (interval.end - interval.begin)/2 + 1<< endl;
	/*x和y为character中找到的最长回文子串到orig位置的映射*/
	int x = map[(interval.begin+1)/2-1], y = map[(interval.end+1)/2-1];
	for(int p = x; p <= y; ++p)
		fout << orig[p];
	fout << endl;
	fin.close();
	fout.close();
	return 0;
} 
/*查找最长回文子串，返回值为子串的左边界和右边界*/
Interval findLongestPal(const char str[], int len)
{
	Interval interval;
	int center = 0, maxLen = 0;
	for(int i = 1; i < len; ++i)  //枚举每一个字符作为中心点 
	{
		int j = 1;
		//从当前中心点向左右两个方向进行扩展 
		while(str[i-j]==str[i+j] && i+j<len && i-j>=0)
			++j;
		--j;
		if(j > maxLen)
		{
			center = i;
			maxLen = j;
		}
	}
	/*+1,-1是因为子串的首尾一定是#，返回的时候可以去掉 */ 
	interval.begin = center-maxLen+1; 
	interval.end = center + maxLen-1;
	return interval;
}
