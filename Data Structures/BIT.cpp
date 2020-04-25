#include <bits/stdc++.h>
using namespace std;

template<typename T> //T must be "sum-able -> may have operator+ defined"
class BIT {
	vector<T> B; //EVERYTHING IS ONE-BASED

public:
	void update(int index, T value) {
		while(index < B.size()){
			B[index] += value;
			index += (index & -index);
		}
	}

	T sum(int end) {
		T ret = 0;
		while(end >= 1){
			ret += B[end];
			end -= (end & -end);
		}
		return ret;
	}

	T range_sum(int begin, int end) {
		assert(begin > 0);
		return sum(end) - sum(begin - 1);
	}

	BIT(const vector<T> &base) {
		B = vector<T>(base.size(), 0);
		for(int i = 1; i<base.size(); ++i){
			this->update(i, base[i]);
		}
	}
	
	BIT(int sz){ B = vector<T>(sz, 0); }
};

int main() {

    return 0;
}
