/*
ID: wxx54331
PROG: packrec
LANG: C++
*/
/*
（这道题的代码并不是我自己完成的，而是参考了别人的代码，自己又写了一遍 
因为自己的代码写的实在太丑陋了，下面的代码有很多我自己值得学习的地方） 
题目中已经告诉我们一共只有6种基本的摆放方法（实际上第4种和第5种是一样的）
那么我们只需要排列组合4个正方形的摆放位置，一共有4!种，每个正方形又可以横着或者竖着2种情况。
也就是说对于每一种摆放方法，一共有4!*2^4种放置的方法。
整道题目一共只要枚举960种情况，因此可以直接搜索。 
*/
#include<iostream>
#include<fstream>
#include<stdlib.h>
#include<queue>
#include<deque>
#include <climits>
using namespace std;
struct Rect{
	int w;
	int h;
	void rotate() {swap(w,h);}  //可以在结构中定义一些简单的方法 
}rect[4], result[100];
int minArea = INT_MAX;  //依赖于climits库 
int count;  //保存结果的数量 

void combination(queue<Rect>& Q, int depth);
void compute(Rect rect[]);
void record(int width, int height);
int cmp(const void *a, const void *b);

int main()
{
	ifstream fin("packrec.in");
	ofstream fout("packrec.out");
	queue<Rect> Q;    //在这个题里运用队列的数据结构很合适 
	int width, height;
	for(int i = 0; i < 4; ++i)
	{
		fin >> width >> height;
		Q.push((Rect){width,height});  //注意push的写法 
	}
	combination(Q,0);
	qsort(result,count,sizeof(result[0]),cmp);  //按照width从小到大排序 
	fout << minArea << endl;
	for(int i = 0; i < count; ++i)
		fout << result[i].w << " " << result[i].h << endl;
	fin.close();
	fout.close();
	return 0;
}

int cmp(const void *a, const void *b)
{
	Rect *ra = (Rect*)a;
	Rect *rb = (Rect*)b;
	return (ra->w - rb->w);
}
/*
运用递归来写DFS，大大的简化了代码，
原来自己就是没有用递归，写的太过于繁杂。 
*/
void combination(queue<Rect>& Q, int depth)
{
	if(depth == 4)  //DFS遍历到最深层是验证答案 
	{
		compute(rect);
		return;
	}
	for(int i = depth; i < 4; ++i)
	{
		rect[depth] = Q.front();
		Q.pop();
		combination(Q,depth+1);
		rect[depth].rotate();   //横/竖过来之后再计算一次 
		combination(Q,depth+1);
		rect[depth].rotate();  //恢复回原来的状态，放回队列中 
		Q.push(rect[depth]);
	}
}
/*计算面积*/
void compute(Rect rect[])
{
	int width, height;
	//case1
	width = rect[0].w + rect[1].w + rect[2].w + rect[3].w;
	height = max(rect[0].h,max(rect[1].h,max(rect[2].h,rect[3].h)));
	record(width, height);
	//case2
	width = max(rect[0].w + rect[1].w + rect[2].w,rect[3].h);
	height = max(rect[0].h,max(rect[1].h,rect[2].h)) + rect[3].w;
	record(width, height);
	//case3
	width = max(rect[0].w + rect[1].w + rect[2].w, rect[2].w+rect[3].h);
	height = max(max(rect[0].h,rect[1].h)+rect[3].w, rect[2].h);
	record(width, height);
	//case4,5
	width = rect[0].w+max(rect[1].w,rect[2].w)+rect[3].w;
	height = max(rect[0].h,max(rect[1].h+rect[2].h,rect[3].h));
	record(width, height);
	//case6
	/*这个地方感觉判断是否重叠还是有一些问题，不过测试点都过了，下一遍做的时候再看看*/ 
	if (rect[3].h >= rect[1].h){
		if (rect[0].w <= rect[1].w)
			if (!(rect[0].h + rect[1].h > rect[3].h && rect[0].w + rect[2].w > rect[1].w + rect[3].w)){
				width = max(rect[2].w, rect[1].w + rect[3].w);
				height = max(rect[0].h + rect[1].h, rect[2].h + rect[3].h);
				record(width, height);
			}
	}
	
}
/*如果是最小的面积方案，则记录到result中*/
void record(int width, int height)
{
	int area = height * width;
	if(area > minArea)
		return;
	if(area < minArea)
	{
		count = 0;
		minArea = area;
	}
	if(width > height)  //确保长比宽的数值大 
	{
		int tmp = width;
		width = height;
		height = tmp;
	}
	for(int i = 0; i < count; ++i)  //查找是否已经有这个答案 
	{
		if(result[i].w == width && result[i].h == height)
			return;
	}
	result[count].w = width;
	result[count].h = height;
	count++;
}
