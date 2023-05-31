//
// Created by Administrator on 2023/5/31 0031.
//

#ifndef TINYSTL_STL_COMPONENTS_TYPE_TRAITS_H_
#define TINYSTL_STL_COMPONENTS_TYPE_TRAITS_H_

# include <type_traits>

namespace stl {

// 静态编译期常量
template<class T, T v>
struct m_integral_constant {
  static constexpr T value = v;
};

template<bool b>
using m_bool_constant = m_integral_constant<bool, b>;
// 编译期常量
typedef m_bool_constant<true> m_true_type;
typedef m_bool_constant<false> m_false_type;
}
#endif //TINYSTL_STL_COMPONENTS_TYPE_TRAITS_H_
