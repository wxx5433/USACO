/*
ID: wxx54331
PROG: transform
LANG: C++
*/

/*直接模拟的方法就能得到结果*/ 

#include<iostream>
#include<fstream>

using namespace std;

const int MAX = 11;
/*
在这里设置了一个结构是因为， 我在写函数的时候不知道要怎么往回传二维数组，
上网查了一些资料以后找到了一个方法，但是传回来之后与原来的数组比较的时候
char**与char[11][11]又不匹配，感觉处理起来太麻烦了， 
因此，还不如采用一个结构的方式来存储，这样可以很方便的由函数返回，
而不会被指针的问题搞的晕头转向。 
*/
struct Square {
	char pattern[MAX][MAX];   
	int n;
};

Square readData(ifstream &fin, int n);
Square rotate(Square pre);
Square reflect(Square pre);
bool compare(Square a, Square b);
void solve(ofstream &fout, Square pre, Square post); 


int main()
{
	ifstream fin("transform.in");
	ofstream fout("transform.out");
	int n;
	fin >> n;
	Square pre, post;
	pre = readData(fin,n);
	post = readData(fin,n);
	solve(fout, pre, post);
	
	fin.close();
	fout.close();
	return 0;
}

Square readData(ifstream &fin, int n)
{
	Square square;
	square.n = n;
	for(int i = 1; i <= n; ++i)
		for(int j = 1; j <= n; ++j)
			fin >> square.pattern[i][j];
	return square;
}

Square rotate(Square pre)
{
	Square tmp;
	int N;
	N = tmp.n = pre.n;
	for(int i = 1; i <= N; ++i)
		for(int j = 1; j <= N; ++j)
			tmp.pattern[j][N-i+1] = pre.pattern[i][j];
	return tmp;
}

Square reflect(Square pre)
{
	Square tmp;
	int N;
	N = tmp.n = pre.n;
	for(int i = 1; i <= N; ++i)
		for(int j = 1; j <= N; ++j)
			tmp.pattern[i][N-j+1] = pre.pattern[i][j];
	return tmp;
}

bool compare(Square a, Square b)
{
	if(a.n != b.n)
		return false;
	int N = a.n;
	for(int i = 1; i <= N; ++i)
		for(int j = 1; j <= N; ++j)
			if(a.pattern[i][j] != b.pattern[i][j])
				return false;
	return true;
}

void solve(ofstream &fout, Square pre, Square post)
{
	if(compare(post, rotate(pre)))
		fout << 1 << endl;
	else if(compare(post, rotate(rotate(pre))))
		fout << 2 << endl;
	else if(compare(post, rotate(rotate(rotate(pre)))))
		fout << 3 << endl;
	else if(compare(post, reflect(pre)))
		fout << 4 << endl;
	else if(compare(post, rotate(reflect(pre)))
			|| compare(post, rotate(rotate(reflect(pre))))
			|| compare(post, rotate(rotate(rotate(reflect(pre))))))
		fout << 5 << endl;
	else if(compare(post, pre))
		fout << 6 << endl;
	else
		fout << 7 << endl;
}
