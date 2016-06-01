#pragma once
#include "stdafx.h"
#include <iostream>
#include <string>

using namespace std;


class Player
{
public:
		string name;
		int money;

		void readPlayerName();
		void playerTurn(string&, string, string, int& );
		void finalRound(int);
		void saveRank();
		void loadRank();
		int getReward();
		string read_string();

	
};

class Question
{
public:
	string category;
	string questions;
	string dotQuestion;
	string line;

	void readQuestion(int);
	void changeToDot();
	

};
