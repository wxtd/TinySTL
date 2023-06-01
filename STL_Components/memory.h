//
// Created by Administrator on 2023/5/31 0031.
//

#ifndef TINYSTL_STL_COMPONENTS_MEMORY_H_
#define TINYSTL_STL_COMPONENTS_MEMORY_H_
#include <cstddef>
#include <cstdlib>
#include <climits>

#include "allocator.h"

namespace stl {

// 获取地址
template<class T>
constexpr T* address_of(const T& v) noexcept {
  return &v;
}

// 临时缓冲区


}

#endif //TINYSTL_STL_COMPONENTS_MEMORY_H_
