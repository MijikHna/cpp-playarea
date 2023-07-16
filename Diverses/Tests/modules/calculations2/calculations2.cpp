#include "../calculations/calculations.hpp"

int test() {
  int arr[] = {1, 5, 4, 6, 7, 9, 8, 10, 2};

  size_t n = sizeof(arr) / sizeof(arr[0]);
  return calculate_sum(arr, n);
}
