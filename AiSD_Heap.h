#pragma once
#include "AiSD_Utilities.h"
#include <iostream>
#include <limits>
#include <functional>
using namespace std;
namespace AiSD
{
	template<class T>
	class Heap : public PriorityQueue<T>
	{
		using BinaryPredicate = std::function<bool(const T&, const T&)>;

		T *data; //max_size+1 elements, data[0] is a sentinel
		int size;
		int max_size;
		void UpHeap(int i);
		void DownHeap(int i);
		BinaryPredicate op;
		BinaryPredicate eq;
	public:
		Heap(int maxsize=0, BinaryPredicate op=std::greater<T>(), BinaryPredicate eq = std::equal_to<T>());
		Heap(T *data, int datasize, int maxsize, BinaryPredicate op = std::greater<T>(), BinaryPredicate eq = std::equal_to<T>());
		Heap(const Heap<T> &h);
		Heap(Heap<T> &&h);
		Heap<T>& operator=(const Heap<T> &h);
		Heap<T>& operator=(Heap<T> &&h);
		~Heap();
		void Insert(T elem);
		T Max();
		T DeleteMax();
		T Delete(int i);
		T Replace(int i, T v);
		int Search(const T &v);
		T operator[](int i);
		template<class T>
		friend ostream& operator<<(ostream &out, const Heap<T> &heap);
	};
	template<class T>
	void Heap<T>::UpHeap(int i)
	{
		T val = move(data[i]);
		while (this->op(val, this->data[i / 2]))
		{
			this->data[i] = move(this->data[i / 2]);
			i /= 2;
		}
		data[i] = move(val);
	}
	template<class T>
	void Heap<T>::DownHeap(int i)
	{
		int k = 2 * i;
		T val = move(data[i]);
		while (!(k > this->size))
		{
			if (k + 1 <= this->size)
				if (this->op(this->data[k + 1], this->data[k]))
					k++;
			if (this->op(this->data[k], val))
			{
				this->data[i] = move(this->data[k]);
				i = k;
				k = 2 * i;
			}
			else break;
		}
		this->data[i] = move(val);
	}
	template<class T>
	Heap<T>::Heap(int maxsize, BinaryPredicate op, BinaryPredicate eq)
	{
		if (maxsize < 0) throw exception("Bad Heap size");
		this->data = new T[maxsize + 1]; 
		this->size = 0;
		this->max_size = maxsize;
		this->op = op;
		this->eq = eq;
		this->data[0] = numeric_limits<T>::max(); //for non-specialized types its T();
	}
	template<class T>
	Heap<T>::Heap(T * data, int datasize, int maxsize, BinaryPredicate op, BinaryPredicate eq)
	{
		if (maxsize < 0) throw exception("Bad Heap size");
		if (datasize <= 0 || datasize > maxsize) throw exception("Bad data size");
		this->data = new int[maxsize + 1];
		this->size = datasize;
		this->max_size = maxsize;
		this->op = op;
		this->eq = eq;
		this->data[0] = numeric_limits<T>::max();
		for (int i = 1; i <= datasize; i++) this->data[i] = data[i - 1];
		for (int i = this->size / 2; i >= 1; i--) this->DownHeap(i);
	}
	template<class T>
	Heap<T>::Heap(const Heap<T> &h)
	{
		this->data = new T[h.max_size + 1];
		this->size = h.size;
		this->max_size = h.max_size;
		this->op = h.op;
		this->eq = h.eq;
		for (int i = 0; i <= h.size; i++) this->data[i] = h.data[i];
	}
	template<class T>
	Heap<T>::Heap(Heap<T>&& h) :data(h.data), size(h.size), max_size(h.max_size), op(h.op), eq(h.eq)
	{
		h.data = nullptr;
		h.size = 0;
		h.max_size = 0;
	}
	template<class T>
	Heap<T>& Heap<T>::operator=(const Heap<T> &h)
	{
		if (this != &h)
		{
			delete[] this->data;
			this->data = new T[h.max_size + 1];
			for (int i = 0; i <= h.size; i++) this->data[i] = h.data[i];
			this->size = h.size;
			this->max_size = h.max_size;
			this->op = h.op;
			this->eq = h.eq;
		}
		return *this;
	}
	template<class T>
	Heap<T>& Heap<T>::operator=(Heap<T> &&h)
	{
		if (this != &h)
		{
			delete[] this->data;
			this->data = h.data;
			this->size = h.size;
			this->max_size = h.max_size;
			this->op = h.op;
			this->eq = h.eq;
			h.data = nullptr;
			h.size = 0;
			h.max_size = 0;
		}
		return *this;
	}
	template<class T>
	Heap<T>::~Heap()
	{
		delete[] this->data;
	}
	template<class T>
	void Heap<T>::Insert(T elem)
	{
		if (this->size == this->max_size) throw exception("Heap is full");
		this->data[++this->size] = elem;
		this->UpHeap(this->size);
	}
	template<class T>
	T Heap<T>::Max()
	{
		if (this->size == 0) throw exception("Heap is empty");
		return this->data[1];
	}
	template<class T>
	T Heap<T>::DeleteMax()
	{
		if (this->size == 0) throw exception("Heap is empty");
		return this->Delete(0);
	}
	template<class T>
	T Heap<T>::Delete(int i)
	{
		if (i < 0 || i > this->size) throw exception("Bad index");
		T ret = move(this->data[i + 1]);
		this->data[i + 1] = move(this->data[this->size--]);
		this->DownHeap(i + 1);
		return ret;
	}
	template<class T>
	T Heap<T>::Replace(int i, T v)
	{
		if (i < 0 || i > this->size) throw exception("Bad index");
		int sgn = (op(v, this->data[i])) ? 1 : -1;
		T ret = move(this->data[i + 1]);
		cout << endl;
		this->data[i + 1] = v;
		cout << endl;
		if (sgn == 1) this->UpHeap(i + 1);
		else this->DownHeap(i + 1);
		return ret;
	}
	template<class T>
	int Heap<T>::Search(const T &v)
	{
		for (int i = 1; i <= this->size; i++) if (eq(this->data[i], v)) return i - 1;
		return -1;
	}
	template<class T>
	T Heap<T>::operator[](int i)
	{
		if (i >= 0 && i < this->size) return this->data[i + 1];
		throw exception("Index out of bounds");
	}
	template<class T>
	ostream & operator<<(ostream & out, const Heap<T>& heap)
	{
		cout << "Heap size: " << heap.size << endl;
		for (int i = 1; i <= heap.size; i++) out << heap.data[i] << " ";
		return out;
	}
}
