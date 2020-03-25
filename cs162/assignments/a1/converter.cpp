/***************************************************
** Author: Nicholas Milford
** Date: September 23 2016
** Description: Binary conversion functions for A2
***************************************************/ 

#include <string>
#include <stdio.h>

using std::string; 

/***************************************************
** Description: Recursively converts a binary string to a decimal number
**
***************************************************/
int binToDec(string binary) {
	//Get the least significant bit 
	int extractedValue = binary.at(binary.length() - 1) - '0';
	
	//remove the last bit from the string 
	binary = binary.substr(0, binary.length() - 1);
	
	//termination condition: nothing left to read 
	if(binary.length() == 0)
		return extractedValue;
	else return extractedValue + binToDec(binary) * 2;
}

/***************************************************
** Description: Recursively converts a decimal number to a binary string
** 
***************************************************/
string decToBin(int number){
	//variable for the LSB
	string bit;

	//Extract a least significant bit  
	if(number % 2 == 0)
		bit = "0";
	else bit = "1";

	number /= 2;

	//termination condition: we have reduced the number to zero 
	if(number == 0)
		return bit;
	else return decToBin(number) + bit;
}

int main(int argc, char** argv){
	printf("%i\n", binToDec("11111"));
	printf("%i\n", binToDec("10000"));
	printf("%s\n", decToBin(100).c_str());
	printf("%s\n", decToBin(32).c_str());
}
