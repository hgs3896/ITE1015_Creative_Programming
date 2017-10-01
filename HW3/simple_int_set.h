#ifndef __hw03__simple_int_set__
#define __hw03__simple_int_set__

#define MAX_SIZE 1024

class SimpleIntSet
{
private:
	int *mElements;
	int mElementCount;

	void sortElements();
	void uniqueElements();
	SimpleIntSet();

public:
	SimpleIntSet(int *_elements, int _count);
	~SimpleIntSet();

	int *elements() const; // return sorted array
	int elementCount() const;

	SimpleIntSet *unionSet(SimpleIntSet& _operand);
	SimpleIntSet *differenceSet(SimpleIntSet& _operand);
	SimpleIntSet *intersectSet(SimpleIntSet& _operand);

	void printSet();
};

#endif