#ifndef VECTOR_H_INCLUDED
#define VECTOR_H_INCLUDED

#include <cstring>

using namespace std;

template <class Type>
class vector {
private:
    Type* A;
    int _size, _current;
public:
    void push_back(Type x) {
        if (this->_current == this->_size) {
            Type* temp = new Type[this->_size * 2];
            for (int i = 0; i < this->_size; ++i) {
                temp[i] = A[i];
            }
            delete[]A;
            this->_size *= 2;
            A = temp;
        }

        A[this->_current++] = x;
    }

    void pop_back() {
        if (this->_current) {
            --this->_current;
        }
    }

    Type back() {
        return this->A[this->_current - 1];
    }

    Type& operator[](int index) {
        return A[index];
    }

    int size() {
        return this->_current;
    }

    vector() {
        this->A = new Type[1];
        this->_size = 1;
        this->_current = 0;
    }

    vector(int _size) {
        this->A = new Type[_size];
        this->_size = _size;
        this->_current = 0;
    }

    vector(int _size, Type temp) {
        this->_size = _size;
        this->_current = _size;
        this->A = new Type[_size];
        for (int i = 0; i < _size; ++i) {
            this->A[i] = temp;
        }
    }

    Type* begin() {
        return this->A;
    }
    Type* end() {
        return (&this->A[this->_current]);
    }

    ~vector() {
        //delete[]A;
    }
};

#endif // VECTOR_H_INCLUDED
