#include <iostream>
#include <cstring>
#include <vector>

using namespace std;

struct Sadari {
	int x, y, kind;
};

Sadari make_sadari(int a, int b, int c) {
	Sadari temp;
	temp.x = a, temp.y = b, temp.kind = c;
	return temp;
}

int N, M, H, a, b;
int t_board[35][15];
vector<Sadari> v;
bool is_finished = false;
int ans = -1;
int lineIdx;

int sadariResult(int x, int y) {
	while (x != H + 1) {
		x++;
		if (t_board[x][y] != 0) {	// 사다리가 있는 경우
			if (y - 1 > 0 && t_board[x][y] == t_board[x][y - 1]) y--;
			else y++;
		}
	}
	/*디버깅*/ //cout << y << endl;
	return y; 
}

void simulate() {

	/*디버깅*//*cout << endl;
	for (int i = 1; i <= H; i++) {
		for (int j = 1; j <= N; j++) {
			cout << t_board[i][j] << "\t";
		}cout << endl;
	}/*디버깅*/

	for (int i = 1; i <= N; i++) {
		/*디버깅*/ //cout << i << " to ";
		if (sadariResult(0, i) != i) return;
	}
	is_finished = true;
}

void doRecursion(int current, int target) {
	if (current >= target && !is_finished) simulate();
	else {
		for (int i = 1; i <= H; i++) {
			for (int j = 1; j < N; j++) {
				if (t_board[i][j] == 0 && t_board[i][j + 1] == 0 && !is_finished) {
					t_board[i][j] = lineIdx, t_board[i][j + 1] = lineIdx++;
					doRecursion(current + 1, target);
					t_board[i][j] = 0, t_board[i][j + 1] = 0;
					lineIdx--;
				}
			}
		}
	}
}

void init() {	// 초기화
	lineIdx = M + 1;
	memset(t_board, 0, sizeof(t_board));
	for (int i = 0; i < v.size(); i++) {
		Sadari s = v[i];
		t_board[s.x][s.y] = s.kind;
	}
}

int main() {
	cin >> N >> M >> H;
	for (int i = 1; i <= M; i++) {
		cin >> a >> b;
		v.push_back(make_sadari(a, b, i)), v.push_back(make_sadari(a, b+1, i));
	}

	for (int line_num = 0; line_num <= 3; line_num++) {
		init();
		doRecursion(0, line_num);

		if (is_finished) {
			ans = line_num;
			break;
		}
	}
	
	cout << ans;
	return 0;
}