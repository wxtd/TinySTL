//
// Created by Administrator on 2023/5/31 0031.
// 迭代器 类型萃取
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
    class Pointer = T*, class Reference = T&>
struct iterator {
  typedef Category iterator_category; // 迭代器类别
  typedef T value_type; // 元素类型
  typedef Pointer pointer;
  typedef Reference reference;
  typedef Distance difference_type;
};

// iterator traits

// 是否含有迭代器
template<class T>
struct has_iterator_cat {
 private:
  struct two { char a; char b; };
  template<class U>
  static two test(...);
  template<class U>
  static char test(typename U::iterator_category* = 0);
 public:
  // 若含有T类迭代器 则进入test@2 返回char value为true
  // 否则返回two value为false
  static const bool value = sizeof(test<T>(0)) == sizeof(char);
};

template<class Iterator, bool>
struct iterator_traits_impl {};

template<class Iterator>
struct iterator_traits_impl<Iterator, true> {
  typedef typename Iterator::iterator_category iterator_category;
  typedef typename Iterator::value_type value_type;
  typedef typename Iterator::pointer pointer;
  typedef typename Iterator::reference reference;
  typedef typename Iterator::difference_type difference_type;
};

template<class Iterator, bool>
struct iterator_traits_helper {};

// 若传参不能转化为最基类的input和output 则flag为false 代表不是个迭代器类型 各型别为空
template<class Iterator>
struct iterator_traits_helper<Iterator, true>
    : public iterator_traits_impl<Iterator,
                                  std::is_convertible<typename Iterator::iterator_category, input_iterator_tag>::value
                                      ||
                                          std::is_convertible<typename Iterator::iterator_category,
                                                              output_iterator_tag>::value> {
};

// 萃取迭代器的特性
// 若含有迭代器 其第二个参数为true
template<class Iterator>
struct iterator_traits
    : public iterator_traits_helper<Iterator, has_iterator_cat<Iterator>::value> {
};

// 指针被视作是随机访问迭代器
template<class T>
struct iterator_traits<T*> {
  typedef random_access_iterator_tag iterator_category;
  typedef T value_type;
  typedef T* pointer;
  typedef T& reference;
  typedef ptrdiff_t difference_type;
};

template<class T>
struct iterator_traits<const T*> {
  typedef random_access_iterator_tag iterator_category;
  typedef T value_type;
  typedef const T* pointer;
  typedef const T& reference;
  typedef ptrdiff_t difference_type;
};

// T迭代器是否能转化为U迭代器
template<class T, class U, bool = has_iterator_cat<iterator_traits<T>>::value>
struct has_iterator_cat_of
    : public m_bool_constant<std::is_convertible<
        typename iterator_traits<T>::iterator_category, U>::value> {
};

// 无法转化
template<class T, class U>
struct has_iterator_cat_of<T, U, false> : public m_false_type {};

// 转化为具体五类迭代器
template<class Iter>
struct is_input_iterator : public has_iterator_cat_of<Iter, input_iterator_tag> {};

template<class Iter>
struct is_output_iterator : public has_iterator_cat_of<Iter, output_iterator_tag> {};

template<class Iter>
struct is_forward_iterator : public has_iterator_cat_of<Iter, forward_iterator_tag> {};

template<class Iter>
struct is_bidirectional_iterator : public has_iterator_cat_of<Iter, bidirectional_iterator_tag> {};

template<class Iter>
struct is_random_access_iterator : public has_iterator_cat_of<Iter, random_access_iterator_tag> {};

template<class Iterator>
struct is_iterator :
    public m_bool_constant<is_input_iterator<Iterator>::value ||
        is_output_iterator<Iterator>::value> {
};

// 萃取某个迭代器的 category
template<class Iterator>
typename iterator_traits<Iterator>::iterator_category
iterator_category(const Iterator&) {
  typedef typename iterator_traits<Iterator>::iterator_category Category;
  return Category();
}

// 萃取某个迭代器的 distance_type
template<class Iterator>
typename iterator_traits<Iterator>::difference_type*
distance_type(const Iterator&) {
  return static_cast<typename iterator_traits<Iterator>::difference_type*>(0);
}

// 萃取某个迭代器的 value_type
template<class Iterator>
typename iterator_traits<Iterator>::value_type*
value_type(const Iterator&) {
  return static_cast<typename iterator_traits<Iterator>::value_type*>(0);
}

// distance
template<class InputIterator>
typename iterator_traits<InputIterator>::difference_type
distance(InputIterator first, InputIterator last) {
  return distance_dispatch(first, last, iterator_category(first));
}

// distance 的 input_iterator_tag 的版本
template<class InputIter>
typename iterator_traits<InputIter>::difference_type
distance_dispatch(InputIter first, InputIter last,
                  input_iterator_tag) {
  typename iterator_traits<InputIter>::difference_type dis = 0;
  while (first != last) {
    ++first;
    ++dis;
  }
  return dis;
}

// distance 的 random_access_iterator_tag 的版本
template<class RandomIter>
typename iterator_traits<RandomIter>::difference_type
distance_dispatch(RandomIter first, RandomIter last,
                  random_access_iterator_tag) {
  return last - first;
}

// advance
template<class InputIterator, class Distance>
void advance(InputIterator& i, Distance n) {
  advance_dispatch(i, n, iterator_category(i));
}

// advance 的 input_iterator_tag 的版本
template<class InputIterator, class Distance>
void advance_dispatch(InputIterator& i, Distance n, input_iterator_tag) {
  while (n--)
    ++i;
}

// advance 的 bidirectional_iterator_tag 的版本
template<class BidirectionalIterator, class Distance>
void advance_dispatch(BidirectionalIterator& i, Distance n, bidirectional_iterator_tag) {
  if (n >= 0)
    while (n--) ++i;
  else
    while (n++) --i;
}

// advance 的 random_access_iterator_tag 的版本
template<class RandomIter, class Distance>
void advance_dispatch(RandomIter& i, Distance n, random_access_iterator_tag) {
  i += n;
}

/********************************************************************************/

// reverse_iterator
// 反向迭代器 重载+/- 操作
template<class Iterator>
class reverse_iterator {
  Iterator natural; // 对应的正向迭代器
 public:
  typedef typename iterator_traits<Iterator>::iterator_category iterator_category;
  typedef typename iterator_traits<Iterator>::value_type value_type;
  typedef typename iterator_traits<Iterator>::pointer pointer;
  typedef typename iterator_traits<Iterator>::reference reference;
  typedef typename iterator_traits<Iterator>::difference_type difference_type;

  typedef Iterator iterator_type;
  typedef reverse_iterator<Iterator> self_type;

  // constructor
  reverse_iterator() = default;
  explicit reverse_iterator(iterator_type i) : natural(i) {}
  reverse_iterator(const self_type& rhs) : natural(rhs.natural) {}

  // 返回对应的正向迭代器
  iterator_type base() const {
    return natural;
  }

  // 重载 * -> + - 等操作符

  // * 实际对应正向迭代器的前一个位置
  reference operator*() const {
    iterator_type t = natural;
    return *(--t);
  }

  pointer operator->() const {
    return &(operator*());
  }

  // ++x
  self_type& operator++() {
    --natural;
    return *this;
  }

  // x++
  self_type operator++(int) {
    self_type t = *this;
    --natural;
    return t;
  }

  // --x
  self_type& operator--() {
    ++natural;
    return *this;
  }

  // x++
  self_type operator--(int) {
    self_type t = *this;
    ++natural;
    return t;
  }

  self_type& operator+=(difference_type n) {
    natural -= n;
    return *this;
  }

  self_type operator+(difference_type n) const {
    return self_type(natural - n);
  }

  self_type& operator-=(difference_type n) {
    natural += n;
    return *this;
  }

  self_type operator-(difference_type n) const {
    return self_type(natural + n);
  }

  reference operator[](difference_type i) const {
    return *(*this + i);
  }
};

// 重载 operator-
template<class Iterator>
typename reverse_iterator<Iterator>::difference_type
operator-(const reverse_iterator<Iterator>& lhs,
          const reverse_iterator<Iterator>& rhs) {
  return rhs.base() - lhs.base();
}

// 重载比较操作符
template<class Iterator>
bool operator==(const reverse_iterator<Iterator>& lhs,
                const reverse_iterator<Iterator>& rhs) {
  return lhs.base() == rhs.base();
}

template<class Iterator>
bool operator<(const reverse_iterator<Iterator>& lhs,
               const reverse_iterator<Iterator>& rhs) {
  return rhs.base() < lhs.base();
}

template<class Iterator>
bool operator!=(const reverse_iterator<Iterator>& lhs,
                const reverse_iterator<Iterator>& rhs) {
  return !(lhs == rhs);
}

template<class Iterator>
bool operator>(const reverse_iterator<Iterator>& lhs,
               const reverse_iterator<Iterator>& rhs) {
  return rhs < lhs;
}

template<class Iterator>
bool operator<=(const reverse_iterator<Iterator>& lhs,
                const reverse_iterator<Iterator>& rhs) {
  return !(rhs < lhs);
}

template<class Iterator>
bool operator>=(const reverse_iterator<Iterator>& lhs,
                const reverse_iterator<Iterator>& rhs) {
  return !(lhs < rhs);
}

}

#endif //TINYSTL_STL_COMPONENTS_ITERATOR_H_
