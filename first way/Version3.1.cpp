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

int condition(LONG first, LONG end , LONG min)
{
	int i, j, o = 0, n = 0 , Optimal = 0;
	for (i = 0; i < ANSWER.size(); i++)
		if (ANSWER[i].LEN == min)
			Optimal++;

	for (i = 0; i < ANSWER.size(); i++)
	{
		for (j = 0; j < ANSWER[i].path.size() - 1; j++)
			if (ANSWER[i].path[j] == first && ANSWER[i].path[j + 1] == end)
				if (ANSWER[i].LEN == min)
					o++;
				else n++;
	}
	if (o == Optimal)
		return 0;
	else if (o > 0)
		return 1;
	if (n > 0)
		return 2;
	else
		return 3;
}

int short_distance(vector<vector<LONG>> matrix, int n, int first, int end, int lenght, int M, SOL& s)
{
	int min = Infinitely, i, j, cost = 0, temp;
	vector <int> A(n, 0);
	s.path.push_back(first + 1);
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
	LONG N, S, T, i, j, z, k , mm, min, con_num, chance , count = 0 , temp;
	long  long int  M, L = 0;
	bool found , rep;
	SOL ss;
	string* SS;
	cin >> N >> M >> S >> T;
	vector<Edge> E(M);
	vector<Edge> repitedly;
	vector<vector<LONG>> matrix(N, vector<LONG>(N, Infinitely));
	for (int i = 0; i < N; i++)
		matrix[i][i] = 0;
	for (i = 0; i < M; i++)
	{
		cin >> E[i].BEG >> E[i].END >> E[i].LEN;
		if(matrix[E[i].BEG - 1][E[i].END - 1] == Infinitely)
			matrix[E[i].BEG - 1][E[i].END - 1] = E[i].LEN;
		else
		{
			if (matrix[E[i].BEG - 1][E[i].END - 1] > E[i].LEN)
			{
				repitedly.push_back(E[i]);
				repitedly[count].LEN = matrix[E[i].BEG - 1][E[i].END - 1];
				matrix[E[i].BEG - 1][E[i].END - 1] = E[i].LEN;
			}
			else
				repitedly.push_back(E[i]);
			count++;
		}
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
	
	
	for (j = 0; j < ANSWER.size(); j++)
	{
		for (z = j + 1; z < ANSWER.size(); z++)
		{
			if (ANSWER[j].LEN > ANSWER[z].LEN)
				swap(ANSWER[j], ANSWER[z]);
		}
	}
	

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

	rep = false;
	for (i = 0; i < E.size(); i++)
	{
		for (j = 0; j < repitedly.size(); j++)
		{
			if (E[i].BEG == repitedly[j].BEG && E[i].END == repitedly[j].END && E[i].LEN != repitedly[j].LEN)
			{
				///////////////////////////////////////////////////////////////////////////
				temp = matrix[E[i].BEG - 1][E[i].END - 1];
				matrix[E[i].BEG - 1][E[i].END - 1] = repitedly[j].LEN;
				rep = true;
				for (k = 0; k < ANSWER.size(); k++)
				{
					for (z = k + 1; z < ANSWER.size(); z++)
					{
						if (ANSWER[k].LEN > ANSWER[z].LEN)
							swap(ANSWER[k], ANSWER[z]);
					}
				}
				break;
			}
		}
			con_num = condition(E[i].BEG, E[i].END, min);
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
				for (j = 0; j < ANSWER.size() && found == false; j++)
				{
					for (z = 0; z < ANSWER[j].path.size(); z++)
						if (ANSWER[j].path[z] == E[i].BEG && ANSWER[j].path[z + 1] == E[i].END)
						{
							found = true;
							chance = E[i].LEN - (ANSWER[j].LEN - min + 1);
							if (chance > 0)
								cout << "CAN " << ANSWER[j].LEN - min + 1 << endl;
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

			if (rep == true)
			{
				matrix[E[i].BEG - 1][E[i].END - 1] = temp;
				rep = false;
			}
		}

	return 0;
}