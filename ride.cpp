/*
ID: wxx54331
PROG: ride
LANG: C++
*/

/*
输入都为大写字母，要将其映射为数字，例如A-->1, Z-->26.
那么我直接使用 A-A+1 --> 1, B-A+1 --> 2的方式来映射就可以了 
*/

#include<iostream>
#include<fstream>
#include<string>

using namespace std;

int hash(string str);
bool isReady(string a, string b);

int main()
{
	ifstream inFile("ride.in");
	ofstream outFile("ride.out");
	string groupName, cometName;
	
	getline(inFile,groupName);
	getline(inFile,cometName);
	
	if(isReady(groupName, cometName))
		outFile << "GO" << endl;
	else
		outFile << "STAY" << endl;
		
	return 0;
	
}

bool isReady(string a, string b)
{
	int modA = hash(a) % 47;
	int modB = hash(b) % 47;
	
	if(modA == modB)
		return true;
	else 
		return false;
}

int hash(string str)
{
	int result = 1;
	for(int i = 0; i < str.length(); ++i)
		result = result * (str[i] - 'A' + 1);
	//cout << result << endl;
	return result;
}


