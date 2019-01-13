#pragma once
#include <iostream>
#include <windows.h>

using namespace std;

HANDLE cHandle = GetStdHandle(STD_OUTPUT_HANDLE);
int defaultColour = 0x07;

void setDefaultColour(int colour)
{
	defaultColour = colour;
}

void printColoredText(string str)
{
	
	while (str.length() != 0)
	{
		if (str[0] != '&')
		{
			//if (str[0] == '\n') { Sleep(10); }
			cout << str[0];
			str = string(str, 1);
		}
		else if (str.length() == 2)
		{
			if (str[1] == '&')
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
			if (str[1] == '&')
			{
				SetConsoleTextAttribute(cHandle, defaultColour);
				str = string(str, 2);
			}
			else
			{
				SetConsoleTextAttribute(cHandle, (int)strtol((string(str, 1, 2)).c_str(), NULL, 16));
				str = string(str, 3);
			}
		}
	}
}

