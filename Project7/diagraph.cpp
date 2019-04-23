
#include "stdafx.h"
#include "diagraph.h"
#include <stdlib.h>    
#include <vector>
#include <algorithm>
#include <iterator>
#include <Windows.h>//for color

// Function Name: Color1
// Purpose:	  change color of text
// Parameters: (int color = 7, char* Message = "")
// Returns:	  char*
// Pre-conditions: none	
// Post-conditions: color is different
char* Color1(int color = 7, char* Message = "")
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
	return Message;
}

// Function Name: symbolTableMatch
// Purpose:	  map source string to  symbol table
// Parameters: (string port)
// Returns:	  void
// Pre-conditions: none	
// Post-conditions: source string added to table
void Diagraph::symbolTableMatch(string port)
{
	if (findSymbol(port) == INF)
	{
		symbolTable.push_back(port);
	}
}

// Function Name: printSolution
// Purpose:	 print out results of dikjstra's algorithm for price weight path
// Parameters: (vector<int> dist, int n, int start, vector<int>p, matrixInt priceWeight, matrixInt distWeight)
// Returns:	  void
// Pre-conditions: none	
// Post-conditions: none
void Diagraph::printSolution(vector<int> dist, int n, int start, vector<int>p, matrixInt priceWeight, matrixInt distWeight)
{
	vector<string> data1;
	vector<string> data2;
	vector<int>data3;
	vector<int>data4;
	vector<int>data5;
	int dest_holder;
	for (int i = 0; i < p.size(); i++)
	{
		string end = symbolTable[i];
		string src;
		int counter = i;
		dest_holder = i;
		int sum = 0;

		while (dest_holder != start)//this section recreates the path used in dijkstra method from vector p
		{
			data1.push_back(symbolTable[p[dest_holder]]);//source
			data2.push_back(symbolTable[dest_holder]);//destination
			data3.push_back(priceWeight[p[dest_holder]][dest_holder]);//price weight for edge
			data4.push_back(distWeight[p[dest_holder]][dest_holder]);//distance weight for edge
			dest_holder = p[dest_holder];//set destination to value of source for next iteration (backwards)
		}

		src = symbolTable[dest_holder];
		cout << Color1(9, "\n////////////////////////////////////////////////////////");
		Color1(15);
		cout << "\n\n        ********" << src << "--->" << end << "********";
		cout << "\nSource " << "Destination "<<"  Cost"<<"    Mileage";
		cout << "\n--------------------------------------------------------";
		int count =1;
		for (int j = data1.size() - 1; j >= 0; j--) // read data in loop in reverse to get path correct order
		{	
			
			cout << "\n"<<count<<".)";
			cout <<"  "<< data1[j] << "----->" << data2[j]<<"       "<<data3[j]<<"        "<<data4[j];
			cout << "\n--------------------------------------------------------";
			data5.push_back(data4[j]);
			count++;
		}
		for (int i = 0; i < data5.size(); i++)//sum value for total display
		{
			sum += data5[i];
		}
		Color1(14);
		for (int i = 0; i < 8; i++)
		{
			if (i == counter)
			{
				cout << "\n\nTOTAL Dollars: $" << dist[counter] <<"     TOTAL Mileage: "<<sum<< endl;
				cout << Color1(9, "\n////////////////////////////////////////////////////////");
				Color1();
				cout << "\n\n";
				//system("pause");
			}
			
		}

		data1.clear();
		data2.clear();
		data3.clear();
		data4.clear();
		data5.clear();
	}			
}

// Function Name: printSolution2
// Purpose:	 print out results of dikjstra's algorithm for distance weight path
// Parameters: (vector<int> dist, int n, int start, vector<int>p, matrixInt distWeight, matrixInt priceWeight)
// Returns:	  void
// Pre-conditions: none	
// Post-conditions: none
void Diagraph::printSolution2(vector<int> dist, int n, int start, vector<int>p, matrixInt distWeight, matrixInt priceWeight)
{
	vector<string> data1;
	vector<string> data2;
	vector<int>data3;
	vector<int>data4;
	vector<int>data5;
	int dest_holder;
	for (int i = 0; i < p.size(); i++)//this section recreates the path used in dijkstra method from vector p
	{
		string end = symbolTable[i];
		string src;
		int counter = i;
		dest_holder = i;
		int sum = 0;

		while (dest_holder != start)//work backwards from destination to start
		{
			data1.push_back(symbolTable[p[dest_holder]]);//source
			data2.push_back(symbolTable[dest_holder]);//destination
			data3.push_back(distWeight[p[dest_holder]][dest_holder]);//distance weight for edge
			data4.push_back(priceWeight[p[dest_holder]][dest_holder]);//price weight for edge
			dest_holder = p[dest_holder];//set destination to value of source for next iteration (backwards)
		}

		src = symbolTable[dest_holder];
		cout << Color1(12, "\n////////////////////////////////////////////////////////");
		Color1(15);
		cout << "\n\n          ********" << src << "->" << end << "********";
		cout << "\nSource " << "Destination " << "  Cost" << "    Mileage";
		cout << "\n--------------------------------------------------------";
		int count = 1;
		for (int j = data1.size() - 1; j >= 0; j--)//read data in loop in reverse to get path correct order
		{

			cout << "\n" << count << ".)";
			cout << "  " << data1[j] << "----->" << data2[j] << "       " << data3[j] << "        " << data4[j];
			cout << "\n--------------------------------------------------------";
			data5.push_back(data3[j]);
			count++;
		}
		for (int i = 0; i < data5.size(); i++)//sum value for total display
		{
			sum += data5[i];
		}
		Color1(14);
		for (int i = 0; i < 8; i++)
		{
			if (i == counter)
			{
				cout << "\n\nTOTAL Dollars: $" << sum << "     TOTAL Mileage: " <<dist[counter] << endl;
				cout << Color1(12, "\n////////////////////////////////////////////////////////");
				Color1();
				cout << "\n\n";
				//system("pause");
			}
		}

		data1.clear();
		data2.clear();
		data3.clear();
		data4.clear();
		data5.clear();
	}
}

// Function Name: getP
// Purpose:	 generate p vector for use in dijkstra's algorithm
// Parameters: (vector<int> a, int start)
// Returns:	  vector<int>
// Pre-conditions: none	
// Post-conditions: adds edges to p vector from vertex d
vector<int> getP(vector<int> a, int start)
{
	vector<int> p;
	for (int i = 0; i < a.size(); i++)
	{
		if (a[i] != INF)//if d index not equal to INF it is an edge add it
		{
			 p.push_back(start);
		}
		else//else set to zero
		{
			p.push_back(0);
		}
	}
	return p;
}
// Function Name: getI
// Purpose:	 gets the index with the least value from vector d
// Parameters: (vector<int> &d, bool reached[])
// Returns:	  int
// Pre-conditions: none	
// Post-conditions: none
int getI(vector<int> &d, bool reached[])
{
	int min = INF, min_num;

	for (int i = 0; i < 8; i++)
	{
		if (reached[i] == false && d[i] <= min)//find minimum value then return index only if it hasn't been reached
		{
			min = d[i];
			min_num = i;
		}
	}
	return min_num;
}

// Function Name: min_1
// Purpose:	 find the minimum of two values
// Parameters: (int a, int b)
// Returns:	  int
// Pre-conditions: none	
// Post-conditions: none
int min_1(int a, int b)
{
	if (a < b)
	{
		return a;
	}
	else
	{
		return b;
	}
}

// Function Name: dijkstra
// Purpose:	 determines shortest path between vertexes based on weight of edge
// Parameters: (int start, matrixInt priceWeight, matrixInt distWeight, int priceDistIn_num)
// Returns:	  void
// Pre-conditions: none	
// Post-conditions: calls print function
void Diagraph::dijkstra(int start, matrixInt priceWeight, matrixInt distWeight, int priceDistIn_num)
{
	vector<int>d;
	vector<int>p;
	vector<int>l;
	bool reached[8];
	for (int i = 0; i < 8; i++)//initialize d vector and reached array
	{
		d.push_back(priceWeight[start][i]);
		reached[i] = false;
	}
	p = getP(d, start);
	d[start] = 0;
	int counter = 0;
	int size = d.size();
	while (counter < size)//continue for the entire size of d vector
	{
		int i = getI(d, reached);//return index that contains minimum unreached value
		reached[i] = true;
		for (int j = 0; j < size; j++)
		{
			int temp = d[j];
			if (!reached[j])
			{
				d[j] = min_1(d[j], d[i] + priceWeight[i][j]);//select least value and store in d vector
				if (d[j] != temp)//check if value changed
				{
					p[j] = i;//store index into p vector to maintain path info
					//l.push_back(j);
				}
			}

		}
		counter++;
	}
	if (priceDistIn_num == 1)//for price weight
	{
		printSolution(d, d.size(), start, p, priceWeight, distWeight);
	}
	if (priceDistIn_num == 2)//for distance weight
	{
		printSolution2(d, d.size(), start, p, distWeight, priceWeight);
	}
}

// Function Name: printGraph
// Purpose:	 sorts input data alphabetically and displays
// Parameters: (matrixStr data)
// Returns:	  void
// Pre-conditions: none	
// Post-conditions: none
void Diagraph::printGraph(matrixStr data)
{
	//insertion sort baby
	int i, j;
	vector<string> tmp;
	for (i = 1; i < data.size(); i++)
	{
		j = i;
		while (j > 0 && data[j - 1][0] > data[j][0]) //begin comparing prior position to next sequential position (pushes smallest number to front)
		{
			tmp = data[j];
			data[j] = data[j - 1];
			data[j - 1] = tmp;
			j--;
		}
	} 

	cout << "\nDirect Flights";
	cout << "\nSource   Dest   Mileage   Cost";
	cout << "\n--------------------------------"<<endl;
	for (int i = 0; i < data.size(); i++)
	{
		for (int j = 0; j < 4; j++)
		{
			cout << data[i][j]<<"      ";
			
		}
		cout << "\n";
	}
}
// Function Name: weightByPrice
// Purpose:	 calculate the weight of edges by price
// Parameters: (const matrixStr &data)
// Returns:	  matrixInt
// Pre-conditions: none	
// Post-conditions: weighted vector created
matrixInt Diagraph::weightByPrice(const matrixStr &data)
{
	int source;
	int price;
	int dest;
	int size = symbolTable.size();
	matrixInt weight(size, vector<int>(size));
	string source_str;
	string dest_str;
	
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			weight[i][j] = INF;
		}
	}

	for (int a = 0; a < data.size(); a++)
	{
		source_str = data[a][0];
		source = findSymbol(source_str);
		dest_str = data[a][1];
		dest = findSymbol(dest_str);//returns i
		price = stoi(data[a][3]);
		weight[source][dest] = price;
	}
	return weight;
}

// Function Name: weightByDist
// Purpose:	 calculate the weight of edges by distance
// Parameters: (const matrixStr &data)
// Returns:	  matrixInt
// Pre-conditions: none	
// Post-conditions: weighted vector created
matrixInt Diagraph::weightByDist(const matrixStr &data)
{
	int mile;
	int dest;
	int source;
	int size = symbolTable.size();
	string source_str;
	string dest_str;
	matrixInt weight(size, vector<int>(size));

	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			weight[i][j] = INF;
		}
	}

	for (int a = 0; a < data.size(); a++)
	{
		source_str = data[a][0];
		source = findSymbol(source_str);
		dest_str = data[a][1];
		dest = findSymbol(dest_str);
		mile = stoi(data[a][2]);
		weight[source][dest] = mile;
	}
	return weight;
}

// Function Name: findSymbol
// Purpose:	find the index value for a source string
// Parameters: (string port)
// Returns:	  int
// Pre-conditions: none	
// Post-conditions: none
int Diagraph::findSymbol(string port)
{
	if(symbolTable.size() == 0)
	{
		return INF;
	}
	else
	{
		for (int i = 0; i < symbolTable.size(); i++)
		{
			if (symbolTable[i] == port)
			{
				return i;
			}
		}
		return INF;
	}
}

// Function Name: printSymbolTable
// Purpose:	print data in symbol vector
// Parameters: none
// Returns:	  void
// Pre-conditions: none	
// Post-conditions: none
void Diagraph::printSymbolTable()
{
	if (symbolTable.size() == 0)
	{
		cout << "\nNo Items in table!";
	}
	else
	{
		for (int i = 0; i < symbolTable.size(); i++)
		{
			cout << "\n" << symbolTable[i];
		}
	}
}
