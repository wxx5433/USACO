/*
ID: wxx54331
PROG: frac1
LANG: C++
*/
/*
数学的做法
参见Grapham, Kunth and Patashnik. Concrete Mathematics(2th edition). 
		Chapter 4 Number Theory: 4.5 Relative Primality 
*/
#include<fstream>
using namespace std;

int N;
void printOrderedFraction(int m1, int n1, int m2, int n2);
ofstream fout("frac1.out");
int main()
{
	ifstream fin("frac1.in");
	fin >> N;
	fin.close();
	fout << "0/1" << endl;  
    printOrderedFraction(0, 1, 1, 1);  
    fout << "1/1" << endl;
    fout.close();
    return 0;
}
         
void printOrderedFraction(int n1, int d1, int n2, int d2)
{
    if (d1+d2 <= N)
    {
        printOrderedFraction(n1, d1, n1+n2, d1+d2);  
        cout << n1+n2 << "/" << d1+d2 << endl;  
        printOrderedFraction(n1+n2, d1+d2, n2, d2);  
    }
}
