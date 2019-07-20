#include <cassert>
#include <stack>
#include <iostream>
using namespace std;

using minStack = stack< pair<long long, long long> >; //second: min element below at

struct minQueue{
    minStack in, out;

    #define INF (long long)1e16

    minQueue(){ in.push({INF, INF}); out.push({INF, INF}); }

    void push(long long x){
        long long m = in.top().second;
        in.push({x, min(x, m)});
    }

    long long pop(){
        if(out.top().first == INF){
            while(in.top().first != INF){
                pair<long long, long long> p = in.top(); in.pop();
                long long m = out.top().second;
                out.push({p.first, min(p.first, m)});
            }
        }
        long long x = out.top().first; out.pop();
        assert(x != INF);
        return x;
    }

    long long getMin(){ return min(in.top().second, out.top().second); }


};

int main(){

    return 0;
}
