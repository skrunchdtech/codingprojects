/***************************************
Class: CS251
Assignment Number: 1
Honor Pledge: I pledge that I have not recieved nor given help on this assignment.
***************************************/

#ifndef ARRAY_C
#define ARRAY_C

#include <stdexcept>

#include "Array.h"

#if !defined (__INLINE__)
#define INLINE 
#include "Array.inl"
#endif /* __INLINE__ */

Array::Array (size_t size): max_size_(size), cur_size_(size), array_(new T[size])
{}

// Dynamically initialize an array.

Array::Array (size_t size, const T &default_value): max_size_(size), cur_size_(size), array_(new T [size])
{

	for(size_t i = 0; i < cur_size_; ++i)
	{
		array_[i] = default_value;
	}

}

// The copy constructor (performs initialization). 

Array::Array (const Array &s): max_size_(s.cur_size_), cur_size_(s.cur_size_), array_(new T [s.cur_size_])
{
	for(size_t i = 0; i < cur_size_; ++i)
	{
		array_[i] = s[i];
	}
}

// Compare this array with <s> for equality.

bool
Array::operator== (const Array &s) const
{
	if(s.cur_size_ == cur_size_)
	{
		for(size_t i = 0; i < cur_size_; ++i)
		{
			if(array_[i] != s[i])
			{
				return false;
			}
		}
		
		return true;
	}

	return false;
}

// Compare this array with <s> for inequality.

bool
Array::operator!= (const Array &s) const
{
	return !(*this == s);
}

// Assignment operator (performs assignment). 

Array &
Array::operator= (const Array &s)
{
	if(this == &s) return *this; //Check for self-assignment
	
	if(max_size_<s.cur_size_)
	{
		Array tmp(s);
		
		std::swap(cur_size_, tmp.cur_size_);
		std::swap(max_size_, tmp.max_size_);
		std::swap(array_, tmp.array_);
	}
	else
	{
			
		for(size_t i = 0; i < s.cur_size_; ++i)
		{
			array_[i] = s.array_[i];
		}

		cur_size_ = s.cur_size_; //changed cur_size_ after to safeguard against failure in the for loop
	}


	
	return *this;
}

// Clean up the array (e.g., delete dynamically allocated memory).

Array::~Array (void)
{
	delete [] array_;
}

// = Set/get methods.

// Set an item in the array at location index.  Throws
// <std::out_of_range> if index is out of range, i.e., larger than the
// size() of the array.

void
Array::set (const T &new_item, size_t index)
{
	if(in_range(index))
	{	
		array_[index] = new_item;
		
		
	}
	else
	{
		throw std::out_of_range("Index is out of range");	
	} 
}

// Get an item in the array at location index.  Throws
// <std::out_of_range> if index is out of range, i.e., larger than the
// size() of the array.

void
Array::get (T &item, size_t index) const
{
	if(in_range(index))
	{	
		item = array_[index]; 
	}
	else
	{
		throw std::out_of_range("Index is out of range");	
	} 
	
}

#endif /* ARRAY_C */
