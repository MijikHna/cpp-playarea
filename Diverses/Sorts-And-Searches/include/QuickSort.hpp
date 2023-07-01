#ifndef __QUICK_SORT__
#define __QUICK_SORT__

/**
 * @brief pivot will be set (last elem of the array). start, and will be set (start = -1, end = 1). If pivot greater than i, start(temp) will be increased and pivot will be swapped with start. If during the run pivot was the last one increase start and swap with pivot. Return start and call the function recursively with 1: start, return value - 1, 2: returned value + 1, end
 *
 */
class QuickSort {
private:
public:
  QuickSort() {}
  ~QuickSort() {}
  template <typename T>
  T* sort(T unsortedArray[], long length) {
    T* sortedArray = unsortedArray;

    sortedArray = this->createReturnArray(unsortedArray, length);

    this->quickSort(sortedArray, 0, length);

    return sortedArray;
  }
  template <typename T>
  auto swap(T* a, T* b) -> void {
    T temp = *a;
    *a = *b;
    *b = temp;
  }
  template <typename T>
  auto partition(T* unsortedArray, long start, long end) -> auto{
    T pivot = unsortedArray[end];
    int j = start - 1;

    for (int i = start; i <= end; i++) {
      if (pivot > unsortedArray[i]) {
        j++;
        swap(&unsortedArray[i], &unsortedArray[j]);
      }
    }

    swap(&unsortedArray[j + 1], &unsortedArray[end]);

    return (j + 1);
  }
  template <typename T>
  auto createReturnArray(T* initArray, long length) -> T* {
    T* sortedArray = new T[length];

    for (int i = 0; i < length; i++) {
      sortedArray[i] = initArray[i];
    }

    return sortedArray;
  }
  template <typename T>
  auto quickSort(T unsortedArray[], long start, long end) -> T* {
    if (start >= end) {
      return unsortedArray;
    }

    long partitionValue = this->partition(unsortedArray, start, end - 1);

    this->quickSort(unsortedArray, start, partitionValue - 1);
    this->quickSort(unsortedArray, partitionValue + 1, end);

    return unsortedArray;
  }
};

#endif