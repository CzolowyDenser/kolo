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

struct options
{
	int playerNumbers;
	int roundNumbers=5;
} one;

void getSettings();
void showRules();
void playerRoundNumbers(options&);
void showMenu();
int randomNumber();

vector <int> questionNumber(one.roundNumbers+1);

int main()
{
	Player rankk;

	do
	{
		int menu = 0;
		showMenu();
		while (!(cin >> menu) || menu >= 6)
		{
			cin.clear();
			cin.ignore();
			cout << "Zla wartosc." << endl;
			cout << "Sprobuj jeszcze raz: ";
		}
		switch (menu)
		{
			
		case 1:
		{
			system("cls");

			getSettings();

			vector <Player> playerV(one.playerNumbers);
			vector <Question> questionV(one.roundNumbers);
			vector <Player> sort(one.playerNumbers);

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
					for (j; j < one.playerNumbers;)
					{
						playerV[j].playerTurn(questionV[i].dotQuestion, questionV[i].questions, questionV[i].category, j);
						if (j >= one.playerNumbers)
							j = 0;

						if (questionV[i].questions == questionV[i].dotQuestion)
							break;
					}

				} while (questionV[i].questions!=questionV[i].dotQuestion);
				Sleep(2000);
				system("cls");

				
				sort = playerV;
				for (int c = 0; c < one.playerNumbers; c++)
					for (int d = 0; d < one.playerNumbers - 1; d++)
						if (sort[d].money < sort[d + 1].money)
							swap(sort[d], sort[d + 1]);
				cout << "Wyniki po " << i + 1 << " rundzie:" << endl;

				for (int k = 0; k < one.playerNumbers; k++)
					cout << k + 1 << ". " << sort[k].name << " " << sort[k].money << endl;
				
				currentRound++;
				cout << "\n\n\n";
				cout << "Nacisnij ENTER aby przejsc do nastepnej rundy.";
				cin.get();
			}
			one.roundNumbers += 1;
			sort[0].finalRound(randomNumber());
			
			rankk.loadRank();
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
			rankk.loadRank();
			cin.get();
			system("cls");
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
	cout << "1. Gra sklada sie z ilosci rund podanej przez uzytkownika + runda finalowa." << endl << endl;
	cout << "2. Ilosc rund i graczy mozna zmienic w zakladce \"Ustawienia gry\"" << endl << endl;
	cout << "3. W rankingu zostaje zapisany tylko gracz ktory dotarl do finalu." << endl << endl;
	cout << "   Bez koniecznosci odgadniecia hasla finalowego." << endl << endl;
	cout << "4. Spolgloski mozna podawac, a samogloski sie kupuje." << endl << endl;
	cout << "5. Koszt samogloski 50." << endl << endl;
	cout << "6. Jesli podasz samogloske, a nie masz wystarczajacej ilosci pieniedzy na koncie " << endl;
	cout << "   stracisz kolejke." << endl << endl;
	cout << "7. Aby podac haslo w calosci nalezy zamiast litery wpisac 0 (zero)." << endl << endl;
	cout << "8. Przy podawaniu calego hasla nagroda to 50 za kazda litere hasla." << endl << endl;
	cout << "9. W finale gdy uzytkownik odgdnie haslo nagroda to 100 za kazda litere hasla." << endl << endl;
	

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


	system("cls");
}
void showMenu()
{
	cout << "\t\t\tKOLO FORTUNY v1.0\n\n\n";
	cout << "1. Rozpocznij gre." << endl;
	cout << "2. Zasady." << endl;
	cout << "3. Ranking. " << endl;
	cout << "4. Ustawienia gry." << endl;
	cout << "5. Wyjscie." << endl;

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
