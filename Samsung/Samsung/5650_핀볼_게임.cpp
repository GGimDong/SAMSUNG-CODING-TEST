#include <iostream>

using namespace std;

int dir[4][2] = { {-1,0}, {1,0}, {0,-1}, {0,1} };	// 0�� 1�� 2�� 3�� 
int T, N;
int arr[102][102];	// 1 ~ 100: idx, 101�� 0�� out ó��
int ans;

// �ش� ������ �ݴ������ �������
int oppositeDir(int d) {
	if (d == 0) return 1;
	else if (d == 1) return 0;
	else if (d == 2) return 3;
	else if (d == 3) return 2;
}

// ���� ��ġ�ΰ� Ȯ��
bool is_origin(int a, int b, int c, int d) {
	if (a == c && b == d) return true;
	else return false;
}

// ���� ���� �༮ ������ ���� ������ ������, �ٲ� ������ ����
int crashedDir(int arrValue, int currentDir) {
	// ��
	if (arrValue == 1) {
		if (currentDir == 0 || currentDir == 3) return oppositeDir(currentDir);
		else if (currentDir == 1) return 3;
		else if (currentDir == 2) return 0;
	}
	// �� ��Ī
	else if (arrValue == 2) {
		if (currentDir == 3 || currentDir == 1) return oppositeDir(currentDir);
		else if (currentDir == 0) return 3;
		else if (currentDir == 2) return 1;
	}
	// ��
	else if (arrValue == 3) {
		if (currentDir == 2 || currentDir == 1)  return oppositeDir(currentDir);
		else if (currentDir == 0) return 2;
		else if (currentDir == 3) return 1;
	}
	// �� ��Ī
	else if (arrValue == 4) {
		if (currentDir == 0 || currentDir == 2) return oppositeDir(currentDir);
		else if (currentDir == 1) return 2;
		else if (currentDir == 3) return 0;
	}
	// ��
	else if (arrValue == 5) return oppositeDir(currentDir);

	// ���� �ڴ� �͵��� �ƴ� ���, �׳� �Ϲ� ������ ���
	return currentDir;
}

void simulate(int start_x, int start_y, int d) {
	int point = 0;
	int x = start_x, y = start_y;

	while (1) {
		/*�����*/ //cout << x << "," << y << ": " << d << endl; system("pause");
		
		int value = arr[x][y];

		// ��ǥ������ ����
		if (value == -1) {
			/*�����*/ //cout << "Mission complete: " << point << endl;
			break;
		}
		// ��Ȧ�� ��쿣 �����ص帲
		else if (value >= 6) {
			bool flag = false;
			for (int i = 1; i <= N; i++) {
				for (int j = 1; j <= N; j++) {
					if (i == x && j == y) continue;
					if (arr[i][j] == value) {
						x = i, y = j;
						flag = true;
						break;
					}
				}
				if (flag) break;
			}
		}

		// ���� �������� ������ �ٲ�°�?
		int nextDir = crashedDir(value, d);

		// ������ ���� ��Ȳ, ���� ����
		if (nextDir != d) {
			/*�����*/ //cout << "Crashed! " << d  <<" to " << nextDir << endl;
			point++;
			d = nextDir;
		}

		// �ش� �������� �� ĭ ����!
		x += dir[d][0], y += dir[d][1];

		//���� �ڸ��� ���ƿ� ���
		if (is_origin(x, y, start_x, start_y)) {
			/*�����*/ //cout << "Origin position: " << point <<endl;
			break;
		}
	}
	if (point > ans) ans = point;
}

void printBoard() {
	for (int i = 0; i <= N + 1; i++){
		for (int j = 0; j <= N + 1; j++) {
			cout << arr[i][j] << " ";
		}cout << endl;
	}cout << endl;
}

int main() {
	cin >> T; /*���߿� T�� ����*/

	for (int test = 1; test <= T; test++) {
		ans = 0;
		cin >> N;
		for (int i = 0; i <= N + 1; i++)
			for (int j = 0; j <= N + 1; j++) {
				if (i == 0 || j == 0 || i == N + 1 || j == N + 1) arr[i][j] = 5;
				else cin >> arr[i][j];
			}

		//printBoard();

		for (int i = 1; i <= N; i++) {
			for (int j = 1; j <= N; j++) {
				if (arr[i][j] == 0) {
					for (int k = 0; k < 4; k++) simulate(i, j, k);
				}
			}
		}

		cout << "#" << test << " " << ans << endl;
	}
	return 0;
}