#include <cstdio>
#include <algorithm>

using namespace std;

const int MAX = 500000;
int N, M;
int arr[MAX];

int main() {
	scanf("%d", &N);
	for (int i = 0; i < N; i++) scanf("%d", &arr[i]);
	
	sort(arr, arr + N);

	int t;
	scanf("%d", &M);
	
	for (int i = 0; i < M; i++) {
		scanf("%d", &t);
		int min = 0, max = N - 1;
		int lower_idx = -1, upper_idx = -1;

		// 최소 idx 찾기
		while (min <= max) {
			int mid = (min + max) / 2;
			
			if (arr[mid] >= t) {
				max = mid - 1;
				if (arr[mid] == t) lower_idx = mid;
			}
			else
				min = mid + 1;
		}

		// 최대 idx 찾기
		min = 0, max = N - 1;
		while (min <= max) {
			int mid = (min + max) / 2;

			if (arr[mid] <= t) {
				min = mid + 1;
				if (arr[mid] == t) upper_idx = mid;
			}
			else
				max = mid - 1;
		}

		int cnt = (lower_idx != -1 && upper_idx != -1) ? upper_idx - lower_idx + 1 : 0;
		printf("%d ", cnt);
	}

	return 0;
}