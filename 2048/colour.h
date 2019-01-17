// Mark Morra
// 2019

#pragma once
#include <iostream>
#include <windows.h>

using namespace std;

HANDLE cHandle = GetStdHandle(STD_OUTPUT_HANDLE);
int defaultColour = 0x07; //0x07 is the default windows cmd colour

void setDefaultColour(int colour) //allows the default colour to be changed
{
	defaultColour = colour;
}

void printColoredText(string str) //display text with inline colour codes ie the string "&B0Hello" will display Hello writin in black on a cyan background
{
	
	while (str.length() != 0) //loops until the end of the string
	{
		if (str[0] != '&')
		{
			cout << str[0]; //display the next character if it is not an '&'
			str = string(str, 1);
		}
		else if (str.length() == 2) //if the current charcter is an '&' this makes sure there are at least two more characters so you dont get an index out of range
		{
			if (str[1] == '&') //two '&' in a row means revert to default colour
			{
				SetConsoleTextAttribute(cHandle, defaultColour);
			}
			return;
		}
		else if (str.length() < 3)
		{
			return; //if the last character is an & and there are less then 2 characters after it then the & and everything after it is ignored
		}
		else
		{
			if (str[1] == '&') //two '&' in a row means revert to default colour
			{
				SetConsoleTextAttribute(cHandle, defaultColour);
				str = string(str, 2);
			}
			else
			{
				SetConsoleTextAttribute(cHandle, (int)strtol((string(str, 1, 2)).c_str(), NULL, 16)); //coverts the hex value in the string into an int and then sets the console colour
				str = string(str, 3);
			}
		}
	}
}

