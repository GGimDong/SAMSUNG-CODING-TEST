#include <cstdio>

const int MAX = 105;

// n개 중에 r개를 뽑을 때
int n, r;
char result[MAX];
bool check[MAX]; // check[i] = true 면 알파벳이 이미 나옴

void getResult(int current) {
	if (current >= r) {
		printf("%s\n",result);
	}
	else {
		for (int i = 0; i < n; i++) {
			char alpha = i + 'a';
			if (check[i] == false) {
				result[current] = alpha;
				check[i] = true;
				getResult(current + 1);
				result[current] = 0;
				check[i] = false;
			}
		}
	}
}


int main() {
	scanf("%d %d", &n, &r);
	getResult(0);

	return 0;
}