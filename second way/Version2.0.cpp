#include <iostream>
#include <vector>
#define INF INT_MAX
#define LONG unsigned long long int
using namespace std;
void WarShall(vector<vector<LONG>> G, vector<vector<LONG>>& P, LONG N)
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
	LONG N,M, S, T,  min1,min2,min3,tmp;
	LONG i, j, mm;
	cin >> N >> M >> S >> T;
	vector<vector<LONG>> Matrix(N, vector<LONG>(N));
	vector<vector<LONG>> PATH(N, vector<LONG>(N));
	vector<vector<LONG>> Edge(M, vector<LONG>(3));
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
	WarShall(Matrix, PATH, N);
	min1 = PATH[S-1][T-1];
	
	for (register LONG ii = 0; ii < M; ii++)
	{
		cout << Edge[ii][0] << "->" << Edge[ii][1] << " [" << Edge[ii][2] << "] ";
		if (PATH[S-1][Edge[ii][0]] == INF || PATH[Edge[ii], 1][T-1] == INF) {
			cout << "NO\n";
			continue;
		}
		tmp=Matrix[Edge[ii][0] - 1][Edge[ii][1] - 1];
		Matrix[Edge[ii][0] - 1][Edge[ii][1] - 1] = INF;
		WarShall(Matrix, PATH, N);
		Matrix[Edge[ii][0] - 1][Edge[ii][1] - 1] = tmp;
		min2 = PATH[S - 1][T - 1];		
		if (min2 != min1) {
			WarShall(Matrix, PATH, N); //<<---------------------
			if (Edge[ii][2] == tmp)
				cout << "YES\n";
			else
				if (( tmp - 1) < 1)
					cout << "NO\n";
				else
					cout << "CAN " << Edge[ii][2] - tmp + 1 << "\n";
			continue;
		}
		Matrix[Edge[ii][0]-1][Edge[ii][1]-1]--;
		WarShall(Matrix, PATH, N);
		Matrix[Edge[ii][0]-1][Edge[ii][1]-1]++;
		min2 = PATH[S - 1][T - 1];		
		if (min2 < min1) {
			cout << "CAN 1\n";
			continue;
		}
		min3 = (PATH[S - 1][Edge[ii][0]-1] + Edge[ii][2] + PATH[Edge[ii][1]-1][T - 1]) - min1 + 1;//error
		if (min3<=1)
			cout << "NO\n";
		else
			cout << "CAN "<<min3<<"\n";
	}
	return 0;
}