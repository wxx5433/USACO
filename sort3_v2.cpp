/*
ID: wxx54331
PROG: sort3
LANG: C++
*/

#include <fstream>
using namespace std;

int main()
{
	ifstream fin("sort3.in");
	ofstream fout("sort3.out");
	/*cxy表示在本来应该是数字x区间内的y的数量*/
	int N,c12=0,c21=0,c31=0,c32=0;
	int count[4]={0,0,0,0};
	fin>>N;
	int* number=new int[N];
	for (int i=0;i!=N;++i){
		fin>>number[i];
		++count[number[i]];
	}//读入数据，统计1，2，3的个数
	for (int i=0;i!=N;++i)//计算相应的cxy，只计算用到的
	{
		if (i<count[1] && number[i]==2) //统计在1位置上的2的数量						
			++c12;
		else if (count[1]<=i && i<count[1]+count[2] && number[i]==1)   //统计在2位置上的1的数量 
			++c21;
		else if (i>=count[1]+count[2] && number[i]!=3) //统计在3位置上的1和2的数量 
			number[i]==1?++c31:++c32;
	}
	/*采用数学方法计算出结果，假设c12>c21
	首先把位2上的1与位1上的2互换位置，这样之后位1中有2，位2中无1；然后把位3中的1全部交换回位1
	这样位1上就全部是1了，而位3中的2分别为其固有的2(c32)和从1中交换来的2(c12-c21)组成，
	再把它们交换回位2，所以总共需要交换次数为c21+c31+c32+(c12-c21)=c31+c32+c12*/
	fout<<c31+c32+(c21>c12?c21:c12)<<endl;
	return 0;
}
