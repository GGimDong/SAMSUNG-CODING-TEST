#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#define MAX_N 11

using namespace std;

vector<int> _operand;
vector<char> _operator;
int N, temp;
int max_value = -1000000000;
int min_value = 1000000000;

void print_operand() {
	for (int i = 0; i < _operand.size(); i++)
		cout << _operand[i];
	cout << endl;
}
void print_operator() {
	for (int i = 0; i < _operator.size(); i++)
		cout << _operator[i];
	cout << endl;
}

void calc(vector<char> _op) {
	int a = _operand.front();
	int b;
	for (int i = 1; i < N; i++) {
		b = _operand[i];
		
		switch (_op[i - 1]) {
		case '+':
			a = a + b;
			break;
		case '-':
			a = a - b;
			break;
		case '*':
			a = a * b;
			break;
		case '%':
			a = a / b;
			break;
		}
	}
	if (a > max_value)
		max_value = a;
	if (min_value > a)
		min_value = a;

	return;
}

int main() {
	ifstream input;
	input.open("input/input.txt");
	
	input >> N;
	for (int i = 0; i < N; i++) {
		input >> temp;
		_operand.push_back(temp);
	}

	int add_N, sub_N, mul_N, div_N;

	input >> add_N >> sub_N >> mul_N >>div_N;

	/* 4개의 연산을 next_permutation을 위해 값의 크기에 맞게 순서 맞춤 */
	/* 나눗셈 연산자 */
	for (int i = 0; i < div_N; i++) 
		_operator.push_back('%');

	/* 곱셈 연산자 */
	for (int i = 0; i < mul_N; i++) 
		_operator.push_back('*');

	/* + 연산자 */
	for (int i = 0; i < add_N; i++) 
		_operator.push_back('+');

	/* - 연산자 */
	for (int i = 0; i < sub_N; i++) 
		_operator.push_back('-');

	int i = 1;
	do {
		calc(_operator);
	} while (next_permutation(_operator.begin(), _operator.end()));

	cout << max_value << endl << min_value;
	return 0;
}