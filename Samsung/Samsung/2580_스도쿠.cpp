#include <iostream>
#include <vector>

using namespace std;

struct point {
	int x;
	int y;

	bool num[10];
};

bool ans = false;

int board[9][9];
vector<point> v;

bool check_board() {
	for (int i = 0; i < 9; i++) {
		bool num[10] = {false, };
		for (int j = 0; j < 9; j++) {
			num[board[i][j]] = true;
		}
		for (int j = 1; j < 10; j++) {
			if (!num[j]) return false;
		}
	}

	for (int i = 0; i < 9; i++) {
		bool ver_num[10] = { false, };
		for (int j = 0; j < 9; j++) {
			ver_num[board[j][i]] = true;
		}
		for (int j = 1; j < 10; j++) {
			if (!ver_num[j]) return false;
		}
	}

	for (int ii = 0; ii < 3; ii++)
		for (int jj = 0; jj < 3; jj++) {
			int start_x = 3 * ii;
			int start_y = 3 * jj;

			bool nine_num[10] = { false, };
			for (int i = 0; i < 3; i++)
				for (int j = 0; j < 3; j++)
					nine_num[board[start_x + i][start_y + j]]=true;
			
			for (int j = 1; j < 10; j++) {
				if (!nine_num[j]) return false;
			}
		}


	return true;
}

void print_board() {
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			cout << board[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
	ans = true;
}

bool is_pos(int v_idx, int comp_num) {

	// 이 부분이 주어진 board에서 어떤 수를 넣을 수 있냐는 코드 [중복]
	// 사실상 밑에 코드랑 거의 똑같았음... 비슷하긴한데... 합칠수있을진 모르겠.
	int temp_x = v[v_idx].x;
	int temp_y = v[v_idx].y;
	for (int i = 0; i < 9; i++) {
		if (board[temp_x][i] == comp_num && i != temp_y)
			return false;
	}
	
	for (int i = 0; i < 9; i++) {
		if (board[i][temp_y] == comp_num && i != temp_x)
			return false;
	}

	int start_x, start_y;
	int idx = v_idx;
	if (v[idx].x < 3 && v[idx].y < 3) {
		start_x = 0;
		start_y = 0;
	}
	else if (v[idx].x < 6 && v[idx].y < 3) {
		start_x = 3;
		start_y = 0;
	}
	else if (v[idx].x < 9 && v[idx].y < 3) {
		start_x = 6;
		start_y = 0;
	}
	else if (v[idx].x < 3 && v[idx].y < 6) {
		start_x = 0;
		start_y = 3;
	}
	else if (v[idx].x < 6 && v[idx].y < 6) {
		start_x = 3;
		start_y = 3;
	}
	else if (v[idx].x < 9 && v[idx].y < 6) {
		start_x = 6;
		start_y = 3;
	}
	else if (v[idx].x < 3 && v[idx].y < 9) {
		start_x = 0;
		start_y = 6;
	}
	else if (v[idx].x < 6 && v[idx].y < 9) {
		start_x = 3;
		start_y = 6;
	}
	else if (v[idx].x < 9 && v[idx].y < 9) {
		start_x = 6;
		start_y = 6;
	}

	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			if (board[start_x + i][start_y + j] == comp_num && i != temp_x && j != temp_y)
				return false;

	return true;
}


void doRecursion(int current) {
	if (ans) return;
	if (current >= v.size()) {
		if (check_board() && !ans)
			print_board();
	}
	else {
		for(int i=1;i<10;i++)
			if (!ans && v[current].num[i] && is_pos(current, i)) {
				board[v[current].x][v[current].y] = i;
				doRecursion(current + 1);
				board[v[current].x][v[current].y] = 0;
			}
	}
}

void checkPoint(int idx) {

	// 이 부분이 주어진 board에서 어떤 수를 넣을 수 있냐는 코드 [중복]
	for (int i = 1; i < 10; i++)
		v[idx].num[i] = true;

	for (int i = 0; i < 9; i++) {
		int temp = board[v[idx].x][i];
		v[idx].num[temp] = false;
	}

	for (int i = 0; i < 9; i++) {
		int temp = board[i][v[idx].y];
		v[idx].num[temp] = false;
	}

	int start_x, start_y;
	if (v[idx].x < 3 && v[idx].y < 3) {
		start_x = 0;
		start_y = 0;
	}
	else if (v[idx].x < 6 && v[idx].y < 3) {
		start_x = 3;
		start_y = 0;
	}
	else if (v[idx].x < 9 && v[idx].y < 3) {
		start_x = 6;
		start_y = 0;
	}
	else if (v[idx].x < 3 && v[idx].y < 6) {
		start_x = 0;
		start_y = 3;
	}
	else if (v[idx].x < 6 && v[idx].y < 6) {
		start_x = 3;
		start_y = 3;
	}
	else if (v[idx].x < 9 && v[idx].y < 6) {
		start_x = 6;
		start_y = 3;
	}
	else if (v[idx].x < 3 && v[idx].y < 9) {
		start_x = 0;
		start_y = 6;
	}
	else if (v[idx].x < 6 && v[idx].y < 9) {
		start_x = 3;
		start_y = 6;
	}
	else if (v[idx].x < 9 && v[idx].y < 9) {
		start_x = 6;
		start_y = 6;
	}

	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++) {
			int temp = board[start_x + i][start_y + j];
			v[idx].num[temp] = false;
		}

	// 각 빈자리들의 후보군 보여주는 코드
	//cout << v[idx].x << ", " << v[idx].y << " "<<start_x << start_y<<": ";
	//for (int i = 1; i < 10; i++)if (v[idx].num[i]) cout << i;
	//cout << endl;
}


int main() {
	int temp;

	for (int i = 0; i < 9; i++)
		for (int j = 0; j < 9; j++) {
			cin >> temp;

			if (temp == 0) {
				point p;
				p.x = i;
				p.y = j;
				v.push_back(p);
			}
			else
				board[i][j] = temp;
		}

	for (int i = 0; i < v.size(); i++)
		checkPoint(i);

	doRecursion(0);

	return 0;
}