#pragma once
#include <array>
#include <concepts>
#include <numeric>

#include "number.h"

namespace expresly {
template <typename T, typename... Args>
std::common_type_t<T, Args...> addition(const T& num, const Args&... args) {
  return num + (args + ...);
}

template <typename... Args>
std::common_type_t<Args...> subtraction(const Args&... args) {
  return (args - ...);
}

template <typename... Args>
std::common_type_t<Args...> multiplication(const Args&... args) {
  return (args * ...);
}

template <typename... Args>
std::common_type_t<Args...> division(const Args&... args) {
  return (args / ...);
}

template <typename... Args>
std::common_type_t<Args...> modulo(const Args&... args) {
  return (args % ...);
}

}  // namespace expresly