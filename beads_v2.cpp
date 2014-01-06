/*
ID: wxx54331
PROG: beads
LANG: C++
*/


#include<iostream>
#include<fstream>
#include<string>
#include <algorithm>

using namespace std;

int main()
{
	ifstream fin("beads.in");
	ofstream fout("beads.out");
	int len;
	fin >> len;
	string neck;
	fin >> neck;
	neck = neck + neck;
	const int MAX = 800;
	int left[MAX][2], right[MAX][2];    //0表示red，1表示blue 
	left[0][0] = left[0][1] = 0;
	for(int i = 1; i <= len*2; ++i)
	{
		if(neck[i-1] == 'r')
		{
			left[i][0] = left[i-1][0] + 1;
			left[i][1] = 0; 
		}
		else if(neck[i-1] == 'b')
		{
			left[i][0] = 0;
			left[i][1] = left[i-1][1] + 1;
		}
		else
		{
			left[i][0] = left[i-1][0] + 1;
			left[i][1] = left[i-1][1] + 1;
		}
	}
	right[2*len][0] = right[2*len][1] = 0;
	for(int i = 2*len-1; i >= 0; --i)
	{
		if(neck[i] == 'r')
		{
			right[i][0] = right[i+1][0] + 1;
			right[i][1] = 0; 
		}
		else if(neck[i] == 'b')
		{
			right[i][0] = 0;
			right[i][1] = right[i+1][1] + 1;
		}
		else
		{
			right[i][0] = right[i+1][0] + 1;
			right[i][1] = right[i+1][1] + 1;
		}
	}

	int m = 0;
	for(int i = 0; i < len*2; ++i)
	{
		m = max(m,max(left[i][0],left[i][1])+max(right[i][0],right[i][1]));
	}
	if(m > len)
		m = len;
	fout << m << endl;
	
	fin.close();
	fout.close();
	return 0;
} 


