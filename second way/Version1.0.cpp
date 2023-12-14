#include <iostream>
#include <stdlib.h>
#include <string>
#include <vector>
#include <set>
#include <algorithm>
#define INF INT_MAX
#define LONG unsigned long long int
using namespace std;
void WarShall(LONG** G, LONG** P, LONG N)
{
	for (register LONG i = 0; i < N; i++)
	   for (register LONG j = 0; j < N; j++)
    	P [i,j]= G[i,j];
	for (register LONG k = 0; k < N; k++)
		for (register LONG i = 0; i < N; i++)
			for (register LONG j = 0; j < N; j++) 
			    if ((P[i][k] + P[k][j]) < P[i][j])
				   	P[i][j] = P[i][k] + P[k][j];			
}
int main()
{
	LONG N,M, S, T,  min1,min2,min3;
	int i, j, mm;
	cin >> N >> M >> S >> T;
	LONG** Matrix, ** PATH;
	LONG** Edge;
	Matrix = new LONG* [N];
	PATH = new LONG * [N];
	Edge = new LONG* [M];
	for (register int i = 0; i < N; i++)
	{
		Matrix[i] = new LONG[N];
		PATH[i] = new LONG[N];
	}
	for (register LONG i = 0; i < M; i++)
	{
		Edge[i] = new LONG[3];
	}

	for (register LONG i = 0; i < N; i++)
	{
		for (register LONG  j = 0; j < N; j++)
		{
			if (i == j)
				Matrix[i][j] = 0;
			else
				Matrix[i][j] = INF;
		}
	}

	for (register LONG i = 0; i < M; i++)
	{
		cin >> Edge[i][0] >> Edge[i][1] >> Edge[i][2];
		if (Matrix[Edge[i][0] - 1][Edge[i][1] - 1] > Edge[i][2])
			Matrix[Edge[i][0] - 1][Edge[i][1] - 1] = Edge[i][2];
	}
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			if (Matrix[i][j] == INF)
				cout << "@    ";
			else
				cout << Matrix[i][j] << "    ";
		}
		cout << endl;
	}	
	WarShall(Matrix, PATH, N);
	min1 = PATH[S-1][T-1];
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			if (Matrix[i][j] == INF)
				cout << "@    ";
			else
				cout << Matrix[i][j] << "    ";
		}
		cout << endl;
	}

	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			if (PATH[i][j] == INF)
				cout << "@    ";
			else
				cout << PATH[i][j] << "    ";
		}
		cout << endl;
	}
	for (register LONG ii = 0; ii < M; ii++)
	{
		
		if (PATH[S-1][Edge[ii][0]] == INF || PATH[Edge[ii], 1][T-1] == INF) {
			cout << "NO\n";
			continue;
		}
		cout << Matrix[Edge[ii][0] - 1][Edge[ii][1] - 1] << "\n";
		Matrix[Edge[ii][0]-1][Edge[ii][1]-1]++;
		cout << Matrix[Edge[ii][0] - 1][Edge[ii][1] - 1] << "\n";
		WarShall(Matrix, PATH, N);
		min2 = PATH[S - 1][T - 1];
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < N; j++)
			{
				if (PATH[i][j] == INF)
					cout << "@    ";
				else
					cout << PATH[i][j] << "    ";
			}
			cout << endl;
		}
		Matrix[Edge[ii][0]-1][Edge[ii][1]-1]--;
		if (min2 > min1) {
			cout << "YES\n";
			continue;
		}			
		Matrix[Edge[ii][0]-1][Edge[ii][1]-1]--;
		WarShall(Matrix, PATH, N);
		min2 = PATH[S - 1][T - 1];
		Matrix[Edge[ii][0]-1][Edge[ii][1]-1]--;
		if (min2 < min1) {
			cout << "CAN 1\n";
			continue;
		}
		min3=min1-(PATH[S - 1][Edge[ii-1][0]] +Edge[ii-1][1]+PATH[Edge[ii-1][1]][T - 1])+1;
		if (min3<1)
			cout << "NO\n";
		else
			cout << "CAN "<<min3<<"\n";
	}
	return 0;
}