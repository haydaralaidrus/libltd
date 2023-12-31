#ifndef _LTD_INCLUDE_DETAILS_CONSTRAINTS_HPP_
#define _LTD_INCLUDE_DETAILS_CONSTRAINTS_HPP_

#include "traits.hpp"
#include <concepts>

namespace ltd {

template<typename T>
concept Arithmetic = std::is_arithmetic_v<T>;

template <typename T>
concept String = is_string_v<T>;

}

#endif
