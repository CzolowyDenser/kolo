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
		void playerTurn(string&, string, string );
		int getReward();
		
};

class Question
{


public:
	string category;
	string questions;
	string dotQuestion;
	string line;

	string giveDotQuestion();
	void readQuestion(int);
	void changeToDot();


};
