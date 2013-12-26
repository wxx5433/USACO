/*
ID: wxx54331
PROG: beads
LANG: C++
*/

/*
时间复杂度为O(n^2) 
遍历所有珠子，记录从第i个珠子开始的最长子串
例如： wrrbwb
       012345
将项链复制一遍，即考虑环的情况.
	   wrrbwbwrrbwb 
则记录为 count[0]记录的是wrr+bwbw = 7, count[1]记录的是rr+bwbw=6; 
取所有中最大的情况，只有当环了项链一圈的情况下才会将某颗珠子数两次
因此，只要在最后判断，如果max>len，则max=len 
*/

#include<iostream>
#include<fstream>
#include<string>

using namespace std;

int main()
{
	ifstream fin("beads.in");
	ofstream fout("beads.out");
	
	int len;
	fin >> len;
	
	string neck;
	fin >> neck;
	neck = neck + neck;   //将neck复制一份
	
	int max = 0;   //记录最长的长度 
	int count;   //记录从某颗珠子开始的长度 
	char color;   //记录序列最开始的珠子颜色（如果是白色，则遍历到第一颗非白色的为止） 
	bool flag;     //从某颗珠子开始遍历了一种颜色之后，还要遍历第二种颜色。 
	int cur_pos;   //记录当前珠子的位置 
	for(int start = 0; start < len; ++start) 
	{
		count = 0;    
		flag = false;
		cur_pos = start;
		if(neck[start] == 'w')   //如果第一颗珠子为白色，则跳到第一颗非白色的珠子 
		{
			while(neck[cur_pos] == 'w')
			{
				count++;
				cur_pos++;
			}
		}
		color = neck[cur_pos];   //以第一颗非白色珠子的颜色为第一种颜色 
		for(;cur_pos < len*2; ++cur_pos)    //继续向后遍历 
		{
			
			if(neck[cur_pos] == 'w' || neck[cur_pos] == color)   //如果后面的珠子是白色，或者是与color相同颜色，则count++ 
			{
				count++;
				continue;
			}
			if(flag == false)    //如果出现了第二种颜色，则开始统计第二种颜色color的长度 
			{
				color = neck[cur_pos];
				count++;
				flag = true;
			}
			else         //统计完第二种颜色 
				break;
		}
		if(count > max)
			max = count;
	}
	if(max > len)  //只有当环了项链一圈的情况下才会将某颗珠子数两次,因此，只要在最后判断，如果max>len，则max=len 
		max = len; 
	fout << max << endl;
	
	return 0;
}

