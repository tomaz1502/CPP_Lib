#include <bits/stdc++.h>
using namespace std;

class Stack{
    int v[10000];
    int p, minE;
public:

    Stack(){ p = 0; }

    void push(int x){
        if(p == 0){
            v[p++] = x;
            minE = x;
        }
        else{
            if(x > minE) v[p++] = x;
            else{
                v[p++] = 2*x - minE;
                minE = x;
            }
        }
    }

    int pop(){
        if(p == 0) cout << "Empty!\n", assert(false);
        p--;
        if(v[p] < minE){
            minE = 2*minE - v[p];
            return minE;
        }
        else return v[p];
    }

    int MIN(){ return minE; }
};

int main(){
    Stack s;
    s.push(3); s.push(4); s.push(2);
    cout << s.MIN() << '\n';
    s.pop();
    cout << s.MIN() << '\n';
    return 0;
}
