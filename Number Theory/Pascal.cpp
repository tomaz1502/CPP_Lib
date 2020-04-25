#include <vector>
using namespace std;
using ll = long long;

const int MOD = 1e9 + 7;

vector< vector< ll > > pascal(int n_max, ll MOD){
	vector< vector< ll > > ret = vector< vector< ll > >(0, vector<ll>(0));
	ret[0][0] = 1;
	for(int i = 1; i<=n_max; i++){
		ret[i][0] = 1;
		for(int j = 1; j<=i; j++){
			ret[i][j] = (ret[i-1][j] + ret[i-1][j-1]) % MOD;
		}
	}
	return ret;
}

int main() {

    return 0;
}
