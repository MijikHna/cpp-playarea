#ifndef __BUBBLE_SORT__
#define __BUBBLE_SORT__

/**
 * @brief compare adjacent elements and switch them if needed. With each loop the biggest element take place at the end of the array
 *
 */
class BubbleSort {
private:
public:
  BubbleSort();
  ~BubbleSort();

  template <typename T>
  auto sort(T unsortedArray[], unsigned long length) -> T*;
};

#endif
