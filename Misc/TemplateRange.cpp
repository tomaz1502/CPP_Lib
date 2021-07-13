#include <iostream>

/*
 * A range of integers to be used in a range-based loop, equivalent to python's
 * range function
 */
template<int step = 1>
class Range {
  static_assert(step != 0, "Step can't be 0.");

private:
  struct iterator {
    int val;

    iterator(int _val) : val(_val)  { }

    bool operator!=(const iterator& rhs) {
      if constexpr (step > 0) 
        return val < rhs.val;
      else 
        return val > rhs.val;
    } 
    void next() { val += step; }
    void operator++() { this->next(); }
    int operator*() { return val; }
  };

  int left, right;

public:
  iterator begin() { return iterator(left);  } 
  iterator end()   { return iterator(right); } 

  Range(int _right) :
    left(0), right(_right) {}
  Range(int _left, int _right) :
    left(_left), right(_right) {}
};

int main() {

  /* { */
  /*   Range r(0, 3); */
  /*   for (Range::iterator it = r.begin(); it != r.end(); ++it) { */
  /*     const int& i = *it; */
  /*     std::cout << i << "\n"; */
  /*   } */
  /* } */

  int x, y;
  std::cin >> x >> y;
  for (const int& i: Range<>(x,y))
    std::cout << i << "\n";

  return 0;
}
