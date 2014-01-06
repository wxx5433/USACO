/*
ID: wxx54331
PROG: gift1
LANG: C++
*/

/*修改了一下输入输出，并且重新修改了一下程序的结构*/

#include<iostream>
#include<fstream>
#include<string>
#include<vector>

using namespace std;

struct Person {
	string name;
	int initialMoney;
	int finalMoney;
};

ifstream fin("gift1.in");
ofstream fout("gift1.out");
vector<Person> person;
int number;   //总人数 

void initial();
int getIndex(string name);
void distribute();
void output();

int main()
{
	initial();
	distribute();
	output();
	
	return 0;
}

/*初始化，读入所有人的名字*/
void initial()
{
	Person onePerson;
	string name;
	
	fin >> number;
	for(int i = 0; i < number; ++i)
	{
		fin >> onePerson.name;
		onePerson.initialMoney = 0;
		onePerson.finalMoney = 0;
		person.push_back(onePerson);
	}
}

int getIndex(string name)
{
	for(int i = 0; i < number; ++i)
		if(name == person[i].name)
			return i;
}

void distribute()
{
	string name;
	int initialMoney, senderNum;
	int index;
	
	for(int j = 0; j < number;++j)
	{
	
		fin >> name >> initialMoney >> senderNum;		
		index = getIndex(name);
		person[index].initialMoney += initialMoney;   //送钱者最初的钱 
		if(senderNum == 0)   //送钱着送完钱之后还剩下的钱 
			person[index].finalMoney += initialMoney;
		else
			person[index].finalMoney += initialMoney % senderNum;
		for(int i = 0; i < senderNum; ++i)   //对应修改被送钱者的钱 
		{
			fin >> name;
			index = getIndex(name);
			person[index].finalMoney += initialMoney / senderNum;
		}
	}
}

void output()
{
	for(int i = 0; i < number; ++i)
		fout << person[i].name << " " << person[i].finalMoney - person[i].initialMoney << endl;
}
