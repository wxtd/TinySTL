//
// Created by Administrator on 2023/5/31 0031.
//

#ifndef TINYSTL_STL_COMPONENTS_ITERATOR_H_
#define TINYSTL_STL_COMPONENTS_ITERATOR_H_

# include <cstddef>

#include "type_traits.h"

namespace stl {
struct input_iterator_tag {}; // 输入迭代器
struct output_iterator_tag {};  // 输出迭代器
struct forward_iterator_tag : public input_iterator_tag {}; // 前向迭代器
struct bidirectional_iterator_tag : public forward_iterator_tag {}; // 双向迭代器
struct random_access_iterator_tag : public bidirectional_iterator_tag {}; // 随机访问迭代器

// iterator
template<class Category, class T, class Distance = ptrdiff_t,
    class Pointer = T *, class Reference = T &>
struct iterator {
  typedef Category iterator_category;
  typedef T value_type;
  typedef Pointer pointer;
  typedef Reference reference;
  typedef Distance difference_type;
};



}

#endif //TINYSTL_STL_COMPONENTS_ITERATOR_H_
