#include "calculations.hpp"

#include <cstddef>
#include <cstdio>

int calculate_sum(int arr[], size_t length) {
  int sum = 0;
  int i = 0;

  for (i = 0; i < length; i++) {
    sum += arr[i];
  }

  return sum;
}

float calculate_mean(int arr[], size_t length) {
  if (length == 0) {
    return 0;
  }

  int sum = calculate_sum(arr, length);

  return (float)sum / length;
}
