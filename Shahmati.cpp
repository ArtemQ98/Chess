#include <iostream>
#include <string>
#include <vector>
#include <Windows.h>

using namespace std;

string board[8][8]
{
	{"_лч_", "_кч_", "_сч_", "_Фч_", "_Кч_", "_сч_", "_кч_", "_лч_"},
	{"_пч_", "_пч_", "_пч_", "_пч_", "_пч_", "_пч_", "_пч_", "_пч_"},
	{"****", "    ", "****", "    ", "****", "    ", "****", "    "},
	{"    ", "****", "    ", "****", "    ", "****", "    ", "****"},
	{"****", "    ", "****", "    ", "****", "    ", "****", "    "},
	{"    ", "****", "    ", "****", "    ", "****", "    ", "****"},
	{"_пб_", "_пб_", "_пб_", "_пб_", "_пб_", "_пб_", "_пб_", "_пб_"},
	{"_лб_", "_кб_", "_сб_", "_Фб_", "_Кб_", "_сб_", "_кб_", "_лб_"}
};


vector<int> numBoard = { 8, 7, 6, 5, 4, 3, 2, 1, };
vector<char> strBoard = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H'};
string stepStart, stepFinal, peshkaUpdate;
int symStart, symFinal, numStart, numFinal, sum, sovp;
char stepBlackOrWhite;

int main()
{
	setlocale(LC_ALL, "Ru");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
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
		cout << "   " << "--------------------------------" << endl << "   ";
		for (int i = 0; i < 8; i++)
		{
			cout << " " << strBoard[i] << "  ";
		}
		cout << endl << endl;

		// Ход

		while (true)
		{	
			if (sum % 2 == 0)
			{
				stepBlackOrWhite = 'W';
				cout << "Ход белых из: ";
			}
			else
			{
				stepBlackOrWhite = 'B';
				cout << "Ход чёрных из:";
			}
			getline(cin, stepStart);

			while (true) //Ход откуда
			{
				for (int i = 0; i < size(strBoard); i++)
				{
					if (stepStart[0] == strBoard[i])
					{
						symStart = i;
						sovp++;
						break;
					}
				}
				if (sovp > 0)
				{
					sovp = 0;
					break;
				}
				else
				{
					cout << "Неверное значение" << endl;
					cout << "Введите ход: ";
					getline(cin, stepStart);
				}
			}

			stepStart = stepStart[1];
			numStart = stoi(stepStart);
			if (board[8 - numStart][symStart] == "    " || board[8 - numStart][symStart] == "****")
			{
				cout << "Вы выбрали пустое поле!" << endl;
				sum--;
			}
			else
			{
				break;
			}
		}
		
		while (true) //Ход куда
		{
			if (stepBlackOrWhite == 'W')
			{
				cout << "Ход белых в: ";
				getline(cin, stepFinal);
			}
			else
			{
				cout << "Ход чёрных в:";
				getline(cin, stepFinal);
			}

			while (sovp == 0)
			{
				for (int i = 0; i < size(strBoard); i++)
				{
					if (stepFinal[0] == strBoard[i])
					{
						symFinal = i;
						sovp++;
						break;
					}
				}
				if (sovp > 0)
				{
					sovp = 0;
					break;
				}
				else
				{
					cout << "Неверное значение" << endl;
					cout << "Введите ход: ";
					getline(cin, stepFinal);
				}
			}

			stepFinal = stepFinal[1];
			numFinal = stoi(stepFinal);

			if (board[8 - numStart][symStart] == "_пб_")
			{
				if (numStart == numFinal && symStart == symFinal)
				{
					cout << "Нельзя ходить в первоначальную клетку!" << endl;
					continue;	
				}
				else if (numFinal == 8)
				{
					while (true)
					{
						cout << "Какой фигурой вы хотите стать?";
						cin >> peshkaUpdate;
						if (peshkaUpdate == "Король")
						{
							cout << "Вы не можете стать королём";
							continue;
						}
						
						else if (peshkaUpdate == "Ладья")
						{
							board[8 - numStart][symStart] = "_лб_";
							break;
						}
						else if (peshkaUpdate == "Ферзь")
						{
							board[8 - numStart][symStart] = "_Фб_";
							break;
						}
						else if (peshkaUpdate == "Слон")
						{
							board[8 - numStart][symStart] = "_сб_";
							break;
						}
						else if (peshkaUpdate == "Конь")
						{
							board[8 - numStart][symStart] = "_кб_";
							break;
						}
						else
						{
							cout << "Я не знаю такой фигуры" << endl;
							continue;
						}
					}
				}

				if (numStart == 2 && (!(numFinal == numStart + 1 || numFinal == numStart + 2) || !(symStart == symFinal) || !(board[8 - numFinal][symFinal] == "****" || board[8 - numFinal][symFinal] == "    ")))
				{
					cout << "Неверный ход пешкой1" << endl;
					continue;
				}

				if ((numStart != 2 && board[8 - numFinal][symFinal] == "****") || (numStart != 2 && board[8 - numFinal][symFinal] == "    "))
				{
					if (symStart != symFinal || numStart != numFinal-1)
					{
						cout << "Неверный ход пешкой 2" << endl;
						continue;
					}
				}

				if ((numStart != 2 && board[8 - numFinal][symFinal] == "****") && (numStart != 2 && board[8 - numFinal][symFinal] == "    ") && (symStart == symFinal-1 || symStart == symFinal-1))
				{
					cout << "Неверный ход пешкой3" << endl;
					continue;
				}
				/*else if (numStart == 2 && (symFinal != symStart || !(numFinal == 3 || numFinal == 4) && (board[8 - numFinal][symFinal] != "****" || board[8 - numFinal][symFinal] != "    ")))
				{

					cout << "Неверный ход пешкой1" << endl;
					continue;
					
				}
				else if (numStart != 2 && (symFinal == symStart && numFinal == 1+numStart) &&
					((board[8 - numFinal][symFinal] == "_пч_" || board[8 - numFinal][symFinal] == "_лч_" || board[8 - numFinal][symFinal] == "_кч_" ||
					board[8 - numFinal][symFinal] == "_сч_" || board[8 - numFinal][symFinal] =="Кч" || board[8 - numFinal][symFinal] == "Фч")))
				{
					cout << "Неверный ход пешкой!" << endl;
					continue;
				}
				else if (numStart != 2  && (symStart != symFinal) && (8-numFinal == 7-numStart) && (symStart == symFinal + 1 || symStart == symFinal - 1) && (board[8 - numFinal][symFinal] == "    " || (board[8 - numFinal][symFinal] == "****")))
				{
					cout << "Неверное взятие пешкой!" << endl;
					continue;
				}*/
			}

			else if (board[8 - numStart][symStart] == "_лб_")
			{

			}

			else if (board[8 - numStart][symStart] == "_кб_")
			{

			}

			else if (board[8 - numStart][symStart] == "_сб_")
			{

			}

			else if (board[8 - numStart][symStart] == "_ФБ_")
			{

			}

			else if (board[8 - numStart][symStart] == "_КБ_")
			{

			}
			board[8 - numFinal][symFinal] = board[8 - numStart][symStart];
			if (numStart % 2 == 0)
			{
				if ((symStart) % 2 == 0)
				{
					board[8 - numStart][symStart] = "****";
				}
				else
				{
					board[8 - numStart][symStart] = "    ";
				}
			}
			if (numStart % 2 == 1)
			{
				if ((symStart) % 2 == 1)
				{
					board[8 - numStart][symStart] = "****";
				}
				else
				{
					board[8 - numStart][symStart] = "    ";
				}
			}
			break;
		}
		
		cout << endl;
		sum++;
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

