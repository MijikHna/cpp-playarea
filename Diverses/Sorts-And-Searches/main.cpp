#include "./include/BubbleSort.hpp"
#include "./include/InsertionSort.hpp"
#include "./include/QuickSort.hpp"
#include "./template/BinarySearch.t.hpp"
#include "./template/BubbleSort.t.hpp"
#include "include/BinarySearch.hpp"

#include <cstddef>
#include <cstdlib>
#include <iostream>

template <typename T>
auto printArray(T array[], std::size_t length) -> void;

int main(int argc, char const* argv[]) {
  int* sortedArrayInt = {nullptr};
  double* sortedArrayDouble = {nullptr};

  // INSERTION SORT
  InsertionSort insSort;

  int unsortedArrayInt[] {10, 15, 13, 3};
  double unsortedArrayDouble[] {10.5, 15.7, 13.6, 3.8};

  long arrLength = sizeof(unsortedArrayInt) / sizeof(int);
  sortedArrayInt = insSort.sort(unsortedArrayInt, arrLength);
  printArray(unsortedArrayInt, sizeof(unsortedArrayInt) / sizeof(int));
  printArray(sortedArrayInt, sizeof(unsortedArrayInt) / sizeof(int));

  arrLength = sizeof(unsortedArrayDouble) / sizeof(double);
  sortedArrayDouble = insSort.sort(unsortedArrayDouble, arrLength);
  printArray(unsortedArrayDouble, arrLength);
  printArray(sortedArrayDouble, arrLength);

  std::cout << "----" << std::endl;

  // QUICKSORT SORT
  QuickSort quickSort;

  arrLength = sizeof(unsortedArrayInt) / sizeof(int);
  sortedArrayInt = quickSort.sort(unsortedArrayInt, arrLength);
  printArray(unsortedArrayInt, arrLength);
  printArray(sortedArrayInt, arrLength);

  arrLength = sizeof(unsortedArrayDouble) / sizeof(double);
  sortedArrayDouble = quickSort.sort(unsortedArrayDouble, arrLength);
  printArray(unsortedArrayDouble, arrLength);
  printArray(sortedArrayDouble, arrLength);

  std::cout << "---" << std::endl;

  // BUBBLE SORT
  BubbleSort bubbleSort;

  arrLength = sizeof(unsortedArrayInt) / sizeof(int);
  sortedArrayInt = bubbleSort.sort<int>(unsortedArrayInt, arrLength);
  printArray(unsortedArrayInt, arrLength);
  printArray(sortedArrayInt, arrLength);

  arrLength = sizeof(unsortedArrayDouble) / sizeof(double);
  sortedArrayDouble = bubbleSort.sort<double>(unsortedArrayDouble, arrLength);
  printArray(unsortedArrayDouble, arrLength);
  printArray(sortedArrayDouble, arrLength);

  // BinarySearch
  BinarySearch binarySearch;
  int foundValue = binarySearch.searchWhile(sortedArrayInt, arrLength, 13);
  std::cout << "Binary search: index=" << foundValue << ", value=" << sortedArrayInt[foundValue] << std::endl;

  foundValue = binarySearch.searchRecursive(sortedArrayInt, arrLength, 13);
  std::cout << "Binary search: index=" << foundValue << ", value=" << sortedArrayInt[foundValue] << std::endl;

  foundValue = binarySearch.searchWhile(sortedArrayInt, arrLength, 10);
  std::cout << "Binary search: index=" << foundValue << ", value=" << sortedArrayInt[foundValue] << std::endl;

  foundValue = binarySearch.searchRecursive(sortedArrayInt, arrLength, 10);
  std::cout << "Binary search: index=" << foundValue << ", value=" << sortedArrayInt[foundValue] << std::endl;

  return EXIT_SUCCESS;
}

template <typename T>
auto printArray(T array[], std::size_t length) -> void {
  for (int i = 0; i < length; i++) {
    if (i < length - 1) {
      std::cout << array[i] << ", ";
    } else {
      std::cout << array[i] << std::endl;
    }
  }
}
