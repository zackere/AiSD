#pragma once
#include "AiSD_Utilities.h"
#include <iostream>
#include <limits>
using namespace std;
namespace AiSD
{
	template<class T>
	class Heap :public PriorityQueue<T>
	{
		T *data; //max_size+1 elements, data[0] is a sentinel
		int size;
		int max_size;
		void UpHeap(int i);
		void DownHeap(int i);
	public:
		Heap(int maxsize=0);
		Heap(T *data, int datasize, int maxsize);
		~Heap();
		void Insert(T elem);
		T Max();
		T DeleteMax();
		T Delete(int i);
		T Replace(int i, T v);
		int Search(T v);
		T operator[](int i);
		template<class T>
		friend ostream& operator<<(ostream &out, const Heap<T> &heap);
	};
	template<class T>
	void Heap<T>::UpHeap(int i)
	{
		T val = move(data[i]);
		while (val > this->data[i / 2])
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
				if (this->data[k + 1] > this->data[k])
					k++;
			if (this->data[k] > val)
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
	Heap<T>::Heap(int maxsize)
	{
		if (maxsize < 0) throw exception("Bad Heap size");
		this->data = new T[maxsize + 1]; 
		this->size = 0;
		this->max_size = maxsize;
		this->data[0] = numeric_limits<T>::max(); //for non-specialized types its T();
	}
	template<class T>
	Heap<T>::Heap(T * data, int datasize, int maxsize)
	{
		if (maxsize < 0) throw exception("Bad Heap size");
		if (datasize <= 0 || datasize > maxsize) throw exception("Bad data size");
		this->data = new int[maxsize + 1];
		this->size = datasize;
		this->max_size = maxsize;
		this->data[0] = numeric_limits<T>::max();
		for (int i = 1; i <= datasize; i++) this->data[i] = data[i - 1];
		for (int i = this->size / 2; i >= 1; i--) this->DownHeap(i);
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
		this->UpHeap(size);
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
		int sgn = (v > this->data[i]) ? 1 : -1;
		T ret = move(this->data[i + 1]);
		cout << endl;
		this->data[i + 1] = v;
		cout << endl;
		if (sgn == 1) this->UpHeap(i + 1);
		else this->DownHeap(i + 1);
		return ret;
	}
	template<class T>
	int Heap<T>::Search(T v)
	{
		for (int i = 1; i <= this->size; i++) if (this->data[i] == v) return i - 1;
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