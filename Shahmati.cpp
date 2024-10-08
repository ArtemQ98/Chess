﻿#include <iostream>
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
	{"****", "    ", "****", "    ", "****", "_лч_", "****", "    "},
	{"    ", "****", "    ", "_сч_", "    ", "****", "    ", "****"},
	{"_пб_", "_пб_", "_пб_", "_пб_", "_пб_", "_пб_", "_пб_", "_пб_"},
	{"_лб_", "_кб_", "_сб_", "_Фб_", "_Кб_", "_сб_", "_кб_", "_лб_"}
};


vector<char> numBoard = {'8', '7', '6', '5', '4', '3', '2', '1'};
vector<char> strBoard = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H'};
vector<string> eatW;
vector<string> eatB;
string stepStart, stepFinal, peshkaUpdate, drawAnswer;
int symStart, symFinal, numStart, numFinal, sum, sovp, controlStep; //controlStep для взятия на проходе у пешки
int stepCheck_B, stepCheck_W, quantityCheck_B, quantityCheck_W; //Для шах и мата
char stepBlackOrWhite;
bool okStep{ true }, check_B{ false }, check_W{ false }, draw{ false }, shortRokB{ true }, shortRokW{ true }, longRokB{ true }, longRokW{ true }, stepShortRok_W{ true }, stepShortRok_B{ true }, stepLongRok_W{ true }, stepLongRok_B{ true }, queenStep_B{ true }, queenStep_W{ true };

int main()
{
	setlocale(LC_ALL, "Ru");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	cout << "****ШАХМАТЫ****" << endl << "ВКЛЮЧИТЕ CapsLock!!!" << endl << "Для ввода хода используйте английскую раскладку" << endl << "Для изменения пешки введите фигуру так, например, ФЕРЗЬ" << endl << "Для предложения ничьи введите 'НИЧЬЯ'" << endl << endl;

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
		cout << endl <<endl << "===================================";
		cout << endl << "Совершено ходов: " << sum << endl;
		cout << "Белые съели: ";
		for (int i = 0; i < size(eatW); i++)
		{
			cout << eatW[i] << "|";
		}
		cout << endl;
		cout << "Чёрные съели: ";
		for (int i = 0; i < size(eatB); i++)
		{
			cout << eatB[i] << "|";
		}
		cout << endl;
		cout << "===================================" << endl << endl;
		
		// Ход
		while (true)
		{
			shortRokW = true;
			shortRokB = true;
			check_W = false;
			check_B = false;
			for (int i = 0; i < 8; i++)
			{
				for (int j = 0; j < 8; j++)
				{	
					if (board[i][j] == "_пб_") //Рокировка
					{
						if (i == 1 && (j-1 == 6 || j-1 == 5 || j + 1 == 6 || j + 1 == 5))
						{
							shortRokB = false;
						}
						if (i == 1 && (j == 0 || j == 1 || j == 2 || j == 3 || j == 4))
						{
							longRokB = false;
						}
					}
					if (board[i][j] == "_лб_" || board[i][j] == "_Фб_")
					{
						for (int x = 1; x <= 7 - j; x++)
						{
							if (board[i][j + x] != "    " && board[i][j + x] != "****" && board[i][j + x] != "_Кч_")
							{
								break;
							}
							if (board[i][j + x] == "_Кч_")
							{
								check_B = true;
								break;
							}
						}

						for (int x = 1; x <= 7 - (7 - j); x++)
						{
							if (board[i][j - x] != "    " && board[i][j-x] != "****" && board[i][j-x] != "_Кч_")
							{
								break;
							}
							if (board[i][j - x] == "_Кч_")
							{
								check_B = true;
								break;
							}
						}

						for (int x = 1; x <= 8 - (8 - i); x++)
						{
							if (board[i - x][j] != "    " && board[i - x][j] != "****" && board[i - x][j] != "_Кч_")
							{
								break;
							}
							if (board[i - x][j] == "_Кч_")
							{
								check_B = true;
								break;
							}
						}
						
						for (int x = 1; i < 8 - (8 - i); x++)
						{
							if (board[i + x][j] != "    " && board[i + x][j] != "****" && board[i + x][j] != "_Кч_")
							{
								break;
							}
							if (board[i + x][j] == "_Кч_")
							{	
								check_B = true;
								break;
							}
						}

						if (j == 6 || j == 5)
						{

							for (int x = 1; x < 8 - (8 - i); x++) //Рокировка
							{
								if (board[i - x][j] != "    " && board[i - x][j] != "****" && i != 0)
								{
									break;
								}
								else if (i - x == 0)
								{
									shortRokB = false;
								}
							}
						}

						if (j == 1 || j == 2 || j == 3) 
						{

							for (int x = 1; x < 8 - (8 - i); x++) //Рокировка 
							{
								if (board[i - x][j] != "    " && board[i - x][j] != "****" && i != 0) 
								{
									break;
								}
								else if (i - x == 7) 
								{
									longRokB = false; 
								}
							}
						}
					}
					if (board[i][j] == "_кб_")
					{
						if ((board[i + 2][j - 1] == "_Кч_") || (board[i + 2][j + 1] == "_Кч_") ||
							(board[i - 2][j - 1] == "_Кч_") || (board[i - 2][j + 1] == "_Кч_") ||
							(board[i + 1][j - 2] == "_Кч_") || (board[i + 1][j + 2] == "_Кч_") ||
							(board[i - 1][j - 2] == "_Кч_") || (board[i - 1][j + 2] == "_Кч_"))
						{
							check_B = true;
						}
						if ((i == 2 && j == 4) || (i == 2 && j == 5) || (i == 2 && j == 6) || (i == 2 && j == 7) || (i == 1 && j == 3) || (i == 1 && j == 7) || (i == 2 && j == 4))
						{
							shortRokB = false;
						}
						if ((i == 2 && (j == 0 || j == 1 || j == 2 || j == 3 || j == 4)) || (i == 1 && (j == 0 || j == 1 || j == 3 || j == 4 || j == 5)))
						{
							longRokB = false;
						}
					}
					if (board[i][j] == "_сб_" || board[i][j] == "_Фб_")
					{
						for (int x = 1; x <= 8 - (8 - i); x++)
						{
							if (board[i + x][j + x] != "    " && board[i + x][j + x] != "****" && board[i + x][j + x] != "_Кч_")
							{
								break;
							}
							if (board[i + x][j + x] == "_Кч_")
							{
								check_B = true;
								break;
							}
						}

						for (int x = 1; x <= 8 - (8 - i); x++)
						{
							if (board[i - x][j - x] != "    " && board[i - x][j - x] != "****" && board[i - x][j - x] != "_Кч_")
							{
								break;
							}
							if (board[i - x][j - x] == "_Кч_")
							{
								check_B = true;
								break;
							}
						}

						for (int x = 1; x <= 8 - (8 - i); x++)
						{
							if (board[i - x][j + x] != "    " && board[i - x][j + x] != "****" && board[i - x][j + x] != "_Кч_")
							{
								break;
							}
							if (board[i - x][j + x] == "_Кч_")
							{
								check_B = true;
								break;
							}
						}

						for (int x = 1; x <= 8 - (8 - i); x++)
						{
							if (board[i + x][j - x] != "    " && board[i + x][j - x] != "****" && board[i + x][j - x] != "_Кч_")
							{
								break;
							}
							if (board[i + x][j - x] == "_Кч_")
							{
								check_B = true;
								break;
							}
						}

						for (int x = 1; x <= 8 - (8 - i); x++) //Рокировка 
						{
							if (board[i - x][j - x] != "    " && board[i - x][j - x] != "****" && i != 0)
							{
								break;
							}
							if (i - x == 0 && (j - x == 6 || j - x == 5))
							{
								shortRokB = false;
							}
						}

						for (int x = 1; x <= 8 - (8 - i); x++) //Рокировка 
						{
							if (board[i - x][j + x] != "    " && board[i - x][j + x] != "****" && i != 0)
							{
								break;
							}
							if (i - x == 0 && (j + x == 6 || j + x == 5))
							{
								shortRokB = false;
							}
						}

						for (int x = 1; x <= 8 - (8 - i); x++) //Рокировка
						{
							if (board[i - x][j - x] != "    " && board[i - x][j - x] != "****" && i != 0)
							{
								break;
							}
							if (i - x == 0 && (j - x == 1 || j - x == 2 || j - x == 3))
							{
								longRokB = false;
							}
						}

						for (int x = 1; x <= 8 - (8 - i); x++) //Рокировка
						{
							if (board[i - x][j + x] != "    " && board[i - x][j + x] != "****" && i != 0)
							{
								break;
							}
							if (i - x == 0 && (j + x == 1 || j + x == 2 || j + x == 3))
							{
								longRokB = false;
							}
						}
					}
					if (board[i][j] == "_Кб_")
					{
						if (i == 1 && (j == 7 || j == 6 || j == 5 || j == 4))
						{
							shortRokB = false;
						}
						if (i == 1 && (j == 0 || j == 1 || j == 2 || j == 3 || j == 4))
						{
							longRokB = false;
						}
					}
					
					if (board[i][j] == "_пч_") //Рокировка
					{
						if (i == 6 && (j - 1 == 6 || j - 1 == 5 || j + 1 == 6 || j + 1 == 5))
						{
							shortRokW = false;
						}
						if (i == 6 && (j == 0 || j == 1 || j == 2 || j == 3 || j == 4))
						{
							longRokW = false; 
						}
					}
					if (board[i][j] == "_лч_" || board[i][j] == "_Фч_")
					{
						for (int x = 1; x <= 7 - j; x++)
						{
							if (board[i][j + x] != "    " && board[i][j + x] != "****" && board[i][j + x] != "_Кб_")
							{
								break;
							}
							if (board[i][j + x] == "_Кб_")
							{
								check_W = true;
								break;
							}
						}

						for (int x = 1; x <= 7 - (7 - j); x++)
						{
							if (board[i][j - x] != "    " && board[i][j - x] != "****" && board[i][j - x] != "_Кб_")
							{
								break;
							}
							if (board[i][j - x] == "_Кб_")
							{
								check_W = true;
								break;
							}
						}

						for (int x = 1; x <= 8 - (8 - i); x++)
						{
							if (board[i - x][j] != "    " && board[i - x][j] != "****" && board[i - x][j] != "_Кб_")
							{
								break;
							}
							if (board[i - x][j] == "_Кб_")
							{
								check_W = true;
								break;
							}
						}
						
						for (int x = 1; i < 8 - (8 - i); x++)
						{
							
							if (board[i + x][j] != "    " && board[i + x][j] != "****" && board[i + x][j] != "_Кб_")
							{
								break;
							}
							if (board[i + x][j] == "_Кб_")
							{
								check_W = true;
								break;
							}
						}

						if (j == 6 || j == 5)
						{
							
							for (int x = 1; x < 8 - (8 - i); x++) //Рокировка
							{
								if (board[i + x][j] != "    " && board[i + x][j] != "****" && i != 7)
								{
									break;
								}
								else if (i + x == 7)
								{
									shortRokW = false;
								}
							}
						}
						
						if (j == 1 || j == 2 || j == 3)
						{

							for (int x = 1; x < 8 - (8 - i); x++) //Рокировка
							{
								if (board[i + x][j] != "    " && board[i + x][j] != "****" && i != 7)
								{
									break;
								}
								else if (i + x == 7)
								{
									longRokW = false;
								}
							}
						}
					}
					if (board[i][j] == "_кч_")
					{
						if ((board[i + 2][j - 1] == "_Кб_") || (board[i + 2][j + 1] == "_Кб_") ||
							(board[i - 2][j - 1] == "_Кб_") || (board[i - 2][j + 1] == "_Кб_") ||
							(board[i + 1][j - 2] == "_Кб_") || (board[i + 1][j + 2] == "_Кб_") ||
							(board[i - 1][j - 2] == "_Кб_") || (board[i - 1][j + 2] == "_Кб_"))
						{
							check_W = true;
						}
						if ((i == 5 && j == 4) || (i == 5 && j == 5) || (i == 5 && j == 6) || (i == 5 && j == 7) || (i == 6 && j == 3) || (i == 6 && j == 7) || (i == 5 && j == 4))
						{
							shortRokW = false;
						}
						if ((i == 5 && (j == 0 || j == 1 || j == 2 || j == 3 || j == 4)) || (i == 6 && (j == 0 || j == 1 || j == 3 || j == 4 || j == 5)))
						{
							longRokW = false;
						}
					}
					if (board[i][j] == "_сч_" || board[i][j] == "_Фч_")
					{
						for (int x = 1; x <= 8 - (8 - i); x++)
						{
							if (board[i + x][j + x] != "    " && board[i + x][j + x] != "****" && board[i + x][j + x] != "_Кб_")
							{
								break;
							}
							if (board[i + x][j + x] == "_Кб_")
							{
								check_W = true;
								break;
							}
						}

						for (int x = 1; x <= 8 - (8 - i); x++)
						{
							if (board[i - x][j - x] != "    " && board[i - x][j - x] != "****" && board[i - x][j - x] != "_Кб_")
							{
								break;
							}
							if (board[i - x][j - x] == "_Кб_")
							{
								check_W = true;
								break;
							}
						}

						for (int x = 1; x <= 8 - (8 - i); x++)
						{
							if (board[i - x][j + x] != "    " && board[i - x][j + x] != "****" && board[i - x][j + x] != "_Кб_")
							{
								break;
							}
							if (board[i - x][j + x] == "_Кб_")
							{
								check_W = true;
								break;
							}
						}

						for (int x = 1; x <= 8 - (8 - i); x++)
						{
							if (board[i + x][j - x] != "    " && board[i + x][j - x] != "****" && board[i + x][j - x] != "_Кб_")
							{
								break;
							}
							if (board[i + x][j - x] == "_Кб_")
							{
								check_W = true;
								break;
							}
						}

						for (int x = 1; x < 8 - (8 - i); x++) //Рокировка 
						{
							if (board[i + x][j + x] != "    " && board[i + x][j + x] != "****" && i != 7) 
							{
								break;
							}
							if (i + x == 7 && (j + x == 6 || j + x == 5))
							{
								shortRokW = false; 
							}
						}

						for (int x = 1; x < 8 - (8 - i); x++) //Рокировка 
						{
							if (board[i + x][j - x] != "    " && board[i + x][j - x] != "****" && i != 7)
							{
								break;
							}
							if (i + x == 7 && (j - x == 6 || j - x == 5))
							{
								shortRokW = false;
							}
						}

						for (int x = 1; x < 8 - (8 - i); x++) //Рокировка 
						{
							if (board[i + x][j + x] != "    " && board[i + x][j + x] != "****" && i != 7)
							{
								break;
							}
							if (i + x == 7 && (j + x == 1 || j + x == 2 || j + x == 3))
							{
								longRokW = false;
							}
						}

						for (int x = 1; x < 8 - (8 - i); x++) //Рокировка
						{
							if (board[i + x][j - x] != "    " && board[i + x][j - x] != "****" && i != 7)
							{
								break;
							}
							if (i + x == 7 && (j - x == 1 || j - x == 2 || j - x == 3))
							{
								longRokW = false;
							}
						}
					}
				
					if (board[i][j] == "_Кч_") 
					{
						if (i == 6 && (j == 7 || j == 6 || j == 5 || j == 4))
						{
							shortRokW = false;
						}
						if (i == 6 && (j == 0 || j == 1 || j == 2 || j == 3 || j == 4))
						{
							longRokW = false;
						}
					}
				}
			}

			//Шах и мат чёрным
			if (quantityCheck_B == 0 && check_B)
			{
				stepCheck_B = sum;
			}
		
			if (check_B == true)
			{
				quantityCheck_B++;
			}
			else if (!check_B)
			{
				quantityCheck_B = 0;
			}
			if (quantityCheck_B > 0 && stepBlackOrWhite == 'B')
			{
				cout << "ШАХ И МАТ ЧЁРНЫМ!" << endl << endl << endl << endl;
				return 0;
			}
			else if (stepCheck_B + 1 == sum && quantityCheck_B > 0)
			{
				cout << "МАТ ЧЁРНЫМ!" << endl << endl << endl << endl;
				return 0;
			}
			//Шах и мат белым
			if (quantityCheck_W == 0 && check_W)
			{
				stepCheck_W = sum;
			}

			if (check_W == true)
			{
				quantityCheck_W++;
			}
			else if (!check_W)
			{
				quantityCheck_W = 0;
			}
			if (quantityCheck_W > 0 && stepBlackOrWhite == 'W')
			{
				cout << "ШАХ И МАТ БЕЛЫМ!" << endl << endl << endl << endl;
				return 0;
			}
			else if (stepCheck_B + 1 == sum && quantityCheck_B > 0)
			{
				cout << "МАТ БЕЛЫМ!" << endl << endl << endl << endl;
				return 0;
			}

			if (quantityCheck_B > 0)
			{
				cout << "Шах чёрным!" << endl;
				
			}
			else if(quantityCheck_W > 0)
			{
				cout << "Шах белым!" << endl;

			}

			
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
			//Ничья
			if (stepStart == "НИЧЬЯ")
			{
				draw = true;
			}
			if (draw)
			{
				cout << "Вы согласны на ничью?" << endl;
				cin >> drawAnswer;
				if (drawAnswer == "ДА")
				{
					cout << "НИЧЬЯ!" << endl;
					return 0;
				}
				else if (drawAnswer == "НЕТ")
				{
					cout << "Отказ!" << endl;
					draw = false;
					continue;
				}
			}
			if (stepStart.length() != 2)
			{
				cout << "Неверное значение, введите координату 2 символами, например, A3, но не A2 A3" << endl;
				continue;
			}
				while (true)
				{
					okStep = true;
					
					for (int i = 0; i < size(numBoard); i++)
					{
						if (stepStart[1] == numBoard[i])
						{
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
						okStep = false;
						break;
					}
				}
				if (!okStep)
				{
					okStep = true;
					continue;
				}
				//Ход откуда
				while (true)
				{
					okStep = true;
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
						okStep = false;
						break;
					}
				}

				if (!okStep)
				{
					okStep = true;
					continue;
				}

				stepStart = stepStart[1];
				numStart = stoi(stepStart);
				if (board[8 - numStart][symStart] == "    " || board[8 - numStart][symStart] == "****")
				{
					cout << "Вы выбрали пустое поле!" << endl;
					continue;
				}
				else if (stepBlackOrWhite == 'W' && (board[8 - numStart][symStart][2] == 'ч'))
				{
					cout << "Вы взяли не свою фигуру" << endl;
					numStart = 0;
					symStart = 0;
					continue;
				}
				else if (stepBlackOrWhite == 'B' && (board[8 - numStart][symStart][2] == 'б'))
				{
					cout << "Вы взяли не свою фигуру" << endl;
					numStart = 0;
					symStart = 0;
					continue;
				}
				else
				{
					break;
				}
	
				
			}
			//Ход куда
			while (true)
			{
				okStep = true;
				if (stepBlackOrWhite == 'W')
				{
					cout << "Ход белых в: ";
				}
				else
				{
					cout << "Ход чёрных в: ";
				}
				if (true)
				{
					getline(cin, stepFinal);
				}
				
				if (stepFinal.length() != 2)
				{
					cout << "Неверное значение, введите координату 2 символами, например, A3, но не A2 A3" << endl;
					continue;
				}
				while (true)
				{
					
					for (int i = 0; i < size(numBoard); i++)
					{
						if (stepFinal[1] == numBoard[i])
						{
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
						okStep = false;
						break;
					}
				}
				if (!okStep)
				{
					okStep = true;
					continue;
				}
				while (true)
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
						okStep = false;
						break;
					}
				}
				if (!okStep)
				{
					okStep = true;
					continue;
				}

				stepFinal = stepFinal[1];
				numFinal = stoi(stepFinal);
				okStep = true;

				if (numStart == numFinal && symStart == symFinal)
				{
					cout << "Нельзя ходить в первоначальную клетку!" << endl;
					continue;
				}

				
				/////// Ход белых
				else if (stepBlackOrWhite == 'W') 
				{
					if (board[8 - numFinal][symFinal][2] == 'б')
					{
						cout << "Вы не можете есть свои фигуры" << endl;
						continue;
					}
					/////Пешка
					else if (board[8 - numStart][symStart] == "_пб_")
					{
						

						if (numFinal == 6 && board[3][symFinal] == "_пч_" && controlStep == symFinal && numStart == numFinal - 1)
						{
							eatW.push_back(board[3][symFinal]);
							if (numStart % 2 == 0)
							{
								if ((symFinal) % 2 == 0)
								{
									board[3][symFinal] = "****";
								}
								else
								{
									board[3][symFinal] = "    ";
								}
							}
							if (numStart % 2 == 1)
							{
								if ((symFinal) % 2 == 1)
								{
									board[3][symFinal] = "****";
								}
								else
								{
									board[3][symFinal] = "    ";
								}
							}
							
						}

						else if (numStart == 2)
						{
							if (symStart != symFinal || !((numStart == numFinal - 1 || numStart == numFinal - 2)))
							{
								cout << "Неверный ход пешкой" << endl;
								okStep = false;
							}
							else if (!(board[8-numFinal][symFinal] == "    " || board[8 - numFinal][symFinal] == "****"))
							{
								cout << "Неверный ход пешкой" << endl;
								okStep = false;
							}
							else if (!(board[5][symFinal] == "    " || board[5][symFinal] == "****"))
							{
								cout << "Неверный ход пешкой" << endl;
								okStep = false;
							}
						}
						else if (numStart != 2 && (board[8 - numFinal][symFinal] == "    " || board[8 - numFinal][symFinal] == "****"))
						{
							if (symStart != symFinal || !(numStart == numFinal - 1))
							{
								cout << "Неверный ход пешкой" << endl;
								okStep = false;
							}
						}

						else if ((numStart != 2 && board[8 - numFinal][symFinal] != "****") && (numStart != 2 && board[8 - numFinal][symFinal] != "    "))
						{
							if ((board[8 - numFinal][symFinal] == "_Кч_"))
							{
								cout << "Вы не можете съесть Короля пешкой" << endl;
								numFinal = 0;
								symFinal = 0;
								continue;
							}
							else if ((symStart != symFinal - 1 && numStart != numFinal - 1) || (symStart != symFinal + 1 && numStart != numFinal - 1) || (symStart == symFinal) || (numStart != numFinal-1))
							{
								cout << "Неверный ход пешкой" << endl;
								numFinal = 0;
								symFinal = 0;
								continue;
							}
							else
							{
								eatW.push_back(board[8 - numFinal][symFinal]);
							}
						}
						if (!okStep)
						{
							numFinal = 0;
							symFinal = 0;
							continue;
						}
						if (numFinal == 8)
						{
							if (board[0][symFinal][2] == 'б' && board[1][symFinal] != "_Кб_")
							{
								eatW.push_back(board[8 - numFinal][symFinal]);
							}
							while (true)
							{
								cout << "Какой фигурой вы хотите стать?";
								getline(cin, peshkaUpdate);
								if (peshkaUpdate == "КОРОЛЬ")
								{
									cout << "Вы не можете стать королём";
									continue;
								}

								else if (peshkaUpdate == "ЛАДЬЯ")
								{
									board[8 - numStart][symStart] = "_лб_";
									break;
								}
								else if (peshkaUpdate == "ФЕРЗЬ")
								{
									board[8 - numStart][symStart] = "_Фб_";
									break;
								}
								else if (peshkaUpdate == "СЛОН")
								{
									board[8 - numStart][symStart] = "_сб_";
									break;
								}
								else if (peshkaUpdate == "КОНЬ")
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

					}

					/////Ладья
					else if (board[8 - numStart][symStart] == "_лб_")
					{
						//Ход по горизонтали
						if (numStart == numFinal && symStart != symFinal) 
						{
							if (symFinal > symStart)
							{
								for (int i = 1; i <= symFinal - symStart; i++)
								{
									if (board[8-numStart][symStart+i][2] == 'б')
									{
										cout << "Вы не можете перейти через свою фигуру" << endl;	
										okStep = false;
									}
									else if (board[8 - numStart][symStart + i][2] == 'ч' && i != symFinal-symStart)
									{
										cout << "Вы должны съесть вражескую фигуру, чтобы пройти дальше" << endl;
										okStep = false;
									}
								}
								if (okStep && board[8 - numFinal][symFinal][2] == 'ч')
								{
									eatW.push_back(board[8 - numFinal][symFinal]);
								}
								
							}
							else
							{
								for (int i = 1; i <= symStart - symFinal; i++)
								{
									if (board[8 - numStart][symStart - i][2] == 'б')
									{
										cout << "Вы не можете перейти через свою фигуру" << endl;
										okStep = false;
									}
									else if (board[8 - numStart][symStart - i][2] == 'ч' && i != symStart - symFinal)
									{
										cout << "Вы должны съесть вражескую фигуру, чтобы пройти дальше" << endl;
										okStep = false;
									}
								}
								if (okStep && board[8 - numFinal][symFinal][2] == 'ч')
								{
									eatW.push_back(board[8 - numFinal][symFinal]);
								}
								
							}
							
						}
						//Ход по вертикали
						else if (numStart != numFinal && symStart == symFinal) 
						{
							if (numFinal > numStart)
							{
								for (int i = 1; i <= numFinal - numStart; i++)
								{
									if (board[8 - numStart - i][symStart][2] == 'б')
									{
										cout << "Вы не можете перейти через свою фигуру" << endl;
										okStep = false;
									}
									else if (board[8 - numStart - i][symStart][2] == 'ч' && i != numFinal - numStart)
									{
										cout << "Вы должны съесть вражескую фигуру, чтобы пройти дальше" << endl;
										okStep = false;
									}
								}
								if (okStep && board[8 - numFinal][symFinal][2] == 'ч')
								{
									eatW.push_back(board[8 - numFinal][symFinal]);
								}
								
							}
							else
							{
								for (int i = 1; i <= numStart-numFinal; i++)
								{
									if (board[8 - numStart + i][symStart][2] == 'б')
									{
										cout << "Вы не можете перейти через свою фигуру" << endl;
										okStep = false;
									}
									else if (board[8 - numStart + i][symStart][2] == 'ч' && i != numStart - numFinal)
									{
										cout << "Вы должны съесть вражескую фигуру, чтобы пройти дальше" << endl;
										okStep = false;
									}
								}
								if (okStep && board[8 - numFinal][symFinal][2] == 'ч')
								{
									eatW.push_back(board[8 - numFinal][symFinal]);
								}
								
							}
						}
						//Неверный ход
						else
						{
							if (board[8 - numStart][symStart] == "_лб_")
							{
								cout << "Неверный ход ладьёй" << endl;
							}
							else
							{
								cout << "Неверный ход Ферзём" << endl;
							}
							numFinal = 0;
							symFinal = 0;
							continue;
						}
						if (!okStep)
						{
							numFinal = 0;
							symFinal = 0;
							continue;
						}
						


					}
					/////Конь
					else if (board[8 - numStart][symStart] == "_кб_") 
					{
						if ((numFinal == numStart + 2 && symFinal == symStart - 1) || (numFinal == numStart + 2 && symFinal == symStart + 1) ||
							(numFinal == numStart - 2 && symFinal == symStart - 1) || (numFinal == numStart - 2 && symFinal == symStart + 1) ||
							(numFinal == numStart + 1 && symFinal == symStart - 2) || (numFinal == numStart + 1 && symFinal == symStart + 2) ||
							(numFinal == numStart - 1 && symFinal == symStart - 2) || (numFinal == numStart - 1 && symFinal == symStart + 2))
						{
							if (board[8 - numFinal][symFinal][2] == 'ч')
							{
								eatW.push_back(board[8 - numFinal][symFinal]);
							}
						}
						
						
						else
						{
							cout << "Неверный ход конём" << endl;
							numFinal = 0;
							symFinal = 0;
							continue;
						}
					}

					/////Слон
					else if (board[8 - numStart][symStart] == "_сб_")
					{
						// R1
						if (numStart < numFinal && symStart < symFinal && symFinal - symStart == numFinal - numStart)
						{
							for (int i = 1; i <= symFinal - symStart; i++)
							{
								if (board[8 - numStart - i][symStart+i][2] == 'б')
								{
									cout << "Вы не можете перейти через свою фигуру" << endl;
									okStep = false;
								}
								else if (board[8 - numStart - i][symStart+i][2] == 'ч' && i != numFinal - numStart)
								{
									cout << "Вы должны съесть вражескую фигуру, чтобы пройти дальше" << endl;
									okStep = false;
								}
								
							}
						}
						// R2
						else if (numStart < numFinal && symStart > symFinal && symStart - symFinal == numFinal - numStart)
						{
							for (int i = 1; i <= symStart-symFinal; i++)
							{
								if (board[8 - numStart - i][symStart - i][2] == 'б')
								{
									cout << "Вы не можете перейти через свою фигуру" << endl;
									okStep = false;
								}
								else if (board[8 - numStart - i][symStart - i][2] == 'ч' && i != numFinal - numStart)
								{
									cout << "Вы должны съесть вражескую фигуру, чтобы пройти дальше" << endl;
									okStep = false;
								}
								
							}
						}
						// R3
						else if (numStart > numFinal && symStart > symFinal && symStart - symFinal ==  numStart - numFinal)
						{
							for (int i = 1; i <= symStart - symFinal; i++)
							{
								if (board[8 - numStart + i][symStart - i][2] == 'б')
								{
									cout << "Вы не можете перейти через свою фигуру" << endl;
									okStep = false;
								}
								else if (board[8 - numStart + i][symStart - i][2] == 'ч' && i != numStart - numFinal)
								{
									cout << "Вы должны съесть вражескую фигуру, чтобы пройти дальше" << endl;
									okStep = false;
								}
								
							}
						}
						// R4
						else if (numStart > numFinal && symStart < symFinal && symFinal - symStart == numStart - numFinal)
						{
							for (int i = 1; i <= symFinal - symStart; i++)
							{
								if (board[8 - numStart + i][symStart + i][2] == 'б')
								{
									cout << "Вы не можете перейти через свою фигуру" << endl;
									okStep = false;
								}
								else if (board[8 - numStart + i][symStart + i][2] == 'ч' && i != numStart - numFinal)
								{
									cout << "Вы должны съесть вражескую фигуру, чтобы пройти дальше" << endl;
									okStep = false;
								}
								
							}
						}
						//Неверный ход
						else
						{
							if (board[8 - numStart][symStart] == "_сб_")
							{
								cout << "Неверный ход слоном" << endl;
							}
							else
							{
								cout << "Неверный ход Ферзём" << endl;
							}
							numFinal = 0;
							symFinal = 0;
							continue;
						}
						if (!okStep)
						{
							numFinal = 0;
							symFinal = 0;
							continue;
						}
						else if (board[8 - numFinal][symFinal][2] == 'ч')
						{
							eatW.push_back(board[8 - numFinal][symFinal]);
						}
					}
					
					/////Ферзь
					else if (board[8 - numStart][symStart] == "_Фб_")
					{
						//Ход по горизонтали
						if (numStart == numFinal && symStart != symFinal)
						{
							if (symFinal > symStart)
							{
								for (int i = 1; i <= symFinal - symStart; i++)
								{
									if (board[8 - numStart][symStart + i][2] == 'б')
									{
										cout << "Вы не можете перейти через свою фигуру" << endl;
										okStep = false;
									}
									else if (board[8 - numStart][symStart + i][2] == 'ч' && i != symFinal - symStart)
									{
										cout << "Вы должны съесть вражескую фигуру, чтобы пройти дальше" << endl;
										okStep = false;
									}
								}
								
							}
							else
							{
								for (int i = 1; i <= symStart - symFinal; i++)
								{
									if (board[8 - numStart][symStart - i][2] == 'б')
									{
										cout << "Вы не можете перейти через свою фигуру" << endl;
										okStep = false;
									}
									else if (board[8 - numStart][symStart - i][2] == 'ч' && i != symStart - symFinal)
									{
										cout << "Вы должны съесть вражескую фигуру, чтобы пройти дальше" << endl;
										okStep = false;
									}

								}
								
							}
						}
						//Ход по вертикали
						else if (numStart != numFinal && symStart == symFinal)
						{
							if (numFinal > numStart)
							{
								for (int i = 1; i <= numFinal - numStart; i++)
								{
									if (board[8 - numStart - i][symStart][2] == 'б')
									{
										cout << "Вы не можете перейти через свою фигуру" << endl;
										okStep = false;
									}
									else if (board[8 - numStart - i][symStart][2] == 'ч' && i != numFinal - numStart)
									{
										cout << "Вы должны съесть вражескую фигуру, чтобы пройти дальше" << endl;
										okStep = false;
									}
								}
								
							}
							else
							{
								for (int i = 1; i <= numStart - numFinal; i++)
								{
									if (board[8 - numStart + i][symStart][2] == 'б')
									{
										cout << "Вы не можете перейти через свою фигуру" << endl;
										okStep = false;
									}
									else if (board[8 - numStart + i][symStart][2] == 'ч' && i != numStart - numFinal)
									{
										cout << "Вы должны съесть вражескую фигуру, чтобы пройти дальше" << endl;
										okStep = false;
									}
								}
								
							}
						}
						
						// R1
						if (numStart < numFinal && symStart < symFinal && symFinal - symStart == numFinal - numStart)
						{
							for (int i = 1; i <= symFinal - symStart; i++)
							{
								if (board[8 - numStart - i][symStart + i][2] == 'б')
								{
									cout << "Вы не можете перейти через свою фигуру" << endl;
									okStep = false;
								}
								else if (board[8 - numStart - i][symStart + i][2] == 'ч' && i != numFinal - numStart)
								{
									cout << "Вы должны съесть вражескую фигуру, чтобы пройти дальше" << endl;
									okStep = false;
								}

							}
						}
						// R2
						else if (numStart < numFinal && symStart > symFinal && symStart - symFinal == numFinal - numStart)
						{
							for (int i = 1; i <= symStart - symFinal; i++)
							{
								if (board[8 - numStart - i][symStart - i][2] == 'б')
								{
									cout << "Вы не можете перейти через свою фигуру" << endl;
									okStep = false;
								}
								else if (board[8 - numStart - i][symStart - i][2] == 'ч' && i != numFinal - numStart)
								{
									cout << "Вы должны съесть вражескую фигуру, чтобы пройти дальше" << endl;
									okStep = false;
								}

							}
						}
						// R3
						else if (numStart > numFinal && symStart > symFinal && symStart - symFinal == numStart - numFinal)
						{
							for (int i = 1; i <= symStart - symFinal; i++)
							{
								if (board[8 - numStart + i][symStart - i][2] == 'б')
								{
									cout << "Вы не можете перейти через свою фигуру" << endl;
									okStep = false;
								}
								else if (board[8 - numStart + i][symStart - i][2] == 'ч' && i != numStart - numFinal)
								{
									cout << "Вы должны съесть вражескую фигуру, чтобы пройти дальше" << endl;
									okStep = false;
								}

							}
						}
						// R4
						else if (numStart > numFinal && symStart < symFinal && symFinal - symStart == numStart - numFinal)
						{
							for (int i = 1; i <= symFinal - symStart; i++)
							{
								if (board[8 - numStart + i][symStart + i][2] == 'б')
								{
									cout << "Вы не можете перейти через свою фигуру" << endl;
									okStep = false;
								}
								else if (board[8 - numStart + i][symStart + i][2] == 'ч' && i != numStart - numFinal)
								{
									cout << "Вы должны съесть вражескую фигуру, чтобы пройти дальше" << endl;
									okStep = false;
								}

							}
						}
						//Неверный ход
						else
						{
							cout << "Неверный ход Ферзём" << endl;
							numFinal = 0;
							symFinal = 0;
							continue;
						}
						if (!okStep)
						{
							numFinal = 0;
							symFinal = 0;
							continue;
						}
						else if (board[8 - numFinal][symFinal][2] == 'ч')
						{
							eatW.push_back(board[8 - numFinal][symFinal]);
						}
					}
					/////Король
					else if (board[8 - numStart][symStart] == "_Кб_") 
					{
						if (numFinal == 1 && (symFinal == 6 || symFinal == 2))
						{
							if (!queenStep_W)
							{
								cout << "Рокировка невозможна" << endl;
								okStep = false;
							}
							for (int i = 0; i < 2; i++) 
							{
								
								if (symFinal == 6) 
								{
									if (!shortRokW || !stepShortRok_W)
									{
										cout << "Рокировка невозможна" << endl;
										okStep = false;
										break;
									}
									else if (!(board[7][6 - i] == "    " || board[7][6 - i] == "****")) 
									{
										cout << "Рокировка невозможна" << endl;
										okStep = false;
										break;
									}
								}
								else if (symFinal == 2)
								{
									if (!longRokW || !stepLongRok_W)
									{
										cout << "Рокировка невозможна" << endl; 
										okStep = false; 
										break;
									}
									if (!(board[7][2 + i] == "    " || board[7][2 + i] == "****")) 
									{
										cout << "Рокировка невозможна" << endl; 
										okStep = false; 
										break;
									}
								}
							}
							if (!okStep) 
							{
								numFinal = 0; 
								symFinal = 0; 
								continue; 
							}
							else if (okStep) 
							{
								if (symFinal == 6)
								{
									board[7][5] = "_лб_";
									board[7][7] = "****";
								}
								if (symFinal == 2)
								{
									board[7][3] = "_лб_";
									board[7][0] = "    ";
								}
							}
							
						}
						else if ((numFinal - 1 == numStart || numFinal + 1 == numStart) && symFinal == symStart)
						{
							if (board[8 - numFinal][symFinal] == "_Фч_" || board[8 - numFinal][symFinal] == "_Кч_")
							{
								cout << "Вы не можете съесть эту фигуру" << endl;
								numFinal = 0;
								symFinal = 0;
								continue;
							}
							if (board[8 - numFinal][symFinal][2] == 'б')
							{
								eatW.push_back(board[8 - numFinal][symFinal]);
							}
						}
						else if ((numFinal - 1 == numStart || numFinal + 1 == numStart) && (symFinal - 1 == symStart || symFinal + 1 == symStart))
						{
							if (board[8 - numFinal][symFinal] == "_Фч_" || board[8 - numFinal][symFinal] == "_Кч_")
							{
								cout << "Вы не можете съесть эту фигуру" << endl;
								numFinal = 0;
								symFinal = 0;
								continue;
							}
							if (board[8 - numFinal][symFinal][2] == 'ч')
							{
								eatW.push_back(board[8 - numFinal][symFinal]);
							}
						}
						else if ((symFinal - 1 == symStart || symFinal + 1 == symStart) && numFinal == numStart)
						{
							if (board[8 - numFinal][symFinal] == "_Фч_" || board[8 - numFinal][symFinal] == "_Кч_")
							{
								cout << "Вы не можете съесть эту фигуру" << endl;
								numFinal = 0;
								symFinal = 0;
								continue;
							}
							if (board[8 - numFinal][symFinal][2] == 'ч')
							{
								eatW.push_back(board[8 - numFinal][symFinal]);
							}

						}
						else
						{
							cout << "Неверный ход Королём" << endl;
							numFinal = 0;
							symFinal = 0;
							continue;
						}
					}
				}
				/////// Ход чёрных
				else if (stepBlackOrWhite == 'B')
				{
					if (board[8 - numFinal][symFinal][2] == 'ч')
					{
						cout << "Вы не можете есть свои фигуры" << endl;
						continue;
					}
					/////Пешка
					if (board[8 - numStart][symStart] == "_пч_")
					{
						if (numStart == numFinal && symStart == symFinal)
						{
							cout << "Нельзя ходить в первоначальную клетку!" << endl;
							continue;
						}

						if (numFinal == 3 && board[4][symFinal] == "_пб_" && controlStep == symFinal && numStart == numFinal + 1) // Взятие на проходе
						{
							eatB.push_back(board[4][symFinal]);
							if (numStart % 2 == 0)
							{
								if ((symFinal) % 2 == 0)
								{
									board[4][symFinal] = "****";
								}
								else
								{
									board[4][symFinal] = "    ";
								}
							}
							if (numStart % 2 == 1)
							{
								if ((symFinal) % 2 == 1)
								{
									board[4][symFinal] = "****";
								}
								else
								{
									board[4][symFinal] = "    ";
								}
							}
						}

						else if (numStart == 7)
						{
							if (symStart != symFinal || !((numStart == numFinal + 1 || numStart == numFinal + 2)))
							{
								cout << "Неверный ход пешкой" << endl;
								okStep = false;
							}
							else if (!(board[8 - numFinal][symFinal] == "    " || board[8 - numFinal][symFinal] == "****"))
							{
								cout << "Неверный ход пешкой" << endl;
								okStep = false;
							}
							else if (!(board[2][symFinal] == "    " || board[2][symFinal] == "****"))
							{
								cout << "Неверный ход пешкой" << endl;
								okStep = false;
							}
						}
						else if (numStart != 7 && (board[8 - numFinal][symFinal] == "    " || board[8 - numFinal][symFinal] == "****"))
						{
							if (symStart != symFinal || !(numStart == numFinal + 1))
							{
								cout << "Неверный ход пешкой" << endl;
								okStep = false;
							}
						}

						else if ((numStart != 7 && board[8 - numFinal][symFinal] != "****") && (numStart != 2 && board[8 - numFinal][symFinal] != "    "))
						{
							if ((board[8 - numFinal][symFinal] == "_Кб_"))
							{
								cout << "Вы не можете съесть Короля пешкой" << endl;
								numFinal = 0;
								symFinal = 0;
								continue;
							}
							else if ((symStart != symFinal - 1 && numStart != numFinal + 1) || (symStart != symFinal + 1 && numStart != numFinal + 1) || (symStart == symFinal))
							{
								cout << "Неверный ход пешкой" << endl;
								numFinal = 0;
								symFinal = 0;
								continue;
							}
							else
							{
								eatB.push_back(board[8 - numFinal][symFinal]);
							}
						}

						if (!okStep)
						{
							numFinal = 0;
							symFinal = 0;
							continue;
						}

						else if (numFinal == 1)
						{
							if (board[7][symFinal][2] == 'б' && board[1][symFinal] != "_Кб_")
							{
								eatB.push_back(board[8 - numFinal][symFinal]);
							}
							while (true)
							{
								
								cout << "Какой фигурой вы хотите стать?";
								getline(cin, peshkaUpdate);
								if (peshkaUpdate == "КОРОЛЬ")
								{
									cout << "Вы не можете стать Королём";
									continue;
								}

								else if (peshkaUpdate == "ЛАДЬЯ")
								{
									board[8 - numStart][symStart] = "_лч_";
									break;
								}
								else if (peshkaUpdate == "ФЕРЗЬ")
								{
									board[8 - numStart][symStart] = "_Фч_";
									break;
								}
								else if (peshkaUpdate == "СЛОН")
								{
									board[8 - numStart][symStart] = "_сч_";
									break;
								}
								else if (peshkaUpdate == "КОНЬ")
								{
									board[8 - numStart][symStart] = "_кч_";
									break;
								}
								else
								{
									cout << "Я не знаю такой фигуры" << endl;
									continue;
								}
							}
						}
						
					}
					/////Ладья
					else if (board[8 - numStart][symStart] == "_лч_")
					{
						//Ход по горизонтали
						if (numStart == numFinal && symStart != symFinal)
						{
							if (symFinal > symStart)
							{
								for (int i = 1; i <= symFinal - symStart; i++)
								{
									if (board[8 - numStart][symStart + i][2] == 'ч')
									{
										cout << "Вы не можете перейти через свою фигуру" << endl;
										okStep = false;
									}
									else if (board[8 - numStart][symStart + i][2] == 'б' && i != symFinal - symStart)
									{
										cout << "Вы должны съесть вражескую фигуру, чтобы пройти дальше" << endl;
										okStep = false;
									}
								}
								
							}
							else
							{
								for (int i = 1; i <= symStart - symFinal; i++)
								{
									if (board[8 - numStart][symStart - i][2] == 'ч')
									{
										cout << "Вы не можете перейти через свою фигуру" << endl;
										okStep = false;
									}
									else if (board[8 - numStart][symStart - i][2] == 'б' && i != symStart - symFinal)
									{
										cout << "Вы должны съесть вражескую фигуру, чтобы пройти дальше" << endl;
										okStep = false;
									}
									
								}
								
							}
						}
						//Ход по вертикали
						else if (numStart != numFinal && symStart == symFinal)
						{
							if (numFinal > numStart)
							{
								for (int i = 1; i <= numFinal - numStart; i++)
								{
									if (board[8 - numStart - i][symStart][2] == 'ч')
									{
										cout << "Вы не можете перейти через свою фигуру" << endl;
										okStep = false;
									}
									else if (board[8 - numStart - i][symStart][2] == 'б' && i != numFinal - numStart)
									{
										cout << "Вы должны съесть вражескую фигуру, чтобы пройти дальше" << endl;
										okStep = false;
									}
								}
								
							}
							else
							{
								for (int i = 1; i <= numStart - numFinal; i++)
								{
									if (board[8 - numStart + i][symStart][2] == 'ч')
									{
										cout << "Вы не можете перейти через свою фигуру" << endl;
										okStep = false;
									}
									else if (board[8 - numStart + i][symStart][2] == 'б' && i != numStart - numFinal)
									{
										cout << "Вы должны съесть вражескую фигуру, чтобы пройти дальше" << endl;
										okStep = false;
									}
								}
								
							}
						}
						//Неверный ход
						else
						{
							cout << "Неверный ход ладьёй" << endl;
							numFinal = 0;
							symFinal = 0;
							continue;
						}
						if (!okStep)
						{
							numFinal = 0;
							symFinal = 0;
							continue;
						}
						else if (board[8 - numFinal][symFinal][2] == 'б')
						{
							eatB.push_back(board[8 - numFinal][symFinal]);
						}
						
					}
					/////Конь
					else if (board[8 - numStart][symStart] == "_кч_")
					{
						if ((numFinal == numStart + 2 && symFinal == symStart - 1) || (numFinal == numStart + 2 && symFinal == symStart + 1) ||
							(numFinal == numStart - 2 && symFinal == symStart - 1) || (numFinal == numStart - 2 && symFinal == symStart + 1) ||
							(numFinal == numStart + 1 && symFinal == symStart - 2) || (numFinal == numStart + 1 && symFinal == symStart + 2) ||
							(numFinal == numStart - 1 && symFinal == symStart - 2) || (numFinal == numStart + 1 && symFinal == symStart + 2))
						{
							if (board[8 - numFinal][symFinal][2] == 'б')
							{
								eatB.push_back(board[8 - numFinal][symFinal]);
							}	
						}
						else
						{
							cout << "Неверный ход конём" << endl;
							numFinal = 0;
							symFinal = 0;
							continue;
						}
					}
					/////Слон
					else if (board[8 - numStart][symStart] == "_сч_")
					{
						// R1
						if (numStart < numFinal && symStart < symFinal && symFinal - symStart == numFinal - numStart)
						{
							for (int i = 1; i <= symFinal - symStart; i++)
							{
								if (board[8 - numStart - i][symStart + i][2] == 'ч')
								{
									cout << "Вы не можете перейти через свою фигуру" << endl;
									okStep = false;
								}
								else if (board[8 - numStart - i][symStart + i][2] == 'б' && i != numFinal - numStart)
								{
									cout << "Вы должны съесть вражескую фигуру, чтобы пройти дальше" << endl;
									okStep = false;
								}
								
							}
						}
						// R2
						else if (numStart < numFinal && symStart > symFinal && symStart - symFinal == numFinal - numStart)
						{
							for (int i = 1; i <= symStart - symFinal; i++)
							{
								if (board[8 - numStart - i][symStart - i][2] == 'ч')
								{
									cout << "Вы не можете перейти через свою фигуру" << endl;
									okStep = false;
								}
								else if (board[8 - numStart - i][symStart - i][2] == 'б' && i != numFinal - numStart)
								{
									cout << "Вы должны съесть вражескую фигуру, чтобы пройти дальше" << endl;
									okStep = false;
								}
								
							}
						}
						// R3
						else if (numStart > numFinal && symStart > symFinal && symStart - symFinal == numStart - numFinal)
						{
							for (int i = 1; i <= symStart - symFinal; i++)
							{
								if (board[8 - numStart + i][symStart - i][2] == 'ч')
								{
									cout << "Вы не можете перейти через свою фигуру" << endl;
									okStep = false;
								}
								else if (board[8 - numStart + i][symStart - i][2] == 'б' && i != numStart - numFinal)
								{
									cout << "Вы должны съесть вражескую фигуру, чтобы пройти дальше 3" << endl;
									okStep = false;
								}
								
							}
						}
						// R4
						else if (numStart > numFinal && symStart < symFinal && symFinal - symStart == numStart - numFinal)
						{
							for (int i = 1; i <= symFinal - symStart; i++)
							{
								if (board[8 - numStart + i][symStart + i][2] == 'ч')
								{
									cout << "Вы не можете перейти через свою фигуру" << endl;
									okStep = false;
								}
								else if (board[8 - numStart + i][symStart + i][2] == 'б' && i != numStart - numFinal)
								{
									cout << "Вы должны съесть вражескую фигуру, чтобы пройти дальше" << endl;
									okStep = false;
								}
							}

							
						}
						//Неверный ход
						else
						{
							cout << "Неверный ход слоном" << endl;
							numFinal = 0;
							symFinal = 0;
							continue;
						}
						if (!okStep)
						{
							numFinal = 0;
							symFinal = 0;
							continue;
						}
						else if (board[8 - numFinal][symFinal][2] == 'б')
						{
							eatB.push_back(board[8 - numFinal][symFinal]);
						}
					}
					/////Ферзь
					else if (board[8 - numStart][symStart] == "_Фч_")
					{
						//Ход по горизонтали
						if (numStart == numFinal && symStart != symFinal)
						{
							if (symFinal > symStart)
							{
								for (int i = 1; i <= symFinal - symStart; i++)
								{
									if (board[8 - numStart][symStart + i][2] == 'ч')
									{
										cout << "Вы не можете перейти через свою фигуру" << endl;
										okStep = false;
									}
									else if (board[8 - numStart][symStart + i][2] == 'б' && i != symFinal - symStart)
									{
										cout << "Вы должны съесть вражескую фигуру, чтобы пройти дальше" << endl;
										okStep = false;
									}
								}

							}
							else
							{
								for (int i = 1; i <= symStart - symFinal; i++)
								{
									if (board[8 - numStart][symStart - i][2] == 'ч')
									{
										cout << "Вы не можете перейти через свою фигуру" << endl;
										okStep = false;
									}
									else if (board[8 - numStart][symStart - i][2] == 'б' && i != symStart - symFinal)
									{
										cout << "Вы должны съесть вражескую фигуру, чтобы пройти дальше" << endl;
										okStep = false;
									}

								}

							}
						}
						//Ход по вертикали
						else if (numStart != numFinal && symStart == symFinal)
						{
							if (numFinal > numStart)
							{
								for (int i = 1; i <= numFinal - numStart; i++)
								{
									if (board[8 - numStart - i][symStart][2] == 'ч')
									{
										cout << "Вы не можете перейти через свою фигуру" << endl;
										okStep = false;
									}
									else if (board[8 - numStart - i][symStart][2] == 'б' && i != numFinal - numStart)
									{
										cout << "Вы должны съесть вражескую фигуру, чтобы пройти дальше" << endl;
										okStep = false;
									}
								}

							}
							else
							{
								for (int i = 1; i <= numStart - numFinal; i++)
								{
									if (board[8 - numStart + i][symStart][2] == 'ч')
									{
										cout << "Вы не можете перейти через свою фигуру" << endl;
										okStep = false;
									}
									else if (board[8 - numStart + i][symStart][2] == 'б' && i != numStart - numFinal)
									{
										cout << "Вы должны съесть вражескую фигуру, чтобы пройти дальше" << endl;
										okStep = false;
									}
								}

							}
						}
						// R1
						else if (numStart < numFinal && symStart < symFinal && symFinal - symStart == numFinal - numStart)
						{
							for (int i = 1; i <= symFinal - symStart; i++)
							{
								if (board[8 - numStart - i][symStart + i][2] == 'ч')
								{
									cout << "Вы не можете перейти через свою фигуру" << endl;
									okStep = false;
								}
								else if (board[8 - numStart - i][symStart + i][2] == 'б' && i != numFinal - numStart)
								{
									cout << "Вы должны съесть вражескую фигуру, чтобы пройти дальше" << endl;
									okStep = false;
								}

							}
						}
						// R2
						else if (numStart < numFinal && symStart > symFinal && symStart - symFinal == numFinal - numStart)
						{
							for (int i = 1; i <= symStart - symFinal; i++)
							{
								if (board[8 - numStart - i][symStart - i][2] == 'ч')
								{
									cout << "Вы не можете перейти через свою фигуру" << endl;
									okStep = false;
								}
								else if (board[8 - numStart - i][symStart - i][2] == 'б' && i != numFinal - numStart)
								{
									cout << "Вы должны съесть вражескую фигуру, чтобы пройти дальше" << endl;
									okStep = false;
								}

							}
						}
						// R3
						else if (numStart > numFinal && symStart > symFinal && symStart - symFinal == numStart - numFinal)
						{
							for (int i = 1; i <= symStart - symFinal; i++)
							{
								if (board[8 - numStart + i][symStart - i][2] == 'ч')
								{
									cout << "Вы не можете перейти через свою фигуру" << endl;
									okStep = false;
								}
								else if (board[8 - numStart + i][symStart - i][2] == 'б' && i != numStart - numFinal)
								{
									cout << "Вы должны съесть вражескую фигуру, чтобы пройти дальше 3" << endl;
									okStep = false;
								}

							}
						}
						// R4
						else if (numStart > numFinal && symStart < symFinal && symFinal - symStart == numStart - numFinal)
						{
							for (int i = 1; i <= symFinal - symStart; i++)
							{
								if (board[8 - numStart + i][symStart + i][2] == 'ч')
								{
									cout << "Вы не можете перейти через свою фигуру" << endl;
									okStep = false;
								}
								else if (board[8 - numStart + i][symStart + i][2] == 'б' && i != numStart - numFinal)
								{
									cout << "Вы должны съесть вражескую фигуру, чтобы пройти дальше" << endl;
									okStep = false;
								}

							}
						}
						//Неверный ход
						else
						{
							cout << "Неверный ход Ферзём" << endl;
							numFinal = 0;
							symFinal = 0;
							continue;
						}
						if (!okStep)
						{
							numFinal = 0;
							symFinal = 0;
							continue;
						}
						else if (board[8 - numFinal][symFinal][2] == 'б')
						{
							eatB.push_back(board[8 - numFinal][symFinal]);
						}

					}
					/////Король
					else if (board[8 - numStart][symStart] == "_Кч_")
					{
						if (numFinal == 8 && (symFinal == 6 || symFinal == 2))
						{
							if (!queenStep_B)
							{
								cout << "Рокировка невозможна" << endl; 
								okStep = false; 
							}
							for (int i = 0; i < 2; i++)
							{

								if (symFinal == 6)
								{
									if (!shortRokB || !stepShortRok_B)
									{
										cout << "Рокировка невозможна" << endl; 
										okStep = false; 
										break;  
									}
									else if (!(board[0][6 - i] == "    " || board[0][6 - i] == "****")) 
									{
										cout << "Рокировка невозможна" << endl; 
										okStep = false; 
										break;
									}
								}
								else if (symFinal == 2) 
								{
									if (!longRokB || !stepLongRok_B)
									{
										cout << "Рокировка невозможна" << endl;
										okStep = false;
										break;
									}
									else if (!(board[0][2 + i] == "    " || board[0][2 + i] == "****")) 
									{
										cout << "Рокировка невозможна" << endl; 
										okStep = false; 
										break; 
									}
								}
							}
							if (!okStep) 
							{
								numFinal = 0; 
								symFinal = 0; 
								continue;
							}
							else if (okStep)
							{
								
								if (symFinal == 6)
								{
									board[0][5] = "_лч_"; 
									board[0][7] = "    ";
								}
								else if (symFinal == 2)
								{
									board[0][3] = "_лч_";
									board[0][0] = "****";
								}
							}

						}


						else if ((numFinal - 1 == numStart || numFinal + 1 == numStart) && symFinal == symStart)
						{
							if (board[8 - numFinal][symFinal] == "_Фб_" || board[8 - numFinal][symFinal] == "_Кб_")
							{
								cout << "Вы не можете съесть эту фигуру" << endl;
								numFinal = 0;
								symFinal = 0;
								continue;
							}
							if (board[8 - numFinal][symFinal][2] == 'б')
							{
								eatB.push_back(board[8 - numFinal][symFinal]);
							}
						}
						else if ((numFinal - 1 == numStart || numFinal + 1 == numStart) && (symFinal - 1 == symStart || symFinal + 1 == symStart))
						{
							if (board[8 - numFinal][symFinal] == "_Фб_" || board[8 - numFinal][symFinal] == "_Кб_")
							{
								cout << "Вы не можете съесть эту фигуру" << endl;
								numFinal = 0;
								symFinal = 0;
								continue;
							}
							if (board[8 - numFinal][symFinal][2] == 'б')
							{
								eatB.push_back(board[8 - numFinal][symFinal]);
							}
						}
						else if ((symFinal - 1 == symStart || symFinal + 1 == symStart) && numFinal == numStart)
						{
							if (board[8 - numFinal][symFinal] == "_Фб_" || board[8 - numFinal][symFinal] == "_Кб_")
							{
								cout << "Вы не можете съесть эту фигуру" << endl;
								numFinal = 0;
								symFinal = 0;
								continue;
							}
							if (board[8 - numFinal][symFinal][2] == 'б')
							{
								eatB.push_back(board[8 - numFinal][symFinal]);
							}
							
						}
						else
						{
							cout << "Неверный ход Королём" << endl;
							numFinal = 0;
							symFinal = 0;
							continue;
						}
					}
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

			
			cout << endl << endl;
			sum++;

			if (numStart == 1 && symStart == 0)
			{
				stepLongRok_W = false;
			}
			if (numStart == 1 && symStart == 7)
			{
				stepShortRok_W = false;
			}
			if (numStart == 8 && symStart == 0)
			{
				stepLongRok_B = false;
			}
			if (numStart == 8 && symStart == 7)
			{
				stepShortRok_B = false;
			}
			if (numStart == 8 && symStart == 4)
			{
				queenStep_B = false;
			}
			if (numStart == 1 && symStart == 4)
			{
				queenStep_W = false;
			}
			if (numStart == 7 && numFinal == 5 && stepBlackOrWhite == 'B')
			{
				controlStep = symFinal;
			}
			else if (numStart == 2 && numFinal == 4 && stepBlackOrWhite == 'W')
			{
				controlStep = symFinal;
			}
			else
			{
				controlStep = 0;
			}
		}
	}