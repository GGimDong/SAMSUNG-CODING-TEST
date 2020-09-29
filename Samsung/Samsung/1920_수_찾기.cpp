#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

const int MAX = 100000;
vector<int> arr;
int N, M;

int BF(int min, int max, int target) {
	if (min > max)
		return 0;
	int mid = (min + max) / 2;

	if (arr[mid] == target)
		return 1;
	else if (arr[mid] > target)
		return BF(min, mid - 1, target);
	else
		return BF(mid + 1, max, target);
}

int main() {
	scanf("%d", &N);
	int t;
	for (int i = 0; i < N; i++) {
		scanf("%d", &t);
		arr.push_back(t);
	}

	sort(arr.begin(), arr.end());

	scanf("%d", &M);

	for (int i = 0; i < M; i++) {
		scanf("%d", &t);
		printf("%d\n", BF(0, N - 1, t));
	}

	return 0;
}