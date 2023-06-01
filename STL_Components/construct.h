//
// Created by Administrator on 2023/6/1 0001.
//

#ifndef TINYSTL_STL_COMPONENTS_CONSTRUCT_H_
#define TINYSTL_STL_COMPONENTS_CONSTRUCT_H_

#include <new>
#include "type_traits.h"
#include "iterator.h"
#include "utils.h"

namespace stl {
// construct
// placement new
template<class T>
void construct(T* ptr) {
  new((void*) ptr) T();
}

template<class T1, class T2>
void construct(T1* ptr, const T2& v) {
  new((void*) ptr) T1(v);
}

template<class T1, class... Args>
void construct(T1* ptr, const Args& ... args) {
  ::new((void*) ptr) T1(stl::forward<Args>(args)...);
}

// destroy

template<class T>
void destroy(T* p) {
  destroy_one(p);
}

template<class ForwardIter>
void destroy(ForwardIter first, ForwardIter last) {
  destroy_range(first, last, std::is_trivially_destructible<ForwardIter>());
}

// 若是编译期默认生成的析构函数 则不需要特殊执行destroy
template<class T>
void destroy_one(T* p) {
  destroy_one(p, std::is_trivially_destructible<T>());
}

template<class T>
void destroy_one(T* p, std::true_type) {

}

template<class T>
void destroy_one(T* p, std::false_type) {
  if (p) p->~T();
}

template<class ForwardIter>
void destroy_range(ForwardIter first, ForwardIter last, std::true_type) {}

template<class ForwardIter>
void destroy_range(ForwardIter first, ForwardIter last, std::false_type) {
  while (first != last) {
    destroy(&*first);
    ++first;
  }
}

}

#endif //TINYSTL_STL_COMPONENTS_CONSTRUCT_H_
