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


vector<char> numBoard = { '8', '7', '6', '5', '4', '3', '2', '1'};
vector<char> strBoard = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H'};
string stepStart, stepFinal, peshkaUpdate;
int symStart, symFinal, numStart, numFinal, sum, sovp, eatW, eatB, controlStep; //controlStep для взятия на проходе у пешки
char stepBlackOrWhite;
bool okStep = true;

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
		cout << endl <<endl << "===================================";
		cout << endl << "Совершено ходов: " << sum << endl;
		cout << "Белые съели: " << eatW << endl;
		cout << "Чёрные съели: " << eatB << endl;
		cout << "===================================" << endl << endl;
		// Ход

		while (true)
		{
			cout << controlStep << endl;
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
			cin >> stepStart;

				while (true)
				{
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
						if (stepBlackOrWhite == 'W')
						{
							cout << "Ход белых из: ";
							cin >> stepStart;
						}
						else
						{
							cout << "Ход чёрных из:";
							cin >> stepStart;
						}
					}
				}

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
						cin >> stepStart;
					}
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

			while (true) //Ход куда
			{
				if (stepBlackOrWhite == 'W')
				{
					cout << "Ход белых в: ";
					cin >> stepFinal;
				}
				else
				{
					cout << "Ход чёрных в:";
					cin >> stepFinal;
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
						if (stepBlackOrWhite == 'W')
						{
							cout << "Ход белых в: ";
							cin >> stepFinal;
						}
						else
						{
							cout << "Ход чёрных в:";
							cin >> stepFinal;
						}
					}
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
						if (stepBlackOrWhite == 'W')
						{
							cout << "Ход белых в: ";
							cin >> stepFinal;
						}
						else
						{
							cout << "Ход чёрных в:";
							cin >> stepFinal;
						}
					}
				}

				stepFinal = stepFinal[1];
				numFinal = stoi(stepFinal);
				okStep = true;

				if (stepBlackOrWhite == 'W') // Ход белых
				{
					if (numStart == numFinal && symStart == symFinal)
					{
						cout << "Нельзя ходить в первоначальную клетку!" << endl;
						continue;
					}

					/*if (board[8 - numFinal][symFinal][2] == 'б')
					{
						cout << "Вы не можете есть свои фигуры" << endl;
						continue;
					}*/
					/////Пешка
					else if (board[8 - numStart][symStart] == "_пб_")
					{
						

						if (numFinal == 6 && board[3][symFinal] == "_пч_" && controlStep == symFinal)
						{
							if (numStart % 2 == 0)
							{
								if ((symStart) % 2 == 0)
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
								if ((symStart) % 2 == 1)
								{
									board[3][symFinal] = "****";
								}
								else
								{
									board[3][symFinal] = "    ";
								}
							}
							eatW++;
						}

						if (numStart == 2 && (!(numFinal == numStart + 1 || numFinal == numStart + 2) || !(symStart == symFinal) || !(board[8 - numFinal][symFinal] == "****" || board[8 - numFinal][symFinal] == "    ")))
						{
							cout << "Неверный ход пешкой1" << endl;
							numFinal = 0;
							symFinal = 0;
							continue;
						}

						else if ((numStart != 2 && board[8 - numFinal][symFinal] == "****") || (numStart != 2 && board[8 - numFinal][symFinal] == "    "))
						{
							if (symStart != symFinal || numStart != numFinal - 1)
							{
								cout << "Неверный ход пешкой 2" << endl;
								numFinal = 0;
								symFinal = 0;
								continue;
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
								cout << "Неверный ход пешкой 3" << endl;
								numFinal = 0;
								symFinal = 0;
								continue;
							}
							else
							{
								eatW++;
							}
						}
						
						if (numFinal == 8)
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
									else
									{
										eatW++;
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
									else
									{
										eatW++;
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
									else
									{
										eatW++;
									}
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
									else
									{
										eatW++;
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

					}
					/////Конь
					else if (board[8 - numStart][symStart] == "_кб_") 
					{
						if ((numFinal == numStart + 2 && symFinal == symStart - 1) || (numFinal == numStart + 2 && symFinal == symStart + 1) ||
							(numFinal == numStart - 2 && symFinal == symStart - 1) || (numFinal == numStart - 2 && symFinal == symStart + 1) ||
							(numFinal == numStart + 1 && symFinal == symStart - 2) || (numFinal == numStart + 1 && symFinal == symStart + 2) ||
							(numFinal == numStart - 1 && symFinal == symStart - 2) || (numFinal == numStart + 1 && symFinal == symStart + 2))
						{
							eatW++;
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

					}
					/////Ферзь
					else if (board[8 - numStart][symStart] == "_ФБ_") 
					{

					}
					/////Король
					else if (board[8 - numStart][symStart] == "_КБ_") 
					{

					}
				}

				else if (stepBlackOrWhite == 'B') /////// Ход чёрных
				{
					if (board[8 - numStart][symStart] == "_пч_")
					{
						if (numStart == numFinal && symStart == symFinal)
						{
							cout << "Нельзя ходить в первоначальную клетку!" << endl;
							continue;
						}

						if (numFinal == 3 && board[4][symFinal] == "_пб_" && controlStep == symFinal) // Взятие на проходе
						{
							if (numStart % 2 == 0)
							{
								if ((symStart) % 2 == 0)
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
								if ((symStart) % 2 == 1)
								{
									board[4][symFinal] = "****";
								}
								else
								{
									board[4][symFinal] = "    ";
								}
							}
							eatB++;
						}

						else if (numStart == 7 && (!(numFinal == numStart - 1 || numFinal == numStart - 2) || !(symStart == symFinal) || !(board[8 - numFinal][symFinal] == "****" || board[8 - numFinal][symFinal] == "    ")))
						{
							cout << "Неверный ход пешкой1" << endl;
							numFinal = 0;
							symFinal = 0;
							continue;
						}

						else if ((numStart != 7 && board[8 - numFinal][symFinal] == "****") || (numStart != 7 && board[8 - numFinal][symFinal] == "    "))
						{
							if (symStart != symFinal || numStart != numFinal + 1)
							{
								cout << "Неверный ход пешкой 2" << endl;
								numFinal = 0;
								symFinal = 0;
								continue;
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
								cout << "Неверный ход пешкой 3" << endl;
								numFinal = 0;
								symFinal = 0;
								continue;
							}
							else
							{
								eatB++;
							}
						}

						else if (numFinal == 1)
						{
							while (true)
							{
								cout << "Какой фигурой вы хотите стать?";
								cin >> peshkaUpdate;
								if (peshkaUpdate == "Король")
								{
									cout << "Вы не можете стать Королём";
									continue;
								}

								else if (peshkaUpdate == "Ладья")
								{
									board[8 - numStart][symStart] = "_лч_";
									break;
								}
								else if (peshkaUpdate == "Ферзь")
								{
									board[8 - numStart][symStart] = "_Фч_";
									break;
								}
								else if (peshkaUpdate == "Слон")
								{
									board[8 - numStart][symStart] = "_сч_";
									break;
								}
								else if (peshkaUpdate == "Конь")
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
									else
									{
										eatB++;
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
									else
									{
										eatB++;
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
									else
									{
										eatB++;
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
									else
									{
										eatB++;
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
					}

					else if (board[8 - numStart][symStart] == "_кч_")
					{
						if ((numFinal == numStart + 2 && symFinal == symStart - 1) || (numFinal == numStart + 2 && symFinal == symStart + 1) ||
							(numFinal == numStart - 2 && symFinal == symStart - 1) || (numFinal == numStart - 2 && symFinal == symStart + 1) ||
							(numFinal == numStart + 1 && symFinal == symStart - 2) || (numFinal == numStart + 1 && symFinal == symStart + 2) ||
							(numFinal == numStart - 1 && symFinal == symStart - 2) || (numFinal == numStart + 1 && symFinal == symStart + 2))
						{
							eatB++;
						}
						else
						{
							cout << "Неверный ход конём" << endl;
							numFinal = 0;
							symFinal = 0;
							continue;
						}
					}

					else if (board[8 - numStart][symStart] == "_сч_")
					{

					}

					else if (board[8 - numStart][symStart] == "_Фч_")
					{

					}

					else if (board[8 - numStart][symStart] == "_Кч_")
					{

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