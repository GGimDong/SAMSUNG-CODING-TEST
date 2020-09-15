/*
2-(6*(2-3))
*/
#include <stdio.h>
#include <stdbool.h>

bool is_correct = true;

void calc(char input[100]) {

	char output[100];	// ����ǥ������� ��ȯ�� ���
	int output_idx = 0;	// ����ǥ��� ����
	char mem[100];		// stack
	int top = -1;		// stack�� idx

	// �ϴ� �׳� ����ϴ°� �غ���
	for (int idx = 0; input[idx] != '\0'; idx++) {
		char t = input[idx];

		// )�� ������ ���� ��ȣ�� ���� ���ÿ� ����
		if (t == '(' || t == '*' || t == '+' || t == '-') {
			mem[++top] = t;
		}
		// )�� ������ (�� ���ÿ��� ���ö� ���� �� ���
		else if (t == ')') {
			while (mem[top] != '(') output[output_idx++] = mem[top--];
			top--;
		}
		// ���ڴ� �׳� ���
		else {
			output[output_idx++] = t;
		}
	}

	// ���� stack�� �͵� ���� ���
	while (top != -1) output[output_idx++] = mem[top--];

	printf("����ǥ���: ");
	for (int i = 0; i < output_idx; i++) printf("%c", output[i]);
	printf("\n���: ");

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
	char arr[100];	// �Է� ����
	scanf("%str", &arr);
	
	calc(arr);

	return 0;
}