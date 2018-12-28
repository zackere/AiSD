#pragma once
#include "AiSD_Utilities.h"
#include <iostream>
#include <math.h>
#include <tuple>
using namespace std;
namespace AiSD
{
	template<class T>
	class Beap :public PriorityQueue<T>
	{
		T *data;
		int size;
		int max_size;
		void ij2k(int &k, const int &i, const int &j) { k = i * (i - 1) / 2 + j; }
		void k2ij(const int &k, int &i, int &j) { i = int(ceil(0.5*(-1 + sqrt(1.0 + 8 * k)))); j = int(k - 0.5*i*(i - 1)); }
		void UpBeap(int k);
		void DownBeap(int k);
	public:
		Beap(int maxsize = 0);
		void Insert(T elem);
		T Max() { return T(); }
		T DeleteMax() { return T(); }
		template<class T>
		friend ostream& operator<<(ostream &out, const Beap<T> &beap);
	};
	template<class T>
	void Beap<T>::UpBeap(int k)
	{
		T val = move(this->data[k]);
		int i = 0, j = 0;
		k2ij(k, i, j);
		int k1 = k;
		while (i > 1)
		{
			if (j == 1) k = k - i + 1;
			else if (j == i)
			{
				k = k - i;
				j--;
			}
			else
			{
				k = k - i;
				j--;
				if (this->data[k] > this->data[k + 1])
				{
					k++;
					j++;
				}
			}
			if (val > this->data[k])
			{
				this->data[k1] = move(this->data[k]);
				k1 = k;
				i--;
			}
			else break;
		}
		this->data[k1] = move(val);
	}
	template<class T>
	void Beap<T>::DownBeap(int k)
	{
		T val = move(this->data[k]);
		int i, j;
		k2ij(k, i, j);
		int k1 = k;
		k += i;
		i++;
		while (k <= this->size)
		{
			if (k < this->size) if (this->data[k + 1] > this->data[k]) k++;
			if (this->data[k] > val)
			{
				this->data[k1] = move(this->data[k]);
				k1 = k;
				k += i;
				i++;
			}
			else break;
		}
		this->data[k1] = move(val);
	}
	template<class T>
	Beap<T>::Beap(int maxsize)
	{
		if (maxsize < 0) throw exception("Bad Heap size");
		this->data = new T[maxsize + 1];
		this->size = 0;
		this->max_size = maxsize;
		this->data[0] = numeric_limits<T>::max(); //for non-specialized types its T();
	}
	template<class T>
	void Beap<T>::Insert(T elem)
	{
		if (this->size == this->max_size) throw exception("Beap is full");
		this->data[++this->size] = elem;
		this->UpBeap(this->size);
	}
	template<class T>
	ostream & operator<<(ostream & out, const Beap<T>& beap)
	{
		for (int i = 1; i <= beap.size; i++) out << beap.data[i] << " ";
		return out;
	}
}