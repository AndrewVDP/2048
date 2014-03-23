#include <iostream>
#include <vector>
#include <iomanip>
#include <cstdlib>
#include <stdio.h>
#include <time.h>

using namespace std;

class TwoZeroFourEight
{
protected:
	int size;
	int zero;
	vector<int> d1;
	vector <vector <d1> > game;
public:
	TwoZeroFourEight();
	TwoZeroFourEight(int s, int z);
	void resetGame();
	void moveLeft();
	void moveRight();
	void moveUp();
	void moveDown();
	void printGame();//
	void playGame();
	void addRandomTIle();
	bool gameOver();//
	bool gameWin();//
	void collapseZeros();
};
//--------------------------------------------
TwoZeroFourEight::TwoZeroFourEight()
{
	size = 4;
	zero = 0;
}
//--------------------------------------------
TwoZeroFourEight::TwoZeroFourEight(int s, int z)
{
	size = s;
	zero = z;
}
//--------------------------------------------
void TwoZeroFourEight::resetGame()
{
	for (int r=0; r<size; r++)
	{
		for(int c=0; c<size; c++)
		{
			game[r][c] = zero;
		}
	}
	return;
}
//--------------------------------------------

//--------------------------------------------
void TwoZeroFourEight::moveLeft()
{
	for (int r=0; r<size; r++)
	{
		for (int c=1; c<size; c++)
		{
			if(game[r][c-1] == zero) // cell to left is blank
			{
				game[r][c-1] = game[r][c];
			}
			if (game[r][c] == game[r][c-1])// cells next to each other are the same
			{ 							
				game[r][c-1] = game[r][c-1] + game[r][c-1];
				game[r][c] = zero;
			}
		}
	}
	return;
}
//--------------------------------------------
void TwoZeroFourEight::collapseZeros()
{
	int c=0;
	int j=0;
	for (int r=0; r<size; r++)
	{
		while (c < size && j <size)
		{
			if(game[r][c] == zero)
			{
				game.erase(game.begin()+c);
				game[r][3] = zero;
				j++;
			}
			else
			{
				c++;
			}
		}
	}
}
//--------------------------------------------
void TwoZeroFourEight::moveRight() // seg fault
{
	for (int r=0; r<size; r++)
	{
		for (int c=2; c>0; c--)
		{
			if(game[r][c+1] == zero) // cell to right is blank
			{
				game[r][c+1] = game[r][c];
			}
			if (game[r][c] == game[r][c+1]) // cells next to each other are pairs
			{
				game[r][c+1] = game[r][c+1] + game[r][c+1];
				game[r][c] = zero;
			}
		}
	}
	return;
}
//--------------------------------------------
void TwoZeroFourEight::moveUp()
{
	for (int c=0; c<size; c++)
	{
		for (int r=1; r<size; r++)
		{
			if(game[r-1][c] == zero) 
			{
				game[r-1][c] = game[r][c];
			}
			if (game[r][c] == game[r-1][c])
			{ 
				game[r-1][c] = game[r-1][c] + game[r-1][c];
				game[r][c] = zero;
			}
		}
	}
	return;
}
//--------------------------------------------
void TwoZeroFourEight::moveDown()
{
	for (int c=0; c<size; c++)
	{
		for (int r=2; r>0; r--)
		{
			if(game[r+1][c] == zero)
			{
				game[r+1][c] = game[r][c];
			}
			if (game[r][c] == game[r+1][c])
			{
				game[r+1][c] = game[r+1][c] + game[r+1][c];
				game[r][c] = zero;
			}
		}
	}
	return;
}
//--------------------------------------------
void TwoZeroFourEight::printGame()
{
	for (int r=0; r<size; r++)
	{
		for (int c=0; c<size; c++)
		{
			cout << setw(5) << game[r][c] << " ";
		}
		cout << endl;
	}
	return;
}
//--------------------------------------------
bool TwoZeroFourEight::gameOver()
{
	bool end = false;
	for (int r=0; r<size; r++)
	{
		for (int c=0; c<size; c++)
		{
			if(game[r][c] == zero)
			{
				end = false;
			}
			else
			{
				end = true;
			}
		}
	}
	return end;
}
//--------------------------------------------
bool TwoZeroFourEight::gameWin()
{
	for (int r=0; r<size; r++)
	{
		for (int c=0; c<size; c++)
		{
			if(game[r][c] == 2048)
			{
				return true;
				break;
			}
			else
			{
				return false;
				break;
			}
		}
	}
}
//--------------------------------------------
void TwoZeroFourEight::addRandomTIle()
{
	srand (time(NULL));
	int tile = 0;
	int i, j;
	int randomNum =0;
	for (int k=0; k<1000; k++) // Need a better way to do this
	{
		randomNum = rand() % 100 + 1;
		if (randomNum < 91)
			tile = 2;
		else
			tile = 4;

		randomNum = rand() % 100 + 1;
		if (randomNum < 26)
			i=0;
		else if (randomNum < 51)
			i=1;
		else if (randomNum < 76)
			i=2;
		else
			i=3;

		randomNum = rand() % 100 + 1;
		if (randomNum < 26)
			j=0;
		else if (randomNum < 51)
			j=1;
		else if (randomNum < 76)
			j=2;
		else
			j=3;

		if (game[i][j] == zero)
		{
			game[i][j] = tile;
			k = 1000;
		}
	}
	return;
}
//--------------------------------------------
void TwoZeroFourEight::playGame()
{
	char cmd = ' ';
	char left = 'a';
	char down = 's';
	char right = 'd';
	char up = 'w';
	bool endGame;
	bool winGame;

	cout << "Enter \'r\' to end the game." << endl;
	addRandomTIle();
	addRandomTIle();
	printGame();

	while (cmd!='r')
	{
		cin >> cmd;
		if (cmd == left)
		{
			moveLeft();
		}
		if (cmd == right)
		{
			moveRight();
		}
		if (cmd == down)
		{
			moveDown();
		}
		if (cmd == up)
		{
			moveUp();
		}
		addRandomTIle();
		printGame();
		winGame = gameWin();
		if (winGame == true)
		{
			cmd = 'r';
			cout <<"Congrats Johnny"<< endl;
		}
		endGame = gameOver();
		if (endGame == true)
		{
			cmd = 'r';
			cout <<"Thanks for playing. Bitch."<< endl;
		}
	}
	return;
}
//--------------------------------------------
int main()
{
	TwoZeroFourEight game1;
	game1.resetGame();
	game1.playGame();

	return 0;
}