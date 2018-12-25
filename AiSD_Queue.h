#pragma once
#include <iostream>
#include "AiSD_List.h"
using namespace std;
namespace AiSD
{
	template<class T>
	class Queue
	{
		List<T> values;
	public:
		Queue() = default;
		void Push(T elem);
		T Pop();
		bool IsEmpty();
		template<class T>
		friend ostream& operator<<(ostream &out, const Queue<T> &queue);
	};
	template<class T>
	void Queue<T>::Push(T elem)
	{
		this->values.PushBack(elem);
	}
	template<class T>
	T Queue<T>::Pop()
	{
		T ret = this->values->GetFront();
		this->values.PopFront();
		return ret;
	}
	template<class T>
	bool Queue<T>::IsEmpty()
	{
		return this->values.IsEmpty();
	}
	template<class T>
	ostream& operator<<(ostream &out, const Queue<T> &queue)
	{
		out << queue.values;
		return out;
	}
}