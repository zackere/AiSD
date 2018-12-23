#pragma once
#include <iostream>
#include <functional>
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

	template<class T>
	class List
	{
		node<T> *head, *tail;
		int size;
	public:
		List();
		List(const List<T> &list);
		~List();
		int GetSize() const;
		bool IsEmpty() const;
		void PushFront(T elem);
		void PushBack(T elem);
		void PopFront();
		void PopBack();
		void Clear();
		void RemoveIf(function<bool(T)> UnaryPredicate);

		template<class T>
		friend ostream& operator<<(ostream &out, const List<T> &list);
		List<T>& operator=(const List<T>& list);
	};
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
		this->size--;
		if (this->head == nullptr) return;
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
		this->size--;
		if (this->head == nullptr) return;
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
		while (UnaryPredicate(this->head->value)) this->PopFront();
		while (UnaryPredicate(this->tail->value)) this->PopBack();
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
	ostream & operator<<(ostream &out, const List<T> &list)
	{
		node<T>* p = list.head;
		while (p != nullptr)
		{
			out << (*p) << " ";
			p = p->GetNext();
		}
		return out;
	}
}