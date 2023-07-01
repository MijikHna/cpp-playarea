#include "../include/BinarySearch.hpp"

template <typename T>
auto BinarySearch::searchWhile(T sortedArray[], long length, T searchValue) -> T {
  int low = 0;
  int high = length - 1;

  while (low <= high) {
    int middle = (low + high) / 2;

    if (searchValue == sortedArray[middle]) {
      return middle;
    }

    if (searchValue < middle) {
      high = middle - 1;
    }

    if (searchValue > middle) {
      low = middle + 1;
    }
  }

  return -1;
}

template <typename T>
auto BinarySearch::searchRecursive(T sortedArray[], long length, T searchValue) -> T {
  int low = 0;
  int high = length - 1;

  int middle = (low + high) / 2;

  if (searchValue == sortedArray[middle])
    return middle;
  if (searchValue < middle) {
    length = length - (middle + 1);
    return low + this->searchRecursive(&sortedArray[low], length, searchValue);
  }

  if (searchValue > middle) {
    length = length - (middle + 1);

    return middle + 1 + this->searchRecursive(&sortedArray[middle + 1], length, searchValue);
  }

  return -1;
}
