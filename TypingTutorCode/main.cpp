#include <iostream>
#include <cstdlib>
#include <ctime>
#include <windows.h>
#include <fstream>
#include "myconsole.h"
#include "mygraphics.h"
using namespace std;

//Function headers
void myInterface();
void randomWords(char wordArr[], int size);
int extractWordIndex(char wordArr[], int size);
void placeWords(char wordArr[], int size);
bool moveWord(char wordArr[], int size, int speed, int xPosition, int &startIndex, int &y);
int calScores(int &loop, int &totalScores, int startIndex, int y);
int highScore(int totalScores);
void gameTermination(int startIndex, int y, int &correct);

int main()
{
	ClearScreen();
	int speed;
	cout << "Enter 1 if you want a slow speed else enter any other digit for a faster speed.\nMake sure to open the console in full screen." << endl;
	cin >> speed;

	ClearScreen();
	const int size = 18;
	char wordArr[size];
	int count = 0;
	int xPosition = 40;	//It is the x-coordinate of the place where the word entered by the user is to be placed
	int loop = 0;		//Used to calculate the scores
	int totalScores = 0;
	int startIndex=0;	//It tells the index in the array of the first alphabet in the three letter random word extracted
	int y = 0;			//It is the y-coordinate of the place where the word entered by the user is placed
	int correct = 1;	//This represents the number of correct inputs the user has given
	bool stop;

	myInterface();

	PlaceCursor(162, 29);
	cout << "High Score";
	PlaceCursor(162, 39);
	cout << "Your Score";
	PlaceCursor(90, 22);
	cout << "Welcome to Typing Tutor!";
	PlaceCursor(93, 23);
	cout << "By Zara Ahmad" << endl;

	placeWords(wordArr, size);
	PlaceCursor(167, 32);
	cout << highScore(totalScores);

	while(count < 7 && correct != 5)
	{
		gameTermination(startIndex, y, correct);
		stop = moveWord(wordArr, size, speed, xPosition, startIndex, y);
		xPosition += 10;

		calScores(loop, totalScores, startIndex, y);
		PlaceCursor(167, 42);
		cout << totalScores;
		
		PlaceCursor(167, 32);
		cout << highScore(totalScores);

		count++;
	}

	if(correct == 5)
	{
		ClearScreen();
		int x = 100, y = 100;
		int width = 150, length = 250;

		COLORREF greenColor= RGB(0,255,0);
		PlaceCursor(x, y);
		for (int a = y; a < width + y; a++)
		{
			for(int b = x; b < length + x; b++)
				mySetPixel(b,a,greenColor);
		}

		PlaceCursor(20,55);
		cout << "Congratulations! You Won!" << endl;
	}

	else
	{
		ClearScreen();
		int x = 100, y = 100;
		int length = 150, width = 250;

		COLORREF blueColor= RGB(0,0,255);
		PlaceCursor(x, y);
		for (int a = y; a < length + y; a++)
		{
			for(int b = x; b < width + x; b++)
				mySetPixel(b,a,blueColor);
		}

		PlaceCursor(20,55);
		cout << "You Lost! Better Luck next time!" << endl;
	}
}


void myInterface()
{
	// for drawing the top and bottom horizontal lines
	int x = 20, y = 20;
	int width = 50, length = 180;
	int lines = 0;

	while (lines < 2)
	{
		PlaceCursor(x, y);
		for (int start = x; start < length + x; start++)
			cout << "*";

		y = y + width;
		lines = lines + 1;
	}

	// for drawing the left and right vertical lines
	lines = 0, x = 20, y = 20;
	while (lines < 2)
	{
		PlaceCursor(x, y);
		for (int start = y; start < width + y; start++)
		{
			PlaceCursor(x, start);
			cout << "*";
		}
		x = x + length;
		lines = lines + 1;
	}

	cout << endl;

	// for drawing horizontal lines inside the boundary
	x = 25, y = 30;
	length = 100;
	lines = 0;

	for ( ; lines < 6; lines++)
	{
		PlaceCursor(x, y);
		for (int start = x; start < length + x; start++)
			cout << "*";
		y = y + 5;
	}

	//	for drawing horizontal lines for the High score and your score boxes
	x = 160, y = 30;
	width = 5, length = 15;
	lines = 0;

	while (lines < 4)
	{
		PlaceCursor(x, y);
		for (int start = x; start < length + x; start++)
			cout << "*";

		y = y + width;
		lines = lines + 1;
	}

	//for drawing vertical lines for high score box
	x = 160, y = 30;
	lines = 0;
	int loop = 0;
	while(loop < 2)
	{
		x = 160, y = 30;
		while (lines < 2)
		{
			PlaceCursor(x, y);
			for (int start = y; start < width + y; start++)
			{
				PlaceCursor(x, start);
				cout << "*";
			}
			x = x + length;
			lines = lines + 1;
		}
		y += 10;
		loop++;
	}

	//for drawing vertical lines for your score box
	cout << endl;
	while (lines < 4)
	{
		PlaceCursor(x, y);
		for (int start = y; start < width + y; start++)
		{
			PlaceCursor(x, start);
			cout << "*";
		}
		x = x + length;
		lines = lines + 1;
	}

	cout << endl;

}


void randomWords(char wordArr[], int size)
{
	// This function stores the alphabets in an array using the ASCII code.
	// This fuction is called by the function placeWords.
	srand(time(0));
	char c;
	for(int alphabets = 0; alphabets < size; alphabets++)
	{
		c = 97 + rand()% 26;
		wordArr[alphabets] = c;
	}

}

int extractWordIndex(char wordArr[], int size)
{
	// This function identifies the index number of the first alphabet in the three letter word.
	// This fuction is called by the function moveWord.
	srand(time(0));
	int x = 105, y = 27;
	int alphabetIndex = 0;
	int wordStartIndex;


	wordStartIndex = 1 + rand()% 6;

	if (wordStartIndex == 1)
		alphabetIndex = 0;

	else if (wordStartIndex == 2)
		alphabetIndex = 3;

	else if (wordStartIndex == 3)
		alphabetIndex = 6;

	else if (wordStartIndex == 4)
		alphabetIndex = 9;

	else if (wordStartIndex == 5)
		alphabetIndex = 12;

	else
		alphabetIndex = 15;

	return alphabetIndex;

}

void placeWords(char wordArr[], int size)
{
	//This function places the six words extracted on different lines
	int x = 30, y = 27;
	int alphabet = 0;
	int loop = 0;

	randomWords(wordArr, size);
	for(; alphabet < size; alphabet++)
	{
		if (alphabet % 3 == 0)
		{
			PlaceCursor(x, y);
			y = y + 5;
		}
		cout << wordArr[alphabet];
	}
	cout << endl;
}

bool moveWord(char wordArr[], int size, int speed, int xPosition, int &startIndex, int &y)
{
	// This function controls the up and down movement of the random word extracted
	// This function also compares compares the user input
	int x = 130;
	y = 57;
	int count = 0;
	int wait = 0;
	bool stop = false;

	// alphabetIndex is returned by the function extractWordIndex
	startIndex = extractWordIndex(wordArr, size);
	int endIndex = startIndex + 3;
	char z = 0;	//non-printable charcter

	if(speed == 1)
		wait = 500;
	else
		wait = 300;

	// This while loop is for the upward motion of the word
	while(count < 6 && !stop)
	{

		PlaceCursor(x, y);
		for(int i= startIndex; i < endIndex; i++)
			cout << wordArr[i];

		Sleep(wait);
		PlaceCursor(x, y);
		cout << z << z << z;
		y = y - 5;
		count++;

		//These conditions takes the user input
		//If the user input does not match than the word moves one step upwards
		if(CheckKeyPressed1() == wordArr[startIndex])
		{
			if(CheckKeyPressed1() == wordArr[startIndex + 1])
			{
				if(CheckKeyPressed1() == wordArr[startIndex + 2])
				{
					PlaceCursor(xPosition, y);
					for(int i= startIndex; i < endIndex; i++)
					{
						cout << wordArr[i];
						stop = true;
					}
				}
			}
		}
	}

	// This while loop is for the downward motion of the word
	while(count < 11 && !stop)
	{
		PlaceCursor(x, y);
		for(int i= startIndex; i < endIndex; i++)
			cout << wordArr[i];

		Sleep(wait);
		PlaceCursor(x, y);
		cout << z << z << z;
		y = y + 5;
		count++;

		//These conditions takes the user input
		//If the user input does not match than the word moves one step downwards
		if(CheckKeyPressed1() == wordArr[startIndex])
		{
			if(CheckKeyPressed1() == wordArr[startIndex + 1])
			{
				if(CheckKeyPressed1() == wordArr[startIndex + 2])
				{
					PlaceCursor(xPosition, y);
					for(int i= startIndex; i < endIndex; i++)
					{
						cout << wordArr[i];
						stop = true;
					}
				}
			}
		}
	}

	//If the user does not enter anything or gives incorrect answer then this condition places the word in the last row
	if(!stop)
	{
		int count = 0;
		PlaceCursor(x, 52);
		for(int i= startIndex; i < endIndex; i++)
			cout << wordArr[i];
	}

	return stop;
}

int calScores(int &loop, int &totalScores, int startIndex, int y)
{

	int scores = 0;
	int tetraBonus = 0;
	int winBonus = 0;

	if((startIndex == 0 && y == 27) || (startIndex == 3 && y == 32) || (startIndex == 6 && y == 37) ||
		(startIndex == 9 && y == 42) || (startIndex == 12 && y == 47) || (startIndex == 15 && y == 52))
		{
			loop += 1;
			scores += 5;
			if(loop == 3)
				tetraBonus += 30;

			if(loop == 5)
				winBonus += 50;
		}

	totalScores = scores + tetraBonus + winBonus;

}

int highScore(int totalScores)
{
	int hs = 0;
	ifstream input("highScore.txt");
	if (input.is_open())
	{
		input >> hs;
		if (hs < totalScores)
		{
			hs = totalScores;
			ofstream output ("highScore.txt");
			output << hs;
		}
		input.close();
	}

	return hs;
}

void gameTermination(int startIndex, int y, int &correct)
{
	if((startIndex == 0 && y == 27) || (startIndex == 3 && y == 32) || (startIndex == 6 && y == 37) ||
		(startIndex == 9 && y == 42) || (startIndex == 12 && y == 47) || (startIndex == 15 && y == 52))
		{
			correct += 1;
		}
}
