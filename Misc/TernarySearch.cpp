#include <iostream>
using namespace std;

int f(int x) { // example function
    return x * x - 3 * x + 5;
}

// discrete version
int ts(int l, int r) {  // mininum
    if(l >= r) return l;

    int m = (l + r - 1) / 2;

    if (f(m) < f(m + 1))
        return ts(l, m);
    else
        return ts(m + 1, r);

}

int main() {
    
    cout << ts(-100, 150) << "\n";

    return 0;
}
