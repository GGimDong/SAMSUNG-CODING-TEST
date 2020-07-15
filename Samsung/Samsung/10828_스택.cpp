#include <iostream>
#include <stack>
#include <string>

using namespace std;

stack<int> s;
int N;
string str;

void operation(string str) {
	if (str == "top") {
		if (s.empty())
			cout << "-1" << endl;
		else
			cout << s.top() << endl;
	}
	else if (str == "size") {
		cout << s.size() << endl;
	}
	else if (str == "pop") {
		if (s.empty())
			cout << "-1" << endl;
		else {
			cout << s.top() << endl;
			s.pop();
		}
	}
	else if (str == "empty") {
		if (s.empty())
			cout << "1" << endl;
		else 
			cout << "0" << endl;
	}
	else {
		int temp;
		cin >> temp;
		s.push(temp);
	}
	

}

int main() {
	
	cin >> N;

	for (int i = 0; i < N; i++) {
		cin >> str;
		operation(str);
	}


}