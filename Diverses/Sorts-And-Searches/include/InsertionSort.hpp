#ifndef __INSERTION_SORT__
#define __INSERTION_SORT__

#include <cstddef>

/**
 * @brief first element is sorted. Take next elements  and compoare with sorted elements. If smaller swap them
 *
 */
class InsertionSort {
private:
public:
  InsertionSort() {}
  ~InsertionSort() {}
  template <typename T>
  auto sort(T unsortedArray[], std::size_t length) -> T* {
    T* sortedArray = new T[length];

    for (int i = 0; i < length; i++) {
      sortedArray[i] = unsortedArray[i];
    }

    for (int i = 1; i < length; i++) {
      T currentElem = sortedArray[i];

      int j = i - 1;

      while (j >= 0 && currentElem < sortedArray[j]) {
        sortedArray[j + 1] = sortedArray[j];
        j -= 1;
      }

      sortedArray[j + 1] = currentElem;
    }

    return sortedArray;
  }
};

#endif
