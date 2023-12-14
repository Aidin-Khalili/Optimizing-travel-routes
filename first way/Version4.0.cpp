#include <iostream>
#include <stdlib.h>
#include <string>
#include <vector>
#define Infinitely 2147483647
#define LONG long long int

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


LONG find_op_num(const vector <SOL>& ANSWER, LONG min)
{
	LONG i, op = 0;
	for (i = 0; i < ANSWER.size(); i++)
		if (ANSWER[i].LEN == min)
			op++;
	return op;
}

void sort(vector <SOL>& ANSWER)
{
	int j, z;
	for (j = 0; j < ANSWER.size(); j++)
	{
		for (z = j + 1; z < ANSWER.size(); z++)
		{
			if (ANSWER[j].LEN > ANSWER[z].LEN)
				swap(ANSWER[j], ANSWER[z]);
		}
	}
}
int condition(const vector <SOL>& ANSWER, LONG first, LONG end, LONG min, LONG Optimal)
{
	LONG i, j, o = 0, n = 0;

	for (i = 0; i < ANSWER.size(); i++)
	{
		for (j = 0; j < ANSWER[i].path.size() - 1; j++)
			if (ANSWER[i].path[j] == first && ANSWER[i].path[j + 1] == end)
			{
				if (ANSWER[i].LEN == min)
					o++;
				else n++;
			}
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

int short_distance(const vector<vector<LONG>>& matrix, vector <SOL>& ANSWER, LONG n, LONG first, LONG end, LONG lenght, LONG M, SOL& s)
{
	LONG min = Infinitely, i, j, cost = 0, temp;
	vector <int> A(n, 0);
	s.path.push_back(first+1);
	if (M != 0)
		s.l.push_back(M);
	if (first == end)
	{
		LONG SUM;
		/*
		cout << s.path[0];
		for (j = 1; j < s.path.size(); j++)
		{
			cout << " =>> " << s.path[j];
		}
		cout << endl;
		cout << "   " << s.l[0];
		*/
		s.LEN = s.l[0];
		for (j = 1; j < s.l.size(); j++)
		{
			//cout << " --> " << s.l[j];
			s.LEN += s.l[j];
		}
		//cout << "= = >>" << s.LEN << endl;
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
	if (end < first)
	{
		for (i = n; i < 0; i--)
		{
			if (matrix[first][i] != 0 && matrix[first][i] != Infinitely)
			{
				A[i] = matrix[first][i] + short_distance(matrix, ANSWER, n, i, end, lenght + 1, matrix[first][i], s);
				if (min > A[i] && A[i] > 0)
					min = A[i];
			}
		}
	}
	else
	{
		for (i = 0; i < n; i++)
		{
			if (matrix[first][i] != 0 && matrix[first][i] != Infinitely)
			{
				A[i] = matrix[first][i] + short_distance(matrix, ANSWER, n, i, end, lenght + 1, matrix[first][i], s);
				if (min > A[i] && A[i] > 0)
					min = A[i];
			}
		}
	}
	if (!s.path.empty())
		s.path.pop_back();
	if (!s.l.empty())
		s.l.pop_back();
	return min;
}

int main()
{
	LONG N, S, T, i, j, z, k, min, con_num, chance, count = 0, temp = 0, Optimal = 0, jj;
	LONG  M, L = 0;
	bool found, rep , rept = false;
	vector <SOL> ANSWER;
	SOL ss;
	cin >> N >> M >> S >> T;
	vector<Edge> E(M);
	vector<Edge> repitedly;
	vector<vector<LONG>> matrix(N, vector<LONG>(N, Infinitely));
	for (int i = 0; i < N; i++)
		matrix[i][i] = 0;
	for (i = 0; i < M; i++)
	{
		cin >> E[i].BEG >> E[i].END >> E[i].LEN;
		if (matrix[E[i].BEG - 1][E[i].END - 1] == Infinitely)
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
	//print(matrix);
	min = short_distance(matrix, ANSWER, N, S - 1, T - 1, 0, 0, ss);
	//cout << "Short distance among " << S << " and " << T << " :=" << min << endl;
	sort(ANSWER);
	//print(ANSWER);
	Optimal = find_op_num(ANSWER, min);

	for (i = 0; i < E.size(); i++)
	{
		rep = false;
		for (j = 0; j < repitedly.size(); j++)
		{
			if (E[i].BEG == repitedly[j].BEG && E[i].END == repitedly[j].END && E[i].LEN != repitedly[j].LEN)
			{
				temp = matrix[E[i].BEG - 1][E[i].END - 1];
				matrix[E[i].BEG - 1][E[i].END - 1] = E[i].LEN;
				rep = true;
				for (k = 0; k < ANSWER.size(); k++)
				{
					for (z = 0; z < ANSWER[k].path.size(); z++)
						if (ANSWER[k].path[z] == E[i].BEG && ANSWER[k].path[z + 1] == E[i].END)
							ANSWER[k].LEN += matrix[E[i].BEG - 1][E[i].END - 1] - temp;
				}
				sort(ANSWER);
			}
		}
		if (matrix[E[i].BEG - 1][E[i].END - 1] != E[i].LEN && rep != true)
		{
			temp = matrix[E[i].BEG - 1][E[i].END - 1];
			matrix[E[i].BEG - 1][E[i].END - 1] = E[i].LEN;
			rep = true;
			for (k = 0; k < ANSWER.size(); k++)
			{
				for (z = 0; z < ANSWER[k].path.size(); z++)
					if (ANSWER[k].path[z] == E[i].BEG && ANSWER[k].path[z + 1] == E[i].END)
						ANSWER[k].LEN += matrix[E[i].BEG - 1][E[i].END - 1] - temp;
			}
			sort(ANSWER);
		}
		
		con_num = condition(ANSWER, E[i].BEG, E[i].END, min, Optimal);
		switch (con_num)
		{
		case(0):
		{
			for (j = 0; j < repitedly.size(); j++)
			{
				if (E[i].BEG == repitedly[j].BEG && E[i].END == repitedly[j].END && E[i].LEN == repitedly[j].LEN)
				{
					if (E[i].LEN == 1)
						cout << "NO" << endl;
					else cout << "CAN 1" << endl;
					rept = true;
					break;
				}
			}
			if (rept == true)
			{
				rept = false;
				break;
			}
			else
				cout << "YES" << endl;
			break;
		}
		case(1):
		{
			if (E[i].LEN != 1)
				cout << "CAN 1" << endl;
			else cout << "NO" << endl;
			break;
		}
		case(2):
		{
			found = false;
			for (j = 0; j < ANSWER.size() && found == false; j++)
			{
				for (z = 0; z < ANSWER[j].path.size() - 1; z++)
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
			for (k = 0; k < ANSWER.size(); k++)
			{
				for (z = 0; z < ANSWER[k].path.size() - 1; z++)
				{
					if (ANSWER[k].path[z] == E[i].BEG && ANSWER[k].path[z + 1] == E[i].END)
						ANSWER[k].LEN -= matrix[E[i].BEG - 1][E[i].END - 1] - temp;
				}
			}
		}
		sort(ANSWER);
	}

	return 0;
}
