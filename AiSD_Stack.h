#pragma once
#include <iostream>
#include "AiSD_List.h"
using namespace std;
namespace AiSD
{
	template<class T>
	class Stack
	{
		List<T> values;
	public:
		Stack() = default;
		void Push(T elem);
		T Pop();
		bool IsEmpty();
		template<class T>
		friend ostream& operator<<(ostream &out, const Stack<T> &stack);
	};
	template<class T>
	void Stack<T>::Push(T elem)
	{
		this->values.PushFront(elem);
	}
	template<class T>
	T Stack<T>::Pop()
	{
		T ret = this->values->GetFront();
		this->values.PopFront();
		return ret;
	}
	template<class T>
	bool Stack<T>::IsEmpty()
	{
		return this->values->IsEmpty();
	}
	template<class T>
	ostream & operator<<(ostream & out, const Stack<T>& stack)
	{
		out << stack.values;
		return out;
	}
}