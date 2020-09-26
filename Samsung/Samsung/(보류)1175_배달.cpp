#include <iostream>

using namespace std;

int N, M;
char arr[60];
int field[50][50]; // 1 시작, 2 선물타겟, -1 못감 0 갈수 있음
int dir[4][2] = { 
	0,1,
	1,0,
	-1,0,
	0,-1
};

void printField() {
	cout << "입력값" << endl;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) cout << field[i][j] << "\t";
		cout << endl;
	}cout << endl;
}

int main() {
	cin >> N >> M;
	for (int i = 0; i < N; i++) {
		cin >> arr;
		for (int j = 0; arr[j] != '\0'; j++) {
			if (arr[j] == 'S') field[i][j] = 1;
			else if (arr[j] == 'C') field[i][j] = 2;
			else if (arr[j] == '#') field[i][j] = -1;
		}
	}

	/*디버깅*/printField();

	// 첫번째로 간다


	return 0;
}