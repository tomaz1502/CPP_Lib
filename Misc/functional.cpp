#include <algorithm>
#include <functional>
#include <iostream>
#include <vector>

using namespace std;

namespace tom {
template <typename T_in, typename T_out>
vector<T_out> map(const vector<T_in> &L, const function<T_in(T_out)> &func) {
  vector<T_out> out;

  for (auto elem : L)
    out.push_back(func(elem, elem));

  return out;
}
} // namespace tom

template <typename T>
vector<T> filter(const vector<T> &L, bool (*criterion)(T)) {
  vector<T> out;

  for (T elem : L)
    if (criterion(elem))
      out.push_back(elem);

  return out;
}

int main() {
  vector<int> L = {3, 1, 5, 3, 2}, M, F, FI;

  M = tom::map<int, int>(L, [](int x, int y) -> int { return x * x; });

  F = filter<int>(M, [](int x) -> bool { return x > 5; });

  cout << "map result:" << endl;
  for (auto elem : M)
    cout << elem << ' ';
  cout << endl << endl;

  cout << "filter result:" << endl;
  for (auto elem : F)
    cout << elem << ' ';
  cout << endl;

  // vector<int> L = {1,2,3,4,5,6,7,8,9,10};

  // vector<int>::iterator it = find_if(L.begin(), L.end(), [](int x) -> bool{
  // return x > 4;});

  // cout << *it << endl;

  return 0;
}
