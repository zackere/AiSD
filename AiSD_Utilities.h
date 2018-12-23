#pragma once
#include <iostream>
using namespace std;
namespace AiSD
{
	template<class T> class List;
	template<class T>
	class node
	{
		friend class List<T>;
		T value;
		node<T> *prev, *next;

		node(T value, node<T> *prev, node<T> *next);
		template<class T>
		friend ostream& operator<<(ostream &out, const node<T> &node);
	public:
		node<T>* GetNext() { return this->next; }
		node<T>* GetPrev() { return this->prev; }
	};
	template<class T>
	node<T>::node(T value, node<T> *prev, node<T> *next) :value(value), prev(prev), next(next) {}
	template<class T>
	ostream & operator<<(ostream & out, const node<T>& node)
	{
		out << node.value;
		return out;
	}

}