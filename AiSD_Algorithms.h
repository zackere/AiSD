#pragma once

#include <ppl.h>

#include "AiSD_Heap.h"
#include "AiSD_List.h"

namespace AiSD
{
	template<class T>
	class Sort
	{
		virtual void _() = 0;
		static void Merge(T *const &arr, const int &a, const int &b, const int &c);
		static void MergeRP(T *const &arr, const int &a, const int &b);
	public:
		// NOTE: after each of the algorithms arr is in nondecreasing order by default.
		static void BubbleSort(T *const &arr,const int &size); // stable
		static void InsertionSort(T *const &arr,const int &size); // stable
		static void HeapSort(T *const &arr,const int &size); // unstable
		static void MergeSort(T *const &arr, const int &size); // stable
		static void MergeRPSort(T * const & arr, const int & size); // stable
	};
	template<class T>
	void Sort<T>::Merge(T * const & arr, const int & a, const int & b, const int & c)
	{
		T *pom = new T[c - a];
		for (int i = 0; i < c - a; i++) 
			pom[i] = std::move(arr[a + i]);
		int x = 0, y = b - a, i = a;
		while (x < b - a && y < c - a)
		{
			if (pom[x] == pom[y])
			{
				arr[i++] = std::move(pom[x++]);
				arr[i++] = std::move(pom[y++]);
			}
			else 
				if (pom[x] > pom[y])
					arr[i++] = std::move(pom[y++]);
			else
				arr[i++] = std::move(pom[x++]);
		}
		if (x == b - a) 
			while (y < c - a) 
				arr[i++] = std::move(pom[y++]);
		else if (y == c - a) 
			while (x < b - a) 
				arr[i++] = std::move(pom[x++]);
		delete[] pom;
	}
	template<class T>
	void Sort<T>::MergeRP(T *const & arr, const int & a, const int & b)
	{
		if (b - a < 17)
		{
			int j, x;
			for (int i = a + 1; i < b; i++)
			{
				j = i - 1;
				x = std::move(arr[i]);
				while (arr[j] > x && j >= a)
				{
					arr[j + 1] = std::move(arr[j]);
					j--;
				}
				arr[j + 1] = x;
			}
		}
		if (a + 1 < b)
		{
			int mid = (int)floor(((double)a + (double)b) / 2);
			Concurrency::parallel_invoke(
				[&] { MergeRP(arr, a, mid); },
				[&] { MergeRP(arr, mid, b); }
			);
			Merge(arr, a, mid, b);
		}
	}
	template<class T>
	void Sort<T>::BubbleSort(T *const &arr,const int &size)
	{
		int newn = 0;
		int bound = size;
		while (bound > 1)
		{
			newn = 0;
			for (int i = 1; i < bound; i++)
				if (arr[i - 1] > arr[i])
				{
					std::swap(arr[i - 1], arr[i]);
					newn = i; // after the last swap all elements are sorted and dont need be checked again
				}
			bound = newn;
		}
	}
	template<class T>
	void Sort<T>::InsertionSort(T *const &arr,const int &size)
	{
		int j, x;
		for (int i = 1; i < size; i++)
		{
			j = i - 1;
			x = std::move(arr[i]);
			while (arr[j] > x && j >= 0)
			{
				arr[j + 1] = std::move(arr[j]);
				j--;
			}
			arr[j + 1] = x;
		}
	}
	template<class T>
	void Sort<T>::HeapSort(T *const &arr,const int &size)
	{
		Heap<T> heap(arr, size, size);
		for (int i = 0; i < size; i++)
			arr[size - i - 1] = heap.DeleteMax();
	}
	template<class T>
	void Sort<T>::MergeSort(T * const & arr, const int & size)
	{
		List<int> indexlist;
		indexlist.PushBack(0);
		for (int i = 1; i < size; i++)
			if (arr[i - 1] > arr[i])
				indexlist.PushBack(i);
		indexlist.PushBack(size);
		while (indexlist.GetSize() > 2)
		{
			int a = indexlist.GetFront(); indexlist.PopFront();
			int b = indexlist.GetFront(); indexlist.PopFront();
			int c = indexlist.GetFront(); indexlist.PopFront();
			Sort<T>::Merge(arr, a, b, c);
			indexlist.PushFront(c);
			indexlist.PushFront(a);
		}
	}
	template<class T>
	void Sort<T>::MergeRPSort(T * const & arr, const int & size)
	{
		MergeRP(arr, 0, size);
	}
}