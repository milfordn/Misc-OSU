
/************************************************
** Author: Nicholas Milford
** Date: October 4 2016
** Description: Compares linear and binary search in terms of time
*************************************************/

#include <algorithm>
#include <time.h>
#include <cstdlib>
#include <cstdio>

using std::sort;

/*************************************************
** Description: Performs a linear search on the list, as copied
**              from the textbook
*************************************************/
int linearSearch(const int list[], int size, int value) 
{ 
	for(int index = 0; index < size; index++)
	{ 
		if (list[index] == value)
		{
			printf("Made %i comparisons\n", index);
			return index;
		}
	}
	printf("Made %i comparisons\n", size - 1);
	return -1;
}

/**************************************************
** Description: Performs a binary search on the list, as copied
**              from the textbook
**************************************************/
int binarySearch(const int array[], int size, int value)
{
	int first = 0;
	int last = size - 1;
	int middle;
	int comparisons = 0;

	while(first <= last)
	{
		comparisons++;
		middle = (first + last) / 2;
		if (array[middle] == value)
		{
			printf("Made %i comparisons\n", comparisons);
			return middle;
		}
		else if (array[middle] > value)
			last = middle - 1;
		else
			first = middle + 1;
	}
	printf("Made %i comparisons\n", comparisons);
	return -1;
}

/**************************************************
** Description: gets a random number with rand and resets
**              the seed with srand
**************************************************/
int getRandom()
{
	//srand(time(NULL));
	int result = rand() % 1000000;
	//printf("Got %i", result);
	return result;
}

/***************************************************
** Description: searches through a list using linear
**              and binary methods, showing information
**              to the console as it goes
***************************************************/
int searchOne(const int array[], int size)
{
	int target = getRandom();

	printf("Linear searching array of size %i for %i\n", size, target);
	int position = linearSearch(array, size, target);
	printf("Linear search found %i at %i\n", target, position);

	printf("Binary searching array of size %i for %i\n", size, target);
	position = binarySearch(array, size, target);
	printf("Binary search found %i at %i\n", target, position);
}

int main()
{
	srand(time(NULL));

	int array1[1000];
	int array2[10000];
	int array3[100000];
	int array4[1000000];

	for(int i = 0; i < 1000000; i++)
	{
		if(i < 1000)
		{
			array1[i] = getRandom();
		}
		if(i < 10000)
		{	
			array2[i] = getRandom();
		}
		if(i < 100000)
		{
			array3[i] = getRandom();
		}
		array4[i] = getRandom();
	}

	sort(array1, array1 + 1000);
	sort(array2, array2 + 10000);
	sort(array3, array3 + 100000);
	sort(array4, array4 + 1000000);

	searchOne(array1, 1000);
	searchOne(array2, 10000);
	searchOne(array3, 100000);
	searchOne(array4, 1000000);
}
