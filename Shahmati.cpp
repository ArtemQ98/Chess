#include <iostream>
#include <string>
#include <vector>
#include <Windows.h>

using namespace std;

char board[8][8]
{
	{'л', 'к', 'с', 'Ф', 'К', 'с', 'к', 'л'},
	{'п', 'п', 'п', 'п', 'п', 'п', 'п', 'п'},
	{'*', ' ', '*', ' ', '*', ' ', '*', ' '},
	{' ', '*', ' ', '*', ' ', '*', ' ', '*'},
	{'*', ' ', '*', ' ', '*', ' ', '*', ' '},
	{' ', '*', ' ', '*', ' ', '*', ' ', '*'},
	{'п', 'п', 'п', 'п', 'п', 'п', 'п', 'п'},
	{'л', 'к', 'с', 'Ф', 'К', 'с', 'к', 'л'}
};


vector<int> numBoard = { 8, 7, 6, 5, 4, 3, 2, 1, };
vector<char> strBoard = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H'};
string stepStart, stepFinal;
int symStart, symFinal;
int numStart, numFinal;

int main()
{
	setlocale(LC_ALL, "Ru");
	SetConsoleCP(CP_UTF7);
	while (true)
	{
		for (int i = 0; i < 8; i++)
		{
			cout << i + 8 - i * 2 << "| ";
			for (int j = 0; j < 8; j++)
			{
				cout << board[i][j];
			}
			cout << endl;
		}
		cout << "   " << "--------" << endl << "   ";
		for (int i = 0; i < 8; i++)
		{
			cout << strBoard[i];
		}
		cout << endl << endl;

		// Ход белых
		cout << "Ход белых из: ";
		getline(cin, stepStart);
		for (int i = 0; i < size(strBoard); i++)
		{
			if (stepStart[0] == strBoard[i])
			{
				symStart = i;
				break;
			}
		}
		stepStart = stepStart[1];
		numStart = stoi(stepStart);
		cout << "Ход белых в: ";
		getline(cin, stepFinal);
		for (int i = 0; i < size(strBoard); i++)
		{
			if (stepFinal[0] == strBoard[i])
			{
				symFinal = i;
				break;
			}
		}
		stepFinal = stepFinal[1];
		numFinal = stoi(stepFinal);
		board[8-numFinal][symFinal] = board[8 - numStart][symStart];
		if (numStart%2 == 0)
		{
			if ((symStart) % 2 == 0)
			{
				board[8 - numStart][symStart] = '*';
			}
			else
			{
				board[8 - numStart][symStart] = ' ';
			}
		}
		if (numStart % 2 == 1)
		{
			if ((symStart) % 2 == 1)
			{
				board[8 - numStart][symStart] = '*';
			}
			else
			{
				board[8 - numStart][symStart] = ' ';
			}
		}		cout << endl;
	}
	



















	/*while (true)
	{
		for (int i = 8; i > 0; i--)
		{
			cout << "\t";
			for (int j = 1; j <= 8; j++)
			{
				if (j == 1)
				{
					cout << i;
				}
				if (i == 8 && (j == 1 || j == 8))
				{
					cout << "Л";
				}
				else if (i == 8 && (j == 2 || j == 7))
				{
					cout << "К";
				}
				else if (i == 8 || i == 7)
				{
					cout << "П";
				}
				
				if (i > 2 && i < 7)
				{
					if (i % 2 == 1)
					{
						if (j % 2 == 1)
						{
							cout << " ";
						}
						else
						{
							cout << "*";
						}
					}
					if (i % 2 == 0)
					{
						if (j % 2 == 0)
						{
							cout << " ";
						}
						else
						{
							cout << "*";
						}
					}
				}

				if (i == 1 && (j == 1 || j == 8))
				{
					cout << "Л";
				}
				else if (i == 1 && (j == 2 || j == 7))
				{
					cout << "к";
				}
				else if (i == 1 && (j == 3 || j == 6))
				{
					cout << "С";
				}
				else if (i == 1 && j == 4)
				{
					cout << "Ф";
				}
				else if (i == 1 && j == 5)
				{
					cout << "К";
				}
				else if (i == 1 || i == 2)
				{
					cout << "П";
				}




			}
			cout << endl;
		}

		cout << "\t";
		cout << " ";
		for (int i = 0; i < size(strBoard); i++)
		{

			cout << strBoard[i];
		}
		cout << endl << endl;
		
		cout << "Ход белых из: ";
		getline(cin, stepStart);
		for (int i = 0; i < size(strBoard); i++)
		{
			if (stepStart[0] == strBoard[i])
			{
				symStart = i;
			}
		}
		stepStart = stepStart[1];
		numStart = stoi(stepStart);

		cout << symStart << "L" << numStart << endl;
		cout << "Ход белых в: ";
		getline(cin, stepFinal);
		for (int i = 0; i < size(strBoard); i++)
		{
			if (stepFinal[0] == strBoard[i])
			{
				symFinal = i;
			}
		}
		stepFinal = stepFinal[1];
		numFinal = stoi(stepFinal);

		cout << symFinal << "L" << numFinal << endl;
		cin;
	}*/
	

}

