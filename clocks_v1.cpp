/*
ID: wxx54331
PROG: clocks
LANG: C++
*/
/*
转动的顺序和最后的结果无关，且每个操作进行4次就会回到原始状态，
因此搜索空间是4*9，可以直接用枚举法做。 
*/
#include<iostream>
#include<fstream>
#include<climits>

using namespace std; 

const int MAX = 3;
const int STEP = 3;
const int MOD = 12;
int clocks[MAX][MAX];
int back[MAX][MAX];
int result[10];

int mod(int num);
void move(int op);
bool isComplete();
void reset();
bool solve();

int main()
{
	ifstream fin("clocks.in");
	ofstream fout("clocks.out");
	
	for(int i = 0; i < MAX; ++i)
		for(int j = 0; j < MAX; ++j)
		{
			fin >> clocks[i][j];
			back[i][j] = clocks[i][j];
		}

	if(solve())
	{
		bool flag = true;
		for(int i = 1; i <= 9; ++i)
			for(int j = 0; j < result[i]; ++j)
			{
				if(flag)
				{
					fout << i;
					flag = false;
				}
				else
					fout << " " << i;
			}
		fout << endl;
	}
	
	fin.close();
	fout.close();
	return 0;
}

void move(int op)
{
	switch(op)
	{
		case 1:		//ABDE
			clocks[0][0] = mod(clocks[0][0] + STEP);	//A
			clocks[0][1] = mod(clocks[0][1] + STEP);	//B
			clocks[1][0] = mod(clocks[1][0] + STEP);	//D
			clocks[1][1] = mod(clocks[1][1] + STEP);	//E
			break;
		case 2:		//ABC
			clocks[0][0] = mod(clocks[0][0] + STEP);	//A
			clocks[0][1] = mod(clocks[0][1] + STEP);	//B
			clocks[0][2] = mod(clocks[0][2] + STEP);	//C
			break;
		case 3:		//BCEF
			clocks[0][1] = mod(clocks[0][1] + STEP);	//B
			clocks[0][2] = mod(clocks[0][2] + STEP);	//C
			clocks[1][1] = mod(clocks[1][1] + STEP);	//E
			clocks[1][2] = mod(clocks[1][2] + STEP);	//F
			break;
		case 4:		//ADG
			clocks[0][0] = mod(clocks[0][0] + STEP);	//A
			clocks[1][0] = mod(clocks[1][0] + STEP);	//D
			clocks[2][0] = mod(clocks[2][0] + STEP);	//G
			break;
		case 5:		//BDEFH
			clocks[0][1] = mod(clocks[0][1] + STEP);	//B
			clocks[1][0] = mod(clocks[1][0] + STEP);	//D
			clocks[1][1] = mod(clocks[1][1] + STEP);	//E
			clocks[1][2] = mod(clocks[1][2] + STEP);	//F
			clocks[2][1] = mod(clocks[2][1] + STEP);	//H
			break;
		case 6:		//CFI
			clocks[0][2] = mod(clocks[0][2] + STEP);	//C
			clocks[1][2] = mod(clocks[1][2] + STEP);	//F
			clocks[2][2] = mod(clocks[2][2] + STEP);	//I
			break;
		case 7:		//DEGH
			clocks[1][0] = mod(clocks[1][0] + STEP);	//D
			clocks[1][1] = mod(clocks[1][1] + STEP);	//E
			clocks[2][0] = mod(clocks[2][0] + STEP);	//G
			clocks[2][1] = mod(clocks[2][1] + STEP);	//H
			break;
		case 8:		//GHI
			clocks[2][0] = mod(clocks[2][0] + STEP);	//G
			clocks[2][1] = mod(clocks[2][1] + STEP);	//H
			clocks[2][2] = mod(clocks[2][2] + STEP);	//I
			break;
		case 9:		//EFHI
			clocks[1][1] = mod(clocks[1][1] + STEP);	//E
			clocks[1][2] = mod(clocks[1][2] + STEP);	//F
			clocks[2][1] = mod(clocks[2][1] + STEP);	//H
			clocks[2][2] = mod(clocks[2][2] + STEP);	//I
			break;
	}
}

int mod(int num)
{
	if(num % MOD == 0)
		return 12;
	else
		return (num % MOD);
}

bool isComplete()
{
	for(int i = 0; i < MAX; ++i)
		for(int j = 0; j < MAX; ++j)
			if(clocks[i][j] != 12)
				return false;
	return true;
}

bool solve()
{
	int min = INT_MAX;
	int a[10];
	bool flag = false;

	for(a[1] = 0; a[1] <= 3; ++a[1])
		for(a[2] = 0; a[2] <= 3; ++a[2])
			for(a[3] = 0; a[3] <= 3; ++a[3])
				for(a[4] = 0; a[4] <= 3; ++a[4])
					for(a[5] = 0; a[5] <= 3; ++a[5])
						for(a[6] = 0; a[6] <= 3; ++a[6])
							for(a[7] = 0; a[7] <= 3; ++a[7])
								for(a[8] = 0; a[8] <= 3; ++a[8])
									for(a[9] = 0; a[9] <= 3; ++a[9])
									{
										reset();
										for(int i = 1; i <= 9; ++i)
											for(int j = 0; j < a[i]; ++j)
												move(i);
										if(isComplete())
										{
											flag = true;
											int sum = 0;
											for(int i =1; i <=9; ++i)
												sum += a[i];
											if(sum < min)
											{
												min = sum;
												for(int i = 1; i < 10; ++i)
													result[i] = a[i];
											}
										}
									}
	return flag;
}


void reset()
{
	for(int i = 0; i < 3; ++i)
		for(int j = 0; j < 3; ++j)
			clocks[i][j] = back[i][j];
}
