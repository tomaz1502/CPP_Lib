#include <iostream>
#include <vector>
using namespace std;

struct KMP {

    vector<int> lps;
    vector<vector<int>> automaton;
    string Ptt;

    KMP(string _Ptt) : Ptt(_Ptt) {
        lps.resize(Ptt.size());
        lps[0] = 0;
        int i = 1, j = 0;
        while(i < (int)Ptt.size()) { //preenche lps[i] (ja tem todos ate i-1 calculados)
            if(Ptt[i] == Ptt[j]) {
                i++;
                j++;
                lps[i-1] = j;
            }
            else{
                if(j == 0) {
                    lps[i] = 0;
                    i++;
                }
                else j = lps[j-1];
            }
        }
        make_automaton();
    }

    void make_automaton() {
        int len = Ptt.size();
        automaton = vector<vector<int>>(len, vector<int>(26));
        for (int i = 0; i <= len; ++i) {
            for (char ch = 'a'; ch <= 'z'; ch++) {
                if (i < len && ch == Ptt[i]) automaton[i][ch - 'a'] = i + 1;
                else if (i > 0) automaton[i][ch - 'a'] = automaton[lps[i - 1]][ch - 'a'];
                else automaton[i][ch - 'a'] = 0;
            }
        }
    }

    void search(string Ptt, string Txt) {
        int i = 0, j = 0, n = Txt.size(), m = Ptt.size();
        while(i - j <= n - m) {
            if(Ptt[j] == Txt[i]) {
                i++;
                j++;
                if(j == m){
                    cout << "achei: " << i-j << '\n';
                    j = lps[j-1];
                }
            }
            else {
                if(j == 0) i++;
                else j = lps[j-1];
            }
        }
    }
};


int main() {
    string Ptt, Txt;
    getline(cin, Txt);
    getline(cin, Ptt);
    KMP kmp(Ptt);
    kmp.search(Ptt, Txt);

    for (auto [l, r] : v) {

    }

    return 0;
}
