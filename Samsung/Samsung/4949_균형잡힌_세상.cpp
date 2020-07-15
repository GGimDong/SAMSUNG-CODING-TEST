/*
	1. 문자열 처리에는 String 라이브러리가 유용한데 이게 실제 코테에 나올진 몰겠군
	2. 문자열이 100자리면 101자리까지 만들어줘야 하는데 그 이유가 마지막 개행때문
*/
#include <iostream>
#include <string>
#include <stack>

using namespace std;

const int MAX = 101;

void check(char* str) {
	stack<int> s;
	for (int i = 0; str[i] != '.'; i++) {
		if (str[i] == '(') {
			s.push(1);
		}
		else if (str[i] == '[') {
			s.push(2);
		}
		else if (str[i] == ']') {
			if (s.empty()) {
				s.push(-1);
				break;
			}
			if (s.top() == 2) 
				s.pop();
			else if (s.top() == 1) {
				s.push(-1);
				break;
			}
		}
		else if(str[i] == ')'){
			if (s.empty()) {
				s.push(-1);
				break;
			}
			if (s.top() == 1)
				s.pop();
			else if (s.top() == 2) {
				s.push(-1);
				break;
			}
		}
		else {

		}
	}

	if (s.empty())
		cout << "yes" << endl;
	else
		cout << "no" << endl;
}

int main() {
	char line[MAX];
	string end = ".";

	while (1) {
		cin.getline(line,101);
		
		if (line == end) {
			//cout << "end";
			break;
		}

		check(line);
	}

	return 0;
}