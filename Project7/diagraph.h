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

#include <vector> 
#include "stdafx.h"
#include <string>
#include <iostream>
using namespace std;
typedef vector<vector<string>> matrixStr;
typedef vector<vector<int>> matrixInt;

const int INF = 100000;

class Diagraph
{
public:
	vector<string> getSymbolTable(){ return symbolTable; };
	matrixInt weightByPrice(const matrixStr &dataTable);
	matrixInt weightByDist(const matrixStr &dataTable);
	int findSymbol(string port);
	void symbolTableMatch(string port);//
	void printSymbolTable();
	void printBestPrice( const matrixInt &price, const matrixInt &dist);
	void dijkstra(int start, matrixInt priceWeight, matrixInt distWeight, int);
	void printSolution(vector<int>, int n, int start, vector<int>, matrixInt, matrixInt);
	void printSolution2(vector<int>, int n, int start, vector<int>, matrixInt, matrixInt);
	void printGraph(matrixStr);
private:
	vector<string> symbolTable;
};