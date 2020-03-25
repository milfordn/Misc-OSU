#include <vector>
#include <iostream>
#include <string>
#include <cstdlib>

using std::vector;
using std::cout;
using std::endl;
using std::string;

template <class T> void printVec(vector<T> &v)
{
	typename vector<T>::iterator iter;
	for(iter = v.begin(); iter != v.end(); iter++)
		cout << *iter << endl;
}

template <class T> void shuffleVec(vector <T> &v)
{
	typename vector<T>::iterator iter;

	//moving elements at random locations size * 3 times
	//should make sure that most elements are swapped
	for(int i = 0; i < v.size() * 3; i++)
	{
		//copy a random element to the back of the vector
		int r1 = rand() % v.size();
		v.push_back(v.at(r1));
		
		//erase the old element
		v.erase(v.begin() + r1);
	}
}

int main(int, char**)
{
	//seed
	srand(time(NULL));
	
	vector<int> v1;
	vector<double> v2;
	vector<string> v3;

	for(int i = 0; i < 6; i++)
	{
		v1.push_back(i);
	}

	for(double d = 0.6; d < 10; d *= 2)
	{
		v2.push_back(d);
	}

	string s;
	for(char c = 'a'; c < 'f'; s += c, c++)
	{
		v3.push_back(s);
	}

	cout << "===== Vector 1 =====" << endl;
	printVec<int>(v1);
	cout << endl << "===== Vector 2 =====" << endl;
	printVec<double>(v2);
	cout << endl << "===== Vector 3 =====" << endl;
	printVec<string>(v3);

	
	shuffleVec(v1);
	shuffleVec(v2);
	shuffleVec(v3);
	

	cout << endl << endl << "===== Vector 1 =====" << endl;
	printVec<int>(v1);
	cout << endl << "===== Vector 2 =====" << endl;
	printVec<double>(v2);
	cout << endl << "===== Vector 3 =====" << endl;
	printVec<string>(v3);

	return 0;
} 
