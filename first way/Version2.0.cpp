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
int short_distance(int** matrix, int n, int first, int end, int lenght, int M , SOL& s)
{
	int min = INF, i, j, cost = 0, temp;
	vector <int> A(n, 0);
	//cout << " " << first + 1 << "&" << end + 1 << endl;
	s.path.push_back(first + 1);
	//PATH.push_back(first + 1);
	if (M != 0)
		s.l.push_back(M);
		//L.push_back(M);
	if (first == end)
	{
		//string s ;
		LONG SUM;
		cout << s.path[0];
		//cout << PATH[0];
		//s = to_string(PATH[0]);
		//for (j = 1; j < PATH.size(); j++) {
		for (j = 1; j < s.path.size(); j++) {
			cout << " =>> " << s.path[j];
			/*
			cout << " =>> " << PATH[j];
			s += "->";
			s += to_string(PATH[j]);
			*/
		}
		cout << endl;
		cout << "   " << s.l[0];
		//cout << "   " << L[0];
		s.LEN = s.l[0];
		//SUM = L[0];
		for (j = 1; j < s.l.size(); j++) {
		//for (j = 1; j < L.size(); j++) {
			cout << " --> " << s.l[j];
			//cout << " --> " << L[j];
			s.LEN += s.l[j];
			//SUM += L[j];
		}
		cout << "= = >>" << s.LEN << endl;
		//cout << "= = >>" << SUM << endl;
		ANSWER.push_back(s);
		//cout << ANSWER[0].Str;
		//cout << ANSWER[0].LEN;
		s.path.pop_back();
		//PATH.pop_back();
		s.l.pop_back();
		//L.pop_back();
		return 0;
	}
	if (lenght >= n - 1) {
		//PATH.pop_back();
		s.path.pop_back();
		//L.pop_back();
		s.l.pop_back();
		return INF;
	}
	/////////////////////////////////////////////
	for (i = 0; i < n; i++) {
		if (matrix[first][i] != 0 && matrix[first][i] != INF) {
			A[i] = matrix[first][i] + short_distance(matrix, n, i, end, lenght + 1, matrix[first][i] , s);
			//cost = A[i];
			if (min > A[i] && A[i] > 0)
				min = A[i];
		}
		//if ((PATH.front() == first + 1) && (PATH.back() == end + 1)) {
		if ((s.path.front() == first + 1) && (s.path.back() == end + 1)) {
			//string s ='\0' ;
			int SUM;
			cout << "\n % ";
			//cout << PATH[0];
			cout << s.path[0];
			//for (j = 1; j < PATH.size(); j++) {
			for (j = 1; j < s.path.size(); j++) {
				//cout << "->" << PATH[j];
				cout << "->" << s.path[j];
				//s += "->";
				//s+=PATH[j];
			}
			cout << " % \n";
			//cout << L[0];
			cout << s.l[0];
			s.LEN = s.l[0];
			//SUM = L[0];
			//for (j = 1; j < L.size(); j++) {
			for (j = 1; j < s.l.size(); j++) {
				//cout << " + " << L[j];
				cout << " + " << s.l[j];
				s.LEN += s.l[j];
				//SUM += L[j];
			}
			//cout << "=" << SUM << endl;
			cout << "=" << s.LEN << endl;
			ANSWER.push_back(s);
			//PATH.clear();
			s.path.clear();
			//PATH.push_back(first + 1);
			s.path.push_back(first + 1);
			//L.clear();
			s.l.clear();
			s.path.push_back(M);
			//PATH.push_back(M);
		}
	}
	/*
	if (!PATH.empty())
		PATH.pop_back();
	if (!L.empty())
		L.pop_back();
		*/
	if (!s.path.empty())
		s.path.pop_back();
	if (!s.l.empty())
		s.l.pop_back();

	return min;
}
int main()
{
	unsigned long long  int N, S, T, i, j, mm;
	long  long int  M, L = 0;
	SOL ss;
	string* SS;
	cin >> N >> M >> S >> T;	
	vector<Edge> E(M);
	//define table
	int** matrix;
	//vector <long long int>PATH;
	//vector <long long int>LL;
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
	cout << "Short distance among " << S << " and " << T << " :=" << short_distance(matrix, N, S - 1, T - 1, 0, mm , ss) << endl;

	for (i = 0; i < ANSWER.size(); i++)
	{
		cout << "(" << ANSWER[i].path[0] <<")";		
		for (j = 1; j < ANSWER[i].path.size(); j++) {
			cout << " - "  << ANSWER[i].l[j-1] << " - ";
			cout << "(" << ANSWER[i].path[j] << ")";		
		}
		
		cout << " = " << ANSWER[i].LEN << endl;
	}
	return 0;
}