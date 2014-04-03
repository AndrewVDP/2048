#include <iostream>
#include <vector>
#include <iomanip>
#include <cstdlib>
#include <stdio.h>
#include <time.h>
//#include <ncurses.h>  // use with getch()


using namespace std;


class TwoZeroFourEight
{
protected:
	int size;
	int zero;
	int game[4][4];
	vector <int> v;
	int b[4][4];
	int arr[4][4];
public:
	TwoZeroFourEight();
	TwoZeroFourEight(int s, int z);
	void resetGame();
	void moveLeft();
	void printGame();
	void playGame();
	void addRandomTile();
	bool gameOver();
	bool gameWin();
	void collapseZerosLeft();
	bool movement(int j[4][4]);
	void rotateBoard();
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
			game[r][c] = zero;
	}

	for (int i=0; i<size; i++)
		v.push_back(0);
	return;
}
//--------------------------------------------
void TwoZeroFourEight::rotateBoard()
{
	int j=0;

	for (int r=0; r<4; r++)
	{
		for (int c=0; c<4; c++)
		{
			arr[c][3 + j] = game[r][c];
		}
		j--;
	}
	for (int r=0; r<size; r++)
		for (int c=0; c<size; c++)
		{
			game[r][c] = arr[r][c];
		}
	return;
}
//--------------------------------------------
void TwoZeroFourEight::collapseZerosLeft()
{
	int c=0;
	for (int r=0; r<size; r++)
	{
		for (c=0; c<size; c++)
			v[c] = game[r][c]; //tranfers one row at a time to a vector
		c = 0;
		int b=0;
		while((c<size) && (b<size))
			if(v[c] == zero)
			{
				v.erase(v.begin()+c); //if there is a zero it will be deleted
				v.push_back(zero); //add zero on end if there was a zero deleted
				b++;
			}
			else
				c++;
		for (int i=0; i<size; i++)
			game[r][i] = v[i]; //tranfers new line back to game board
	}
}
//--------------------------------------------
void TwoZeroFourEight::moveLeft()
{
	collapseZerosLeft();
	for (int r=0; r<size; r++)
		for (int c=0; c<size-1; c++)
			if(game[r][c] == game[r][c+1])
			{
				game[r][c] += game[r][c+1];
				game[r][c+1] = zero;
				collapseZerosLeft();
			}
	return;
}
//--------------------------------------------
void TwoZeroFourEight::printGame()
{
	for (int r=zero; r<size; r++)
	{
		for (int c=zero; c<size; c++)
			cout << setw(5) << game[r][c] << " ";
		cout << endl;
	}
	return;
}
//--------------------------------------------
bool TwoZeroFourEight::gameOver() //not game over when you can still move with no 0's
{
	bool end = true;
	for (int r=0; r<size; r++)
	{
		for (int c=0; c<size; c++)
		{
			if(game[r][c] == zero)
			{
				end = false;
				break;
			}
		}
	}
	for (int i=0; i<4; i++)
	{
		for (int r=0; r<size; r++)
		{
			for (int c=0; c<size-1; c++)
			{
				if(game[r][c] == game[r][c+1])
				{
					end = false;
				}
			}
		}
		rotateBoard();
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
		}
	}
	return false;
}
//--------------------------------------------
bool TwoZeroFourEight::movement(int j[4][4]) // check to see if tiles moved
{
	for (int r=0; r<size; r++)
		for (int c=0; c<size; c++)
			if (j[r][c] != game[r][c])
				return true; // if tiles move tile is added

	return false;
}

void TwoZeroFourEight::addRandomTile()
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

	cout << "Enter \'r\' to end the game." << endl;
	addRandomTile();
	addRandomTile();
	printGame();

	while (cmd!='r')
	{
		for (int r=0; r<size; r++)
			for (int c=0; c<size; c++)
				b[r][c] = game[r][c];
		cin >> cmd;// cmd = getch();
		if (cmd == left) // arrow key 68
			moveLeft();
		if (cmd == right) // arrow key 67
		{
			rotateBoard();
			rotateBoard();
			moveLeft();
			rotateBoard();
			rotateBoard();
		}
		if (cmd == down) // arrow key 66
		{
			rotateBoard();
			moveLeft();
			rotateBoard();
			rotateBoard();
			rotateBoard();
		}
		if (cmd == up) // arrow key 65
		{
			rotateBoard();
			rotateBoard();
			rotateBoard();
			moveLeft();
			rotateBoard();
		}
			
		if (movement(b) == true)
			addRandomTile();
		printGame();
		if (gameWin() == true)
		{
			cmd = 'r';
			cout <<"Congrats Johnny"<< endl;
		}
		if (gameOver() == true)
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