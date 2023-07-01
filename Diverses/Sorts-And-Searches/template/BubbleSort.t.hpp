#include "../include/BubbleSort.hpp"

template <typename T>
auto BubbleSort::sort(T unsortedArray[], unsigned long length) -> T* {
  T* sortedArray = new T[length];

  for (int i = 0; i < length; i++) {
    sortedArray[i] = unsortedArray[i];
  }

  for (int i = 0; i < (length - 1); i++) {
    bool sorted = false;
    for (int j = 0; j < (length - 1 - i); j++) {
      if (sortedArray[j] > sortedArray[j + 1]) {
        T temp = sortedArray[j];
        sortedArray[j] = sortedArray[j + 1];
        sortedArray[j + 1] = temp;

        sorted = true;
      }
    }

    if (!sorted) {
      break;
    }
  }

  return sortedArray;
}
