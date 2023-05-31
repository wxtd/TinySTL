//
// Created by Administrator on 2023/5/31 0031.
//

#ifndef TINYSTL_STL_COMPONENTS_UTILS_H_
#define TINYSTL_STL_COMPONENTS_UTILS_H_

/*!
 * it contains some utils, such as move, forward and so on.
 */

# include <cstddef>
# include "type_traits.h"

namespace mystl {

// move 右值
template<class T>
typename std::remove_reference<T>::type &&move(T &&arg) {
  return static_cast<typename std::remove_reference<T>::type &&>(arg);
}

// forward 完美转发
template<class T>
T &&forward(typename std::remove_reference<T>::type &arg) {
  return static_cast<T &&>(arg);
}

template<class T>
T &&forward(typename std::remove_reference<T>::type &&arg) {
  static_assert(!std::is_lvalue_reference<T>::value, "Bad Forward");
  return static_cast<T &&>(arg);
}

}

#endif //TINYSTL_STL_COMPONENTS_UTILS_H_
