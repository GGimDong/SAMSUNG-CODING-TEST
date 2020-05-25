/*INPUT

9
3+8*7-9*2
⇒ 136

5
8*3+5
⇒ 64

7
8*3+5+2
⇒ 66

19
1*2+3*4*5-6*7*8*9*0
⇒ 0

19
1*2+3*4*5-6*7*8*9*9
⇒ 426384

19
1-9-1-9-1-9-1-9-1-9
⇒ 24

*/
#include <cstdio>
#include <vector>
#include <fstream>
#include <iostream>
#define MAX_N 100

using namespace std;

int is_changed = -1;
int max_value;

int N;
char equation[MAX_N];
char new_equation[MAX_N];

//void print_equation() {
//	for (int i = 0; i < N; i++) 
//		printf("%c ", equation[i]);
//	printf("\n");
//}
//
//void print_op(vector<int> _operand, vector<char> _operator) {
//	printf("Operand: ");
//	for (int i = 0; i < _operand.size(); i++)
//		printf("%d ", _operand[i]);
//	printf("\n");
//	for (int i = 0; i < _operator.size(); i++)
//		printf("%c ", _operator[i]);
//	printf("\n");
//}

void total_calc() {
	
	/*지워*///print_equation();

	vector<int> _operand;
	vector<char> _operator;

	for (int i = 0; i < N; i++)
		switch (equation[i]) {
		/* 얘내들은 그냥 넣고 보면 됨 */
		case '+':
		case '-':
		case '*':
		case '(':
			_operator.push_back(equation[i]);
			break;
		case ')':
			int temp_a, temp_b;
			char temp_op;
			temp_b = _operand.back();
			_operand.pop_back();
			temp_a = _operand.back();
			_operand.pop_back();
			temp_op = _operator.back();
			_operator.pop_back();

			if (temp_op == '+')
				_operand.push_back(temp_a + temp_b);
			else if (temp_op == '-')
				_operand.push_back(temp_a - temp_b);
			else if (temp_op == '*')
				_operand.push_back(temp_a*temp_b);

			_operator.pop_back();
			break;
		default:
			_operand.push_back(equation[i] - '0');
			break;
		}

	/*지워*///print_op(_operand, _operator);

	int total_calc_a, total_calc_b;
	char total_calc_op;
	total_calc_a = _operand[0];

	if(_operator.size() > 0)
		for (int i = 0; i < _operator.size(); i++) {
			total_calc_b = _operand[i+1];
			total_calc_op = _operator[i];
			if (total_calc_op == '+')
				total_calc_a = total_calc_a + total_calc_b;
			else if (total_calc_op == '-')
				total_calc_a = total_calc_a - total_calc_b;
			else if (total_calc_op == '*')
				total_calc_a = total_calc_a * total_calc_b;
		}
	else {
		//printf("Error: No operand. \n");
	}
	/*지워*///printf("Result: %d \n\n", total_calc_a);

	if (total_calc_a < 2e31 && -2e31 < total_calc_a) {
		if (is_changed == -1) {
			max_value = total_calc_a;
			is_changed = 1;
		}
		else {
			if (max_value < total_calc_a)
				max_value = total_calc_a;
		}
	}
}

void dfs(int n) {

	if (n == N - 1) {
		total_calc();
		return;
	}

	// operator인데, 첫번째 idx는 아니고, 바로 왼쪽이 operand가 있는 경우
	if (equation[n] - '0' < 0 && equation[n - 1] - '0' >= 0 && equation[n + 1] - '0' >= 0) {
		/* 괄호를 씌움 */
		char origin_equation[MAX_N];
		for (int i = 0; i < N; i++) {
			origin_equation[i] = equation[i];
			if (i < n - 1)
				new_equation[i] = equation[i];
			else if (i > n + 1)
				new_equation[i + 2] = equation[i];
			else {
				new_equation[i + 1] = equation[i];
			}
		}
		N += 2;
		new_equation[n - 1] = '(';
		new_equation[n + 3] = ')';


		for (int i = 0; i < N; i++)
			equation[i] = new_equation[i];
		dfs(n + 2);

		/* 그냥 넘어가기 */
		N -= 2;
		for (int i = 0; i < N; i++)
			equation[i] = origin_equation[i];

		dfs(n + 1);

	}
	else {
		// operand, (, ), 일 경우 그냥 pass
		dfs(n + 1);
	}
}

int main() {
	/*
	ifstream input;
	input.open("input/input.txt");
	input >> N;

	for (int i = 0; i < N; i++)
		input >> equation[i];
	*/
	cin >> N;

	for (int i = 0; i < N; i++)
		cin >> equation[i];

	if (N == 1)
		printf("%d", equation[0] - '0');
	else if (N == 3) {
		int temp_a = equation[0] - '0';
		int temp_b = equation[2] - '0';
		int result;
		if (equation[1] == '+')
			printf("%d", temp_a+temp_b);
		else if (equation[1] == '-')
			printf("%d", temp_a-temp_b);
		else if (equation[1] == '*')
			printf("%d", temp_a*temp_b);
	}
	else {
		dfs(0);
		printf("%d", max_value);
	}
	return 0;
}