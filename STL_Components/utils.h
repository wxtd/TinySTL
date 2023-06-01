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

namespace stl {

// move 右值
template<class T>
typename std::remove_reference<T>::type&& move(T&& arg) {
  return static_cast<typename std::remove_reference<T>::type&&>(arg);
}

// forward 完美转发
template<class T>
T&& forward(typename std::remove_reference<T>::type& arg) noexcept {
  return static_cast<T&&>(arg);
}

template<class T>
T&& forward(typename std::remove_reference<T>::type&& arg) {
  static_assert(!std::is_lvalue_reference<T>::value, "Bad Forward");
  return static_cast<T&&>(arg);
}

// swap

template<class T>
void swap(T& lhs, T& rhs) {
  auto temp(stl::move(lhs));
  lhs = stl::move(rhs);
  rhs = stl::move(temp);
}

template<class ForwardIter>
void swap_range(ForwardIter first1, ForwardIter last1, ForwardIter first2) {
  while (first1 != last1) {
    stl::swap(first1, first2);
    ++first1;
    ++first2;
  }
}

template<class T, size_t n>
void swap(T a[n], T b[n]) {
  stl::swap_range(a, a + n, b);
}

// pair

template<class T1, class T2>
class pair {
 public:
  typedef T1 first_type;
  typedef T2 second_type;

  first_type first; // first item
  second_type second; // second item

  // default constructable
  template<class Other1 = T1, class Other2 = T2,
      typename = typename std::enable_if<
          std::is_default_constructible<Other1>::value &&
              std::is_default_constructible<Other2>::value, void>::type>
  constexpr pair()
      : first(), second() {
  }

  // implicit constructable for this type
  template<class U1 = T1, class U2 = T2,
      typename std::enable_if<
          std::is_copy_constructible<U1>::value &&
              std::is_copy_constructible<U2>::value &&
              std::is_convertible<const U1&, T1>::value &&
              std::is_convertible<const U2&, T2>::value, int>::type = 0>
  constexpr pair(const T1& a, const T2& b)
      : first(a), second(b) {
  }

  // explicit constructable for this type
  template<class U1 = T1, class U2 = T2,
      typename std::enable_if<
          std::is_copy_constructible<U1>::value &&
              std::is_copy_constructible<U2>::value &&
              (!std::is_convertible<const U1&, T1>::value ||
                  !std::is_convertible<const U2&, T2>::value), int>::type = 0>
  explicit constexpr pair(const T1& a, const T2& b)
      : first(a), second(b) {
  }

  pair(const pair& rhs) = default;
  pair(pair&& rhs) noexcept = default;

  // implicit constructable for other type
  template<class Other1, class Other2,
      typename std::enable_if<
          std::is_constructible<T1, Other1>::value &&
              std::is_constructible<T2, Other2>::value &&
              std::is_convertible<Other1&&, T1>::value &&
              std::is_convertible<Other2&&, T2>::value, int>::type = 0>
  constexpr pair(Other1&& a, Other2&& b)
      : first(stl::forward<Other1>(a)),
        second(stl::forward<Other2>(b)) {
  }

  // explicit constructable for other type
  template<class Other1, class Other2,
      typename std::enable_if<
          std::is_constructible<T1, Other1>::value &&
              std::is_constructible<T2, Other2>::value &&
              (!std::is_convertible<Other1, T1>::value ||
                  !std::is_convertible<Other2, T2>::value), int>::type = 0>
  explicit constexpr pair(Other1&& a, Other2&& b)
      : first(stl::forward<Other1>(a)),
        second(stl::forward<Other2>(b)) {
  }

  // implicit constructable for other pair
  template<class Other1, class Other2,
      typename std::enable_if<
          std::is_constructible<T1, const Other1&>::value &&
              std::is_constructible<T2, const Other2&>::value &&
              std::is_convertible<const Other1&, T1>::value &&
              std::is_convertible<const Other2&, T2>::value, int>::type = 0>
  constexpr explicit pair(const pair<Other1, Other2>& other)
      : first(other.first),
        second(other.second) {
  }

  // explicit constructable for other pair
  template<class Other1, class Other2,
      typename std::enable_if<
          std::is_constructible<T1, const Other1&>::value &&
              std::is_constructible<T2, const Other2&>::value &&
              (!std::is_convertible<const Other1&, T1>::value ||
                  !std::is_convertible<const Other2&, T2>::value), int>::type = 0>
  explicit constexpr pair(const pair<Other1, Other2>& other)
      : first(other.first),
        second(other.second) {
  }

  // implicit constructable for other pair
  template<class Other1, class Other2,
      typename std::enable_if<
          std::is_constructible<T1, Other1>::value &&
              std::is_constructible<T2, Other2>::value &&
              std::is_convertible<Other1, T1>::value &&
              std::is_convertible<Other2, T2>::value, int>::type = 0>
  constexpr explicit pair(pair<Other1, Other2>&& other)
      : first(stl::forward<Other1>(other.first)),
        second(stl::forward<Other2>(other.second)) {
  }

  // explicit constructable for other pair
  template<class Other1, class Other2,
      typename std::enable_if<
          std::is_constructible<T1, Other1>::value &&
              std::is_constructible<T2, Other2>::value &&
              (!std::is_convertible<Other1, T1>::value ||
                  !std::is_convertible<Other2, T2>::value), int>::type = 0>
  explicit constexpr pair(pair<Other1, Other2>&& other)
      : first(stl::forward<Other1>(other.first)),
        second(stl::forward<Other2>(other.second)) {
  }

  // assignment

  pair& operator=(const pair& rhs) {
    if (&rhs == this) return *this;
    first = rhs.first;
    second = rhs.second;
    return *this;
  }

  pair& operator=(pair&& rhs) {
    if (&rhs == this) return *this;
    first = stl::move(rhs.first);
    second = stl::move(rhs.second);
    return *this;
  }

  // copy assign for other pair
  template<class Other1, class Other2>
  pair& operator=(const pair<Other1, Other2>& other) {
    first = other.first;
    second = other.second;
    return *this;
  }

  // move assign for other pair
  template<class Other1, class Other2>
  pair& operator=(pair<Other1, Other2>&& other) {
    first = stl::forward<Other1>(other.first);
    second = stl::forward<Other2>(other.second);
    return *this;
  }

  ~pair() = default;

  void swap(pair& other) {
    if (this != &other) {
      stl::swap(first, other.first);
      stl::swap(second, other.second);
    }
  }
};

template<class T1, class T2>
bool operator==(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs) {
  return lhs.first == rhs.first && lhs.second == rhs.second;
}

template<class T1, class T2>
bool operator!=(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs) {
  return !(lhs == rhs);
}

template<class T1, class T2>
bool operator<(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs) {
  return lhs.first < rhs.first || (lhs.first == rhs.first && lhs.second < rhs.second);
}

template<class T1, class T2>
bool operator>(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs) {
  return rhs < lhs;
}

template<class T1, class T2>
bool operator<=(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs) {
  return !(rhs < lhs);
}

template<class T1, class T2>
bool operator>=(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs) {
  return !(lhs < rhs);
}

template<class T1, class T2>
void swap(pair<T1, T2>& lhs, pair<T1, T2>& rhs) {
  lhs.swap(rhs);
}

template<class T1, class T2>
pair<T1, T2> make_pair(const T1& v1, const T2& v2) {
  return pair<T1, T2>(stl::forward<T1>(v1), stl::forward<T2>(v2));
}

}

#endif //TINYSTL_STL_COMPONENTS_UTILS_H_
