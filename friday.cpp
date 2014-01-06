/*
ID: wxx54331
PROG: friday
LANG: C++
*/ 

/*0对应周日，1对应周一，……*/

#include<iostream>
#include<fstream>

using namespace std;

const int DAYS = 7;

int calculateDay(int day);
int daysInAMonth(int year, int month);

int main()
{
	ifstream fin("friday.in");
	ofstream fout("friday.out");
	int count[DAYS]={};
	int start = 1;	 //1900年一月一日为星期一 
	int N;
	int totalMonth;    //一共有多少个月 
	int year, month;    //记录当前年份和月份 
	
	fin >> N;
	totalMonth = N*12;
	for(int i = 1; i <= totalMonth; ++i)	
	{
		count[calculateDay(start)]++;
		year = 1900+(i-1)/12;    //当前年份 
		month = i%12;   //当前月份 
		start = (start+daysInAMonth(year,month)) % 7;   //下个月月初为星期几 
	}
	
	fout << count[6] << " " << count[0] << " ";
	for(int i = 1; i < 5; ++i)
		fout << count[i] << " ";
	fout << count[5] << endl;
	
	return 0;
}

/*
输入： int day;   某个月第一天为周几 
输出： 这个月第13天为周几 
*/
int calculateDay(int day)
{
	return (day + 12) % 7;
}

/*计算一个月中有几天*/
int daysInAMonth(int year, int month)
{
	int days;
	if(month == 2)
	{
		if(year % 100 == 0)
		{
			if(year % 400 == 0)
				days = 29;
			else 
				days = 28;
		}
		else if(year % 4 == 0)
			days = 29;
		else
			days = 28;
	}
	else if(month == 4 || month == 6 || month == 9 || month == 11)
		days = 30;
	else
		days = 31;
	return days;
}
