#include <vector>

template <typename T>
bool next_Permutation(
    std::vector<T> &Perm) { // swaps Perm to it's next Permutation
  int k = -1;
  int size = (int)Perm.size();
  for (int i = 0; i < size - 1; i++) {
    if (Perm[i] < Perm[i + 1])
      k = i; // find longest non-increasing suffix
  }

  if (k == -1)
    return false; // last lexicograph Permutation achieved

  int l;
  for (int j = k + 1; j < size; j++) {
    if (Perm[j] > Perm[k])
      l = j;
  }

  swap(Perm[k], Perm[l]);

  int p1 = k + 1, p2 = size - 1;
  while (p1 < p2) {
    swap(Perm[p1], Perm[p2]);
    p1++;
    p2--;
  }

  return true;
}

int main() { return 0; }
