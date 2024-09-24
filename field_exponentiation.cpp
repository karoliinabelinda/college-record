#include <stdio.h>
#include <stdlib.h> 

template<typename FieldT, mp_size_t m>
    FieldT power(const FieldT &base, const bigint<m> &exponent) {
  FieldT result = FieldT::one();
  bool found_one = false;
  for (int64_t i = (int64_t)exponent.max_bits() - 1; i >= 0; --i) {
    if (found_one) {
      result = result * result;
    }
    if (exponent.test_bit(i)) {
      found_one = true;
      result = result * base;
    }
  }
  return result;
}
