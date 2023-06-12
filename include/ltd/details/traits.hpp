#ifndef _LTD_INCLUDE_DETAILS_TRAITS_HPP_
#define _LTD_INCLUDE_DETAILS_TRAITS_HPP_

#include <string>

namespace ltd {

template<typename T>
struct __is_string_helper
{ static constexpr bool value = false; };

template<>
struct __is_string_helper<char *>
{ static constexpr bool value = true; };

template<>
struct __is_string_helper<const char *>
{ static constexpr bool value = true; };

template<>
struct __is_string_helper<std::string>
{ static constexpr bool value = true; };

template<>
struct __is_string_helper<std::wstring>
{ static constexpr bool value = true; };

template<>
struct __is_string_helper<std::u16string>
{ static constexpr bool value = true; };

template<>
struct __is_string_helper<std::u32string>
{ static constexpr bool value = true; };

template<>
struct __is_string_helper<std::string_view>
{ static constexpr bool value = true; };

template<>
struct __is_string_helper<std::wstring_view>
{ static constexpr bool value = true; };

template<>
struct __is_string_helper<std::u16string_view>
{ static constexpr bool value = true; };

template<>
struct __is_string_helper<std::u32string_view>
{ static constexpr bool value = true; };

#if __cplusplus >= 202002L

template<>
struct __is_string_helper<std::u8string>
{ static constexpr bool value = true; };

template<>
struct __is_string_helper<std::u8string_view>
{ static constexpr bool value = true; };

#endif

template<typename T>
struct is_string {
    static constexpr bool value = __is_string_helper<
        std::remove_cv_t<T>
    >::value;
};

template <typename T>
inline constexpr bool is_string_v = is_string<T>::value;

}

#endif
