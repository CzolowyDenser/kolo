#include "stdafx.h"
#include <iostream>
#include <fstream>
#include "question.h"


using namespace std;




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

	cout << "\n" << category << "\n" << questions;


}
