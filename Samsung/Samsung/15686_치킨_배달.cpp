#include <iostream>

using namespace std;

int N, M;
int arr[50][50];	// 0�� �� ĭ, 1�� ��, 2�� ġŲ��, ���� ������ 2N���� ���� ������, ��� 1���� ����

int main() {
	cin >> N >> M;
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			cin >> arr[i][j];


	return 0;
}