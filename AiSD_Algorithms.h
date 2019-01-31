#pragma once

#include <functional>
#include <math.h>

#include "AiSD_Heap.h"
#include "AiSD_List.h"
namespace AiSD
{
	template<class T>
	class Sort
	{
		using BinaryPredicate = std::function<bool(const T&, const T&)>;

		virtual void _() = 0;

		static void BubbleSortRange(T *const &arr, const int &l, const int &r, BinaryPredicate &op);
		static void InsertionSortRange(T *const &arr, const int &l, const int &r, BinaryPredicate &op);
		static void SelectionSortRange(T *const &arr, const int &l, const int &r, BinaryPredicate &op);
		static void MergeSortRange(T *const &arr, const int &l, const int &r, BinaryPredicate &op, BinaryPredicate &eq);
		static void Merge(T *const &arr, const int &l, const int &mid, const int &r, BinaryPredicate &op, BinaryPredicate &eq);
		static void QuickSortRange(T *const &arr, const int &l, const int &r, BinaryPredicate &op);
		static int  Partition(T *const &arr, const int &l, const int &r, BinaryPredicate &op);
		static void IntroSortRange(T * const & arr, const int & l, const int & r, const int & part_bound, int &partitions, BinaryPredicate &op);
		static void HeapSortRange(T *const &arr, const int &l, const int &r, BinaryPredicate &op);
	public:
		// NOTE: after each of the algorithms arr is in nondecreasing order by default.
		static void BubbleSort(T *const &arr, const int &size, BinaryPredicate op = std::greater<T>()); // stable
		static void InsertionSort(T *const &arr, const int &size, BinaryPredicate op = std::greater<T>()); // stable
		static void SelectionSort(T *const &arr, const int &size, BinaryPredicate op = std::greater<T>()); // unstable
		static void HeapSort(T *const &arr, const int &size, BinaryPredicate op = std::greater<T>()); // unstable
		static void MergeSort(T *const &arr, const int &size, BinaryPredicate op = std::greater<T>(), BinaryPredicate eq = std::equal_to<T>()); // stable
		static void QuickSort(T *const &arr, const int &size, BinaryPredicate op = std::greater<T>()); // stable
		static void IntroSort(T *const &arr, const int &size, BinaryPredicate op = std::greater<T>()); // stable
	};
	template<class T>
	void Sort<T>::BubbleSortRange(T * const & arr, const int & l, const int & r, BinaryPredicate & op)
	{
		int newn = l;
		int bound = r;
		while (bound > l + 1)
		{
			newn = l;
			for (int i = l + 1; i < bound; i++)
				if (op(arr[i - 1], arr[i]))
				{
					std::swap(arr[i - 1], arr[i]);
					newn = i; // after the last swap all elements are sorted and dont need be checked again
				}
			bound = newn;
		}
	}
	template<class T>
	void Sort<T>::InsertionSortRange(T *const &arr, const int &l, const int &r, BinaryPredicate &op)
	{
		int j;
		T x;
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
	template<class T>
	void Sort<T>::SelectionSortRange(T * const & arr, const int & l, const int & r, BinaryPredicate & op)
	{
		int index = l;
		for (int i = l; i < r; i++)
		{
			index = i;
			for (int j = i+1; j < r; j++)
			{
				if (op(arr[j], arr[index])) index = j;
			}
			std::swap(arr[i], arr[index]);
		}
	}
	template<class T>
	void Sort<T>::MergeSortRange(T * const & arr, const int & l, const int & r, BinaryPredicate & op, BinaryPredicate & eq)
	{
		List<int> indexlist;
		List<int> pom;
		indexlist.PushBack(l);
		for (int i = l + 1; i < r; i++)
			if (op(arr[i - 1], arr[i]))
				indexlist.PushBack(i);
		indexlist.PushBack(r);
		if (indexlist.GetSize() == 2) return;
		int a, b, c;
		while (true)
		{
			if (indexlist.GetSize() < 3)
			{
				if (pom.GetSize() == 0) return;
				while (indexlist.GetSize() != 0)
				{
					pom.PushBack(indexlist.GetFront());
					indexlist.PopFront();
				}
				indexlist = std::move(pom);
				continue;
			}
			a = indexlist.GetFront(); indexlist.PopFront();
			b = indexlist.GetFront(); indexlist.PopFront();
			c = indexlist.GetFront();
			Sort<T>::Merge(arr, a, b, c, op, eq);
			pom.PushBack(a);
		}
	}
	template<class T>
	void Sort<T>::Merge(T * const & arr, const int & l, const int & mid, const int & r, BinaryPredicate &op, BinaryPredicate &eq)
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
	void Sort<T>::QuickSortRange(T * const & arr, const int & l, const int & r, BinaryPredicate & op)
	{
		if (r - l <= 1) return;
		if (r - l <= 16)
		{
			Sort<T>::InsertionSortRange(arr, l, r, op);
			return;
		}
		int pivot = Partition(arr, l, r-1, op);
		if (r - pivot > pivot - l)
		{
			Sort<T>::QuickSortRange(arr, l, pivot, op);
			Sort<T>::QuickSortRange(arr, pivot, r, op);
		}
		else
		{
			Sort<T>::QuickSortRange(arr, pivot, r, op);
			Sort<T>::QuickSortRange(arr, l, pivot, op);
		}
	}
	template<class T>
	int Sort<T>::Partition(T * const & arr, const int & l, const int & r, BinaryPredicate &op)
	{
		int mid = (l + r) / 2;
		if (op(arr[l], arr[mid]))
			std::swap(arr[l], arr[mid]);
		if (op(arr[l], arr[r]))
			std::swap(arr[l], arr[r]);
		if (op(arr[r], arr[mid]))
			std::swap(arr[r], arr[mid]);
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
	void Sort<T>::IntroSortRange(T * const & arr, const int & l, const int & r, const int & part_bound, int &partitions, BinaryPredicate &op)
	{
		if (r - l <= 16)
		{
			InsertionSortRange(arr, l, r, op);
		}
		else if (partitions > part_bound)
		{
			Sort<T>::HeapSortRange(arr, l, r, op);
		}
		else
		{
			int pivot = Sort<T>::Partition(arr, l, r-1, op);
			partitions++;
			if (r - pivot > pivot - l)
			{
				Sort<T>::IntroSortRange(arr, l, pivot, part_bound, partitions, op);
				Sort<T>::IntroSortRange(arr, pivot + 1, r, part_bound, partitions, op);
			}
			else
			{
				Sort<T>::IntroSortRange(arr, pivot + 1, r, part_bound, partitions, op);
				Sort<T>::IntroSortRange(arr, l, pivot, part_bound, partitions, op);
			}
		}
	}
	template<class T>
	void Sort<T>::HeapSortRange(T * const & arr, const int & l, const int & r, BinaryPredicate &op)
	{
		T *pom = new T[r - l];
		for (int i = 0; i < r - l; i++) 
			pom[i] = std::move(arr[l + i]);
		Heap<T> heap(pom, r - l, r - l, op);
		for (int i = 0; i < r - l; i++)
			arr[r - i - 1] = heap.DeleteMax();
	}
	template<class T>
	void Sort<T>::BubbleSort(T *const &arr, const int &size, BinaryPredicate op)
	{
		Sort<T>::BubbleSortRange(arr, 0, size, op);
	}
	template<class T>
	void Sort<T>::InsertionSort(T *const &arr, const int &size, BinaryPredicate op)
	{
		Sort<T>::InsertionSortRange(arr, 0, size, op);
	}
	template<class T>
	void Sort<T>::SelectionSort(T * const & arr, const int & size, BinaryPredicate op)
	{
		Sort<T>::SelectionSortRange(arr, 0, size, op);
	}
	template<class T>
	void Sort<T>::HeapSort(T *const &arr, const int &size, BinaryPredicate op)
	{
		Sort<T>::HeapSortRange(arr, 0, size, op);
	}
	template<class T>
	void Sort<T>::MergeSort(T * const & arr, const int & size, BinaryPredicate op, BinaryPredicate eq)
	{
		Sort<T>::MergeSortRange(arr, 0, size, op, eq);
	}
	template<class T>
	void Sort<T>::QuickSort(T * const & arr, const int & size, BinaryPredicate op)
	{
		Sort<T>::QuickSortRange(arr, 0, size, op);
	}
	template<class T>
	void Sort<T>::IntroSort(T * const & arr, const int & size, BinaryPredicate op)
	{
		int partitions = 1;
		Sort<T>::IntroSortRange(arr, 0, size, 2 * size * log(size), partitions, op);
	}
}