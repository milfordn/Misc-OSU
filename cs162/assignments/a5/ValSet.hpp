/********************************************************************
 * Author: Nick Milford
 * Date: November 21 2016
 * Description: Header for a ValSet, an abstract data type representing a 
 * 		mathematical set of values
 * *****************************************************************/

#include <vector>
using std::vector;

template <class T> 
class ValSet
{
private:
	T *valueArray;
	int arraySize;
	int numValues;
public:
	ValSet();
	ValSet(const ValSet<T>&);
	ValSet operator=(const ValSet&);
	~ValSet();
	int size();
	bool isEmpty();
	bool contains(T);
	void add(T);
	void remove(T);
	ValSet<T> unionWith(ValSet<T>);
	ValSet<T> intersectWith(ValSet<T>);
	ValSet<T> symmDiffWith(ValSet<T>);
	vector<T> getAsVector();
};
