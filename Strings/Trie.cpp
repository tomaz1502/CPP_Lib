#include <bits/stdc++.h>
using namespace std;

template <typename T> struct Trie {
  vector<vector<int>> Tree;
  vector<bool> end_word;
  int nxt = 1;
  T alph_base;

  Trie(int max_nodes, int alph_size = 26, int _alph_base = 'a')
      : alph_base(_alph_base) {
    Tree = vector(max_nodes, vector(alph_size, 0));
    end_word = vector(max_nodes, false);
  }

  void insert(const vector<T> &S) {
    int at = 1;
    for (const T &s : S) {
      int index = s - alph_base;
      if (Tree[at][index] == 0)
        Tree[at][index] = ++nxt;
      at = Tree[at][index];
    }
    end_word[at] = true;
  }

  void insert(const string &s) {
    vector<char> sc(s.begin(), s.end());
    insert(sc);
  }
};

int main() {}
