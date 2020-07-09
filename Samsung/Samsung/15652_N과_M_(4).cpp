#include <cstdio>

const int MAX = 8;

int N, M;
int order[MAX];
int len = 0;

void print_nums() {
	for (int i = 0; i < len; i++) 
		printf("%d ", order[i]);
	printf("\n");
}

void doRecursion(int current, int idx) {
	if (current >= M)
		print_nums();
	else {
		for (int i = idx; i <= N; i++) {
			order[len++] = i;
			doRecursion(current + 1, i);
			len--;
		}
	}
}

int main() {
	scanf("%d %d", &N, &M);

	doRecursion(0, 1);

	return 0;
}