#include <iostream>

using namespace std;

int N;

bool check(int x) {
	int gap;
	int a = -1;
	int b = -1;
	while (x != 0) {
		if (a == -1) 
			a = x % 10;
		else if (b == -1) {
			b = x % 10;
			gap = b - a;
		}
		else {
			a = b;
			b = x % 10;
			if (gap != b - a)
				return false;
		}
		x = 0.1 * x;
	}
	return true;
}

// 연속된 두 개의 수의 차이가 일정한 수열, 그러니 최소 3자리

int main() {
	cin >> N;
	int ans = 0;

	for (int i = 1; i <= N; i++)
		if(check(i)) 
			ans++;
	
	cout << ans;
	return 0;
}