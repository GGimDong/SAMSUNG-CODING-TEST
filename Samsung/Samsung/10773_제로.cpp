#include <iostream>
#include <stack>

using namespace std;

int K;

int main() {
	cin >> K;
	int temp;
	stack<int> s;
	for (int i = 0; i < K; i++) {
		cin >> temp;
		if (temp == 0)
			s.pop();
		else
			s.push(temp);
	}
	int ans=0;
	while(!s.empty()) {
		ans += s.top();
		s.pop();
	}
	cout << ans;
	return 0;
}