#pragma once

#include <iostream>

// Danh sach lien ket don (Khanh)
// DataType can co ham Display() neu muon dung LinkedList::display().

template <class DataType>
class Node {
public:
    DataType _data;
    Node* _pNext;

    Node(const DataType& data) : _data(data), _pNext(nullptr) {}
    void display() { _data.Display(); }
};

template <class DataType>
class LinkedList {
public:
    Node<DataType>* _pHead;
    Node<DataType>* _pTail;
    int _iSize;

    LinkedList() : _pHead(nullptr), _pTail(nullptr), _iSize(0) {}
    ~LinkedList() { clear(); }

    int size() const { return _iSize; }
    bool isEmpty() const { return _pHead == nullptr; }

    void addTail(const DataType& data);
    void display();
    void clear();

    // Tim node dau tien thoa dieu kien match(data), tra ve nullptr neu khong co
    template <class Predicate>
    Node<DataType>* search(Predicate match);

    // Xoa node dau tien thoa dieu kien match(data), tra ve true neu da xoa
    template <class Predicate>
    bool remove(Predicate match);

private:
    // Khong cho phep sao chep de tranh giai phong mot node hai lan
    LinkedList(const LinkedList&);
    LinkedList& operator=(const LinkedList&);
};

template <class DataType>
void LinkedList<DataType>::addTail(const DataType& data) {
    Node<DataType>* pAdd = new Node<DataType>(data);
    if (_pHead == nullptr) {
        _pHead = _pTail = pAdd;
    }
    else {
        _pTail->_pNext = pAdd;
        _pTail = pAdd;
    }
    _iSize++;
}

template <class DataType>
void LinkedList<DataType>::display() {
    for (Node<DataType>* pWalker = _pHead; pWalker != nullptr; pWalker = pWalker->_pNext) {
        pWalker->display();
        std::cout << std::endl;
    }
}

template <class DataType>
void LinkedList<DataType>::clear() {
    Node<DataType>* pWalker = _pHead;
    while (pWalker != nullptr) {
        Node<DataType>* pTemp = pWalker;
        pWalker = pWalker->_pNext;
        delete pTemp;
    }
    _pHead = _pTail = nullptr;
    _iSize = 0;
}

template <class DataType>
template <class Predicate>
Node<DataType>* LinkedList<DataType>::search(Predicate match) {
    Node<DataType>* p = _pHead;
    while (p != nullptr && !match(p->_data)) {
        p = p->_pNext;
    }
    return p;
}

template <class DataType>
template <class Predicate>
bool LinkedList<DataType>::remove(Predicate match) {
    Node<DataType>* pPrev = nullptr;
    Node<DataType>* pWalker = _pHead;
    while (pWalker != nullptr && !match(pWalker->_data)) {
        pPrev = pWalker;
        pWalker = pWalker->_pNext;
    }
    if (pWalker == nullptr) return false;

    if (pPrev == nullptr) _pHead = pWalker->_pNext;
    else pPrev->_pNext = pWalker->_pNext;

    if (pWalker == _pTail) _pTail = pPrev;

    delete pWalker;
    _iSize--;
    return true;
}
