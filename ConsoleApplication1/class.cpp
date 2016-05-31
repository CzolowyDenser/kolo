#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <cctype>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <vector>
#include "class.h"

using namespace std;

void Player::readPlayerName()
{
	cout << "Podaj imie gracza: " << endl;
	getline(cin, name);
}

void Player::playerTurn(string& dot, string que, string cat, int& j)
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
			j++;
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
				cout << "\nHaslo prawidlowe!" << endl;
				cout << "Twoj stan konta: " << money << "." << endl;
				dot = que;
				return;
			}
			else
			{
				cout << "Haslo nie prawidlowe." << endl;
				j++;
				return;
			}
		}

		if(letter == 'a' || letter == 'e' || letter == 'y' || letter == 'u' || letter == 'i' || letter == 'o')
			if (money < 50)
			{
				cout << "Nie mozesz podac samogloski.\nBrak srodkow na koncie. Tracisz kolejke." << endl;
				j++;
				Sleep(2000);
				system("cls");
				return;
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
			j++;
			
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

void Player::finalRound(int qnr)
{
	system("cls");
	Question finalR;
	char sam, spo1, spo2;
	string check;

	cout << name << " gratulacje. Witamy w finale." << "\n\n";
	cout << "Podaj jedna samogloske i dwie spolgloski." << endl;
	cout << endl;
	cout << "Samogloska: ";
	while (!(cin >> sam) || sam == 'b' || sam == 'c' || sam == 'd' || sam == 'f' || sam == 'g' || sam == 'j' || sam == 'k' || sam == 'l' || sam == 'm' || sam == 'n' || sam == 'p' || sam == 'r' || sam == 's' || sam == 't' || sam == 'w' || sam == 'z' || (sam<97 && sam<122))
	{
		cin.clear();
		cin.ignore();
		cout << "To nie jest samogloska." << endl;
		cout << "Sprobuj jeszcze raz: ";
	}
	cout << endl;
	cout << "Pierwsza spolgloska: ";
	while (!(cin >> spo1) || spo1 == 'a' || spo1 == 'e' || spo1 == 'y' || spo1 == 'u' || spo1 == 'i' || spo1 == 'o' || (spo1<97 && spo1<122))
	{
		cin.clear();
		cin.ignore();
		cout << "To nie jest spolgloska." << endl;
		cout << "Sprobuj jeszcze raz: ";
	}
	cout << endl;
	cout << "Druga spolgloska: ";
	while (!(cin >> spo2) || spo2 == 'a' || spo2 == 'e' || spo2 == 'y' || spo2 == 'u' || spo2 == 'i' || spo2 == 'o' || (spo2<97 && spo2<122))
	{
		cin.clear();
		cin.ignore();
		cout << "To nie jest spolgloska." << endl;
		cout << "Sprobuj jeszcze raz: ";
	}
	while (spo2 == spo1)
	{
		cin.clear();
		cin.ignore();
		cout << "Podales juz ta spolgloske." << endl;
		cout << "Sprobuj jeszcze raz: ";
		cin >> spo2;
	}
	finalR.readQuestion(qnr);
	finalR.changeToDot();
	for (int i = 0; i < finalR.questions.size(); i++)
	{	
		if (finalR.questions[i] == sam)
			finalR.dotQuestion[i] = sam;
		else
			if(finalR.questions[i] == spo1)
				finalR.dotQuestion[i] = spo1;
			else
				if (finalR.questions[i] == spo2)
					finalR.dotQuestion[i] = spo2;
	}
	cout << finalR.category << " " << finalR.dotQuestion << "\n\n";
	cout << "Podaj haslo: ";
	cin >> check;
	if (finalR.questions == check)
	{
		int c = 0;
		for (int i = 0; i < check.size(); i++)
			if (isalpha(check[i]))
				c += 100;
		money += c;
		cout << "Haslo prawidlowe! Gratulacje." << endl;
	}
	else
	{
		cout << "\nHaslo nieprawidlowe.\n\nPrawidlowe haslo to " << finalR.questions << endl;
	}

	cout << "\n\n" << name << " twoj stan konta po finale " << money <<"."<< endl;
	
	saveRank();
	loadRank();

	cin.get();
	cin.get();
}

void Player::saveRank()
{
	fstream save;
	save.open("ranking.txt", ios::app );
	save << money << " " << name << endl;
	save.close();
}
void Player::loadRank()
{
	struct rank
	{
		string nam;
		int mon;
	};
	int i = 0;
	int k = 0;
	string test;

	system("cls");
	fstream load;
	load.open("ranking.txt", ios::in);
	while (!(load.eof()))
	{
		getline(load, test);
		k++;
	}
	load.seekg(0);
	rank* tab = new rank[k+1];
	while (!(load.eof()))
	{
		load >> tab[i].mon;
		getline(load, tab[i].nam);
		i++;
	}
	load.close();
	for (int j = 0; j < k; j++)
	{
		for (int c = 0; c < k - 1; c++)
		{
			if (tab[c].mon < tab[c + 1].mon)
				swap(tab[c], tab[c + 1]);
		}
	}
	for (int j = 0; j < i; j++)
	{
		cout <<j+1 <<". " << tab[j].nam << " " << tab[j].mon << ".\n";
	}
	cin.get();
	
}