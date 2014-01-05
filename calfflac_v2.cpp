/*
ID: wxx54331
PROG: calfflac
LANG: C++
*/
/*
时间复杂度O(n)
Manacher’s Algorithm 
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
	Interval interval = findLongestPal(character, j);
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

Interval findLongestPal(const char str[], int len)
{
	Interval interval;
	int *P = new int[len];  //P记录以i为起点的最长回文子串的半径长度(不包括自己） 
	/*C为当前的最长回文子串中心点，R为半径长度（不包括自己）*/
	int C = 0, R = 0;  
	for(int i = 1; i < len - 1; ++i)  //首尾的'#'符号不用遍历 
	{
		int iMirror = 2*C-i;  //i关于中心点C的镜像
		if(R <= i)
			P[i] = 0;  //暂时记为0，因为无法从之前的最长回文子串中获得信息，之后的while循环继续扩展  
		else
		{
			if(R-i > P[iMirror])  
				P[i] = P[iMirror];
			else
				P[i] = R - i;   //P[i]>=R-i, 之后的while循环继续扩展 
		} 
		/*
		如果向前后扩展一个字符相等，则将半径P[i]+1后继续向前扩展
		在原来的文章中，由于首尾的边界不相同(^#a#b#a#$)，所以不需要进行边界判断 
		*/ 
		while(str[i+P[i]+1] == str[i-P[i]-1] && (i+P[i]+1)<len && (i-P[i]-1)>=0)
			P[i]++;
			
		if(i+P[i] > R)
		{
			C = i;
			R = i + P[i];
		}
	} 
	int maxLen = 0;
	int center = 0;
	for(int i = 1; i < len-1; ++i)
	{
		//取最大的P[i] 
		if(P[i] > maxLen)
		{
			maxLen = P[i];
			interval.begin = i-P[i]+1;
			interval.end = i+ P[i]-1;
		}
	}
	
	delete[] P;
	return interval;
}

