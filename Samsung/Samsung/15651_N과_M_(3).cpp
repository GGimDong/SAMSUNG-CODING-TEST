#include <cstdio>

const int MAX = 8;
int N, M;
int len = 0;
int order[MAX];

void print_nums() {
	for (int i = 0; i < len; i++)
		printf("%d ", order[i]);
	printf("\n");
}

void doRecursion(int current) {
	if (current >= M)
		print_nums();
	else {
		for (int i = 1; i <= N; i++) {
			order[len++] = i;
			doRecursion(current + 1);
			len--;
		}
	}
}

int main(void) {
	scanf("%d %d", &N, &M);

	doRecursion(0);

	return 0;
}