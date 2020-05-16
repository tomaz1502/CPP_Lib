#include <iostream>

int f(int x) { // example function
    return x * x - 3 * x + 5;
}

// discrete version
int ternary_search(int l, int r) {  // return minimum of f in the interval [l, r]
    if(l >= r) return l;

    int m = (l + r - 1) / 2;

    if (f(m) < f(m + 1))
        return ts(l, m);
    else
        return ts(m + 1, r);

}

int main() {
    
    std::cout << ts(-100, 150) << "\n";

    return 0;
}
