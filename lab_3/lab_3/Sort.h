#pragma once
#pragma once
#include <iostream>

const int optimizedSize = 10;


template<typename T, typename Compare>
void sort(T* first, T* last, Compare comp) {
	while (first < last) {
		if (last - first < optimizedSize) {
			insertionSort(first, last, comp);
			return;
		}

		T* pivot = partition(first, last, comp);

		if (pivot - first < last - pivot) {
			quickSort(first, pivot, comp);
			first = pivot + 1;
		}
		else
		{
			quickSort(pivot + 1, last, comp);
			last = pivot;
		}

	}
}


template<typename T, typename Compare>
void insertionSort(T* first, T* last, Compare comp) {
	for (T* i = first; i <= last; i++)
	{
		T key = std::move(*i);
		T* j = i - 1;

		while (j >= first && comp(key, *j)) {
			*(j + 1) = std::move(*j);
			j--;
		}

		*(j + 1) = std::move(key);
	}

}

template<typename T, typename Compare>
T findPivot(T* first, T* middle, T* last, Compare comp) {
	if (comp(*first, *middle)) {
		if (comp(*middle, *last))
			return *middle;
		else
			if (comp(*first, *last))
				return *last;
			else
				return *first;

	}
	else
	{
		if (comp(*first, *last))
			return *first;
		else
			if (comp(*middle, *last))
				return *last;
			else
				return *middle;
	}
}

template<typename T, typename Compare>
T* partition(T* first, T* last, Compare comp) {
	T* middle = (first + (last - first) / 2);
	T pivot = std::move(findPivot(first, middle, last, comp));
	T* i = first;
	T* j = last;

	while (i < j)
	{
		while (comp(*i, pivot))
		{
			i++;
		}
		while (comp(pivot, *j)) {
			j--;
		}


		if (i < j) {
			std::swap(*i, *j);
			i++;
			j--;
		}
	}
	return j;
}

template<typename T, typename Compare>
void quickSort(T* first, T* last, Compare comp) {
	while (first < last)
	{
		T* pivot = partition(first, last, comp);

		if (pivot - first < last - pivot) {
			quickSort(first, pivot, comp);
			first = pivot + 1;
		}
		else
		{
			quickSort(pivot + 1, last, comp);
			last = pivot;
		}
	}
}