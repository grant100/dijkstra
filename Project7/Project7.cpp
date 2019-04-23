// Project7.cpp : Defines the entry point for the console application.
// Author:	   Grant Sowards
// Assignment:	   project 7
// File:	   project7.cpp, diagraph.cpp, diagraph.h
// Instructor:	   Reza Sonati
// Class:	   CS 2420  Section: 001 
// Date Written:   06/25/2015 
// Description:  Dijkstra

// I declare that the source code contained in this assignment was written solely by me.
// I understand that copying any source code, in whole or in part,
// constitutes cheating, and that I will receive a zero on this project
// if I am found in violation of this policy.

#include "stdafx.h"
#include "diagraph.h"
#include <iostream>
#include <cstdlib>
#include <vector>
#include <fstream>
#include <string>
#include <algorithm>
#include <Windows.h>
using namespace std;

const int ONE = 1;
const int TWO = 2;

// Function Name: priceDistIn()
// Purpose:	  check that input from user is valid
// Parameters: none
// Returns:	  int
// Pre-conditions: none	
// Post-conditions: none
int priceDistIn()
{
	int input;
	std::cin >> input;
	while (std::cin.fail() || input > TWO || input < ONE)//if failed, not number
	{
		std::cin.clear();
		std::cin.ignore();
		cout << "\nError... Incorrect input!" << "\nPrice or Distance? 1 = Price 2 = Distance : ";
		std::cin >> input;
	}
	return input;
}

// Function Name: continueInput()
// Purpose:	  check that input from user is valid
// Parameters: none
// Returns:	  int
// Pre-conditions: none	
// Post-conditions: none
int continueInput()
{
	int input;
	std::cin >> input;
	while (std::cin.fail() || input > TWO || input < ONE)//if failed, not number
	{
		std::cin.clear();
		std::cin.ignore();
		cout << "\nError... Incorrect input!" << "\nLoad new file? 1 = Yes 2 = No : ";
		std::cin >> input;
	}
	return input;
}

// Function Name: sourceInput
// Purpose:	  check that input from user is valid
// Parameters: (string source, Diagraph a)
// Returns:	  bool
// Pre-conditions: none	
// Post-conditions: none
bool sourceInput(string source, Diagraph a)
{
	if (a.findSymbol(source) == INF)
	{
		return false;
	}
	else
	{
		return true;
	}
}

// Function Name: Color
// Purpose:	  change color of text
// Parameters: (int color = 7, char* Message = "")
// Returns:	  char*
// Pre-conditions: none	
// Post-conditions: color is different
char* Color(int color = 7, char* Message = "")
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
	return Message;
}
int _tmain(int argc, _TCHAR* argv[])
{
	Diagraph diagraph;
	string fileName;
	string insStr;
	int continue_in;
	int priceDistIn_num;
	ifstream iFile;
	bool isOpen = false;
	bool isContinue = true;


	std::cout <<"Grant Sowards" << "\nCS 2420" << "\nProject 7 Dijkstra" << endl;

	while (isContinue)
	{
		std::cout << "\nEnter file name (include extension), e.g. numbers.txt: " << endl;
		while (!isOpen)
		{
			cin.clear();
			string cinName;
			cin >> cinName;
			string fileName = cinName;
			iFile.open(fileName);
			if (iFile.is_open())
			{
				isOpen = true;
				std::cout << "\nOpening File..." << endl;
			}
			else
			{
				cin.clear();
				std::cout << "Could not open file!" << "\n\nTry Again: ";
			}

		}

		matrixStr data(1, vector<string>(4));
		int i = 0;
		int j = 0;

		while (!iFile.eof() && !iFile.fail())//read in data from file and store in vector
		{
			
			iFile >> insStr;
			if (j < 4)
			{
				data[i][j++] = insStr;//insert into row
			}
			else
			{
				data.resize(++i + 1);//resize vector 
				data[i].resize(4);//resize inner vector 
				j = 0;
				data[i][j++] = insStr;
			}
			if (iFile.fail() && iFile.eof())
			{
				cout << "\Exiting...";
				system("pause");
				exit(1);
			}
		}

		for (int x = 0; x < data.size(); x++)//get data out to create verticies
		{
			for (int y = 0; y < 2; y++)
			{
				diagraph.symbolTableMatch(data[x][y]);
			}
		}

		iFile.close();
		diagraph.printGraph(data);//prints flights
		matrixInt b = diagraph.weightByDist(data);//creates weighted matrix by distance
		matrixInt a = diagraph.weightByPrice(data);//creates weighted matrix by price
		string quit;
	
		while (quit != "Y")
		{
			cout << "\nEnter Three Letter Flight Code e.g. DEN, PHX...";
			cout << "\n-----------------------------------------------";
			quit = "";
			bool srcInput = false;
			string src= "";
			while (srcInput == false)
			{
				cout << "\n\nSOURCE   : ";
				cin.clear();
				cin >> src;
				if (sourceInput(src, diagraph) != true)//error checking for source input
				{
					cout << "Inccorect source... Try again...";
				}
				else
				{
					srcInput = true;
				}
			}
			
			int start = diagraph.findSymbol(src);//get starting index based on source
			cout << "\nSee Shortest Path by Price, or Distance? 1 = Price 2 = Distance: ";
			priceDistIn_num = priceDistIn();
			if (priceDistIn_num == ONE)
			{
				cout << "\nBest Price Flight Paths from (" << src << "):" << endl;
				diagraph.dijkstra(start, a, b, priceDistIn_num);
				data.clear();
				cout << "\nQuit? (Y/N): ";
				cin.clear();	
			}
			if (priceDistIn_num == TWO)
			{
				cout <<"\nShortest Flight Paths from (" << src << "):" << endl;
				diagraph.dijkstra(start, b, a, priceDistIn_num);
				data.clear();
				cout << "\nQuit? (Y/N): ";
				cin.clear();				
			}
			cin >> quit;
		    transform(quit.begin(), quit.end(), quit.begin(), ::toupper);//upper case input for error checking
		}
		
		cout << "\nLoad a new file? 1 = Yes 2 = No: ";
		continue_in = continueInput();//check for continuation
		if (continue_in == ONE)
		{
			isContinue = true;
			isOpen = false;
		}
		else if (continue_in == TWO)
		{
			isContinue = false;
		}
	}
	return 0;
}

