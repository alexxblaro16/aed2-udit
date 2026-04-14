#pragma once
// AEDProfeLib.cpp : Define las funciones de la biblioteca estática.
//
#include "AEDProfeLib.h"
#include <vector>


void swap(int* a, int* b) {
	int t = *a;
	*a = *b;
	*b = t;
}
//bubblesort for vectors/arrays
void bubbleSort(std::vector<int>& arr) {
	int n = arr.size();
	bool swapped = true;
	int temp;
	// If no two elements were swapped, then everything is already sorted
	for (int i = 0; i < n - 1 && swapped; i++) {
		swapped = false;
		for (int j = 0; j < n - i - 1; j++) {
			if (arr[j] > arr[j + 1]) {
				swap(&arr[j], &arr[j + 1]);
				/*temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;*/
				swapped = true;
			}
		}
	}
}

int partition(std::vector<int>& arr, int low, int high) {

	// choose the pivot
	int pivot = arr[high];

	// undex of smaller element and indicates 
	// the right position of pivot found so far
	int i = low - 1;

	// Traverse arr[low..high] and move all smaller
	// elements on left side. Elements from low to 
	// i are smaller after every iteration
	for (int j = low; j <= high - 1; j++) {
		if (arr[j] < pivot) {
			i++;
			swap(&arr[i], &arr[j]);
		}
	}

	// move pivot after smaller elements and
	// return its position
	swap(&arr[i + 1], &arr[high]);
	return i + 1;
}

// the QuickSort function implementation
void quickSort(std::vector<int>& arr, int low, int high) {

	if (low < high) {

		// pi is the partition return index of pivot
		int pi = partition(arr, low, high);

		// recursion calls for smaller elements
		// and greater or equals elements
		quickSort(arr, low, pi - 1);
		quickSort(arr, pi + 1, high);
	}
}

//call  mergeSort(arr, 0, arr.size() - 1);
// Merges two subarrays of arr[].
// First subarray is arr[left..mid]
// Second subarray is arr[mid+1..right]
void merge(std::vector<int>& arr, int left,	int mid, int right) {

	int n1 = mid - left + 1;
	int n2 = right - mid;

	// Create temp vectors
	std::vector<int> L(n1), R(n2);

	// Copy data to temp vectors L[] and R[]
	for (int i = 0; i < n1; i++)
		L[i] = arr[left + i];
	for (int j = 0; j < n2; j++)
		R[j] = arr[mid + 1 + j];

	int i = 0, j = 0;
	int k = left;

	// Merge the temp vectors back 
	// into arr[left..right]
	while(i < n1 && j < n2) {
		if (L[i] <= R[j]) {
			arr[k] = L[i];
			i++;
		}
		else {
			arr[k] = R[j];
			j++;
		}
		k++;
	}

	// Copy the remaining elements of L[], 
	// if there are any
	while (i < n1) {
		arr[k] = L[i];
		i++;
		k++;
	}

	// Copy the remaining elements of R[], 
	// if there are any
	while (j < n2) {
		arr[k] = R[j];
		j++;
		k++;
	}
}

// begin is for left index and end is right index
// of the sub-array of arr to be sorted
void mergeSort(std::vector<int>& arr, int left, int right) {

	if (left >= right)
		return;

	int mid = left + (right - left) / 2;
	mergeSort(arr, left, mid);
	mergeSort(arr, mid + 1, right);
	merge(arr, left, mid, right);
}


/* Function to sort array using insertion sort */
void insertionSort(int arr[], int n)
{
	for (int i = 1; i < n; ++i) {
		int key = arr[i];
		int j = i - 1;

		/* Move elements of arr[0..i-1], that are
		   greater than key, to one position ahead
		   of their current position */
		while (j >= 0 && arr[j] > key) {
			arr[j + 1] = arr[j];
			j = j - 1;
		}
		arr[j + 1] = key;
	}
}
