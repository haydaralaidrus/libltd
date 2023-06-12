#ifndef _LTD_INCLUDE_DETAILS_STRCONV_HPP_
#define _LTD_INCLUDE_DETAILS_STRCONV_HPP_

#include <string>
#include <type_traits>
#if __cplusplus >= 202002L
  #include "constraints.hpp"
#endif

namespace ltd {

#if __cplusplus >= 202002L
template<Arithmetic T>
#else
template<typename T>
#endif
T strconv(const std::string &s)
{
    if constexpr (std::is_integral_v<T> && std::is_signed_v<T>)
        return static_cast<T>(std::stoll(s));
    else if constexpr (std::is_integral_v<T> && std::is_unsigned_v<T>)
        return static_cast<T>(std::stoull(s));
    else if constexpr (std::is_floating_point_v<T>)
        return static_cast<T>(std::stod(s));
}

}

#endif
