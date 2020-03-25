/**************************************************
** Author: Nick Milford
** Date: September 27 2016
** Description: Sums the elements of an array
**************************************************/

#include <cstdio>
	
/**************************************************
** Description: Recursive helper function for arraySum(int[], int)
**
**************************************************/
double arraySum(double array[], int size, int loc) {
	// End condition: we have reached the end of the array
	if (loc == size)
		return 0;
				
	// current + (evaluate rest)
	return array[loc] + arraySum(array, size, loc+1);
}

/**************************************************
** Description: Top level function to sum values in an array
**
**************************************************/
double arraySum(double array[], int size) {
	//call the helper function with initial conditions
	return arraySum(array, size, 0);
}

int main(int argc, char** argv){
	double nums[10];
	double checkSum;

	for(int i = 0; i < 10; i++){
		double num = (i * i);
		nums[i] = num;
		checkSum += num;
	}

	printf("%f\n%f\n", arraySum(nums, 10), checkSum);
}
