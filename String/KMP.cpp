#include <iostream>
#include <vector>
using namespace std;

struct KMP {

    vector<int> lps;

    KMP(string Ptt) {
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

    return 0;
}
