#pragma once
#include "AiSD_Utilities.h"
#include <iostream>
#include <functional>
using namespace std;
namespace AiSD
{
	template<class T>
	class List
	{
		node<T> *head, *tail;
		int size;
		void SwapNodes(node<T> &p1, node<T> &p2);
	public:
		List();
		List(const List<T> &list);
		List(List<T> &&list);
		~List();
		int GetSize() const;
		bool IsEmpty() const;
		void PushFront(T elem);
		void PushBack(T elem);
		void PopFront();
		void PopBack();
		void Clear();
		void RemoveIf(function<bool(T)> UnaryPredicate);
		void BubbleSort();

		template<class T>
		friend ostream& operator<<(ostream &out, const List<T> &list);
		List<T>& operator=(const List<T> &list);
		List<T>& operator=(List<T> &&list);
	};
	template<class T>
	void List<T>::SwapNodes(node<T> &p1, node<T> &p2)
	{
		if (&p1 == &p2) return;
		swap(p1, p2);
		swap(p1.next, p2.next);
		swap(p1.prev, p2.prev);
	}
	template<class T>
	List<T>::List() :head(nullptr), tail(nullptr),size(0) {}
	template<class T>
	List<T>::List(const List<T>& list)
	{
		node<T> *p = list.head;
		while (p != nullptr)
		{
			this->PushBack(p->value);
			p = p->next;
		}
	}
	template<class T>
	List<T>::List(List<T>&& list):head(list.head),tail(list.tail),size(list.size)
	{
		list.head = nullptr;
		list.tail = nullptr;
		list.size = 0;
	}
	template<class T>
	List<T>::~List()
	{
		if (this->head != nullptr)
		{
			node<T> *p1, *p2;
			p1 = this->head;
			p2 = p1->next;
			while (p2 != nullptr)
			{
				delete p1;
				p1 = p2;
				p2 = p2->next;
			}
			delete p1;
		}
	}
	template<class T>
	int List<T>::GetSize() const
	{
		return this->size;
	}
	template<class T>
	bool List<T>::IsEmpty() const
	{
		return this->size == 0;
	}
	template<class T>
	void List<T>::PushFront(T elem)
	{
		this->size++;
		node<T> *p = new node<T>(elem, nullptr, nullptr);
		if (this->head == nullptr)
		{
			this->head = p;
			this->tail = p;
		}
		else
		{
			p->next = this->head;
			this->head->prev = p;
			this->head = p;
		}
	}
	template<class T>
	void List<T>::PushBack(T elem)
	{
		this->size++;
		node<T> *p = new node<T>(elem, nullptr, nullptr);
		if (this->head == nullptr)
		{
			this->head = p;
			this->tail = p;
		}
		else
		{
			p->prev = this->tail;
			this->tail->next = p;
			this->tail = p;
		}
	}
	template<class T>
	void List<T>::PopFront()
	{
		if (this->head == nullptr) return;
		this->size--;
		if (this->head == this->tail)
		{
			delete this->head;
			this->head = nullptr;
			this->tail = nullptr;
			return;
		}
		node<T> *p = this->head->next;
		delete this->head;
		this->head = p;
		this->head->prev = nullptr;
	}
	template<class T>
	void List<T>::PopBack()
	{
		if (this->head == nullptr) return;
		this->size--;
		if (this->head == this->tail)
		{
			delete this->head;
			this->head = nullptr;
			this->tail = nullptr;
			return;
		}
		node<T> *p = this->tail->prev;
		delete this->tail;
		this->tail = p;
		this->tail->next = nullptr;
	}
	template<class T>
	void List<T>::Clear()
	{
		while (!this->IsEmpty()) this->PopFront();
	}
	template<class T>
	void List<T>::RemoveIf(function<bool(T)> UnaryPredicate)
	{
		while (this->head && UnaryPredicate(this->head->value)) this->PopFront();
		while (this->tail && UnaryPredicate(this->tail->value)) this->PopBack();
		if (this->head == nullptr) return;
		node<T> *p = this->head->next;
		while (p != nullptr)
		{
			if (UnaryPredicate(p->value))
			{
				p->prev->next = p->next;
				p->next->prev = p->prev;
				node<T>* tmp=p;
				p = p->next;
				delete tmp;
			}
			else p = p->next;
		}
	}
	template<class T>
	void List<T>::BubbleSort()
	{
		node<T> *p = this->head;
		node<T> *bound = this->tail;
		while (bound!=this->head)
		{
			if (p == bound)
			{
				p = this->head;
				bound = bound->prev;
			}
			if (p->value > p->next->value) SwapNodes(*p, *(p->next));
			p = p->next;
		}
	}
	template<class T>
	List<T>& List<T>::operator=(const List<T> &list)
	{
		if (this != &list)
		{
			this->Clear();
			node<T> *p = list.head;
			while (p != nullptr)
			{
				this->PushBack(p->value);
				p = p->next;
			}
		}
		return *this;
	}
	template<class T>
	List<T>& List<T>::operator=(List<T> &&list)
	{
		if (this != &list)
		{
			this->Clear();
			this->head = list.head;
			this->tail = list.tail;
			this->size = list.size;
			list.head = nullptr;
			list.tail = nullptr;
			list.size = 0;
		}
		return *this;
	}
	template<class T>
	ostream & operator<<(ostream &out, const List<T> &list)
	{
		node<T>* p = list.head;
		while (p != nullptr)
		{
			out << *p << " ";
			p = p->GetNext();
		}
		return out;
	}
}