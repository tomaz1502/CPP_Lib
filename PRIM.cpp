#include <iostream>
#include <vector>
#include <queue>
#include <tuple>
using namespace std;

#define LIM ((int)1e5 + 1)

const int inf = (int)1e8;
vector< pair<int, int> > G[LIM];
vector< tuple<int, int, int> > MST;
bool seen[LIM];
long long cost = 0;

int main(){
    ios::sync_with_stdio(false);
    int n, m; cin >> n >> m;
    priority_queue< tuple<int, int, int> > pq; //{weight, inside, outside}

    fill(seen, seen+LIM, false);

    for(int i = 0; i<m; i++){
        int u, v, w; cin >> u >> v >> w;
        G[u].push_back({v, w});
        G[v].push_back({u, w});
    }
    
    for(auto elem : G[1]) pq.push({-elem.second, 1, elem.first});
    seen[1] = true;

    while(!pq.empty()){
        tuple<int, int, int> at = pq.top(); pq.pop();
        get<0>(at) *= -1;

        if(seen[get<2>(at)]) continue;
        seen[get<2>(at)] = true;
        
        //include get<2>(at) in the cut
        MST.push_back({get<0>(at), get<1>(at), get<2>(at)});
        cost += get<0>(at);

        for(auto child : G[get<2>(at)]){
            pq.push({-child.second, get<2>(at), child.first});
        }
    }
        
    cout << "Custo da MST: " << cost << '\n' << "Arestas (u,v,w): \n";
    for(auto elem : MST){
        cout << '(' << get<1>(elem) << ", " << get<2>(elem) << ", " << get<0>(elem) << ')' << '\n';
    }

    return 0;
}
