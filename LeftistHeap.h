#pragma once
#include "AiSD_Utilities.h"
namespace AiSD
{
	template<class T>
	class LeftistHeap :public PriorityQueue<T>
	{
	public:
		void Insert(T elem);
		T Max();
		T DeleteMax();
		void Union(LeftistHeap h);
	};
}