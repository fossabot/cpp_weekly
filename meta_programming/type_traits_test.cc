#include "internal_check_conds.h"
#include <gtest/gtest.h>
#include <type_traits>
#include <typeinfo>

// std::conditional
// Provides member typedef type, which is defined as T if B is `true` at
// compile time, or as F if B is `false`. The behavior of a program that adds
// specializations for conditional is undefined.
// Possible implementation
/// \code
/// template <bool B, typename T, typename F>
/// struct conditional { using type = T; }
///
/// template <class T, class F>
/// struct conditional<false, T, F> { using type = F; }
/// \endcode
// Helper types
/// \code
/// template <bool B, typename T, typename F>
/// using conditional_t = typename conditional<B, T, F>::type;
/// \endcode

TEST(type_traits_test, conditional_test) {
  typedef std::conditional<true, int, double>::type Type1;
  typedef std::conditional<false, int, double>::type Type2;
  typedef std::conditional<sizeof(int) >= sizeof(double), int, double>::type
      Type3;

  std::stringstream oss;
  testing::internal::CaptureStdout();

  std::cout << typeid(Type1).name() << '\n';
  std::cout << typeid(Type2).name() << '\n';
  std::cout << typeid(Type3).name() << '\n';
  oss << "i\n"
         "d\n"
         "d\n";

  auto act_output = testing::internal::GetCapturedStdout();
  debug_msg(oss, act_output);

  EXPECT_TRUE(oss.str() == act_output);
}

#define SHOW(...) std::cout << #__VA_ARGS__ " : " << std::__VA_ARGS__ << '\n'

// Reference: [is_base_of](https://en.cppreference.com/w/cpp/types/is_base_of)
TEST(type_traits_test, is_base_of_test) {
  class A {};
  class B : A {};
  class C : B {};
  class D {};

  std::stringstream oss;
  testing::internal::CaptureStdout();

  std::cout << std::boolalpha;
  SHOW(is_base_of_v<A, A>);
  SHOW(is_base_of_v<A, B>);
  SHOW(is_base_of_v<A, C>);
  SHOW(is_base_of_v<A, D>);
  SHOW(is_base_of_v<B, A>);
  oss << "is_base_of_v<A, A> : true\n"
         "is_base_of_v<A, B> : true\n"
         "is_base_of_v<A, C> : true\n"
         "is_base_of_v<A, D> : false\n"
         "is_base_of_v<B, A> : false\n";

  auto act_output = testing::internal::GetCapturedStdout();
  debug_msg(oss, act_output);
  EXPECT_TRUE(oss.str() == act_output);
}