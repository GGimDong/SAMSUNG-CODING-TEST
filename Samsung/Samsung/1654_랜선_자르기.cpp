#include <cstdio>

const int MAX = 10000;
int K, N;
int arr[MAX];

typedef long long ll;

int main() {
	scanf("%d %d", &K, &N);
	
	ll min = 1, max = 0;
	ll ans = 0;
	for (int i = 0; i < K; i++) {
		scanf("%d", &arr[i]);
		if (arr[i] > max) max = arr[i];
	}

	while (min <= max) {
		ll mid = (min + max) / 2;
		int cnt = 0;
		for (int i = 0; i < K; i++) cnt += arr[i] / mid;
		
		if (cnt >= N) {
			min = mid + 1;
			ans = mid;
		}
		else
			max = mid - 1;
	}

	printf("%ld", ans);
	return 0;
}