#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include <iostream>

using namespace __gnu_pbds;
using namespace std;
using ll = long long;

template <class T>
using ord_set =
    tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

int main() {
  ord_set<int> os;
  os.insert(3);
  os.insert(5);
  os.insert(1);
  cout << *os.find_by_order(1) << "\n";
  cout << os.order_of_key(2) << "\n";

  return 0;
}
