/*
	memset�� ��������... �ǽ����� ����
	�ٸ�, �ð� �ʰ��� ����, �ð��ʰ��� �Ϻη� ���� ��ġ�� ������ ��������.
*/
#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

struct shark {
	int x, y, speed, d, size;
	bool is_dead = false;

	void changeDir() {
		if (d == 1) d = 2;
		else if (d == 2) d = 1;
		else if (d == 3) d = 4;
		else if (d == 4) d = 3;
	}

	void die() { is_dead = true; }
};

shark make_shark(int a, int b, int c, int d, int e) {
	shark temp;
	temp.x = a, temp.y = b, temp.speed = c, temp.d = d, temp.size = e;
	return temp;
}

int dir[5][2] = { {0,0}, {-1,0}, {1,0}, {0,1}, {0,-1} };
int arr[101][101];
int temp[101];
int R, C, M, a, b, c, d, e;
vector<shark> v;	// �ε����� 0���� �����̶� idx -1 ��° �� ã���� ��.

/*�����*/ //void printBoard() { cout << endl; for (int i = 1; i <= R; i++) { for (int j = 1; j <= C; j++) { cout << arr[i][j] << " "; }cout << endl; } }

void sharkMove() {
	memset(arr, 0, sizeof(arr));
	for (int sharkIdx = 0; sharkIdx < M; sharkIdx++) {	// 0 ~ M-1
		if (v[sharkIdx].is_dead) continue;	// ���� �ִ� �н�
		int x = v[sharkIdx].x, y = v[sharkIdx].y, speed = v[sharkIdx].speed, d = v[sharkIdx].d;
		
		// TODO: �ð� ���̱������ speed �ٿ����� 1000�� �ʹ�ū��
		if (d == 1 || d == 2) {// �� �Ʒ���, 
			int max = 2 * (R - 1);
			if (speed > max) speed = speed % max;
		}
		else {
			int max = 2 * (C - 1);
			if (speed > max) speed = speed % max;
		}


		for (int i = 0; i < speed; i++) {	// d�������� speed��ŭ ������
			int nx = x + dir[d][0], ny = y+dir[d][1];
			if (nx < 1 || ny < 1 || nx > R || ny > C) {	// ���� ���� ���¸�
				v[sharkIdx].changeDir(); //	�ڷ� ���Ƽ�
				d = v[sharkIdx].d, nx = x + dir[d][0], ny = y+dir[d][1];	// �ش� ������ �ٽ� �����
			}
			x = nx, y = ny;
		}
		v[sharkIdx].x = x, v[sharkIdx].y = y;
		//cout << sharkIdx << "����ְ� " << x << y << endl;
		if(arr[x][y] == 0) arr[x][y] = sharkIdx + 1;
		else {
			int size_1 = v[arr[x][y] - 1].size , size_2 = v[sharkIdx].size;
			
			if (size_1 > size_2) v[sharkIdx].die();	// ���� �ִ� ���� �� ũ�� �� ����
			else {	// ���� ���³��� ��ũ��
				v[arr[x][y] - 1].die();
				arr[x][y] = sharkIdx + 1;
			}
		}
	}
}

int main() {
	int ans = 0;
	cin >> R >> C >> M;
	for (int i = 1; i <= M; i++) {
		cin >> a >> b >> c >> d >> e;
		v.push_back(make_shark(a, b, c, d, e));
	}
	
	for (int i = 1; i <= C; i++) {
		for (int j = 0; j < M; j++) if (!v[j].is_dead) arr[v[j].x][v[j].y] = j + 1;
		// i ��°�� �� ����!
		for (int j = 1; j <= R; j++) {
			if (arr[j][i] != 0) {
				int idx = arr[j][i] -1;
				ans += v[idx].size, v[idx].die();
				arr[j][i] = 0;
				break;
			}
		}

		sharkMove();
		//printBoard(), system("pause");
	}

	cout << ans;
	return 0;
}