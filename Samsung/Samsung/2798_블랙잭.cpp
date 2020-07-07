/*
	1. 아무리 쉬워보여도 문제 조건을 꼼꼼하게 읽을 것.
	2. BF 좀 더 연습.
*/

#include <iostream>

using namespace std;

const int MAX = 300000;

int N, M;
int numbers[MAX];
bool number_select[MAX];
int result;
bool first = true;

void print_numbers() {
	int temp = 0;
	for (int i = 0; i < N; i++)
		if (number_select[i])
			temp += numbers[i];

	if (temp > M)
		return;

	if (first) {
		result = temp;
		first = false;
	}
	else
		if ((M - temp) < (M - result))
			result = temp;
}

void doRecursion(int current) {
	if (current >= 3)
		print_numbers();
	else {
		for (int i = 0; i < N; i++) {
			if (!number_select[i]) {
				number_select[i] = 1;
				doRecursion(current + 1);
				number_select[i] = 0;
			}
		}

	}
}

int main() {
	cin >> N >> M;

	for (int i = 0; i < N; i++)
		cin >> numbers[i];

	doRecursion(0);

	cout << result;

	return 0;
}