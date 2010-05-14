/********************************************/
/*	vector.h 17th November 2005				*/
/*	(c) Danny Wilson.						*/
/*	www.danielwilson.me.uk					*/
/********************************************/

#ifndef _MYUTILS_VECTOR_H_
#define _MYUTILS_VECTOR_H_

#include "myerror.h"
#include <stdlib.h>
#include <stdio.h>

namespace myutils {
template <typename T>
class Vector {
public:
	/* Preserve public access for back-compatibility */
	// PLUG
	T* element;
	
	/// On destruction, should I delete contents as well?
	bool control_contents;

protected:
	int protected_size;
	int initialized;

public:
	/* Default constructor */
	Vector() {
		initialized = 0;
		initialize (0);
	}
	
	/* Constructor */
	Vector (int size) {
		initialize (size);
	}
	
	/* Constructor */
	Vector (int size, T value) {
		initialize (size);
		for (int i = 0; i < size; i++) {
			element[i] = value;
		}
	}
	
	/* Destructor */
	~Vector() {
		if (protected_size > 0) {
			if (element) {
				delete[] element;
			}
		}
	}
	
	/*
	Delete all contained objects.
	
	Should only do this if the container "owns" them and if it is a "deletable"
	object, i.e. a pointer. 
	*/
	void deleteContents () {
		for (int i = 0; i < size; i++) {
			delete element[i];
		}
	}
	
	Vector<T>& initialize (int size) {
		control_contents = false;
		element = NULL;
		// NOTE: this is the problem line
		element = new T[size];
		if (!element) {
			error ("allocation failure in Vector::initialize()");
		}
		protected_size = size;
		initialized = 1;
		return *this;
	}
	
	/* All current data is lost when the Matrix is resized */
	Vector<T>& resize (int size) {
		if (!initialized) {
			return initialize (size);
		}
		if (size == protected_size) {
			return *this;
		}
		delete[] element;

		element = new T[size];
		if (!element) {
			error ("allocation failure in Vector::resize()");
		}

		protected_size = size;
		return *this;
	}

	int size() {
		return protected_size;
	}
	
	int size() const {
		return protected_size;
	}
	
	/*	void error(char* error_text)
		{
			printf("Run-time error in Vector::");
			printf("%s%\n", error_text);
			printf("Exiting to system...\n");
			exit(13);
		}*/
	
	/*Copy constructor*/
	Vector (const Vector<T> &vec)
	/*
	Copy constructor for the following cases:
		Vector vec2(vec);
		Vector vec2=vec;
	and when Vector is returned from a function.
	*/
	{
		initialize (vec.protected_size);
		int i;
		for (i = 0; i < protected_size; i++) {
			element[i] = vec.element[i];
		}
	}
	
	/*Assignment operator*/
	Vector<T>& operator= (const Vector<T>& vec) {
		resize (vec.size() );
		int i;
		for (i = 0; i < protected_size; i++) {
			element[i] = vec.element[i];
		}
		return *this;
	}
	
#ifdef _VECTOR_
	/*Copy constructor*/
	Vector (const std::vector<T> &vec)
	/*
	Copy constructor for the following cases:
		Vector vec2(vec);
		Vector vec2=vec;
	and when Vector is returned from a function
	*/
	{
		initialize (vec.size() );
		int i;
		for (i = 0; i < protected_size; i++) {
			element[i] = vec[i];
		}
	}
	
	/*Assignment operator*/
	Vector<T>& operator= (const std::vector<T>& vec) {
		resize (vec.size() );
		int i;
		for (i = 0; i < protected_size; i++) {
			element[i] = vec[i];
		}
		return *this;
	}
#endif
#ifdef _MYUTILS_DEBUG
	/*Subscript operator*/
	inline T& operator[] (int pos) {
		if (pos < 0) {
			error ("Vector::operator[](int pos): pos<0");
		}
		if (pos >= protected_size) {
			error ("Vector::operator[](int pos): pos>=size()");
		}
		return element[pos];
	};
#else
	/*Subscript operator*/
	inline T& operator[] (int pos) {
		return element[pos];
	};
#endif

};
};

#endif // _MYUTILS_VECTOR_H_

