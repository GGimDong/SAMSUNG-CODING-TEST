#include <iostream>

using namespace std;

const int MAX = 50;

int N;
int value[MAX][2];
int order[MAX];

void print() {
	for (int i = 0; i < N; i++) 
		cout << order[i] << " ";
	return;
}

void doRecursion(int current) {
	if (current >= N)
		print(); // 여기 추가해야댐
	else {
		int Rank = 1;
		for (int i = 0; i < N; i++) {
			if (i != current) {
				if (value[i][0] > value[current][0] && value[i][1] > value[current][1])
					Rank++;
			}
		}
		order[current] = Rank;
		doRecursion(current + 1);
	}
}

int main() {
	cin >> N;

	for (int i = 0; i < N; i++)
		cin >> value[i][0] >> value[i][1];

	doRecursion(0);

	return 0;
}