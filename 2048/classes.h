// Mark Morra
// 2019

#pragma once
#include "stdafx.h"
#include "math.h"
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;


class Tile
{
public:
	Tile(int _value);
	Tile();
	~Tile();

	int getsetValue();
	bool getsetValue(int newValue);

private:
	int value;
};

Tile::Tile()
{
	value = 0;
}

Tile::Tile(int _value)
{
	value = _value;
}

Tile::~Tile()
{
}

int Tile::getsetValue()
{
	return value;
}

bool Tile::getsetValue(int newValue)
{
	value = newValue;
	return true;
}

class Colours
{
public:
	Colours();
	~Colours();

	string getsetEmptyC();
	void getsetEmptyC(string);
	string getsetDefaultC();
	void getsetDefaultC(string);
	string getsetColours(int);
	void getsetColours(string*, int);


private:
	string emptyC, defaultC;
	string* colours;
	int coloursSize = 0;
};

Colours::Colours()
{
}

Colours::~Colours()
{
}

string Colours::getsetEmptyC()
{
	return emptyC;
}

void Colours::getsetEmptyC(string str)
{
	emptyC = str;
}

string Colours::getsetDefaultC()
{
	return defaultC;
}

void Colours::getsetDefaultC(string str)
{
	defaultC = str;
}

inline string Colours::getsetColours(int index)
{
	if (index < 0 || index > coloursSize - 1)
	{
		return defaultC;
	}
	else
	{
		return colours[index];
	}
}

void Colours::getsetColours(string *newColours, int size)
{

	coloursSize = size;

	delete colours;
	colours = new string[coloursSize];

	for (int i = 0; i < coloursSize; i++)
	{

		colours[i] = newColours[i];

	}

}

class Grid
{
public:
	Grid(int width, int hight);
	~Grid();

	bool addTile(int value);
	bool deleteTile(int x, int y);
	bool slideBoard(char direction);
	bool noMoreMoves();
	int getscore();
	string renderGrid();
	string renderScore();

	Colours colours;

private:
	int width, height;
	int score;
	Tile ***grid;
	bool slideTile(int x, int y, char direction);
};

Grid::Grid(int _width, int _height)
{
	width = _width;
	height = _height;

	grid = new Tile**[width]; //make it a list of pojters

	for (size_t i = 0; i < width; i++)
	{
		grid[i] = new Tile*[height];

		for (int j = 0; j < height; j++)
		{
			grid[i][j] = nullptr;
		};
	}
}

Grid::~Grid()
{

	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < height; j++)
		{
			if (grid[i][j] != nullptr)
			{
				grid[i][j]->~Tile();
			}
		}
	}

}

bool Grid::addTile(int value)
{

	vector<Tile**> empty; //a list of all the empty spaces in grid

	for (int i = 0; i < height; i++) //creates the list empty
	{
		for (int j = 0; j < width; j++)
		{
			if (grid[j][i] == nullptr)
			{
				empty.push_back(&(grid[j][i]));
			}
		}
	}

	if (empty.size() <= 0)
	{
		return false;
	}



	*(empty[rand() % empty.size()]) = new Tile(value);

	return true;

}

bool Grid::deleteTile(int x, int y)
{
	if (x > width or y > height)
	{
		throw "The x or y value givin to deleteTile is out of bounds";
	}
	else if (grid[x][y] == nullptr)
	{
		throw "Tried deleting a tile that dosent exist";
	}
	else
	{
		grid[x][y]->~Tile();
		grid[x][y] = nullptr;
	}
}

string Grid::renderGrid()
{
	string render = "";

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			render += ((grid[j][i] == nullptr) ? colours.getsetEmptyC() : colours.getsetColours(int(log2f(grid[j][i]->getsetValue())))) + "+----+";
		}
		render += "\n";

		for (int j = 0; j < width; j++)
		{
			render += ((grid[j][i] == nullptr) ? colours.getsetEmptyC() : colours.getsetColours(int(log2f(grid[j][i]->getsetValue())))) + "|    |";
		}
		render += "\n";

		for (int j = 0; j < width; j++)
		{
			if (grid[j][i] == nullptr)
			{
				render += colours.getsetEmptyC() + "|    |";
			}
			else
			{
				char strNumber[5];
				sprintf_s(strNumber, 5, "%4d", grid[j][i]->getsetValue());
				render += colours.getsetColours(int(log2f(grid[j][i]->getsetValue()))) + "|" + string(strNumber) + "|";
			}
		}
		render += "\n";

		for (int j = 0; j < width; j++)
		{
			render += ((grid[j][i] == nullptr) ? colours.getsetEmptyC() : colours.getsetColours(int(log2f(grid[j][i]->getsetValue())))) + "|    |";
		}
		render += "\n";

		for (int j = 0; j < width; j++)
		{
			render += ((grid[j][i] == nullptr) ? colours.getsetEmptyC() : colours.getsetColours(int(log2f(grid[j][i]->getsetValue())))) + "+----+";
		}
		render += "\n";
	}
	render += "&&";
	return render;

}

string Grid::renderScore()
{
	string str = "";

	str += "&&+" + string(max(numDigits(score) + 2, 5), '~') + "+\n";
	str += "|SCORE" + string(max(numDigits(score) -3, 0), ' ') + "|\n";
	str += "|" + string(max(4 - numDigits(score), 1), ' ') + to_string(score) + " |\n";
	str += "&&+" + string(max(numDigits(score) + 2, 5), '~') + "+";

	return str;
}

bool Grid::slideTile(int x , int y, char direction)
{
	int newx = x, newy = y;
	switch (direction)
	{
	case 'U':
	case 'u':
		do
		{
			newy--;
		} while ((newy > 0) && (grid[x][newy] == nullptr));
		
		if (newy < 0) { newy = 0; }

		if (newy == y) { return false; }

		if (grid[x][newy] == nullptr)
		{
			grid[x][newy] = grid[x][y];
			grid[x][y] = nullptr;
		}
		else if (grid[x][y]->getsetValue() == grid[x][newy]->getsetValue())
		{
			deleteTile(x, y);
			grid[x][newy]->getsetValue(grid[x][newy]->getsetValue() * 2);
			score += grid[x][newy]->getsetValue();
		}
		else if (y == (newy + 1))
		{
			return false;
		}
		else
		{
			grid[x][newy + 1] = grid[x][y];
			grid[x][y] = nullptr;
		}
		return true;
	case 'D':
	case 'd':
		do
		{
			newy++;
		} while ((newy < (height - 1)) && (grid[x][newy] == nullptr));

		if (newy > (height - 1)) { newy = (height - 1); }

		if (newy == y) { return false; }

		if (grid[x][newy] == nullptr)
		{
			grid[x][newy] = grid[x][y];
			grid[x][y] = nullptr;
		}
		else if (grid[x][y]->getsetValue() == grid[x][newy]->getsetValue())
		{
			deleteTile(x, y);
			grid[x][newy]->getsetValue(grid[x][newy]->getsetValue() * 2);
			score += grid[x][newy]->getsetValue();
		}
		else if (y == (newy - 1))
		{
			return false;
		}
		else
		{
			grid[x][newy - 1] = grid[x][y];
			grid[x][y] = nullptr;
		}
		return true;
	case 'L':
	case 'l':
		do
		{
			newx--;
		} while ((newx > 0) && (grid[newx][y] == nullptr));

		if (newx < 0) { newx = 0; }

		if (newx == x) { return false; }

		if (grid[newx][y] == nullptr)
		{
			grid[newx][y] = grid[x][y];
			grid[x][y] = nullptr;
		}
		else if (grid[x][y]->getsetValue() == grid[newx][y]->getsetValue())
		{
			deleteTile(x, y);
			grid[newx][y]->getsetValue(grid[newx][y]->getsetValue() * 2);
			score += grid[newx][y]->getsetValue();
		}
		else if (x == (newx + 1))
		{
			return false;
		}
		else
		{
			grid[newx + 1][y] = grid[x][y];
			grid[x][y] = nullptr;
		}
		return true;
	case 'R':
	case 'r':
		do
		{
			newx++;
		} while ((newx < (width - 1)) && (grid[newx][y] == nullptr));

		if (newx > (width - 1)) { newx = (width - 1); }

		if (newx == x) { return false; }

		if (grid[newx][y] == nullptr)
		{
			grid[newx][y] = grid[x][y];
			grid[x][y] = nullptr;
		}
		else if (grid[x][y]->getsetValue() == grid[newx][y]->getsetValue())
		{
			deleteTile(x, y);
			grid[newx][y]->getsetValue(grid[newx][y]->getsetValue() * 2);
			score += grid[newx][y]->getsetValue();
		}
		else if (x == (newx - 1))
		{
			return false;
		}
		else
		{
			grid[newx - 1][y] = grid[x][y];
			grid[x][y] = nullptr;
		}
		return true;
	}

	return false;
}

bool Grid::slideBoard(char direction)
{
	bool didAnythingMove = false;

	switch (direction)
	{
	case 'U':
	case 'u':
		for (int x = 0; x < width; x++)
		{
			for (int y = 0; y < height; y++)
			{
				if (grid[x][y] != nullptr) { didAnythingMove += slideTile(x, y, direction); }
			}
		}
		break;
	case 'D':
	case 'd':
		for (int x = 0; x < width; x++)
		{
			for (int y = (height - 1); y >= 0; y--)
			{
				if (grid[x][y] != nullptr) { didAnythingMove += slideTile(x, y, direction); }
			}
		}
		break;
	case 'L':
	case 'l':
		for (int y = 0; y < height; y++)
		{
			for (int x = 0; x < width; x++)
			{
				if (grid[x][y] != nullptr) { didAnythingMove += slideTile(x, y, direction); }
			}
		}
		break;
	case 'R':
	case 'r':
		for (int y = 0; y < height; y++)
		{
			for (int x = (width - 1); x >= 0; x--)
			{
				if (grid[x][y] != nullptr) { didAnythingMove += slideTile(x, y, direction); }
			}
		}
	}

	return didAnythingMove;
}

bool Grid::noMoreMoves()
{
	bool emptyTile = false;

	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < height; j++)
		{
			emptyTile += (grid[i][j] == nullptr);
		}
	}

	if (emptyTile == true)
	{
		return false;
	}
	else
	{

		for (int i = 0; i < width - 1; i++)
		{
			for (int j = 0; j < height; j++)
			{
				if (grid[i][j] != nullptr && grid[i + 1][j] != nullptr)
				{
					if (grid[i][j]->getsetValue() == grid[i + 1][j]->getsetValue()) { return false; }
				}
			}
		}

		for (int i = 0; i < width; i++)
		{
			for (int j = 0; j < height - 1; j++)
			{
				if (grid[i][j] != nullptr && grid[i][j+1] != nullptr)
				{
					if (grid[i][j]->getsetValue() == grid[i][j+1]->getsetValue()) { return false; }
				}
			}
		}

	}

	return true;
}

int Grid::getscore()
{
	return score;
}

