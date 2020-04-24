#include <bits/stdc++.h>
using namespace std;

class RomanNumerals {

protected:
    map<char, int> val;
    string seek;

public:
    
    RomanNumerals();
    string toRoman(int x);
    int fromRoman(string rom);

};

RomanNumerals::RomanNumerals() {

    val['M'] = 1000;
    val['D'] = 500;
    val['C'] = 100;
    val['L'] = 50;
    val['X'] = 10;
    val['V'] = 5;
    val['I'] = 1;
    
    string seek = "MDCLXVI";

}

string RomanNumerals::toRoman(int x) {

       
    string ret = "";
    while(x) {
      for(int i = 0; i < 7; i++) {
          char c = seek[i];
          if(i % 2 == 0) {
              if(4 * val[c] <= x) {
                  ret += c;
                  ret += seek[i - 1];
                  x -= (val[seek[i - 1]] - val[c]);
                  break;
              }
              else if(val[c] <= x) {
                  x -= val[c];
                  ret += c;
                  break;
              }
          }
          else {
              if(val[c] + 4 * (val[c] / 5) > x and val[c] <= x) {
                  x -= val[c];
                  ret += c;
                  break;
              }
              else if(val[c] <= x) {
                  x -= (val[seek[i - 1]] - val[seek[i + 1]]);
                  ret += seek[i + 1];
                  ret += seek[i - 1];
                  break;
              }
          }            
      }

    }

    return ret;
}

int RomanNumerals::fromRoman(string rom) {
    
    int ret = 0;
    
    for(int i = 0; i < (int)rom.size() - 1; ++i) {
        
        char c = rom[i], d = rom[i + 1];
        if(val[c] >= val[d]) ret += val[c];
        else ret -= val[c];
        
    }

    ret += val[rom.back()];
    return ret;
}


int main() {
    RomanNumerals RN();
    cout << RN.fromRoman("MCM") << '\n';
    cout << RN.toRoman(1234) << '\n';

    return 0;
}
