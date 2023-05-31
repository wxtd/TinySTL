//
// Created by Administrator on 2023/5/31 0031.
//

#ifndef TINYSTL_STL_COMPONENTS_EXCEPTDEF_H_
#define TINYSTL_STL_COMPONENTS_EXCEPTDEF_H_

#include <stdexcept>

#include <cassert>

namespace stl {

#define STL_DEBUG(expr) \
  assert(expr)

#define THROW_LENGTH_ERROR_IF(expr, what) \
  if ((expr)) throw std::length_error(what)

#define THROW_OUT_OF_RANGE_IF(expr, what) \
  if ((expr)) throw std::out_of_range(what)

#define THROW_RUNTIME_ERROR_IF(expr, what) \
  if ((expr)) throw std::runtime_error(what)

}
#endif //TINYSTL_STL_COMPONENTS_EXCEPTDEF_H_
