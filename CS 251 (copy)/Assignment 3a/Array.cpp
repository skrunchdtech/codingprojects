/***************************************
Class: CS251
Assignment Number: 2
Honor Pledge: I pledge that I have not recieved nor given help on this assignment.
***************************************/

#ifndef ARRAY_CPP
#define ARRAY_CPP

#include <sys/types.h>

#include <algorithm>
#include <sstream>

#include "Array.h"

#if !defined (__INLINE__)
#define INLINE
#include "Array.inl"
#endif /* __INLINE__ */

template <typename T> 
Array<T>::Array (size_t size):max_size_(size), 
cur_size_(size),
default_value_(0), 
array_(new T[size]) 
{}

template <typename T> 
Array<T>::Array (size_t size, const T &default_value):max_size_(size), 
cur_size_(size), 
default_value_(new T(default_value)), 
array_(new T[size])
{
	std::fill(begin(), end(), default_value);
}

// The copy constructor (performs initialization).

template <typename T> 
Array<T>::Array (const Array<T> &s):max_size_(s.cur_size_), 
cur_size_(s.cur_size_), 
default_value_(s.default_value_.get() ? new T(*s.default_value_) :0), 
array_(new T[s.cur_size_])
{
	std::copy(s.begin(), s.end(), begin());
}

template <typename T> void
Array<T>::resize (size_t new_size)
{
	
    if(new_size > max_size_)
	{
 
        size_t physical_size = std::max(new_size, max_size_*2);
      
		scoped_array<T> temp(new T[physical_size]);
      
        std::copy(begin(),end(), temp.get());

        array_.swap(temp);

        max_size_ = physical_size; //change max_size_
    }
	
	if(cur_size_<new_size) //will still access if new_size > max_size_
	{
        
		if(default_value_.get() != 0) 
	    {
			std::fill(array_.get()+cur_size_, array_.get()+new_size, 
                        *default_value_);
	    } 
	}
		
	//cur_size_ is always updated; put last for strong safety
    cur_size_ = new_size;
	
}

template <typename T> void
Array<T>::swap (Array<T> &new_array)
{
      T *dv1 = default_value_.release ();
      
      T *dv2 = new_array.default_value_.release ();

      default_value_.reset (dv2);

      new_array.default_value_.reset (dv1);

      array_.swap(new_array.array_);

      std::swap(max_size_, new_array.max_size_);

      std::swap(cur_size_, new_array.cur_size_);
}

// Assignment operator (performs assignment). 

template <typename T> Array<T> &
Array<T>::operator= (const Array<T> &s)
{
    if (this == &s) return *this; // Check for self-assignment

    Array<T> temp (s);

    swap (temp);

    return *this; //for chaining
}

// Clean up the array (e.g., delete dynamically allocated memory).

template <typename T> 
Array<T>::~Array (void) //do nothing because auto_ptr cleans up itself
{}

// = Set/get methods.

// Set an item in the array at location index.  
// Set an item in the array at location index.  If <index> >=
  // <s.cur_size_> then <resize()> the array so it's big enough.
  // Throws <std::bad_alloc> if resizing the array fails.
template <typename T> void
Array<T>::set (const T &new_item, size_t index)
{
    if(!in_range(index))
	{
        //resize takes what new cur_size_ needs to be
		resize(index+1);
	}
	
    array_[index] = new_item;		
}

// Get an item in the array at location index.
// Get an item in the array at location index.  Throws <std::out_of_range>
  // of index is not <in_range>.
template <typename T> void
Array<T>::get (T &item, size_t index)
{
    if(in_range(index))
	{	
		item = array_[index]; 
	}
	else
	{
        //returns the index number that caused the exception to be thrown
        std::stringstream index_str;

        //cast to int in case user entered negative number
        index_str << static_cast <int> (index);

        throw std::out_of_range (index_str.str ());	
	} 
}

// Compare this array with <s> for equality.

template <typename T> bool
Array<T>::operator== (const Array<T> &s) const
{
    return s.cur_size_ == cur_size_ && std::equal(begin(),end(), s.begin());
}

// Compare this array with <s> for inequality.

template <typename T> bool
Array<T>::operator!= (const Array<T> &s) const
{
    return !(*this == s);
}

template <typename T>
Array_Iterator<T>::Array_Iterator (Array<T> &array, size_t pos): array_(array), 
pos_(pos)
{}

template <typename T>
Const_Array_Iterator<T>::Const_Array_Iterator (const Array<T> &array, size_t pos): 
array_(array), 
pos_(pos)
{}

#endif /* ARRAY_CPP */
