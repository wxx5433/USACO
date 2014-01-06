/*
ID: wxx54331
PROG: gift1
LANG: C++
*/

#include<iostream>
#include<fstream>
#include<string>
#include<vector>

using namespace std;

struct personStruct {
	string name;
	int initialMoney;
	int finalMoney;
};

ifstream fin("gift1.in");


int getIndex(string name, vector<personStruct> person, int number);
int distribute(vector<personStruct> &person);
int main()
{
	ofstream fout("gift1.out");
	vector<personStruct> person;
	personStruct onePerson;
	string name;
	int number;
	
	fin >> number;
	fin.get();  //读掉换行符
	 
	for(int i = 0; i < number; ++i)
	{
		getline(fin,name);
		onePerson.name = name;
		onePerson.initialMoney = 0;
		onePerson.finalMoney = 0;
		person.push_back(onePerson);
	}
	
	while(distribute(person))
		;
	for(int i = 0; i < number; ++i)
		fout << person[i].name << " " << person[i].finalMoney - person[i].initialMoney << endl;
	
	return 0;
}

int getIndex(string name, vector<personStruct> person)
{
	for(int i = 0; i < person.size(); ++i)
		if(name == person[i].name)
			return i;
}

int distribute(vector<personStruct> &person)
{
	string name;
	int initialMoney, senderNum;
	int index;
	if(!getline(fin,name))
		return 0;
	fin >> initialMoney >> senderNum;
	fin.get();
	
	index = getIndex(name, person);
	person[index].initialMoney += initialMoney;
	if(senderNum == 0)
		person[index].finalMoney += initialMoney;
	else
		person[index].finalMoney += initialMoney % senderNum;
	
	for(int i = 0; i < senderNum; ++i)
	{
		getline(fin, name);
		index = getIndex(name, person);
		person[index].finalMoney += initialMoney / senderNum;
	}
	return 1;
}

