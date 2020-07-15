#include <stack>
#include <iostream>

using namespace std;

int N;

int main() {
	cin >> N;

	for (int i = 0; i < N; i++) {
		char arr[50];
		cin >> arr;
		stack<int> s;
		for (int i = 0; arr[i] != '\0'; i++) {
			if (arr[i] == '(')
				s.push(1);
			else {
				if (s.empty()) {
					s.push(1);
					break;
				}
				s.pop();
			}
		}
		if (s.empty()) 
			cout << "YES" << endl;		
		else
			cout << "NO" << endl;
	}

	return 0;
}