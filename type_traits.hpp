#ifndef jm4R_TYPE_TRAITS
#define jm4R_TYPE_TRAITS

#include <type_traits>

namespace mj {

template <typename T, typename... Args>
struct first_type
{
    using type = T;
};

/* When some class has:
 * 1) variadic template constructor
 * 2) copy or move constructor
 * we should be sure that (1) does not "cover" (2).
 * Use this trait for this purpose: 
 *
 * template <typename... Args, typename mj::prefer_std_constructors<T, Args...>::type* = nullptr>
 * T(Args&&... args);
 */
template <typename T, typename... Args>
using prefer_std_constructors = std::enable_if<sizeof...(Args) != 1 || !std::is_same<T, typename std::decay<typename first_type<Args...>::type>::type>::value>;

}  // namespace mj

#endif // jm4R_TYPE_TRAITS
