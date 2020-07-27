#include <cstdio>

int arr[50] = {
	  0, 2, 4, 6, 8,
	 10,12,14,16,18,
	 20,22,24,26,28,
	 30,32,34,36,38,
	 40,-1,13,16,19,
	 25,26,27,28,22,
	 24,30,35
};
int order[10];

void getResult(int idx) {
	if (idx >= 10) {

	}
	else {
		for (int i = 0; i < 4; i++) {
			order[idx] = i;
			getResult(idx + 1);
		}
	}
}

int main() {
	for (int i = 0; i < 10; i++) scanf("%d", &order[i]);

	getResult(0);

}