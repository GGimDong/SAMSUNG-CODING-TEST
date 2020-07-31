#include <iostream>
#include <vector>

using namespace std;

int dir[4][2] = {
	{0, 1},	// ��
	{1, 0},	// ��
	{0,-1},	// ��
	{-1,0}	// �Ʒ�
};

int time = 0;
int N, K, L, a, b;
int arr[100][100]; // 0�� N�� ������ ���� ����, -1�� 1�� 2���
int order[100][2];	// 0�ð��� 1��ɾ�
char temp;

struct Snake {
	int d = 0;
	int body[10000][2];
	int len = 1;

	bool move() {
		int nx = body[0][0] + dir[d][0], ny = body[0][1] + dir[d][1];
		if (nx == N || ny == N || nx == -1 || ny == -1 || arr[nx][ny] == 1) return false;

		if (arr[nx][ny] == 2) { // ������ ����� ���
			// ������ �þ�� ������ �� ĭ�� �����̸� ��.
			for (int i = len; i > 0; i--) {
				body[i][0] = body[i-1][0], body[i][1] = body[i - 1][1];
			}
			body[0][0] = nx, body[0][1] = ny;
			len++;
			arr[nx][ny] = 1;
		}
		else { // �׳� ������ ���
			// ���� �̵��� ��Ű�� ��. ���� �ڸ��� �밡�� �ø���
			arr[body[len-1][0]][body[len-1][1]] = 0;
			for (int i = len-1; i > 0; i--) {
				body[i][0] = body[i - 1][0], body[i][1] = body[i - 1][1];
			}
			body[0][0] = nx, body[0][1] = ny;
			arr[nx][ny] = 1;	
		}
		return true;
	}
	// �밡�� �������
	void rotate(int r) {
		d = d + r;
		if (d == -1) d = 3;
		if (d == 4) d = 0;
	}
}snake;

void print_board() {
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++) {
			cout << arr[i][j] << " ";
		}cout << endl;
	}cout << endl;
}

int main() {
	cin >> N;
	cin >> K;

	for (int i = 0; i < K; i++){
		cin >> a >> b;
		arr[a - 1][b - 1] = 2;
	}
	cin >> L;
	for (int i = 0; i < L; i++) {
		cin >> order[i][0] >> temp;
		if (temp == 'L') order[i][1] = -1;
		else order[i][1] = 1;
	}
	
	arr[0][0] = 1;
	snake.body[0][0] = 0, snake.body[0][1];
	//print_board();
	int moveIdx = 0;
	
	while (1) {
		time++;
		//cout << "Time: "<<time << endl;
		if (!snake.move()) break;	//���̳� �� ���� ������ ��
		if (order[moveIdx][0] == time) snake.rotate(order[moveIdx++][1]);	// �ð��Ǹ� ȸ��!
		//print_board();
		//system("pause");
	}

	cout << time;
	return 0;
}