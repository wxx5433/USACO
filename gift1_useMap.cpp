/*
ID: wxx54331
PROG: gift1
LANG: C++
*/

/*使用map的方法编写*/

#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<map>

using namespace std;

int peopleNumber;
ifstream fin("gift1.in");
map<string, int> peopleMap;
vector<string> people;

void initial();
void distribute();

int main()
{
	ofstream fout("gift1.out");
	
	initial();
	distribute();
	for (vector<string>::iterator iter = people.begin(); iter != people.end(); ++iter) 
        cout << *iter << " " << peopleMap[*iter] << endl;
        
	return 0;
} 

void initial()
{
	string name;
	fin >> peopleNumber;
	for (int i = 0; i < peopleNumber; ++i)
	{
		fin >> name;
		people.push_back(name);
		peopleMap.insert(pair<string,int>(name,0));
	}
}

void distribute()
{
	string name;
	int money = 0,senderNum = 0;
	int oneMoney = 0;
	for(int i = 0; i < peopleNumber; ++i)
	{
		fin >> name >> money >> senderNum;
		if(money == 0 || senderNum == 0)
			continue;
		oneMoney = money / senderNum;     //送给一个人钱的数量 
		peopleMap[name] -= oneMoney * senderNum;  //这个人总共支出的钱的数量 
		for(int j = 0; j < senderNum; ++j)
		{
			fin >> name;
			peopleMap[name] += money/senderNum;
		}
	}
}
