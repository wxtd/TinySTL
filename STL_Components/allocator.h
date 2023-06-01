//
// Created by Administrator on 2023/6/1 0001.
//

#ifndef TINYSTL_STL_COMPONENTS_ALLOCATOR_H_
#define TINYSTL_STL_COMPONENTS_ALLOCATOR_H_

#include "construct.h"
#include "utils.h"

namespace stl {

template<class T>
class allocator {
 public:
  typedef T value_type;
  typedef T* pointer;
  typedef const T* const_pointer;
  typedef T& reference;
  typedef const T& const_reference;
  typedef size_t size_type;
  typedef ptrdiff_t difference_type;

  static T* allocate() {
    return static_cast<T*>(::operator new(sizeof(T)));
  }

  static T* allocate(size_type n) {
    if (n == 0) return nullptr;
    return static_cast<T*>(::operator new(n * sizeof(T)));
  }

  static void deallocate(T* p, size_type n = 0) {
    if (p) {
      ::operator delete(p);
    }
  }

  static void construct(T* p) {
    stl::construct(p);
  }

  static void construct(T* p, const T& v) {
    stl::construct(p, v);
  }

  static void construct(T* p, T&& v) {
    stl::construct(p, stl::move(v));
  }

  template<class... Args>
  static void construct(T* p, Args... args) {
    stl::construct(p, stl::forward<Args>(args)...);
  }

  static void destroy(T* p) {
    stl::destroy(p);
  }

  static void destroy(T* first, T* last) {
    stl::destroy(first, last);
  }
};
}

#endif //TINYSTL_STL_COMPONENTS_ALLOCATOR_H_
