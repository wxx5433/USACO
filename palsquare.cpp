/*
ID: wxx54331
PROG: palsquare
LANG: C++
*/

/*
直接将数值转换到对应的进制，并且判断是否回文即可 
*/

#include<iostream>
#include<fstream>
#include<string>

using namespace std;
bool isPalindrome(string num);
string convert(int num, int base);
const char ch[20] = {'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F','G','H','I','J'};
int main()
{
	ifstream fin("palsquare.in");
	ofstream fout("palsquare.out");
	const int N = 300;
	int base;
	string square;
	fin >> base;
	for(int i = 1; i <= N; ++i)
	{
		square = convert(i*i, base);
		if(isPalindrome(square))
			fout << convert(i, base) << " " << square << endl;
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
	string result="";
	int tmp;
	while(num!=0)
	{
		tmp = num%base;
		/*
		if(tmp <= 9)
			result = (char)(tmp+48)  + result;
		else
			result = (char)(tmp+55)  + result;
		*/
		/*
		原本是像下面注释掉的这样写的，但是这样需要我去查看一下ASCII码表， 
		如果改成 const char ch[20] = {'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F','G','H','I','J'};
		这样的方式，则可直接根据数组下标来形成对应。
		在以后由整数转换到字符这个问题上可以借鉴这个方法。 
		*/ 
		result = ch[tmp] + result;
		num /= base;
	}
	return result;
}
