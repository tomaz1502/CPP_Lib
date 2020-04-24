#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

class BigInt {
    
public:
    string num;
    BigInt(const string &s) : num(s) {}

    string get() { return num; }

    BigInt operator+(BigInt B) {
        string ret = "";
        string n1 = B.get(), n2 = num;
        reverse(n1.begin(), n1.end());
        reverse(n2.begin(), n2.end());

        while(n1.size() < n2.size()) n1 += '0';
        while(n2.size() < n1.size()) n2 += '0';

        int carry = 0;
        for(int i = 0; i < n1.size(); i++) {
            int p = n1[i] - '0' + n2[i] - '0' + carry;
            carry = p/10;
            ret += (p%10) + '0';
        }

        if(carry > 0) ret += (carry + '0');

        reverse(ret.begin(), ret.end());
        return BigInt(ret);
    }

    void operator+=(BigInt B) {
        *this = *this + B;
    }

    BigInt operator-(BigInt B) {

    }
};

int main() {
    BigInt N("1234"), M("9991");
    N += M;
    cout << N.get() << '\n';
    return 0;
}
