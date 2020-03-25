#include <string>
#include <cstdio>
#include "ValSet.hpp"

using std::string;

void emptyFunction(ValSet<int> vals){}

bool testCopy()
{
	ValSet<int> vals;
	vals.add(1);

	//Invoke copy
	emptyFunction(vals);

	//This line will segfault if the argument was copied memberwise
	vals.add(2);
	return true;
}

bool testAssignment()
{
	ValSet<int> vals;
	
	{
		ValSet<int> vals2 = vals; //use overloaded assignment
	};//deconstruct vals2

	vals.add(1); //this will segfault if vals was copied memberwise
	return true;
}

bool testSize()
{
	ValSet<int> vals;

	int expectedSize = 7;
	
	for(int i = 0; i < expectedSize; i++)
	{
		if(vals.size() != i)
			return false;
		vals.add(i);
	}	

	return vals.size() == 7;
}

bool testEmpty()
{
	bool success = true;
	ValSet<int> vals;
	success = success && vals.isEmpty();

	vals.add(1);
	success = success && !vals.isEmpty();

	vals.remove(1);
	success = success && vals.isEmpty();

	return success;
}

bool testContains()
{
	bool success = true;
	ValSet<int> vals;
	
	vals.add(12);
	success = success && vals.contains(12);
	success = success && !vals.contains(13);
	return success;
}

bool testResize()
{
	ValSet<int> vals;
	
	for(int i = 0; i < 30; i++)
		vals.add(i);
	
	return true; //if something went horribly wrong, this will crash
}

bool testRemove()
{
	ValSet<int> vals;
	
	vals.add(1);
	vals.remove(1);
	return !vals.contains(1) && vals.size() == 0;
}

bool testUnion()
{
	//union between sets [0..9] and [5..14]
	ValSet<int> vals1;
	ValSet<int> vals2;
	
	for(int i = 0; i < 10; i++)
	{
		vals1.add(i);
		vals2.add(i+5);
	}

	ValSet<int> unionVals = vals1.unionWith(vals2);

	//should contain all values [0..14]
	for(int i = 0; i < 15; i++)
		if(!unionVals.contains(i))
			return false;

	return true;
}

bool testIntersect()
{
	ValSet<int> vals1;
	ValSet<int> vals2;
	
	for(int i = 0; i < 10; i++)
	{
		vals1.add(i);
		vals2.add(i+5);
	}

	ValSet<int> intersectVals = vals1.intersectWith(vals2);

	for(int i = 5; i < 10; i++)
		if(!intersectVals.contains(i))
			return false;

	return true;
}

bool testSymmDiff()
{
	ValSet<int> vals1;
	ValSet<int> vals2;
	
	for(int i = 0; i < 10; i++)
	{
		vals1.add(i);
		vals2.add(i+5);
	}

	ValSet<int> symdifVals = vals1.symmDiffWith(vals2);

	for(int i = 0; i < 5; i++)
		if(!symdifVals.contains(i) || !symdifVals.contains(i+10))
			return false;

	return true;
}

int main(int argc, char **argv)
{
	typedef bool (*test)();
	
	test testFunctions[] = {testCopy, testAssignment, testSize, testEmpty, testContains, 
				testResize, testRemove, testUnion, testIntersect, testSymmDiff};
	string names[] = {"Copy", "Assignment", "Size", "Empty", "Contains", "Resize", "Remove",
				"Union", "Intersect", "SymmDiff"};

	for(int i = 0; i < 10; i++)
	{
		const char* cName = names[i].c_str();
		printf("\nTesting %s...\n", cName);
		bool result = testFunctions[i]();
		if(result)
			printf("%s Test Passed!\n", cName);
		else
			printf("%s Test Failed!\n", cName);
	}	
	
	return 0;
}
