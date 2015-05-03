#pragma once
#include <iostream>
#include <stdio.h>
#include <map>
#include <fstream>
#include "AVLTree.h"
#define Tpos size_t

using namespace std;

template <class T> class File;

template <class T>
struct binary 
{
    T data;
    binary() : data(){}
    binary(T const & __t): data(__t){}
    operator T&() { 
		return data; 
	}
    operator T const &() const {
		return data; 
	}
    binary& operator=(T const & rhs){
		data=rhs; return (*this);
	}
    void flush(File<T>& f){
        f.fstr.seekp(T.position*sizeof(T));
        f.fstr<<(data);
    }
};

template <class T>
istream & operator>>(istream & is, binary<T> & wt) {
    is.read(reinterpret_cast<char *>(&static_cast<T &>(wt)), sizeof(T));
    return is;
}

template <class T>
ostream & operator<<(ostream & os, binary<T> const & wt) {
    os.write(reinterpret_cast<char const *>(&static_cast<T const &>(wt)), sizeof(T));
    os.flush();
    return os;
}
