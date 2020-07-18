/*
	endl 쓰지 말것. 시간 오지게 먹음
*/
#include<stack>
#include<iostream>
#include<vector>
#include <cstdlib>

using namespace std;

stack<int> s;
vector<char> op;

int N, temp;
int idx = 1;

bool operation(int x) {
	while (1) {
		if (s.empty()) {
			//cout << "PUSH: " << idx << endl;
			
			op.push_back('+');
			s.push(idx++);
		}
		else if (s.top() == x) {
			//cout << "POP: " << x << endl;
			
			op.push_back('-');
			s.pop();
			return true;
		}
		else if (s.top() < x) {
			//cout << "PUSH: " << idx << endl;

			op.push_back('+');
			s.push(idx++);
		}
		else {
			// top보다 x값이 높은 경우 7 저장되있는데 4를 내놓아라 할 경우 -> 이건 못함
			return false;
		}
	}
}

int main() {
	cin >> N;
	bool pos = true;
	for (int i = 0; i < N; i++) {
		cin >> temp;
		if (pos) 
			if(!operation(temp))
				pos = false;
	}

	if (pos) {
		for (int i = 0; i < op.size(); i++)
			cout << op[i] << endl;
	}
	else
		cout << "NO" << endl;
}