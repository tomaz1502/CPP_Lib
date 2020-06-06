#include <iostream>

int f(int x) { // example function
    return x * x - 3 * x + 5;
}

// discrete version
int ternary_search(int l, int r) {  // return minimum of f in the interval [l, r]
    if(l >= r) return l;

    int m = (l + r - 1) / 2;

    if (f(m) < f(m + 1))
        return ternary_search(l, m);
    else
        return ternary_search(m + 1, r);

}

double ternary_search(double l, double r) {
    if (l >= r) return l;

    double m1 = (l + l + r) / 3.0;
    double m2 = (l + r + r) / 3.0;

    if(f(m1) < f(m2)) return ternary_search(l, m2);
    else return ternary_search(m1, r);
}


int main() {
    std::cout << ternary_search(-100, 150) << "\n";


    return 0;
}
