#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

class BigInt {
    
public:
    string num;
    BigInt(string s) : num(s) {}

    string get() { return num; }

    BigInt operator+(BigInt B) {
        string ret = "";
        string n1 = B.get(), n2 = num;
        reverse(n1.begin(), n1.end());
        reverse(n2.begin(), n2.end());

        int i = 0, carry = 0;
        for(; i < min(n1.size(), n2.size()); i++) {
            int p = n1[i] - '0' + n2[i] - '0' + carry;
            carry = p/10;
            ret += (p%10) + '0';
        }

        while(i < n1.size()) {
            int p = n1[i] - '0' + carry;
            carry = p/10;
            ret += (p%10) + '0';
            i++;
        }

        while(i < n2.size()) {
            int p = n2[i] - '0' + carry;
            carry = p/10;
            ret += (p%10) + '0';
            i++;
        }

        if(carry > 0) ret += (carry + '0');

        reverse(ret.begin(), ret.end());
        return BigInt(ret);
    }



};
