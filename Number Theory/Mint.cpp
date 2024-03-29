#include <iostream>
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

    bool operator== (modint other) { return number == other.number; }
    bool operator!= (modint other) { return !(*this == other); }
    bool operator== (Op other) { return number == other; }
    bool operator!= (Op other) { return !(number == other); }

    modint operator+= (modint other) {
        number += other.number;
        if(number >= Modulus) number -= Modulus;
        return number;
    }

    modint operator-= (modint other) {
        if(number < other.number) number += Modulus;
        number -= other.number;
        return number;
    }

    modint operator*= (modint other) {
        number = (number * other.number) % Modulus;
        return number;
    }

    modint operator^= (modint Exp) {
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

    modint inverse() { return *this ^ (Modulus - 2); }

    modint operator/= (modint other) {
        modint invOther = other.inverse();
        *this *= invOther;
        return *this;
    }

};

const int MOD = 998244353;
using mint = modint< MOD, long long >;

ostream &operator<< (ostream &out, mint mi) {
    return out << mi.number;
}

istream &operator>> (istream &in, mint mi) {
    return in >> mi.number;
}

const int N = 1e5 + 10;
mint fat[N], ifat[N];

void fac() {
    fat[0] = 1;
    for(int i = 1; i < N; i++) fat[i] = fat[i - 1] * i;
    ifat[N - 1] = fat[N - 1] ^ (MOD - 2);
    for(int i = N - 2; i >= 0; --i) {
        ifat[i] = ifat[i + 1] * (i + 1);
    }
}

mint bin(int n, int k) {
    return fat[n] * ifat[k] * ifat[n - k];
}

int main() {
    fac();
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
