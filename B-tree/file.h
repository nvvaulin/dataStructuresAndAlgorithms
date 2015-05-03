#pragma once
#include "binary.h"
#include <iostream>
#include <stdio.h>
#include <map>
#include <fstream>
#include "AVLTree.h"
#define Tpos size_t

using namespace std;

template <class T> struct binary;

template <class T>
class File{
    string name;
    fstream fstr;
public:
	friend class binary<T>;
    File(string n) : name(n), fstr(name, ios_base::binary | ios_base::out | ios_base::in){}
	void close() {
		fstr.close();
	}

    ~File(){
        fstr.close();
    }

	void insert(T& elem, size_t pos){
		binary<T> w(elem);
		fstr.seekp(pos*sizeof(T));
		fstr<<w;
	}
	T operator[](size_t pos){
		T p=T();
		binary<T> w(p);
		fstr.seekg(pos*sizeof(T));
		fstr>>w;
		return w.data;
	}
};
