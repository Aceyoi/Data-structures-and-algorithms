//���������� ���� ���-22
#pragma once

#include <exception>
#include <iostream>
#include <vector>

using namespace std;

///���������� ������� ���� ������� ������� ������� � ����� begin � end
///a - �������������� ������
///begin - ����� ������� ��������������� �������
///end - ������ ������� ��������������� �������
template<typename T>
void merging(T* a, size_t begin, size_t mid, size_t end) {
	T* c = new T[end - begin];					//����� ��� �������� ���������� �������

        size_t
		left = begin,						//������ �������� �� ����� �������
		right = mid,							//������ �������� �� ������ �������
		i = 0;								//������ ������� c 

	while (left < mid && right < end) {			//���� �� ��������� ����� ����� �� ��������
		if (a[left] <= a[right]) {				//������������ �������� �� ��������

			c[i] = a[left];						// ���� left ������ right, �� � ������ i ������� � �������� �������� �� ����� �������
			left++;
		}
		else {
			c[i] = a[right];					//� ��������� ������ �� ������
			right++;
		}
		i++;
	}
	//�������� ���������� �������� � ������ c
	if (left == mid) {							//���� ��� ��������� ����� ����� �����

		while (right < end) {					//�� �������� �������� �� ������

			c[i] = a[right];
			right++;
			i++;
		}
	}
	else if (right == end) {					//���� �� ��� ��������� ����� ������ �����

		while (left < mid) {				// �� �������� �������� �� �����

			c[i] = a[left];
			left++;
			i++;
		}
	}

	size_t j = 0;
	while (j < end - begin) {					//��������� �������� �� ������� � � ������ �
		a[begin + j] = c[j];
		j++;
	}
	delete[] c;
}

///����������� ������� ���������� �������� �� �����������
/// a - �����������������
///left - ����� ������� ����������
/// right - ������ ������� ����������
/// 
/// BigO = O(n log(n)) ��� ���� �������
template<typename T>
void mergesort(T* a, size_t left, size_t right) {

	if (left < right - 1) {
		size_t mid = left + (right - left) / 2;
		mergesort(a, left, mid);	//���������� ����� �������� ����������� �������
		mergesort(a, mid, right);  //���������� ������ �������� ����������� �������
		merging(a, left, mid, right);
	}
}


///����������� ������� ������� ���������� �� �����������, � �������� �������� �������� ������� ������ �������
/// arr - ����������� ������
///begin - ����� ������� ����������
/// end - ������ ������� ����������
/// 
/// BigO = O(n2) ��� ������� ������
/// BigO = O(n log n) ��� �������� � ������� ������
template <typename T>
void quicksort(T* arr, size_t begin, size_t end) {
	if (begin >= end) return;

	size_t base = begin; //������� �������
	size_t current = begin;//������� ������� ������������ ����� �� ��������

	for (size_t i = begin + 1; i <= end; i++) {
		if (arr[i] < arr[base]) {				//���� ������� arr[i] ������ ��������
			swap(arr[i], arr[++current]);  //������ ��� � ������� ������� �������
		}
	}
	swap(arr[base], arr[current]);     //������� ������� �������� �� ����� ���������� ������������

	if (current > begin) {
		quicksort(arr, begin, current - 1);//����� ������� ��� ����� ����� �������
	}
	if (end > current + 1) {
		quicksort(arr, current + 1, end);//����� ������� ��� ������ ����� �������
	}
}

// ����� ����������� ����������
template <typename T>
void bubblesort(T* arr, size_t begin, size_t end) {
	if (begin >= end) return;
	for (size_t i = begin; i < end -1 ; i++) {
		for (size_t j = begin; j < end; j++) {
			if (arr[j] > arr[j + 1]) {
				swap(arr[j], arr[j + 1]);
			}
		}
	}
}

// ����� ���������� �����
template <typename T>
void shellsort(T* arr, size_t begin, size_t end) {
	for (size_t gap = end / 2; gap > 0; gap /= 2) {
		for (size_t i = gap; i < end+1; i++) {
			T temp = arr[i];
			size_t j;
			for (j = i; j >= gap && arr[j - gap] > temp; j -= gap) {
				arr[j] = arr[j - gap];
			}
			arr[j] = temp;
		}
	}
}

// ����� ��������� ������
template <typename T>
int binsearch(T* arr, size_t begin, size_t end, T value) {
	size_t left = begin;
	size_t right = end - 1;

	while (left <= right) {
		size_t mid = left + (right - left) / 2; // ������� ��������

		if (arr[mid] == value) { // ���� ������
			return value; // ���������� ������
		}
		else if (arr[mid] < value) { // ���� �������� ������, ���� ������
			left = mid + 1;
		}
		else { // ���� �������� ������, ���� �����
			right = mid - 1;
		}
	}
	return -1; // ���� �� ������
}


// ����� ��������� ������
template <typename T>
int binsearchindex(T* arr, size_t begin, size_t end, T value) {
	size_t left = begin;
	size_t right = end -1;

	while (left <= right) {
		size_t mid = left + (right - left) / 2; // ������� ��������

		if (arr[mid] == value) { // ���� ������
			return mid+1; // ���������� ������
		}
		else if (arr[mid] < value) { // ���� �������� ������, ���� ������
			left = mid + 1;
		}
		else { // ���� �������� ������, ���� �����
			right = mid - 1;
		}
	}
	return -1; // ���� �� ������
}

// ����� ����������������� ������
template <typename T>
int interpolationsearch(T* arr, size_t begin, size_t end, T value) {
	size_t left = begin;
	size_t right = end - 1;

	while (left <= right && value >= arr[left] && value <= arr[right]) {
		// ������� �������, ��������� ������������
		size_t pos = left + ((value - arr[left]) * (right - left) / (arr[right] - arr[left]));

		if (arr[pos] == value) { // ���� ������
			return value; // ���������� ������
		}
		else if (arr[pos] < value) { // ���� �������� ������, ���� ������
			left = pos + 1;
		}
		else { // ���� �������� ������, ���� �����
			right = pos - 1;
		}
	}
	return -1; // ���� �� ������
}

// �� ������������, ��� �������� ������ ���������� ������������.�������� ���������, ��� ����� ���������� ������� ��������, 
// �� ������ ������������� ��������, � ������������ � ����� ��������������� �������, ����� ��������� �������.

//BigO = O(n) ��� ������� ������
//BigO = O(log(log n)) ��� �������� ������
//BigO = O(1) ��� ������� ������
// ����� ����������������� ������
template <typename T>
int interpolationsearchindex(T* arr, size_t begin, size_t end, T value) {
	size_t left = begin;
	size_t right = end - 1;

	while (left <= right && value >= arr[left] && value <= arr[right]) {
		// ������� �������, ��������� ������������
		size_t pos = left + ((value - arr[left]) * (right - left) / (arr[right] - arr[left]));

		if (arr[pos] == value) { // ���� ������
			return pos+1; // ���������� ������
		}
		else if (arr[pos] < value) { // ���� �������� ������, ���� ������
			left = pos + 1;
		}
		else { // ���� �������� ������, ���� �����
			right = pos - 1;
		}
	}
	return -1; // ���� �� ������
}