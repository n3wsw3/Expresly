#pragma once
#include "token.h"

namespace expresly {

template <typename T>
struct token_number : public token {
  T value = 0;

  token_number(const T& _value)
      : value(_value), token{std::to_string(value), token_type::Decimal} {}

	const std::string name() const override {
		return std::to_string(value);
	}

  token_number<T>* operator++() {
    value += 1;
    return this;
  }

  token_number<T>* operator--() {
    value -= 1;
    return this;
  }

  token_number<T>* operator++(int) {
    value += 1;
    return this;
  }

  token_number<T>* operator--(int) {
    value -= 1;
    return this;
  }

  template <typename U>
  token_number<T>* operator+=(const token_number<U>& n1) {
    value += n1.value;
    return this;
  }

  template <typename U>
  token_number<T>* operator-=(const token_number<U>& n1) {
    value -= n1.value;
    return this;
  }

  template <typename U>
  token_number<T>* operator+=(const U& n1) {
    value += n1;
    return this;
  }

  template <typename U>
  token_number<T>* operator-=(const U& n1) {
    value -= n1;
    return this;
  }

  template <typename U, typename V>
  friend token_number<std::common_type_t<U, V>> operator+(
      const token_number<U>& n1, const token_number<V>& n2);
  template <typename U, typename V>
  friend token_number<std::common_type_t<U, V>> operator-(
      const token_number<U>& n1, const token_number<V>& n2);
  template <typename U, typename V>
  friend token_number<double> operator/(const token_number<U>& n1,
                                        const token_number<V>& n2);
  template <typename U, typename V>
  friend token_number<std::common_type_t<U, V>> operator*(
      const token_number<U>& n1, const token_number<V>& n2);

  template <typename U, typename V>
  friend token_number<std::common_type_t<U, V>> operator%(
      const token_number<U>& n1, const token_number<V>& n2);

  // Implicit cast to value type
  operator T() const { return value; }
};

template <typename U, typename V>
token_number<std::common_type_t<U, V>> operator+(const token_number<U>& n1,
                                                 const token_number<V>& n2) {
  return {n1.value + n2.value};
}
template <typename U, typename V>
token_number<std::common_type_t<U, V>> operator-(const token_number<U>& n1,
                                                 const token_number<V>& n2) {
  return {n1.value - n2.value};
}
template <typename U, typename V>
token_number<double> operator/(const token_number<U>& n1,
                               const token_number<V>& n2) {
  return {(double)n1.value / n2.value};
}

template <typename U, typename V>
token_number<std::common_type_t<U, V>> operator*(const token_number<U>& n1,
                                                 const token_number<V>& n2) {
  return {n1.value * n2.value};
}

template <typename U, typename V>
token_number<std::common_type_t<U, V>> operator%(const token_number<U>& n1,
                                                 const token_number<V>& n2) {
  return {n1.value % n2.value};
}

template <>
token_number<int>::token_number(const int& _value)
    : value(_value), token{std::to_string(value), token_type::Integer} {}

template <>
token_number<bool>::token_number(const bool& _value)
    : value(_value), token{std::to_string(value), token_type::Boolean} {}

}  // namespace expresly