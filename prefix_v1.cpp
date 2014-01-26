/*
ID: wxx54331
PROG: prefix
LANG: C++
*/
/*
用dfs能解决这题 
用所有的规则去匹配这个字符串，匹配到某个位置则将其压入栈中 
对于之后匹配的规则，如果还是匹配到该位置的则剪枝。 
例如： A B AB这三个规则，  字串为ABC
那么从第一个位置开始，用A匹配了一个字符，则将1压入栈中，
之后又用AB匹配了两个字符，则将2压入栈中，
这时所有规则匹配完了，则从栈中取出2, 无法继续匹配，
再取出1，这时候匹配了B，则长度为2，而长度2已经搜索过，所以剪枝。 
*/
#include<iostream>
#include<fstream>
#include<string>
#include<stack>
using namespace std;
const int MAX_PRIMITIVES_NUM = 200;
int primitivesNum;
string primitives[MAX_PRIMITIVES_NUM];
string sequence;

void readData();
int dfs();
int main()
{
	ofstream fout("prefix.out");
	readData();
	fout << dfs() << endl;
	fout.close();
	return 0;
} 

void readData()
{
	ifstream fin("prefix.in");
	string tmp;
	//读入primitives集合 
	fin >> tmp;
	while(tmp != ".")
	{
		primitives[primitivesNum++] = tmp;
		fin >> tmp;
	}
	//读入sequence 
	while(fin >> tmp)
		sequence += tmp;
	fin.close();
}

int dfs()
{
	stack<int> stk;
	stk.push(0);
	int from;  //从sequence的第几个字符开始匹配 
	int best = -1;  //记录最长匹配长度 
	//记录某个长度是否已经匹配过，用来剪枝
	bool *hasSearched = new bool[sequence.length()+1];    
	for(int i = 0; i < sequence.length()+1; ++i)
		hasSearched[i] = false;
	bool flag = false;  
	
	while(stk.size())
	{
		from = stk.top();
		stk.pop();
		if(from > best)   //更新最大匹配长度 
			best = from;
		for(int i = 0; i < primitivesNum; ++i)   //遍历所有规则 
		{
			int len = primitives[i].length();
			if(hasSearched[from+len])   //如果之前已经匹配到这个长度，则剪枝 
				continue;
			if(sequence.substr(from, len) == primitives[i])   //匹配某条规则 
			{
				stk.push(from+len);
				if((from+len) == sequence.length())    //当已经匹配到最大长度时则直接返回结果 
				{
					flag = true;
					break;
				}
				hasSearched[from+len] = true;
			}
		}
		if(flag)   //当已经匹配到最大长度时则直接返回结果 
		{
			best = sequence.length();
			break;
		}
	}
	delete[] hasSearched;
	return best;
}
