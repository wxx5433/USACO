/*
ID: wxx54331
PROG: holstein
LANG: C++
*/
/*
这题就是bfs搜索，按照bfs搜索最先得到的答案肯定符合题意。
使用位运算的方法来模拟饲料的组合情况 
*/
#include<iostream>
#include<fstream>
#include<vector>
#include<deque>
using namespace std;

int typeOfVitamins;
int numberOfFeeds;
vector<int> demand;
vector< vector<int> > feeds;

void readData();
vector<int> bfs();
vector<int> getState(int feed);
void addFeed(vector<int> &state, const vector<int> feed);
bool isEnough(vector<int> currentState);
vector<int> bitToVector(int bit);
int main()
{
	ofstream fout("holstein.out");
	readData();
	vector<int> result;
	result = bfs();
	fout << result.size();
	for(int i = 0; i < result.size(); ++i)
		fout << " " << result[i];
	fout << endl;
	fout.close();
	return 0;
}
/*读入数据*/
void readData()
{
	ifstream fin("holstein.in");
	fin >> typeOfVitamins;
	int v;
	for(int i = 0; i < typeOfVitamins; ++i)
	{
		fin >> v;
		demand.push_back(v);
	}
	fin >> numberOfFeeds;
	vector<int> feed;
	int typeAmount;
	for(int i = 0; i < numberOfFeeds; ++i)
	{
		for(int j = 0; j < typeOfVitamins; ++j)
		{
			fin >> typeAmount;
			feed.push_back(typeAmount);
		}
		feeds.push_back(feed);
		feed.clear();
	}
	fin.close();
}
/*采用bfs搜索*/
vector<int> bfs()
{
	deque<int> q;   
	vector<bool> isSearched(1<<numberOfFeeds+1,false); //记录某种饲料的组合是否已经搜索过 
	int feed = 0, currentFeed = 0;	//使用位来表示各种饲料的使用情况 
	vector<int> state, currentState;  //记录当前各种维他命的数量 
	while(true)
	{
		if(!q.empty())
		{
			feed = q.front();   //从队列头部取出一种饲料的组合情况 
			q.pop_front();
			state = getState(feed);   //获取这种组合情况下各种维他命的供给量 
		}
		for(int i = 0; i < numberOfFeeds; ++i)
		{
			currentFeed = feed;
			currentState = state;
			
			currentFeed |= 1 << i;  //采用或运算模拟每次添加一种饲料到原来的组合中
			/*如果这种组合已经搜索过，或者与之前的组合情况相同则剪枝*/ 
			if(currentFeed == feed || isSearched[currentFeed])
				continue;
			isSearched[currentFeed] = true;
			addFeed(currentState, feeds[i]);  //添加这种饲料到组合中 
			if(isEnough(currentState))  //如果已经满足需求，则输出答案 
				return bitToVector(currentFeed);
			else
				q.push_back(currentFeed);
		}
	}
}
/*根据饲料的组合情况，获取当前各种维他命的供给量*/
vector<int> getState(int feed)
{
	vector<int> state;
	int index = 0;
	while(feed)
	{
		if(feed & 1)  //位运算取出最右边的一个1 
			addFeed(state,feeds[index]);
		++index;
		feed >>= 1;
	}
	return state;
}
/*向当前状态添加某种饲料*/
void addFeed(vector<int> &state, const vector<int> feed)
{
	if(state.empty())
		state = feed;
	else
		for(int i = 0; i < typeOfVitamins; ++i)
			state[i] += feed[i]; 
} 
/*判断饲料的组合是否已经满足需求*/
bool isEnough(vector<int> currentState)
{
	for(int i = 0; i < typeOfVitamins; ++i)
		if(currentState[i] < demand[i])
			return false;
	return true;
}
/*将二进制位转化为饲料的组合情况，获得最终的结果*/ 
vector<int> bitToVector(int bit)
{
	vector<int> result;
	int index = 1;
	while(bit)
	{
		if(bit & 1)
			result.push_back(index);
		++index;
		bit >>= 1;
	}
	return result;
}
