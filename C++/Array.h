#ifndef __ARRAY_H
#define __ARRAY_H

#include <iostream>
#include <string.h>
#include <vector>
#include "Department.h"
#include <set>
#include <algorithm>
#include <fstream>
#pragma warning(disable:4996)
using namespace std;


template<class T>
class Array
{
	int physicalSize, logicalSize;
	char delimeter;
	T* arr;
public:
	Array(int size = 1, char delimeter = ' ');
	Array(const Array& other);
	~Array();

	const Array& operator=(const Array& other);
	const Array& operator+=(const T& NewVal);
	bool operator==(const T& NewVal);
	//get f
	int getphysicalSize()    const { return physicalSize; }
	int getlogicalSize()    const { return logicalSize; }

	friend ostream& operator<<(ostream& os, const Array& arr)
	{
		for (int i = 0; i < arr.logicalSize; i++)
			os << *arr.arr[i] << arr.delimeter;
		return os;
	}
	void Array_resizing();
	//files
	void load_arr(ifstream& inFile);// c'tor that reads from file
	void save_arr(ofstream & outFile) const;

	
};
template<class T>
Array<T>::Array(int maxsize, char delimeter)
	:physicalSize(maxsize), logicalSize(0), delimeter(delimeter)
{
	arr = new T[physicalSize];
}
template<class T>
Array<T>::Array(const Array& other)
	: arr(NULL)
{
	*this = other;
}
template<class T>
Array<T>::~Array()
{
	delete[] arr;
}
template<class T>
const Array<T>& Array<T>::operator=(const Array& other)
{
	if (this != &other)
	{
		delete[] arr;
		physicalSize = other.physicalSize;
		logicalSize = other.logicalSize;
		delimeter = other.delimeter;
		arr = new T[physicalSize];
		for (int i = 0; i < other.logicalSize; i++)
			arr[i] = other.arr[i];
	}
	return *this;
}
template<class T>
bool Array<T>::operator==(const T& NewVal)
{
	for (int index = 0; index < logicalSize; index++)
	{
		if (*(arr[index]) == (*NewVal))
			return true;
	}
	return false;
}
template<class T>
const Array<T>& Array<T>::operator+=(const T& NewVal)
{
	if (logicalSize == physicalSize)
	{
		Array_resizing();
	}
	arr[logicalSize++] = NewVal;
	return *this;
}
template<class T>
void Array<T>::Array_resizing()
{

	physicalSize *= 2;
	T* temp_arr = new T[physicalSize];
	for (int index = 0; index < logicalSize; index++)
	{
		temp_arr[index] = arr[index];
	}
	delete[]arr;
	arr = temp_arr;
}
//files
template<class T>
void Array<T>::load_arr(ifstream& inFile)
{
	inFile.read((char*)& physicalSize, sizeof(physicalSize));
	inFile.read((char*)& logicalSize, sizeof(logicalSize));
	delete[] arr;
	arr = new T[physicalSize];
	for (int index = 0; index < logicalSize; index++)
	{
		arr[index] = arr[index]->load_pointer(inFile);
	}
}
template<class T>
void  Array<T>::save_arr(ofstream & outFile) const
{
	outFile.write((const char*)& physicalSize, sizeof(physicalSize));
	outFile.write((const char*)&  logicalSize, sizeof(logicalSize));
	for (int index = 0; index < logicalSize; index++)
		arr[index]->save(outFile);
}
template<class T>
void printCollection(T& collection) throw (const char*)
{

	T::iterator  itr = collection.begin();
	T::iterator  itrEnd = collection.end();
	try
	{
		if (itr == itrEnd)
			throw "Collection Empty";
			
		for (; itr != itrEnd; ++itr)
			cout << **itr << endl;
	}
	catch (const char* msg) { cout << msg << endl << endl; }
}
template<class T, class S>
void Erase_spesicfic_element(T& collection, const S& NewVal)
{
	T::iterator  itr = collection.begin();
	T::iterator  itrEnd = collection.end();
	for (; itr != itrEnd; ++itr)
		if ((**itr) == (*NewVal))
		{
			collection.erase(itr);
			return;
		}
}
#endif 
