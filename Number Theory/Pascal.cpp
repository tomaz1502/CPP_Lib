#include <vector>
using namespace std;
using ll = long long;

const int MOD = 1e9 + 7;

vector<vector<int>> bin_coefs(int L) {
    vector<vector<int>> bin(L, vector<int>(L));
	bin[0][0] = 1;
	for (int i = 1; i < L; i++) {
		bin[i][0] = 1;
		for (int j = 1; j <= i; j++)
			bin[i][j] = (bin[i - 1][j] + bin[i - 1][j - 1]) % MOD;
	}
	return bin;
}

int main() {

    return 0;
}
