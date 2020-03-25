/************************************************************
 * Author: Nick Milford
 * Date: November 21 2016
 * Description: Implementation for ValSet.hpp
 * *********************************************************/

#include "ValSet.hpp"
#include <string>

/*********************************************
 * Description: Default Constructor, instantiates
 * 		the array to size 10
 * ******************************************/
template <class T>
ValSet<T>::ValSet()
{
	valueArray = new T[10];
	arraySize = 10;
	numValues = 0;
}

/********************************************
 * Description: Copy constructor, allocates a 
 * 		new array and copies over all
 * 		values
 * *****************************************/
template <class T>
ValSet<T>::ValSet(const ValSet<T> &copy)
{
	valueArray = new T[copy.arraySize];
	arraySize = copy.arraySize;
	numValues = copy.numValues;
	
	for(int i = 0; i < copy.arraySize; i++)
	{
		valueArray[i] = copy.valueArray[i];
	}
}

/*********************************************
 * Description: Assignment overload, Does the same thing
 * 		as the copy constructor, but returns the
 * 		value pointed to by "this"
 * ******************************************/
template<class T>
ValSet<T> ValSet<T>::operator=(const ValSet<T>& copy)
{
	valueArray = new T[copy.arraySize];
	arraySize = copy.arraySize;
	numValues = copy.numValues;
	
	for(int i = 0; i < copy.arraySize; i++)
	{
		valueArray[i] = copy.valueArray[i];
	}

	return *this;
}

/**********************************************
 * Description: Destructor, deallocates the value array
 * *******************************************/
template<class T>
ValSet<T>::~ValSet()
{
	delete[] valueArray;
}

/**************************************************
 * Description: gets the number of values in the set
 * ***********************************************/
template<class T>
int ValSet<T>::size()
{
	return numValues;
}

/******************************************************
 * Description: returns true if the set is empty
 * ***************************************************/
template<class T>
bool ValSet<T>::isEmpty()
{
	return numValues == 0;
}

/************************************************
 * Description: returns true if the given value is
 * 		in the set
 * *********************************************/
template<class T>
bool ValSet<T>::contains(T val)
{
	for(int i = 0; i < numValues; i++)
	{
		if(val == valueArray[i])
			return true;
	}
	return false;
}

/**********************************************
 * Description: adds the given value to the set,
 * 		expands the set capacity if necessary
 * *******************************************/
template<class T>
void ValSet<T>::add(T val)
{
	if(numValues == arraySize)
	{
		T *newArray = new T[arraySize * 2];

		for(int i = 0; i < arraySize; i++)
			newArray[i] = valueArray[i];

		arraySize *= 2;
		delete[] valueArray;
		valueArray = newArray;
	}

	valueArray[numValues] = val;
	numValues++;
}

/**************************************************
 * Description: removes hte given value from the
 * 		set, if it exists
 * ***********************************************/
template<class T>
void ValSet<T>::remove(T val)
{
	bool found = false;
	for(int i = 0; i < numValues; i++)
	{
		if(found)
		{
			valueArray[i-1] = valueArray[i];
			numValues;
		}
		
		found = found || valueArray[i] == val;
	}
	
	if(found) numValues --;
}

/**************************************************
 * Description: Mathematical union (OR) between two sets
 * ***********************************************/
template<class T>
ValSet<T> ValSet<T>::unionWith(ValSet<T> set)
{
	ValSet<T> toReturn;

	for(int i = 0; i < numValues; i++)
	{
		if(!toReturn.contains(valueArray[i]))
			toReturn.add(valueArray[i]);
	}

	for(int i = 0; i < set.numValues; i++)
	{
		if(!toReturn.contains(set.valueArray[i]))
			toReturn.add(set.valueArray[i]);
	}

	return toReturn;
}

/**************************************************
 * Description: Mathematical intersection (AND) between two sets
 * ************************************************/
template<class T>
ValSet<T> ValSet<T>::intersectWith(ValSet<T> set)
{
	ValSet<T> toReturn;

	ValSet<T> *largeSet;
	ValSet<T> *smallSet;	

	if(set.numValues > numValues)
	{
		largeSet = &set;
		smallSet = this;
	}
	else
	{
		largeSet = this;
		smallSet = &set;
	}

	for(int i = 0; i < smallSet->numValues; i++)
	{
		if(largeSet->contains(smallSet->valueArray[i]))
		{
			toReturn.add(smallSet->valueArray[i]);
		}
	}

	return toReturn;
}

/************************************************
 * Description: Mathematical Symmetric Difference
 * 		(XOR) between two sets
 * *********************************************/
template<class T>
ValSet<T> ValSet<T>::symmDiffWith(ValSet<T> set)
{
	ValSet<T> toReturn;
	
	for(int i = 0; i < set.numValues; i++)
	{
		if(!contains(set.valueArray[i]))
			toReturn.add(set.valueArray[i]);
	}

	for(int i = 0; i < numValues; i++)
	{
		if(!set.contains(valueArray[i]))
			toReturn.add(valueArray[i]);
	}

	return toReturn;
}

/************************************************
 * Description: returns all the values in the set
 * 		collected as a vector
 * *********************************************/
template<class T>
vector<T> ValSet<T>::getAsVector()
{
	vector<T> v;
	
	for(int i = 0; i < numValues; i++)
		v.push_back(valueArray[i]);

	return v;
}

template class ValSet<int>;
template class ValSet<char>;
template class ValSet<std::string>;
