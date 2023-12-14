#include <iostream>
#include <stdlib.h>
#include <string>
#include <vector>
#include <set>
#define INF INT_MAX
#define LONG unsigned long long int
using namespace std;
struct Edge {
	LONG BEG;
	LONG END;
	long long int LEN;
	string Str;
};
struct SOL {
	vector <LONG> path;
	vector <LONG> l;
	LONG LEN;
};
vector <SOL> ANSWER;
int short_distance(int** matrix, int n, int first, int end, int lenght, vector <LONG>& L, vector <LONG>& PATH, int M)
{
	int min = INF, i, j, cost = 0, temp;
	vector <int> A(n, 0);
	//cout << " " << first + 1 << "&" << end + 1 << endl;
	PATH.push_back(first + 1);
	if (M != 0)
		L.push_back(M);
	if (first == end)
	{
		string s ;
		LONG SUM;
		cout << PATH[0];
		s = to_string(PATH[0]);
		for (j = 1; j < PATH.size(); j++) {
			cout << " =>> " << PATH[j];
			s += "->";
			s += to_string(PATH[j]);
		}
		cout << endl;
		cout << "   " << L[0];
		SUM = L[0];
		for (j = 1; j < L.size(); j++) {
			cout << " --> " << L[j];
			SUM += L[j];
		}
		cout << "= = >>" << SUM << endl;
		ANSWER.push_back( PATH , L , SUM );
		//cout << ANSWER[0].Str;
		//cout << ANSWER[0].LEN;
		PATH.pop_back();
		L.pop_back();
		return 0;
	}
	if (lenght >= n - 1) {
		PATH.pop_back();
		L.pop_back();
		return INF;
	}
	/////////////////////////////////////////////
	for (i = 0; i < n; i++) {
		if (matrix[first][i] != 0 && matrix[first][i] != INF) {
			A[i] = matrix[first][i] + short_distance(matrix, n, i, end, lenght + 1, L, PATH, matrix[first][i]);
			cost = A[i];
			if (min > A[i] && A[i] > 0)
				min = A[i];
		}
		if ((PATH.front() == first + 1) && (PATH.back() == end + 1)) {
			string s ='\0' ;
			int SUM;
			cout << "\n % ";
			cout << PATH[0];
			for (j = 1; j < PATH.size(); j++) {
				cout << "->" << PATH[j];
				s += "->";
				s+=PATH[j];
			}
			cout << " % \n";
			cout << L[0];
			SUM = L[0];
			for (j = 1; j < L.size(); j++) {
				cout << " + " << L[j];
				SUM += L[j];
			}
			cout << "=" << SUM << endl;
			ANSWER.push_back({s,SUM});

			PATH.clear();
			PATH.push_back(first + 1);
			L.clear();
			PATH.push_back(M);
		}
	}
	if (!PATH.empty())
		PATH.pop_back();
	if (!L.empty())
		L.pop_back();
	return min;
}
int main()
{
	unsigned long long  int N, S, T, i, j, mm;
	long  long int  M, L = 0;
	string* SS;
	cin >> N >> M >> S >> T;	
	vector<Edge> E(M);
	//define table
	int** matrix;
	vector <long long int>PATH;
	vector <long long int>LL;
	matrix = new int* [N];
	for (int i = 0; i < N; i++) {
		matrix[i] = new int[N];
	}
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (i == j)
				matrix[i][j] = 0;
			else
				matrix[i][j] = INF;
		}
	}
	for (i = 0; i < M; i++)
	{
		cin >> E[i].BEG >> E[i].END >> E[i].LEN;
		if (matrix[E[i].BEG - 1][E[i].END - 1] > E[i].LEN)
			matrix[E[i].BEG - 1][E[i].END - 1] = E[i].LEN;
	}
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (matrix[i][j] == INF)
				cout << "@    ";
			else
				cout << matrix[i][j] << "    ";
		}
		cout << endl;
	}
	mm = 0;
	cout << "Short distance among " << S << " and " << T << " :=" << short_distance(matrix, N, S - 1, T - 1, 0, LL, PATH, mm) << endl;
	return 0;
}