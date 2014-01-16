/*
ID: wxx54331
PROG: subset
LANG: C++
*/
/*
这题用bfs做是不行的，因为数据量太大了，内存消耗过多。
当N较大时不要运行这个程序。。会死机。。这是个失败的程序。。 
*/ 
#include<iostream>
#include<fstream>
#include<deque>
#include<vector>
using namespace std;

struct State {
	vector<int> num;
	int sum;
};
int bfs(int N);
int getSum(const State &state, int num);
int main()
{
	ifstream fin("subset.in");
	ofstream fout("subset.out");
	
	int N;
	fin >> N;
	
	fout << bfs(N)/2 << endl;
	
	fin.close();
	fout.close();
	return 0;
}

int bfs(int N)
{
	int totalSum = (1+N)*N/2;
	if(totalSum%2 != 0)
		return 0;
	int halfSum = totalSum/2;
	deque< State > q;
	State lastState, currentState;
	lastState.sum = currentState.sum = 0;
	int count = 0;

	do
	{
		if(!q.empty())
		{
			lastState = q.front();
			q.pop_front();
		}
		int num;
		if(lastState.num.size() == 0)
			num = 1;
		else
			num = lastState.num.back()+1;
		for(; num <= N; ++num)
		{
			currentState = lastState;
			int sum = getSum(currentState,num);
			if(sum > halfSum)
				continue;
			else if(sum == halfSum)
				count++;
			else
			{
				currentState.sum = sum;
				currentState.num.push_back(num);
				q.push_back(currentState);
			}
		}
	}while(!q.empty());
	return count; 
}

int getSum(const State &state, int num)
{
	return state.sum+num;
}
