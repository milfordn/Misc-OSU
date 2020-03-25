
/***************************************************
** Author: Nicholas Milford
** Date: 9/22/2016
** Description: String sorting algorithm for Assignment 1A
***************************************************/

#include <string>
#include <ctype.h>
#include <stdio.h>
using std::string;

/***************************************************
** Description: Compares strings case-insensitively, 
** 		checking if A is less than B
**
***************************************************/
bool lessThan(string a, string b)
{
	//smallest string, so we don't access an invalid index
	string smallest;

	//assign smallest
	if(a.length() < b.length()) 
	{
		smallest = a;
	}
	else 
	{
		smallest = b;
	}

	//compare char-wise
	for(unsigned i = 0; i < smallest.length(); i++)
	{
		//temp variables for uppercase char values
		char aval, bval;
		aval = toupper(a.at(i));
		bval = toupper(b.at(i));
		if(aval == bval) ;
		else return aval < bval;
	}

	//if strings are equal up to this point, return the smallest.
	//this way, "bit" is less than (and therefore comes before) "bitwise" 
	return smallest != a;
}

/***************************************************
** Description: Sorts strings alphabetically regardless of case
**
***************************************************/
void stringSort(string array[], int size)
{
	int startScan, minIndex;
	string minValue;
	for (startScan = 0; startScan < (size - 1); startScan++)
	{
		minIndex = startScan;
		minValue = array[startScan];

		// Scan from current to end for any lower values
		for (int index = startScan + 1; index < size; index++)
		{
			if(lessThan(array[index], minValue))
			{	
				//Found a new lowest value
				minValue = array[index];
				minIndex = index;
			}
		}

		// swap current and lowest value	
		array[minIndex] = array[startScan];
		array[startScan] = minValue;
	}
}

int main(int argc, char** argv){
	string array[5];
	array[0] = "Zebra";
	array[1] = "aArdVark";
	array[2] = "antelope";
	array[3] = "BetaFish";
	array[4] = "Alpaca";

	stringSort(array, 5);

	for(int i = 0; i < 5; i++){
		printf("%s\n", array[i].c_str());
	}
}
