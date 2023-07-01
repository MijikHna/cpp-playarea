#ifndef __BINARY_SEARCH__
#define __BINARY_SEARCH__

class BinarySearch {
private:
public:
  BinarySearch();
  ~BinarySearch();

  template <typename T>
  auto searchWhile(T sortedArray[], long length, T searchValue) -> T;

  template <typename T>
  auto searchRecursive(T sortedArray[], long length, T searchValue) -> T;
};
#endif // !__BINARY_SEARCH__
