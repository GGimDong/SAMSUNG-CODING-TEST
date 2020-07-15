#include<stack>
#include<iostream>
#include<vector>
using namespace std;

stack<int> s;
vector<char> op;

int N, temp;
int left_num = 1;

bool operation(int x) {
	
	if (s.top() == x) {
		op.push_back('-');
		s.pop();
	}
	else if( !s.empty() && s.top() )
}

int main() {
	cin >> N;
	bool pos = true;
	for (int i = 0; i < N; i++) {
		cin >> temp;
		if (!operation(temp)) {
			pos = false;
			break;
		}
	}
	if (pos) {

	}
	else
		cout << "NO" << endl;
}