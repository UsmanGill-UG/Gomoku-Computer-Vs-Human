#include <iostream>
#include <conio.h>
#include <time.h>
#include <fstream>
using namespace std;
#define max 19
void Init(char B[][max], int& dim, int NOP, int& WC, char PS[], int turn)
{
	cout << "DIMENSIONS:";
	cin >> dim;
	for (int ri = 0; ri < dim; ri++)
	{
		for (int ci = 0; ci < dim; ci++)
		{
			B[ri][ci] = '-';
		}
	}
	cout << "Player Symbol:";
	for (int i = 0; i <= NOP - 1; i++)
	{
		cin >> PS[i];
	}
	cout << "Win Count: "; cin >> WC;
	turn = 0;
}
void DisplayBoard(char B[][max], int dim)
{
	for (int ri = 0; ri < dim; ri++)
	{
		for (int ci = 0; ci < dim; ci++)
		{
			cout << B[ri][ci];
		}
		cout << endl;
	}
}
void Coordinate(int& ri, int& ci)
{
	cout << "Row Pos:\t";
	cin >> ri;
	cout << "Col Pos:\t";
	cin >> ci;
	ri--, ci--;
}
bool IsValid(char B[][max], int dim, int ri, int ci)
{
	return (ri >= 0 && ri < dim&& ci >= 0 && ci < dim && (B[ri][ci] == '-'));

}
void UpdateBoard(char B[][max], int ri, int ci, char PS[], int turn)
{
	B[ri][ci] = PS[turn];
}
void DisplayPlayerMessage(char turn)
{
	cout << "Player " << turn << "'s Turn";
	cout << endl;
}
bool Horizontal(char B[][max], int dim, int WC, char PS[], int turn, int ri, int ci)
{
	int count = 0;
	if (ci + WC - 1 >= dim)
		return false;
	else
	{
		for (int i = 0; i < WC; i++)
		{
			if (B[ri][ci + i] == PS[turn])
				count++;
		}
		if (count == WC)
			return true;
		else return false;
	}
}
bool Vertical(char B[][max], int dim, int WC, char PS[], int turn, int ri, int ci)
{
	int count = 0;
	if (ri + WC - 1 >= dim)
		return false;
	else
	{
		for (int i = 0; i < WC; i++)
		{
			if (B[ri + i][ci] == PS[turn])
				count++;
		}
		if (count == WC)
			return true;
		else
			return false;
	}
}
bool Diaginal1(char B[][max], int dim, int WC, char PS[], int turn, int ri, int ci)
{
	int count = 0;
	if (ci - WC + 1 >= dim && ri + WC - 1 >= dim)
		return false;
	else
	{
		for (int i = 0; i < WC; i++)
		{
			if (B[ri + i][ci - i] == PS[turn])
				count++;
		}
		if (count == WC)
			return true;
		else
			return false;
	}
}
void Wait(int T)
{
	for (int i = 0; i < T * 1000000000000000000; i++)
	{

	}
}
bool Diagonal2(char B[][max], int dim, int WC, char PS[], int turn, int ri, int ci)
{
	int count = 0;
	if (ci + WC - 1 >= dim || ri + WC - 1 >= dim)
		return false;
	else
	{
		for (int i = 0; i < WC; i++)
		{
			if (B[ri + i][ci + i] == PS[turn])
				count++;
		}
		if (count == WC)
			return true;
		else
			return false;
	}
}

bool IsWin(char B[][max], int dim, int WC, char PS[], int turn)
{
	bool WH = false;
	for (int ri = 0; ri < dim; ri++)
	{
		for (int ci = 0; ci < dim; ci++)
		{
			WH = Diaginal1(B, dim, WC, PS, turn, ri, ci) || Diagonal2(B, dim, WC, PS, turn, ri, ci) || Horizontal(B, dim, WC, PS, turn, ri, ci) || Vertical(B, dim, WC, PS, turn, ri, ci);
			if (WH == true)
				return true;
		}
	}
	return false;
}
bool IsDraw(char B[][max], int Dim)
{
	for (int ri = 0; ri < Dim; ri++)
	{
		for (int ci = 0; ci < Dim; ci++)
		{
			if (B[ri][ci] == '-')
				return false;
		}
	}
	return true;
}
void TurnChange(int& turn, int NOP)
{
	turn++;
	if (turn == NOP)
		turn = 0;
}

void ComputerMove(char B[][max], int dim, int& ri, int& ci, int WC, char PS[], int turn)
{
	for (int r = 0; r < dim; r++)
	{
		for (int c = 0; c < dim; c++)
		{
			bool WinH = false;
			if (B[r][c] == '-')
			{
				B[r][c] = PS[1];
				WinH = IsWin(B, dim, WC, PS, 1);
				if (WinH)
				{
					ri = r; ci = c;
					return;
				}
				else
				{
					B[r][c] = '-';
				}
			}
		}
	}

	for (int r = 0; r < dim; r++)
	{
		for (int c = 0; c < dim; c++)
		{
			bool WinH = false;
			if (B[r][c] == '-')
			{
				B[r][c] = PS[0];
				WinH = IsWin(B, dim, WC, PS, 0);
				B[r][c] = '-';
			}
			if (WinH)
			{
				ri = r; ci = c;
				return;
			}
		}
	}
	do
	{
		ri = rand() % dim;
		ci = rand() % dim;
	} while (!IsValid(B, dim, ri, ci));
}
int main()
{
	srand(time(0));
	char Board[max][max];
	char PS[100];
	bool Status = false, Draw = false;
	int ri, ci, Dim = 0, NOP = 2, score = 0, WC, turn = 0;
	Init(Board, Dim, NOP, WC, PS, turn);
	system("cls");
	do
	{
		system("cls");
		DisplayBoard(Board, Dim);
		if (turn == 0) {
			DisplayPlayerMessage(PS[turn]);
			do
			{
				Coordinate(ri, ci);
				if (!IsValid(Board, Dim, ri, ci))
				{
					cout << "Invalid:";
					DisplayPlayerMessage(PS[turn]);
				}
			} while (!IsValid(Board, Dim, ri, ci));
		}
		else
		{
			DisplayPlayerMessage(PS[turn]);
			Wait(10000000000000);
			ComputerMove(Board, Dim, ri, ci, WC, PS, turn);
		}
		UpdateBoard(Board, ri, ci, PS, turn);
		if (IsWin(Board, Dim, WC, PS, turn))
		{
			system("cls");
			DisplayBoard(Board, Dim);
			Status = true;
		}
		else if (IsDraw(Board, Dim))
		{
			DisplayBoard(Board, Dim);
			Status = true;
			Draw = true;
		}
		else
		{
			TurnChange(turn, NOP);
		}
	} while (!Status);
	if (Status && (Draw == false))
	{
		cout << PS[turn] << "  won";
	}
	else if (Draw)
		cout << "DRAW!";
	return _getch();
}

