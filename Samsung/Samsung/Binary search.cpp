#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> arr;
int N, M, ans;

int BF(int low, int high,int x) {
	
	if (low > high) 
		return -1;
	
	int mid = (low + high) / 2;

	if (arr[mid] == x)
		return mid;
	else if (arr[mid] > x)
		return BF(low, mid-1, x);
	else
		return BF(mid+1, high, x);

}

int main() {
	cout << "N: ";
	cin >> N;
	for (int i = 0; i < N; i++) {
		int t;
		cin >> t;
		arr.push_back(t);
	}

	sort(arr.begin(), arr.end());
	
	cout << "["; 
	for (int i = 0; i < N; i++) cout << arr[i] << ", "; 
	cout << "]" << endl;

	cout << "Find: ";
	cin >> M;

	ans = BF(0, N-1, M);

	if (ans == -1)
		cout << "No entry";
	else
		cout << ans + 1;

	return 0;
}