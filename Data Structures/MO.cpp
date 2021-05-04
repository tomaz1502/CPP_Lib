#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

struct query {
    int l, r, i;
    query(int _l, int _r, int _i) : l(_l), r(_r), i(_i) { }

    friend bool operator<(const query& q1, const query& q2) {
        if (q1.r != q2.r) return q1.r < q2.r;
        else return q1.l < q2.l;
    }
};


struct MO {

    const int block_size = 800;

    int size;
    vector<int> a;
    vector<vector<query>> query_blocks;

    MO(const vector<int>& _a, const vector<query>& queries) : a(_a) {
        size = queries.size();
        query_blocks.resize(block_size);
        for (auto& q: queries) {
            int spot = q.l / block_size;
            query_blocks[spot].push_back(q);
        }

        for (auto& qs: query_blocks) {
            sort(qs.begin(), qs.end());
        }
    }

    vector<long long> Run() {
        vector<long long> answer(size);
        for (auto& block: query_blocks) {
            long long sum = 0;
            int L = 0, R = 0;
            for (auto& q: block) {

                while (R < q.r) {
                    sum += a[R];
                    R++;
                }

                while (L > q.l) {
                    L--;
                    sum += a[L];
                }

                while (L < q.l) {
                    sum -= a[L];
                    L++;
                }

                while (R > q.r) {
                    sum -= a[R];
                    R--;
                }

                answer[q.i] = sum;
            }
        }
        return answer;
    }
};

int main() {
    ios::sync_with_stdio(false);

    int n, q; cin >> n >> q;
    vector<int> a(n);
    for (auto& i: a) cin >> i;

    vector<query> queries;

    for (int i = 0; i < q; i++) {
        int l, r; cin >> l >> r; r--;
        queries.emplace_back(l,r,i);
    }

    MO mo(a, queries);
    auto answer = mo.Run();

    for (auto& x: answer) cout << x << " ";
    cout << "\n";

    return 0;
}
