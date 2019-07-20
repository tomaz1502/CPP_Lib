#include <iostream>
#include <vector>
using namespace std;

template <typename T1>
bool next_permutation(vector<T1> &perm){ //swaps perm to it's next permutation
	int i, k = -1, j, l;
	for(i = 0; i<perm.size()-1; i++){
		if(perm[i] < perm[i+1]) k = i;	//find longest non-increasing suffix
	}
	
	if(k == -1) return false; //last lexicograph permutation achieved

	for(j = k+1; j<perm.size(); j++){
		if(perm[j] > perm[k]) l = j;
	}

	swap(perm[k], perm[l]);

	int pt1 = k+1, pt2 = perm.size()-1;
	while(pt1 < pt2){
		swap(perm[pt1], perm[pt2]);
		pt1++;
		pt2--;
	}

	return true;
}

int main(){
	vector<int> perm = {1,2,3,4,5};

	do{
		for(int i = 0; i<perm.size(); i++) cout << perm[i] << ' ';
		cout << '\n';
	} while(next_permutation<int>(perm));

	return 0;
}