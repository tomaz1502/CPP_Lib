#include <bits/stdc++.h>
using namespace std;

template<int Modulus, typename Op> struct modint {
    Op number;

    modint (Op Number = 0) : number(Number % Modulus) { }

    modint operator+ (modint other) { return modint(number) += other; }
    modint operator- (modint other) { return modint(number) -= other; }
    modint operator* (modint other) { return modint(number) *= other; }
    modint operator/ (modint other) { return modint(number) /= other; }
    modint operator^ (modint other) { return modint(number) ^= other; }

    modint operator+ (Op other) { return *this + modint(other); }
    modint operator- (Op other) { return *this - modint(other); }
    modint operator* (Op other) { return *this * modint(other); }
    modint operator/ (Op other) { return *this / modint(other); }
    modint operator^ (Op other) { return *this ^ modint(other); } 

    void operator+= (Op other) { *this = *this + other; }
    void operator-= (Op other) { *this = *this - other; }
    void operator*= (Op other) { *this = *this * other; }
    void operator/= (Op other) { *this = *this / other; }
    void operator^= (Op other) { *this = *this ^ other; }

    modint operator+= (modint &other) {
        number += other.number;
        if(number >= Modulus) number -= Modulus;
        return number;
    }
    
    modint operator-= (modint &other) {
        if(number < other.number) number += Modulus;
        number -= other.number;
        return number;
    }

    modint operator*= (modint &other) {
        number = (number * other.number) % Modulus;
        return number;
    }

    modint operator^= (modint &Exp) {
        modint tmp = *this;
        modint ret(1);
        Op exp = Exp.number;

        while (exp > 0) {
            if(exp & 1) ret *= tmp;
            tmp *= tmp;
            exp >>= 1;
        }
        *this = ret;
        return *this;
    }

    modint operator/= (modint other) {
        modint invOther = other ^ (Modulus - 2);
        *this *= invOther;
        return *this;
    }

    friend ostream &operator<< (ostream &out, modint mi) {
        return out << mi.number;
    }
};

const int MOD = 7;
using mint = modint< MOD, long long >;



int main() {
    
    mint a(3), b(5);
    
    mint e = a + b;
    mint f = a - b;
    mint g = a * b;
    mint h = a / b;
    mint i = a ^ b;

    cout << a << " " << b << "\n";
    cout << "add: " << e << "\n";
    cout << "sub: " << f << "\n";
    cout << "mul: " << g << "\n";
    cout << "div: " << h << "\n";
    cout << "exp: " << i << "\n";

    cout << a + 2 << "\n";
    cout << a << "\n";
    a += 2;
    cout << a << "\n";

    return 0;
}
