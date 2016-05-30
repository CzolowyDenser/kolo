#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <cctype>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include "class.h"

using namespace std;

void Player::readPlayerName()
{
	cout << "Podaj imie gracza: " << endl;
	getline(cin, name);
}

void Player::playerTurn(string& dot, string que, string cat)
{
	char letter;
	bool f = 0;
	string checkQ;
	string checkQ2;

	checkQ2 = que;
	for (int i = 0; i <= checkQ2.size(); i++)
	{
		if (checkQ2[i] == ' ')
			checkQ2[i] = '-';
	}

	do
	{
		f = 0;
		cout << "\t\t\t" << cat << "  " << dot << "\n\n";
		cout << name << " nacisnij ENTER aby zakrecic kolem." << endl;
		cin.get();
		int reward = getReward();
		if (reward == 0)
		{
			cout << "BANKRUT! Tracisz kolejke." << endl;
			money = 0;
			return;
		}
		cout << "Wylosowales/as " << reward << endl;
		cout << "Podaj litere, aby podac haslo w calosci wpisz 0(zero)."<<endl;
		cin >> letter;
		cin.sync();
		cin.clear();
		cin.get();
		if (letter == '0')
		{
			cout << "Podaj cale haslo: ";
			getline(cin, checkQ);
			if (checkQ == que)
			{
				int c = 0;
				for (int i = 0; i <= que.size(); i++)
					if (isalpha(que[i]))
						c++;

				money += (c * 50);
				cout << "Twoj stan konta: " << money << "." << endl;
				return;
			}
			else
			{
				cout << "Haslo nie prawidlowe." << endl;
				
				return;
			}
		}


		for (int i = 0; i <= dot.size(); i++)
		{
			if (que[i] == letter)
			{
				dot[i] = letter;
				money += reward;
				cout << "BRAWO!. Twoj stan konta: " << money << "." << "\n\n";
				f = 1;
			}
		}
		if (f == 0)
		{
			cout << "Brak podanej litery :(" << endl;
			Sleep(2000);
			system("cls");
			
			return;
		}
		if (checkQ2 == dot)
			f = 0;

	} while (f == 1);
	
}

int Player::getReward()
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



void Question::readQuestion(int nr)
{
	fstream file;
	file.open("hasla.txt");

	for (int i = 1; i < nr; i++)
	{
		getline(file, line);
	}

	category.clear();
	questions.clear();
	file >> category;
	getline(file, questions);
	questions.erase(0, 1);
}

void Question::changeToDot()
{
	int qlen = questions.size();
	dotQuestion.clear();
	dotQuestion = questions;
	for (int i = 0; i <= qlen; i++)
	{
		if (isalpha(questions[i]))
			dotQuestion[i] = '.';
		else
			if (questions[i] == ' ')
				dotQuestion[i] = '-';
	}
}
string Question::giveDotQuestion()
{
	return dotQuestion;
}