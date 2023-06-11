//
// Created by Administrator on 2023/5/31 0031.
//

#ifndef TINYSTL_STL_COMPONENTS_VECTOR_H_
#define TINYSTL_STL_COMPONENTS_VECTOR_H_

#include <initializer_list>

#include "exceptdef.h"
#include "iterator.h"
#include "utils.h"
#include "memory.h"

namespace stl {
template<class T, class Alloc = stl::allocator<T>>
class vector {
  static_assert(!std::is_same<T, bool>::value, "vector<bool> is not allowed!");
 public:
  typedef Alloc allocator_type;
  typedef Alloc data_allocator;

  typedef typename allocator_type::value_type value_type;
  typedef typename allocator_type::pointer pointer;
  typedef typename allocator_type::const_pointer const_pointer;
  typedef typename allocator_type::reference reference;
  typedef typename allocator_type::const_reference const_reference;
  typedef typename allocator_type::size_type size_type;
  typedef typename allocator_type::difference_type difference_type;

  typedef value_type* iterator;
  typedef const value_type* const_iterator;
  typedef stl::reverse_iterator<iterator> reverse_iterator;
  typedef stl::reverse_iterator<const_iterator> const_reverse_iterator;

  allocator_type get_allocator() {
    return allocator_type();
  }

 private:
  iterator _begin;
  iterator _end;
  iterator _cap;
};
}

#endif //TINYSTL_STL_COMPONENTS_VECTOR_H_


