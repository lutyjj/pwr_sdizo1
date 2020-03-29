#include <iostream>
#include <random>
#include <fstream>
#include "Array.h"

Array::Array() {
	size = 0;
	head = new int[size];
}

void Array::display() {
	int* tmp = head;
	if (tmp) {
		for (int i = 0; i < size; i++) {
			std::cout << tmp[i] << " ";
		}
	}
}

void Array::push_front(int value) {
	int sizeNew = size + 1;
	int* arrayNew = new int[sizeNew];
	arrayNew[0] = value;
	for (int i = 0; i < size; i++) {
		arrayNew[i + 1] = head[i];
	}
	delete[] head;
	head = arrayNew;
	size++;
}

void Array::push_at(int value, int index) {
	if (size == 0) push_front(value);
	else if (index >= size) push_back(value);
	else {
		int* arrayNew = new int[size + 1];
		for (int i = 0; i < index; i++) {
			arrayNew[i] = head[i];
		}
		arrayNew[index] = value;
		for (int i = index; i < size; i++) {
			arrayNew[i+1] = head[i];
		}
		delete[] head;
		head = arrayNew;
		size++;
	}
}

void Array::push_back(int value) {
	int* arrayNew = new int[size + 1];
	arrayNew[size] = value;
	for (int i = 0; i < size; i++) {
		arrayNew[i] = head[i];
	}
	delete[] head;
	head = arrayNew;
	size++;
}

void Array::pop_front() {
	if (head && size > 0) {
		int* arrayNew = new int[size - 1];
		for (int i = 0; i < size - 1; i++) {
			arrayNew[i] = head[i + 1];
		}
		delete[] head;
		head = arrayNew;
		size--;
	}
}

void Array::pop_at(int index) {
	if (index == 0) pop_front();
	else if (index > size) pop_back();
	else {
		int* newArray = new int[size - 1];
		for (int i = 0; i < index; i++) {
			newArray[i] = head[i];
		}
		for (int i = index; i < size - 1; i++) {
			newArray[i] = head[i + 1];
		}
		delete[] head;
		head = newArray;
		size--;
	}
}

void Array::pop_back() {
	if (head && size > 0) {
		int* arrayNew = new int[size - 1];
		for (int i = 0; i < size - 1; i++) {
			arrayNew[i] = head[i];
		}
		//delete[] head;
		head = arrayNew;
		size--;
	}
}

bool Array::search(int value) {
	if (head && size > 0) {
		for (int i = 0; i < size; i++) {
			if (head[i] == value) {
				return true;
				break;
			}
		}
	}
	return false;
}

void Array::fill_random(int size) {
	std::random_device rd;
	std::mt19937 rng(rd());
	std::uniform_int_distribution<std::mt19937::result_type> dist(0, 100);

	// Clear array
	delete[] head;
	head = new int[size];
	this->size = 0;
	// Fill array with random numbers between [0, 100]
	while (size) {
		push_back(dist(rng));
		size--;
	}
}

void Array::readFromFile(std::string fileName) {
	// Clear list
	delete[] head;
	std::ifstream file;
	int value;
	// Open file with entered name
	file.open(fileName);
	// Check if file exists
	if (file) {
		// First line is always reserved for number of elements
		// as per project requierements
		file >> value;
		std::cout << "Number of items: " << value;
		// Push every value from file to tail of list
		while (file >> value) {
			push_back(value);
		}
	}
	else std::cerr << "Error while reading file";
	file.close();
}