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
		void RemoveNode(node<T> &p);
		node<T>& operator[](int n);
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
		void InsertionSort();

		template<class T>
		friend ostream& operator<<(ostream &out, const List<T> &list);
		List<T>& operator=(const List<T> &list);
		List<T>& operator=(List<T> &&list);
	};
	template<class T>
	void List<T>::SwapNodes(node<T> &p1, node<T> &p2)
	{
		if (&p1 == &p2) return;
		if (this->head == &p1) this->head = &p2;
		else if (this->head == &p2) this->head = &p1;
		if (this->tail == &p1) this->tail = &p2;
		else if (this->tail == &p2) this->tail = &p1;
		if (p1.next == &p2)
		{
			if (p1.prev != nullptr) p1.prev->next = &p2;
			if (p2.next != nullptr) p2.next->prev = &p1;
			node<T> *pom1 = p1.prev, *pom2 = p2.next;
			p1.prev = &p2;
			p1.next = pom2;
			p2.prev = pom1;
			p2.next = &p1;
			
		}
		else if (p1.prev == &p2)
		{
			if (p2.prev != nullptr) p2.prev->next = &p1;
			if (p1.next != nullptr) p1.next->prev = &p2;
			node<T> *pom1 = p2.prev, *pom2 = p1.next;
			p2.prev = &p1;
			p2.next = pom2;
			p1.prev = pom1;
			p1.next = &p2;
		}
		else
		{
			node<T> *pom1 = p1.prev, *pom2 = p1.next;
			node<T> *pom3 = p2.prev, *pom4 = p2.next;
			if (p1.prev != nullptr) p1.prev->next = &p2;
			if (p1.next != nullptr) p1.next->prev = &p2;
			if (p2.prev != nullptr) p2.prev->next = &p1;
			if (p2.next != nullptr) p2.next->prev = &p1;
			p1.prev = pom3;
			p1.next = pom4;
			p2.prev = pom1;
			p2.next = pom2;

		}
	}
	template<class T>
	void List<T>::RemoveNode(node<T> &p)
	{
		if (this->head == &p) this->PopFront();
		else if (this->tail == &p) this->PopBack();
		else
		{
			this->size--;
			p.prev->next = p.next;
			p.next->prev = p.prev;
			delete &p;
		}
	}
	template<class T>
	node<T>& List<T>::operator[](int n)
	{
		if (this->size < n)throw exception("Index out of bounds");
		node<T> *p = this->head;
		for (int i = 0; i < n; i++)p = p->next;
		return*p;
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
	template <class T>
	List<T>::~List() {
		this->Clear();
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
		node<T> **p = &this->head;
		while (*p != nullptr)
		{
			if (UnaryPredicate((*p)->value)) RemoveNode(**p);
			else p = &((*p)->next);
		}
	}
	template<class T>
	void List<T>::BubbleSort()
	{
		node<T> **p = &this->head;
		node<T> **bound = &this->tail;
		while (*bound != this->head)
		{
			if (*p==*bound)
			{
				p = &this->head;
				bound = &((*bound)->prev);
				continue;
			}
			else if ((*p)->value > (*p)->next->value) SwapNodes(**p,*(*p)->next);
			p = &((*p)->next);
		}
	}
	template<class T>
	void List<T>::InsertionSort()
	{
		if (this->head == this->tail) return;
		node<T> **i = &this->head->next;
		node<T> **j;
		while (*i != nullptr)
		{
			j = &((*i)->prev);
			while ((*j)->prev != nullptr && (*j)->prev->value > (*j)->value)
			{
				SwapNodes(*(*j)->prev,**j);
				j = &((*j)->prev);
			}
			i = &((*i)->next);
		}
		j = &this->tail;
		while ((*j)->prev != nullptr && (*j)->prev->value > (*j)->value)
		{
			SwapNodes(*(*j)->prev, **j);
			j = &((*j)->prev);
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