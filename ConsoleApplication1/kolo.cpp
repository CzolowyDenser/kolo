// ConsoleApplication1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "class.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>
#include<string>

using namespace std;

int currentRound = 1;
int currentPlayer = 0;

struct options
{
	int playerNumbers;
	int roundNumbers=5;
} one;

void getSettings();
void showRules();
void playerRoundNumbers(options&);
int randomNumber();
int getReward();



vector <int> questionNumber(one.roundNumbers+1);


int main()
{
	int whichPlayer = 0;

	do
	{
		int menu = 0;
		cout << "1. Rozpocznij gre." << endl;
		cout << "2. Zasady." << endl;
		cout << "3. Ranking. " << endl;
		cout << "4. Ustawienia gry." << endl;
		cout << "5. Wyjscie." << endl;

		cin >> menu;
		switch (menu)
		{
			
		case 1:
		{
		
			system("cls");
	
			getSettings();

			vector <Player> playerV(one.playerNumbers);
			vector <Question> questionV(one.roundNumbers);

			cin.get();
			for (int i = 0; i < one.playerNumbers; i++)
			{
				playerV[i].readPlayerName();
			}

			int j = 0;
			for (int i = 0; i < one.roundNumbers; i++)
			{
				
				questionV[i].readQuestion(randomNumber());
				questionV[i].changeToDot();
				system("cls");

				cout << "\t\t\tPytanie z kategori: " << "\n\n";
				cout<<"\t\t\t"<< questionV[i].category << "  " << questionV[i].dotQuestion << "\n\n\n";
				Sleep(2500);
				system("cls");
				
				do
				{
					for (j = 0; j<one.playerNumbers; j++)
					{
						playerV[j].playerTurn(questionV[i].dotQuestion, questionV[i].questions, questionV[i].category);
						

						if (questionV[i].questions == questionV[i].dotQuestion)
							break;
					}

				} while (questionV[i].questions!=questionV[i].dotQuestion);
				currentRound++;
				cin.get();
			}
			system("cls");
			break;
		}
		case 2:
		{
			showRules();
			break;
		}
		case 3:
		{
			cin.get();
			cin.get();
			break;
		}
		case 4:
		{
			playerRoundNumbers(one);
			break;
		}
		case 5:
		{
			exit(0);
		}
		}

	} while (true);

    return 0;
}


void showRules()
{
	system("cls");
	cout << "1. Gra przeznaczona dla dwoch graczy." << endl << endl;;
	cout << "2. Spolgloski mozna podawac, a samogloski sie kupuje." << endl << endl;
	cout << "3. Koszt samogloski 50." << endl << endl;
	cout << "4. Jesli podasz samogloske, a nie masz wystarczajacej ilosci pieniedzy na koncie " << endl;
	cout << "   stracisz kolejke." << endl << endl;
	cout << "5. Przy podawaniu calego hasla nagroda to 50 za kazda litere hasla." << endl << endl;
	cout << "6. Aby podac haslo w calosci nalezy zamiast litery wpisac 0 (zero)." << endl << endl;

	cin.get();
	cin.get();
	system("cls");
}
void playerRoundNumbers(options& one)
{
	system("cls");
	int w = 1;


	fstream settings;
	settings.open("settings.txt", ios::in);
		settings >> one.playerNumbers;
		settings >> one.roundNumbers;
	settings.close();

	cout << "Aktualne ustawienia:" << endl;
	cout << "Ilosc graczy: " << one.playerNumbers << endl;
	cout << "Ilosc rund: " << one.roundNumbers << endl;
	cout << endl;
	cout << "Jesli chcesz zmienic wpisz 0 (zero). Aby wyjsc wprowadz dowolna wartosc." << endl;
	if (!(cin >> w))
	{
		w = 1;
		cin.sync();
		cin.clear();
	}
	if (w == 0)
	{
		system("cls");
		cout << "Podaj ilosc graczy:" << endl;
		cin >> one.playerNumbers;
		cout << endl;
		cout << "Podaj ilosc rund:" << endl;
		cin >> one.roundNumbers;

	
		fstream settings;
		settings.open("settings.txt", ios::out);
			settings << one.playerNumbers<<endl;
			settings << one.roundNumbers;
		settings.close();
	}


	cin.get();
	system("cls");
}
int randomNumber()
{
	srand(time(NULL));
	questionNumber[0]=(rand() % one.roundNumbers) + 1;
	questionNumber[currentRound] = questionNumber[0];

		if (currentRound > 1)
		{
			for (int i = 1; i < currentRound; i++)
				if (questionNumber[i] == questionNumber[0])
				{
					do
					{
						questionNumber[currentRound] = (rand() % one.roundNumbers) + 1;
						questionNumber[0] = questionNumber[currentRound];
					} while (questionNumber[i] == questionNumber[0]);
					i = 0;
				}
		}


		return questionNumber[0];
}
void getSettings()
{
	fstream settings;
	settings.open("settings.txt", ios::in);
	settings >> one.playerNumbers;
	settings >> one.roundNumbers;
	settings.close();
}
int getReward()
{
	int prizeAm = 0;
	int reward = 0;
	int prizeNr = 0;
	fstream rew;
	rew.open("nagrody.txt");
	while (!rew.eof())
	{
		rew >> reward;
		prizeAm++;
	}
	rew.seekg(0);

	srand(time(NULL));
	prizeNr = (rand() % prizeAm) + 1;
	for (int i = 0; i < prizeNr; i++)
		rew >> reward;
	rew.close();
	return reward;

}