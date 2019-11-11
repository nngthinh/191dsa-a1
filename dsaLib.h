/* Created by Nguyen Duc Dung on 2019-09-03.
 * =========================================================================================
 * Name        : dsaLib.h
 * Author      : Duc Dung Nguyen
 * Email       : nddung@hcmut.edu.vn
 * Copyright   : Faculty of Computer Science and Engineering - HCMUT
 * Description : The data structure library for Assignment 1
 * Course      : Data Structure and Algorithms - Fall 2019
 * =========================================================================================
 */

#ifndef DSA191_A1_DSALIB_H
#define DSA191_A1_DSALIB_H
#include <string>
#include <stdio.h>
#include <string.h>
#include <iostream>

using namespace std;

class DSAException {
	int     _error;
	string  _text;
public:

	DSAException() : _error(0), _text("Success") {}
	DSAException(int err) : _error(err), _text("Unknown Error") {}
	DSAException(int err, const char* text) : _error(err), _text(text) {}

	int getError() { return _error; }
	string& getErrorText() { return _text; }
};

template <class T>
struct L1Item {
	T data;
	L1Item<T>* pNext;
	L1Item() : pNext(NULL) {}
	L1Item(T& a) : data(a), pNext(NULL) {}
};

template <class T>
class L1List {
	L1Item<T>* _pHead;// The head pointer of linked list
	L1Item<T>* _pTail;// The last pointer of linked list
	size_t      _size;// number of elements in this list

	int id_max;
public:
	L1List() : _pHead(NULL), _pTail(NULL), _size(0), id_max(-1) {}
	~L1List();

	void    clean();
	bool    isEmpty() {
		return _pHead == NULL;
	}
	size_t  getSize() {
		return _size;
	}

	T& at(int i);// give the reference to the element i-th in the list
	T& operator[](int i);// give the reference to the element i-th in the list

	bool    find(T& a, int& idx);// find an element similar to a in the list. Set the found index to idx, set idx to -1 if failed. Return true if success.
	int     insert(int i, T& a);// insert an element into the list at location i. Return 0 if success, -1 otherwise
	int     remove(int i);// remove an element at position i in the list. Return 0 if success, -1 otherwise.

	int     push_back(T& a);// insert to the end of the list
	int     insertHead(T& a);// insert to the beginning of the list

	int     removeHead();// remove the beginning element of the list
	int     removeLast();// remove the last element of the list

	void    reverse();

	void    traverse(bool (op)(T&, void*&, void*&), void*& pParam_1, void*& pParam_2) {
		L1Item<T>* _pCur = _pHead;
		while (_pCur != NULL) {
			if ((op)(_pCur->data, pParam_1, pParam_2)) break;
			_pCur = _pCur->pNext;
		}
		return;
	}
	void    traverse(bool (op)(T&, void*&, void*&, void*&), void*& pParam_1, void*& pParam_2, void*& pParam_3) {
		L1Item<T>* _pCur = _pHead;
		while (_pCur != NULL) {
			if ((op)(_pCur->data, pParam_1, pParam_2, pParam_3)) break;
			_pCur = _pCur->pNext;
		}
		return;
	}
	int get_IDmax() {
		return id_max;
	}
	void set_IDmax(int& id_max) {
		this->id_max = id_max;
		return;
	}
};


template <class T>
void L1List<T>::clean() {
	if (isEmpty()) return;
	L1Item<T>* _pCur = _pHead;
	L1Item<T>* _pNext;
	while (_pCur != NULL) {
		_pNext = _pCur->pNext;
		delete _pCur;
		_pCur = _pNext;
	}
	_pHead = NULL;
	_pTail = NULL;
}

template <class T>
T& L1List<T>::at(int i) {
	if (isEmpty()) return _pHead->data;
	L1Item<T>* _pCur = _pHead;
	int count = 0;
	while (count < i) {
		_pCur = _pCur->pNext;
		count++;
	}
	return _pCur->data;
}

template <class T>
T& L1List<T>::operator[](int i) {
	if (isEmpty()) return NULL;
	L1Item<T>* _pCur = _pHead;
	int count = 0;
	while (count < i) {
		_pCur = _pCur->pNext;
		count++;
	}
	return _pCur;
}

template <class T>
bool L1List<T>::find(T& a, int& idx) {
	if (isEmpty()) {
		idx = -1;
		return false;
	}
	L1Item<T>* _pCur = _pHead;
	int count = 0;
	while (_pCur->data != a) {
		_pCur = _pCur->pNext;
		count++;
	}
	if (_pCur->data == a) {
		idx = count;
		return true;
	}	
}

template <class T>
int L1List<T>::insert(int i, T& a) {
	if (i < 0 || i > _size) return -1;
	if (i < _size) {
		L1Item<T>* _pa = new L1Item<T>;
		L1Item<T>* _pCur = _pHead;
		L1Item<T>* _pPre = _pCur;

		_pa->data = a;

		int count = 0;
		while (count < i) {
			_pPre = _pCur;
			_pCur = _pCur->pNext;
			count++;
		}
		_pPre->pNext = _pa;
		_pa->pNext = _pCur;

		_size++;
		return 0;
	}
	else {
		push_back(a);
		return 0;
	}
	return -1;
}

template <class T>
int L1List<T>::remove(int i) {
	if (_size < 0 || i > _size - 1) return -1;
	L1Item<T>* _pCur, * _pPre;
	if (i == 0) {
		_pCur = _pHead;
		_pHead = _pHead->pNext;
	}
	else {
		_pPre = _pHead;
		for (int j = 0; j < i - 1; j++) {
			_pPre = _pPre->pNext;
		}
		_pCur = _pPre->pNext;
		_pPre->pNext = _pCur->pNext;
	}
	delete _pCur;
	_size--;
	return 0;
}

/// Insert item to the end of the list
/// Return 0 if success, -1 otherwise
template <class T>
int L1List<T>::push_back(T& a) {
	L1Item<T>* _pa = new L1Item<T>(a);
	if (isEmpty()) {
		_pHead = _pa;
		_pTail = _pa;
	}
	else {
		_pTail->pNext = _pa;
		_pTail = _pa;
	}
	_size++;
	return 0;
}

/// Insert item to the front of the list
/// Return 0 if success, -1 otherwise
template <class T>
int L1List<T>::insertHead(T& a) {
	L1Item<T>* _pa = new L1Item<T>(a);
	if (isEmpty()) {
		_pHead = _pa;
		_pTail = _pa;
	}
	else {
		_pa->pNext = _pHead;
		_pHead = _pa;
	}
	_size++;
	return 0;
}

/// Remove the first item of the list
/// Return 0 if success, s-1 otherwise
template <class T>
int L1List<T>::removeHead() {
	if (isEmpty()) return -1;
	L1Item<T>* _pCur = _pHead;
	_pHead = _pCur->pNext;

	delete _pCur;
	_pCur = nullptr;

	_size--;
	if (_size == 0) _pTail = nullptr;
	return 0;
}

/// Remove the last item of the list
/// Return 0 if success, -1 otherwise
template <class T>
int L1List<T>::removeLast() {
	if (isEmpty()) return -1;
	L1Item<T>* _pCur = _pHead;
	while (_pCur != _pTail)
		_pCur = _pCur->pNext;

	delete _pTail;
	_pTail = nullptr;

	_size--;
	if (_size == 0) _pHead = nullptr;
	return 0;
}

#endif DSA191_A1_DSALIB_H
