#include <iostream>
#include <stdlib.h>
#include <string>
#include <vector>
#define Infinitely INT_MAX
#define LONG unsigned long long int

using namespace std;

struct Edge {
	LONG BEG;
	LONG END;
	LONG LEN;
};
struct SOL {
	vector <LONG> path;
	vector <LONG> l;
	LONG LEN;
};
vector <SOL> ANSWER;
vector <SOL> Optimal;
vector <SOL> Non_optimal;

int condition(LONG first, LONG end)
{
	int i, j, o = 0 , n = 0;
	for (i = 0; i < Optimal.size(); i++)
	{
		for (j = 0; j < Optimal[i].path.size(); j++)
			if (Optimal[i].path[j] == first && Optimal[i].path[j + 1] == end)
				o++;
	}
	if (o == Optimal.size())
		return 0;
	else if (o > 0)
		return 1;
	for (i = 0; i < Non_optimal.size(); i++)
	{
		for (j = 0; j < Non_optimal[i].path.size(); j++)
			if (Non_optimal[i].path[j] == first && Non_optimal[i].path[j + 1] == end)
				n++;
	}
	if (n > 0)
		return 2;
	else
		return 3;
}

int short_distance(vector<vector<LONG>> matrix, int n, int first, int end, int lenght, int M, SOL& s)
{
	int min = Infinitely, i, j, cost = 0, temp;
	vector <int> A(n, 0);
	s.path.push_back(first+1);
	if (M != 0)
		s.l.push_back(M);
	if (first == end)
	{
		LONG SUM;
		cout << s.path[0];
		for (j = 1; j < s.path.size(); j++)
		{
			cout << " =>> " << s.path[j];
		}
		cout << endl;
		cout << "   " << s.l[0];
		s.LEN = s.l[0];
		for (j = 1; j < s.l.size(); j++)
		{
			cout << " --> " << s.l[j];
			s.LEN += s.l[j];
		}
		cout << "= = >>" << s.LEN << endl;
		ANSWER.push_back(s);
		s.path.pop_back();
		s.l.pop_back();
		return 0;
	}
	if (lenght >= n - 1)
	{
		s.path.pop_back();
		s.l.pop_back();
		return Infinitely;
	}
	for (i = 0; i < n; i++)
	{
		if (matrix[first][i] != 0 && matrix[first][i] != Infinitely)
		{
			A[i] = matrix[first][i] + short_distance(matrix, n, i, end, lenght + 1, matrix[first][i], s);
			if (min > A[i] && A[i] > 0)
				min = A[i];
		}
	}
	if (!s.path.empty())
		s.path.pop_back();
	if (!s.l.empty())
		s.l.pop_back();
	return min;
}

////////////////////////////////////////////////////////////////////////////////

int main()
{
	LONG N, S, T, i, j, z, mm, min , con_num , chance;
	long  long int  M, L = 0;
	bool found;
	SOL ss;
	string* SS;
	cin >> N >> M >> S >> T;
	vector<Edge> E(M);
	vector<vector<LONG>> matrix(N, vector<LONG>(N));
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			if (i == j)
				matrix[i][j] = 0;
			else
				matrix[i][j] = Infinitely;
		}
	}
	for (i = 0; i < M; i++)
	{
		cin >> E[i].BEG >> E[i].END >> E[i].LEN;
		if (matrix[E[i].BEG - 1][E[i].END - 1] > E[i].LEN)
			matrix[E[i].BEG - 1][E[i].END - 1] = E[i].LEN;
	}
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			if (matrix[i][j] == Infinitely)
				cout << "@    ";
			else
				cout << matrix[i][j] << "    ";
		}
		cout << endl;
	}
	mm = 0;
	min = short_distance(matrix, N, S - 1, T - 1, 0, mm, ss);
	cout << "Short distance among " << S << " and " << T << " :=" << min << endl;
	for (i = 0; i < ANSWER.size(); i++)
	{
		cout << "(" << ANSWER[i].path[0] << ")";
		for (j = 1; j < ANSWER[i].path.size(); j++)
		{
			cout << " - " << ANSWER[i].l[j - 1] << " - ";
			cout << "(" << ANSWER[i].path[j] << ")";
		}

		cout << " = " << ANSWER[i].LEN << endl;
	}
	j = 0;
	z = 0;
	cout << "We have ";
	for (i = 0; i < ANSWER.size(); i++)
	{
		if (ANSWER[i].LEN == min)
		{
			Optimal.push_back(ANSWER[i]);
			j++;
		}
		else
		{
			Non_optimal.push_back(ANSWER[i]);
			z++;
		}
	}
	ANSWER.clear();
	cout << j << " minimum that there lenght is : " << min << endl;
	cout << "there are : " << endl;
	for (i = 0; i < Optimal.size(); i++)
	{
		cout << "(" << Optimal[i].path[0] << ")";
		for (j = 1; j < Optimal[i].path.size(); j++)
		{
			cout << " - " << Optimal[i].l[j - 1] << " - ";
			cout << "(" << Optimal[i].path[j] << ")";
		}

		cout << " = " << Optimal[i].LEN << endl;
	}

	for (i = 0; i < Non_optimal.size(); i++)
	{
		for (j = i + 1; j < Non_optimal.size(); j++)
		{
			if (Non_optimal[i].LEN > Non_optimal[j].LEN)
				swap(Non_optimal[i], Non_optimal[j]);
		}
	}

	cout << "And the other is : " << endl;
	for (i = 0; i < Non_optimal.size(); i++)
	{
		cout << "(" << Non_optimal[i].path[0] << ")";
		for (j = 1; j < Non_optimal[i].path.size(); j++)
		{
			cout << " - " << Non_optimal[i].l[j - 1] << " - ";
			cout << "(" << Non_optimal[i].path[j] << ")";
		}

		cout << " = " << Non_optimal[i].LEN << endl;
	}

	for (i = 0; i < E.size(); i++)
	{
		con_num = condition(E[i].BEG, E[i].END);
		switch (con_num)
		{
		case(0):
		{
			cout << "YES" << endl;
			break;
		}
		case(1):
		{
			cout << "CAN 1" << endl;
			break;
		}
		case(2):
		{
			found = false;
			for (j = 0; j < Non_optimal.size() && found == false; j++)
			{
				for(z=0;z<Non_optimal[j].path.size();z++)
					if (Non_optimal[j].path[z] == E[i].BEG && Non_optimal[j].path[z + 1] == E[i].END)
					{
						found = true;
						chance = E[i].LEN - (Non_optimal[j].LEN - min + 1);
						if (chance > 0)
							cout << "CAN " << Non_optimal[j].LEN - min + 1 << endl;
						else cout << "NO" << endl;
						break;
					}
			}
			break;
		}
		case(3):
			cout << "NO" << endl;
		default:
			break;
		}
			

	}


	return 0;
}