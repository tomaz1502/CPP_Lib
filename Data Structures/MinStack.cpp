#include <cassert>
#include <iostream>
using namespace std;

struct Stack {
  static const int MAX_SIZE = 1e5 + 10;

  int v[MAX_SIZE];
  int p, minE;

  Stack() : p(0) {}

  void push(int x) {
    if (p == MAX_SIZE - 1) {
      cout << "Stack is FULL!\n";
      assert(false);
    }
    if (p == 0) {
      v[p++] = x;
      minE = x;
    } else {
      if (x > minE)
        v[p++] = x;
      else {
        v[p++] = 2 * x - minE;
        minE = x;
      }
    }
  }

  int pop() {
    if (p == 0) {
      cout << "Empty!\n";
      assert(false);
    }
    p--;
    if (v[p] < minE) {
      minE = 2 * minE - v[p];
      return minE;
    } else
      return v[p];
  }

  int MIN() { return minE; }
};

int main() {
  Stack s;
  s.push(3);
  s.push(4);
  s.push(2);
  cout << s.MIN() << '\n';
  s.pop();
  cout << s.MIN() << '\n';
  return 0;
}
