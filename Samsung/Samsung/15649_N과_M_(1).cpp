#include <iostream>
#include <cstdio>

using namespace std;

const int MAX = 9;

int N, M;
bool check[MAX] = {false, };
int order[MAX];
int len = 0;

void print_nums() {
	for (int i = 0; i < len; i++)
		printf("%d ",order[i]);// cout << order[i] << " ";
	printf("\n");// << endl;
}

void doRecursion(int current) {
	if (current >= M)
		print_nums();
	else{
		for (int i = 1; i <= N; i++) {
			if (!check[i]) {
				check[i] = true;
				order[len++] = i;
				doRecursion(current + 1);
				len--;
				check[i] = false;
			}
		}
	}
}

int main() {
	cin >> N >> M;
	
	doRecursion(0);

	return 0;
}