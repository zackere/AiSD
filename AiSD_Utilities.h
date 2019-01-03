#pragma once
#include <iostream>
using namespace std;
namespace AiSD
{
	template<class T> class List;
	template<class T>
	class ListNode
	{
		friend class List<T>;
		T value;
		ListNode<T> *prev, *next;

		ListNode(T value, ListNode<T> *prev, ListNode<T> *next);
		template<class T>
		friend ostream& operator<<(ostream &out, const ListNode<T> &node);
	public:
		ListNode<T>* GetNext() { return this->next; }
		ListNode<T>* GetPrev() { return this->prev; }
	};
	template<class T>
	ListNode<T>::ListNode(T value, ListNode<T> *prev, ListNode<T> *next) :value(value), prev(prev), next(next) {}
	template<class T>
	ostream & operator<<(ostream & out, const ListNode<T>& node)
	{
		out << node.value;
		return out;
	}

	template<class T>
	class LeftistHeapNode
	{
		T key;
		LeftistHeapNode<T> *left, *right;
		int npl;
	};

	template<class T>
	class PriorityQueue
	{
	public:
		virtual void Insert(T elem) = 0;
		virtual T Max() = 0;
		virtual T DeleteMax()=0;
	};

}