#pragma once
#include <iostream>
#include <limits>
using namespace std;
namespace AiSD
{
	template<class T>
	class Heap
	{
		T *data; //max_size+1 elements, data[0] is a sentinel
		int size;
		int max_size;
		void UpHeap(int i);
		void DownHeap(int i);
	public:
		Heap(int n=0);
		~Heap();
		void Insert(T elem);
		T Max();
		T DeleteMax();
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
	Heap<T>::Heap(int n)
	{
		if (n < 0) throw exception("Bad Heap size");
		data = new T[n + 1]; 
		size = 0;
		max_size = n;
		data[0] = numeric_limits<int>::max();
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
		if (this->size == 0) throw exception("Heap empty");
		return this->data[1];
	}
	template<class T>
	T Heap<T>::DeleteMax()
	{
		if (this->size == 0)throw exception("Heap empty");
		T ret = move(this->data[1]);
		this->data[1] = move(this->data[size--]);
		this->DownHeap(1);
		return ret;
	}
	template<class T>
	ostream & operator<<(ostream & out, const Heap<T>& heap)
	{
		for (int i = 1; i <= heap.size; i++) out << heap.data[i] << " ";
		return out;
	}
}