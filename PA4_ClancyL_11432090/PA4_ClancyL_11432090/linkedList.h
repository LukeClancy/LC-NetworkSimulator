#pragma once
template<class T>
class linkedList
{
public:
	linkedList *next;
	T data;
	linkedList(T data1, linkedList *next1)
	{
		next = next1;
		data = data1;
	}
	linkedList()
	{
		next = nullptr;
		data = NULL;
	}
	~linkedList()
	{
	}
};