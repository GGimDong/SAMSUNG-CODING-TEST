/*
	1. ���ڿ� ó������ String ���̺귯���� �����ѵ� �̰� ���� ���׿� ������ ���ڱ�
	2. ���ڿ��� 100�ڸ��� 101�ڸ����� �������� �ϴµ� �� ������ ������ ���ට��
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