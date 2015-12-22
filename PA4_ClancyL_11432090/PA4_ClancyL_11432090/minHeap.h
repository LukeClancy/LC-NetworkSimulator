#pragma once
#ifndef minHeapisDef
#define minHeapisDef
#include "vector.h"//Vector.h written and provided by Adam Carter CPTS teacher at Washington State University

//!class requires templated item to have a getOrder() function.!

using namespace std;
template <typename T>
class minHeap:Vector<T>
{
	/*
	The first element in my minHeap is left empty. the second is the smallest in the class, defined as such by the function getSize()
	that I assume the Templated Type T has. Once you remove the smallest, the next smallest will replace it. And if you add a class 
	with a smaller order value then those allready existing to the class, it will rise to the top. The children of a node in this class 
	are considered to be at the positionOfParent*2 and positionOfParent*2+1, and will allways have a bigger value than the parent. This
	gives the class a treelike structure dispite the fact that its in a vector.

	There may be some functions in My teachers class, Vector, that you will see. However using these functions may cause malfunctions in the
	minHeap class. Please only use the functions defined in the minHeap class.
	
	This function assumes that the templated class T has a method getOrder() which it uses to find the order of the class. This is not ideal,
	but I do not, at this time, have the ability to let the templated class T define the way minHeap obtains the order. I would be interested
	to find out though!
	*/
private:
	virtual void addElement(T item)
	{
		//check capacity before adding item to the vector
		checkCapacity(getSize() + 2);
		push(item);
	}
	int traverseLeft(int position)
	{
		T temp = (*this)[position];
		(*this)[position] = (*this)[position * 2]; //smallest of options is left branch, traverse left
		(*this)[position * 2] = temp;
		position = position * 2;
		return position;
	}
	int traverseRight(int position)
	{
		T temp = (*this)[position];
		(*this)[position] = (*this)[position * 2 + 1]; //smallest of options is left branch, traverse left
		(*this)[position * 2 + 1] = temp;
		position = position * 2 + 1;
		return position;
	}
public:
	minHeap(T firstEl) : Vector<T>() //this constructor adds the first element in the minHeap.
	{
		addElement(T());
		addElement(firstEl);
	}
	minHeap():Vector<T>()
	{
		addElement(T());
	}
	~minHeap()
	{
		//any memory used is deleted by the parent function Vector 
	}

	void print()
	{
		//prints the minHeap. Assumes that the classes have a print function. Used for debuging. Comment out if issues arise.
		int x = 0;
		for (x = 0; x < _number_of_items; x++)
		{
			(*this)[x].print();
		}
		cout << endl;
		return;
	}
	
	int add(T object)
	{
		//adds to the end of vector, and moves its way up the tree by replacing its parent at position/2 until its parent is smaller than it.
		//(or its at the top).
		int position;
		addElement(object);
		position = getSize() - 1;
		T temp;
		while (position > 1 && (*this)[position].getOrder() < (*this)[position / 2].getOrder())
		{
			temp = (*this)[position / 2];
			(*this)[position / 2] = (*this)[position];
			(*this)[position] = temp;
			position = position / 2;
		}
		return position;
	}
	int getHeapSize()
	{
		return getSize() - 1;
	}
	T getMin()
	{
		if (getSize() == 1)//checking for empty list (except for [0])
		{
			return (*this)[0]; //nullcase
		}
		return (*this)[1];
	}

	T removeMin()
	{
		/*
		replaces the minimum value of the tree with the last value in the vector. From there it traverses downward until all children
		(found using position*2 and position*2+1) are larger than it. This makes removals O(log(n))
		*/
		if (this->getSize() == 1)//checking empty list
		{
			return (*this)[0];//returns nullcase for whatever class, nullcase defined in constructor
		}
		else if(this->getSize() == 2)//checking for list of size one
		{
			return (*this).pop();
		}

		T returnThis = (*this)[1]; //return the job deleted.
		(*this)[1] = (*this).pop();

		int position = 1;
		bool goFurther = true;
		int left = false;
		int right = false;
		
		while (goFurther == true)
		{
			left = false;
			right = false;
			if (position*2 < getSize() && (*this)[position * 2].getOrder() < (*this)[position].getOrder())//checks for wheather left branch is null ptr, and if it is less than parent
			{
				left = true;
			}
			if (position*2+1 < getSize() && (*this)[position * 2+1].getOrder() < (*this)[position].getOrder())//checks for wheather right branch is null ptr, and if it is less than parent
			{
				right = true;
			}

			if (left && right)//if both are smaller find smallest
			{
				if ((*this)[position * 2].getOrder() < (*this)[position * 2 + 1].getOrder())
				{
					position = traverseLeft(position);
				}
				else
				{
					position = traverseRight(position);
				}
			}
			else if (left)//only one is smaller, go that way.
			{
				position = traverseLeft(position);
			}
			else if (right)
			{
				traverseRight(position);
			}
			else
			{
				goFurther = false;
			}

		}

		return returnThis;//success
	}
};

#endif "minHeapisDef"