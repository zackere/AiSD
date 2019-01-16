#pragma once

#include <ppl.h>

#include "AiSD_Heap.h"
#include "AiSD_List.h"
#include <functional>
namespace AiSD
{
	template<class T>
	class Sort
	{
		using BinaryPredicate = std::function<bool(const T&, const T&)>;

		virtual void _() = 0;
		static void Merge(T *const &arr, const int &l, const int &mid, const int &r, BinaryPredicate op, BinaryPredicate eq);
		static void MergeRP(T *const &arr, const int &l, const int &r, BinaryPredicate op, BinaryPredicate eq);
		static int  Partition(T *const &arr, const int &l, const int &r, BinaryPredicate op);
		static void QuickSortR(T *const &arr, const int &l, const int &r, BinaryPredicate op);
	public:
		// NOTE: after each of the algorithms arr is in nondecreasing order by default.
		static void BubbleSort(T *const &arr, const int &size, BinaryPredicate op = std::greater<T>()); // stable
		static void InsertionSort(T *const &arr, const int &size, BinaryPredicate op = std::greater<T>()); // stable
		static void HeapSort(T *const &arr, const int &size, BinaryPredicate op = std::greater<T>()); // unstable
		static void MergeSort(T *const &arr, const int &size, BinaryPredicate op = std::greater<T>(), BinaryPredicate eq = std::equal_to<T>()); // stable
		static void MergeRPSort(T *const &arr, const int &size, BinaryPredicate op = std::greater<T>(), BinaryPredicate eq = std::equal_to<T>()); // stable
		static void QuickSort(T *const &arr, const int &size, BinaryPredicate op = std::greater<T>()); //stable
	};
	template<class T>
	void Sort<T>::Merge(T * const & arr, const int & l, const int & mid, const int & r, BinaryPredicate op, BinaryPredicate eq)
	{
		T *pom = new T[r - l];
		for (int i = 0; i < r - l; i++)
			pom[i] = std::move(arr[l + i]);
		int x = 0, y = mid - l, i = l;
		while (x < mid - l && y < r - l)
		{
			if (eq(pom[x], pom[y]))
			{
				arr[i++] = std::move(pom[x++]);
				arr[i++] = std::move(pom[y++]);
			}
			else
				if (op(pom[x], pom[y]))
					arr[i++] = std::move(pom[y++]);
				else
					arr[i++] = std::move(pom[x++]);
		}
		if (x == mid - l)
			while (y < r - l)
				arr[i++] = std::move(pom[y++]);
		else if (y == r - l)
			while (x < mid - l)
				arr[i++] = std::move(pom[x++]);
		delete[] pom;
	}
	template<class T>
	void Sort<T>::MergeRP(T *const & arr, const int & l, const int & r, BinaryPredicate op, BinaryPredicate eq)
	{
		if (r - l < 17)
		{
			int j, x;
			for (int i = l + 1; i < r; i++)
			{
				j = i - 1;
				x = std::move(arr[i]);
				while (op(arr[j], x) && j >= l)
				{
					arr[j + 1] = std::move(arr[j]);
					j--;
				}
				arr[j + 1] = x;
			}
		}
		if (l + 1 < r)
		{
			int mid = (int)floor(((double)l + (double)r) / 2);
			Concurrency::parallel_invoke(
				[&] { MergeRP(arr, l, mid, op, eq); },
				[&] { MergeRP(arr, mid, r, op, eq); }
			);
			Merge(arr, l, mid, r, op, eq);
		}
	}
	template<class T>
	int Sort<T>::Partition(T * const & arr, const int & l, const int & r, BinaryPredicate op)
	{
		T v = arr[r];
		int i = l - 1;
		for (int j = l; j < r; j++)
		{
			if (!(op(arr[j], v)))
				std::swap(arr[++i], arr[j]);
		}
		std::swap(arr[i + 1], arr[r]);
		return i + 1;
	}
	template<class T>
	void Sort<T>::QuickSortR(T * const & arr, const int & l, const int & r, BinaryPredicate op)
	{
		if (l < r)
		{
			int pivot = Sort<T>::Partition(arr, l, r, op);
			Sort<T>::QuickSortR(arr, l, pivot - 1, op);
			Sort<T>::QuickSortR(arr, pivot + 1, r, op);
		}
		
	}
	template<class T>
	void Sort<T>::BubbleSort(T *const &arr, const int &size, BinaryPredicate op)
	{
		int newn = 0;
		int bound = size;
		while (bound > 1)
		{
			newn = 0;
			for (int i = 1; i < bound; i++)
				if (op(arr[i - 1], arr[i]))
				{
					std::swap(arr[i - 1], arr[i]);
					newn = i; // after the last swap all elements are sorted and dont need be checked again
				}
			bound = newn;
		}
	}
	template<class T>
	void Sort<T>::InsertionSort(T *const &arr, const int &size, BinaryPredicate op)
	{
		int j, x;
		for (int i = 1; i < size; i++)
		{
			j = i - 1;
			x = std::move(arr[i]);
			while (op(arr[j], x) && j >= 0)
			{
				arr[j + 1] = std::move(arr[j]);
				j--;
			}
			arr[j + 1] = x;
		}
	}
	template<class T>
	void Sort<T>::HeapSort(T *const &arr, const int &size, BinaryPredicate op)
	{
		Heap<T> heap(arr, size, size, op);
		for (int i = 0; i < size; i++)
			arr[size - i - 1] = heap.DeleteMax();
	}
	template<class T>
	void Sort<T>::MergeSort(T * const & arr, const int & size, BinaryPredicate op, BinaryPredicate eq)
	{
		List<int> indexlist;
		indexlist.PushBack(0);
		for (int i = 1; i < size; i++)
			if (op(arr[i - 1], arr[i]))
				indexlist.PushBack(i);
		indexlist.PushBack(size);
		while (indexlist.GetSize() > 2)
		{
			int a = indexlist.GetFront(); indexlist.PopFront();
			int b = indexlist.GetFront(); indexlist.PopFront();
			int c = indexlist.GetFront(); indexlist.PopFront();
			Sort<T>::Merge(arr, a, b, c, op, eq);
			indexlist.PushFront(c);
			indexlist.PushFront(a);
		}
	}
	template<class T>
	void Sort<T>::MergeRPSort(T * const & arr, const int & size, BinaryPredicate op, BinaryPredicate eq)
	{
		Sort<T>::MergeRP(arr, 0, size, op, eq);
	}
	template<class T>
	void Sort<T>::QuickSort(T * const & arr, const int & size, BinaryPredicate op)
	{
		Sort<T>::QuickSortR(arr, 0, size - 1, op);
	}
}