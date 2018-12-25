#pragma once
#include "AiSD_Utilities.h"
#include <iostream>
using namespace std;
namespace AiSD
{
	template<class T>
	class Beap :public PriorityQueue<T>
	{
		T *data;
		int size;
		int max_size;
	public:
		Beap(int maxsize = 0);
		void Insert(T elem);
		T Max();
		T DeleteMax();
	};
	template<class T>
	Beap<T>::Beap(int maxsize)
	{
		if (maxsize < 0) throw exception("Bad Heap size");
		this->data = new T[maxsize + 1];
		this->size = 0;
		this->max_size = maxsize;
		this->data[0] = numeric_limits<T>::max(); //for non-specialized types its T();
	}
}