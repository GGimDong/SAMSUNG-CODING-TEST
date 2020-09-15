/*
2-(6*(2-3))
*/
#include <stdio.h>
#include <stdbool.h>

bool is_correct = true;

void calc(char input[100]) {

	char output[100];	// 후위표기법으로 변환한 결과
	int output_idx = 0;	// 후위표기법 길이
	char mem[100];		// stack
	int top = -1;		// stack의 idx

	// 일단 그냥 계산하는거 해보자
	for (int idx = 0; input[idx] != '\0'; idx++) {
		char t = input[idx];

		// )를 제외한 연산 기호는 전부 스택에 넣음
		if (t == '(' || t == '*' || t == '+' || t == '-') {
			mem[++top] = t;
		}
		// )가 나오면 (가 스택에서 나올때 까지 다 출력
		else if (t == ')') {
			while (mem[top] != '(') output[output_idx++] = mem[top--];
			top--;
		}
		// 숫자는 그냥 출력
		else {
			output[output_idx++] = t;
		}
	}

	// 남은 stack에 것들 전부 출력
	while (top != -1) output[output_idx++] = mem[top--];

	printf("후위표기식: ");
	for (int i = 0; i < output_idx; i++) printf("%c", output[i]);
	printf("\n결과: ");

	while (1) {
		int op_idx = -1;

		for (int i = 0; i < output_idx; i++)
			if (output[i] == '*' || output[i] == '+' || output[i] == '-') {
				op_idx = i;
				break;
			}

		if (op_idx == -1) break;


		int a = output[op_idx - 2] - '0', b = output[op_idx - 1] - '0', result;
		char op = output[op_idx];

		if (op == '*') result = a * b;
		else if (op == '+') result = a + b;
		else if (op == '-') result = a - b;

		output[op_idx - 2] = (char)(result + '0');

		for (int j = op_idx - 1; j < output_idx; j++) output[j] = output[j + 2];
	}

	printf("%d \n", output[0] - '0');
}

int main() {
	char arr[100];	// 입력 수식
	scanf("%str", &arr);
	
	calc(arr);

	return 0;
}