/*
ID: wxx54331
PROG: friday
LANG: C++
*/

/*0对应周日，1对应周一，……*/

#include<iostream>
#include<fstream>

using namespace std;

int calculateDay(int day);

int main()
{
        ifstream fin("friday.in");
        ofstream fout("friday.out");
        int daysOfMonth[13]={0,31,28,31,30,31,30,31,31,30,31,30,31};
        int count[7]={};
        int start = 1;         //1900年一月一日为星期一
        int N;
        int year, month; //记录当前年份和月份
        
        fin >> N;
        
        for(year = 1900; year < 1900+N; ++year)
        {
        	if( (year % 400 == 0) || ((year % 4 == 0) && (year % 100 != 0)) )
        		daysOfMonth[2] = 29;
        	else
        		daysOfMonth[2] = 28;
        	
        	for(month = 1; month <= 12; ++month)
        	{
        		count[calculateDay(start)]++;
        		start = (start + daysOfMonth[month]) % 7;
        	}
        }
        fout << count[6] << " " << count[0] << " ";
        for(int i = 1; i < 5; ++i)
                fout << count[i] << " ";
        fout << count[5] << endl;
        
        return 0;
}

/*
输入： int day; 某个月第一天为周几
输出： 这个月第13天为周几
*/
int calculateDay(int day)
{
        return (day + 12) % 7;
}
