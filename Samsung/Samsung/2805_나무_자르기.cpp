#include <cstdio>

const int MAX = 1000000;
int N, M;
int arr[MAX];

typedef long long ll;

int main() {
	ll min = 1, max = 0;
	ll ans = 0;

	scanf("%d %d", &N, &M);
	for (int i = 0; i < N; i++) {
		scanf("%d", &arr[i]);
		if (arr[i] > max) max = arr[i];
	}
	
	while (min <= max) {
		ll mid = (min + max) / 2;
		ll len = 0;
		for (int i = 0; i < N; i++)
			len += (arr[i] > mid)? arr[i] - mid :0;
		
		if (len >= M) {
			min = mid + 1;
			ans = ans < mid ? mid : ans;
		}
		else 
			max = mid - 1;
			
	}
	printf("%ld", ans);
	return 0;
}