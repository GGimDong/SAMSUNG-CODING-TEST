#include <cstdio>

const int MAX = 8;
int N, M;
bool check[MAX+1];

void print_nums() {
	for (int i = 1; i <= N; i++)
		if (check[i])
			printf("%d ", i);
	printf("\n");
}

void doRecursion(int current, int idx) {
	if (current >= M)
		print_nums();
	else {
		for (int i = idx; i <= N; i++) {
			if (!check[i]){
				check[i] = true;
				doRecursion(current + 1, i);
				check[i] = false;
			}

		}
	}

}

int main(void) {
	scanf("%d %d", &N, &M);

	doRecursion(0, 1);

	return 0;
}