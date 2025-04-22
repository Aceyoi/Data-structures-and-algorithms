//���������� ���� ���-22
#pragma once

#include <iostream>
#include <vector>
#include "DinamicArray.Modul.h"

using namespace std;

//��������� ����� ������������� �������
template <typename T>
class DynamicArray {
public: // ���� ������ 
	T* array;         // ��������� �� ��������� �������
	size_t capacity; // ������� �������
	size_t length;  // ������� ������ �������


	//����� ���������� ���������� ��� ������ ������
	void re_memory() {
		this->capacity = length * 30; //���������� ������� ������� 
		T* arr = new T[capacity];	   //�������� ���������� � ��������� ��� ���� ������ �����	
		memcpy(arr, this->array, sizeof(T) * length);
		//*������� �������� sizeof(T) * length ���� �� ������� ������, �� ������� ��������� array, � ������� ������, �� ������� ��������� arr. 
		//*������� ���������� ����� ���������� arr. 		
		delete[] this->array;						  //�������� ������ ������� ������� array
		this->array = arr;							  //������������ ������ ������ array ������ ��������� �� ������� arr
	}


public:
	//����������� ��� ����������
	DynamicArray() {
		this->length = 0;
		this->array = new T;// �������� ����� ��� ���� ������� 
		this->capacity = 1;
	}

	//����������� � ����������
	//len - ����� �������
	DynamicArray(size_t len) {
		this->length = len;
		this->capacity = len;
		this->array = new T[capacity];

	}

	//����������� � �����������
	//len ����� �������
	//arr - ������
	DynamicArray(size_t len, vector<T>& arr) {
		this->length = len;
		this->capacity = len;
		this->array = new T[capacity];

		memcpy(array, arr.data(), sizeof(T) * len);
	}

	//����������� �����������
	DynamicArray(DynamicArray<T>& arr) : DynamicArray{ arr.size(), arr.get_array() } {}

	//����������, ������� ������, ���������� ��� ������
	~DynamicArray() {
		delete[] this->array;
	}

	//����� ������ ������������� ������� 
	void conclusion() {
		for (int i = 0; i < length; i++) {
        cout << array[i] << ' ';}
        cout << endl;
	};

	//����� ������ ���������� �������� ������������� ������� 
	T conclusion_back() {
		return array[length-1];
	};

	//����� ������ ������� �������� ������������� ������� 
	T conclusion_up() {
		return array[0];
	};

	//����� ������ �������� ������������� ������� //����� ��� ������ ������� � int
	T conclusion_int(int i) {
		return array[i];
	};

	//����� ������ ������� �������� ������������� ������� 
	T conclusion_index(size_t pos) {
		return array[pos-1];
	};

	//����� ������� �������� ������������� �������
	void clear() {
		delete[] this->array;
		this->length = 0;
		this->array = new T;
		this->capacity = 1;
	}

	//����� �������� �������� �� ����� ������������� �������
	void del_back() {
		if (length > 0) {
			this->length--;
			if (length * 4 < capacity) { //�������� ��� ������ ������ ������, ���� ������ ���������� ���������� ���
				re_memory();
			}
		}
	}

	//����� �������� �������� �� ������ ������������� �������
	void del_up() {
		if (length > 0) {
			for (size_t i = 0; i < length; i++) { //�������� ������� ���� �� �� �������� ��������� � �������, ����� �������
				array[i] = array[i + 1];
			}
			this->length--;
			if (length * 4 < capacity) { //�������� ��� ������ ������ ������, ���� ������ ���������� ���������� ���
				re_memory();
			}
		}
	}

	//����� �������� �������� �� ������ pos �� ������������� �������
	void del_Index(size_t pos) {
		if (length > 0) {

			for (size_t i = pos-1; i < length; i++) { //����� ��������� ����� pos �� ���� ������� ������
				array[i] = array[i+1];
			}
			this->length--;

			if (length * 4 < capacity) {//�������� ��� ������ ������ ������, ���� ������ ���������� ���������� ���
				re_memory();
			}
		}
	}

	//����� �������� �������� �� �������� X �� ������������� �������
	void del(size_t X) {
		if (length > 0) {

			for (size_t i = 0; i < array[X]; i++) {
				array[X] = array[i-1];
				this->length--;
			}

			if (length * 4 < capacity) {//�������� ��� ������ ������ ������, ���� ������ ���������� ���������� ���
				re_memory();
			}
		}
	}

	//����� �������� ���� �� ����� � ������������ �������
	bool searchcheck(T find) {
		for (size_t i = 0; i < length; i++) { 
			if (array[i] == find) {               
				return true;                      
			}
		}
		return false;
	}

	//����� �������� ������ �� ������������ ������
	bool nullcheck() {
			if (length == 0) {
				return true;
			}
		return false;
	}

	//����� ���������� �������� X � ����� ������������� �������
	void add_back(T X) {
		if (length == this->capacity) {//���� ���������� ������ ��� ��������� 
			re_memory();
		}		//�� ������������ ��������� ����� ������

		array[length] = X;
		this->length++;
	}

	//����� ���������� �������� X � ������ ������������� �������
	void add_up(T X) {
		if (length == capacity) {//���� ���������� ������ ��� ��������� 
			re_memory();
		}		//�� ������������ ��������� ����� ������

		for (size_t i = length; i > 0; i--) { //����� ��������� ����� pos �� ���� ������� ������
			array[i] = array[i - 1];
		}
		array[0] = X;
		this->length++;
	}

	//����� ���������� �������� X �� ������ pos � ������������ �������
	void add_index(T elem, size_t pos) {
			if (length == capacity) { //���� ���������� ������ ��� ��������� 
				re_memory();		  //�� ������������ ��������� ����� ������ 
			}

			for (size_t i = length; i+1 > pos; i--) { //����� ��������� ����� pos �� ���� ������� ������
				array[i] = array[i - 1];
			}
			array[pos-1] = elem;
			this->length++;
	}

	//����� �� �������� ���������� �� max � min ��� �� min � max � ������������ �������
	bool sort_check() {
		if (array[1] < array[2]) {
			for (size_t i = 0; i < this->length - 1; i++) {
				if (array[i] < array[i + 1]) {
					return true;
				}
			};
		}
		return false;
	}
	
	//����� ���������� �������� � ������������ �������
	void sort_merge() {
		mergesort(this->array, 0, this->length);
	}
	//����� ������� ���������� � ������������ �������
	void sort_quick() {
		quicksort(this->array, 0, this->length-1);
	}
	//����� ���������� ����� � ������������ �������
	void sort_shell() {
		shellsort(this->array, 0, this->length-1);
	}
	//����� ���������� ��������� � ������������ �������
	void sort_bubble() {
		bubblesort(this->array, 0, this->length-1);
	}
	//����� ��������� ������ ����� � ������������ ������� � ������� �����
	int search_bin(int X) {
		return binsearch(this->array, 0, this->length, X);
	}
	//����� ��������� ������ ����� � ������������ ������� � ������� �������
	int search_bin_index(int X) {
		return binsearchindex(this->array, 0, this->length, X);
	}
	//����� �������������� ������ ����� � ������������ ������� � ������ �����
	int search_interpolation(int X) {
		return interpolationsearch(this->array, 0, this->length, X);
	}
	//����� �������������� ������ ����� � ������������ ������� � ������ �������
	int search_interpolation_index(int X) {
		return interpolationsearchindex(this->array, 0, this->length, X);
	}
};

