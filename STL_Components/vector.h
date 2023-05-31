//
// Created by Administrator on 2023/5/31 0031.
//

#ifndef TINYSTL_STL_COMPONENTS_VECTOR_H_
#define TINYSTL_STL_COMPONENTS_VECTOR_H_

#include <initializer_list>

#include "exceptdef.h"

namespace stl {
template<class T>
class vector {
  static_assert(!std::is_same<T, bool>::value, "vector<bool> is not allowed!");
 public:

};
}

#endif //TINYSTL_STL_COMPONENTS_VECTOR_H_


