/*
	int는 2 x 10^9 만큼임을 기억하자
*/
#include <iostream>

using namespace std;

int N, B, C;
int arr[1000000] = {0, };
long long result = 0;

int find_num(int x) {
	int ans = 1;
	x = x - B;
	if (x <= 0) return ans;
	int t_ans = x / C, remain = x % C;
	ans += t_ans;
	if (remain == 0) return ans;
	else return ans + 1;
}

int main() {
	cin >> N;
	for (int i = 0; i < N; i++) cin >> arr[i];
	cin >> B >> C;
	for (int i = 0; i < N; i++) result +=find_num(arr[i]);
	cout << result;
	return 0;
}