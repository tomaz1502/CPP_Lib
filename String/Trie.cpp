#include <bits/stdc++.h>
using namespace std;

struct Trie {
	vector< vector<int> > T;
	vector<bool> endOfWord;
	int proxNode = 1;

	Trie(int maxNodes, int alphabetSize) { //maxNodes is the maximum amount of letters allowed
		T = vector< vector<int> >(maxNodes, vector<int>(alphabetSize, 0));
		endOfWord = vector<bool>(maxNodes, false);
	}

	void insert(string s) {
		int at = 1;
		for(int i = 0; i < (int)s.length(); ++i) {
			int let = s[i] - 'a'; //base letter of the alphabet
			if(T[at][let] == 0){
				T[at][let] = ++this->proxNode;				
			}
			at = T[at][let];
			if(i == (int)s.length() - 1) endOfWord[at] = true;
		}
	}

	bool search(string s) { // retorna falso se s é só o prefixo de alguém que tá na trie, e não uma palavra inteira
		int at = 1;
		for(int i = 0; i < (int)s.length(); ++i) {
			int let = s[i] - 'a';
			if(T[at][let] == 0) return false;
			at = T[at][let];
		}

		return endOfWord[at];
	}

};
