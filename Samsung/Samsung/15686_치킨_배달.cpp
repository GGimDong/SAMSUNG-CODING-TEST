#include <iostream>

using namespace std;

int N, M;
int arr[50][50];	// 0은 빈 칸, 1은 집, 2는 치킨집, 집의 개수는 2N개를 넘지 않으며, 적어도 1개는 존재

int main() {
	cin >> N >> M;
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			cin >> arr[i][j];


	return 0;
}