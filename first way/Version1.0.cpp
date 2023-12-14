#include <iostream>
#include <stdlib.h>
#include <string>
#include <vector>
#include <set>
#define INF INT_MAX
using namespace std;
int short_distance(int** matrix, int n, int first, int end, int lenght, vector <int>& L, vector <int>& PATH,int M)
{
	int min = INF, i,j, cost = 0, temp;
	vector <int> A(n, 0);
	cout <<" "<< first + 1 << "&" << end + 1 << endl;
	PATH.push_back(first + 1);
	if (M!=0)
	   L.push_back(M);	
	if (first == end)
	{	
		cout << PATH[0];
		for (j = 1; j < PATH.size(); j++)
			cout << " =>> " << PATH[j];		
		cout << endl;
		cout <<"   "<< L[0];
		temp = L[0];
		for (j = 1; j < L.size(); j++) {
			cout << " --> " << L[j];
			temp += L[j];
		}
		cout <<"= = ="<< temp <<endl;
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
	for (i = 0; i < n; i++){
		if (matrix[first][i] != 0 && matrix[first][i] != INF){			
			A[i] = matrix[first][i]+short_distance(matrix, n, i, end, lenght + 1, L, PATH, matrix[first][i]);
			//L.push_back(matrix[first][i]);
			cost = A[i];
			//cout << "-=" << cost << endl;
			if (min > A[i] && A[i] > 0)
				min = A[i];
		}
		if ((PATH.front() == first + 1) && (PATH.back() == end + 1)) {
			cout << "\n % ";
			cout << PATH[0];
			for (j = 1; j < PATH.size(); j++)
				cout << "->" << PATH[j];
			cout << " % \n";
			cout << L[0];
			temp = L[0];
			for (j = 1; j < L.size(); j++) {
				cout << " + " << L[j];
				temp += L[j];
			}
			cout << "=" << temp << endl;
			PATH.clear();
			PATH.push_back(first + 1);
			L.clear();
			PATH.push_back(M);
			//PATH.erase(PATH.begin(), PATH.end());
			//L.erase(L.begin(), L.end());
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
	unsigned int N, S, T, i, j,mm;
	long  long int  M, L = 0;
	string* SS;
	cin >> N >> M >> S >> T;
	struct Edge {
		unsigned int BEG;
		unsigned int END;
		long long int LEN;
		string Str;
	};
	//	vector<vector<int>> graph(N, vector<int>(N, 0));
	//   vector<Node> city(N);
	vector<Edge> E(M);
	//define table
	int** matrix;
	vector <int>PATH;
	vector <int>LL;
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
	cout << "Short distance among " << S << " and " << T << " :=" << short_distance(matrix, N, S - 1, T - 1, 0, LL, PATH,mm) << endl;
	return 0;
}