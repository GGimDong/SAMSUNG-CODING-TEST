#include <fstream>
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <vector>
#define MAX_N 100

using namespace std;

int board[MAX_N][MAX_N];
int N, L;
int total_road = 0;



int is_possible(vector<int> v) {
	int last_value = v.front();
	int bridge[MAX_N] = {0,};

	for (int i = 1; i < v.size(); i++) {
		if (last_value != v[i]) {
			
			// 차이가 2이상인 경우는 무조건 안 됨
			if ( abs(last_value - v[i]) > 1)
				return -1;

			/* 이전 값이 더 커서 아래로 내려오는 경우 */
			if (last_value > v[i]) {
				/* L 길이만큼 앞이 평평한지 체크하고 경사로 두기 */
				for (int j = 0; j < L; j++) {
					if (v[i] != v[i + j] || i+j >= N )
						return -1;
					bridge[i + j] = 1; // 이 값은 사실 앞에서 검사만 놓으면 되는데, 경사로가 겹치는 지는 한 쪽만 검사하면 되기 때문
				}
			}
			/* 이전 값이 더 작아서 위로 올라오는 경우 */
			else {
				/* L 길이만큼 뒤가 평평한지 체크하고 경사로 두기 */
				for (int j = 1; j <= L; j++) {
					if (i - j < 0 ) {
						/*지워*/ //cout << "Error: Wrong index" << endl;
						return -1;
					}
					if (bridge[i - j] == 1) {
						/*지워*/ //cout << "Error: Already bridge was built" << endl;
						return -1;

					}
					if (v[i-1] != v[i - j]) {
						/*지워*/ //cout << "Error: Not even" << endl;
						return -1;
					}
				}
			}

		}
		last_value = v[i];
	}

	return 1;
}

void check(int line_num) {
	vector<int> v_row, v_col;
	for (int i = 0; i < N; i++)
		v_row.push_back(board[line_num][i]);

	for (int i = 0; i < N; i++)
		v_col.push_back(board[i][line_num]);

	if (is_possible(v_row) == 1)
		total_road++;
	if(is_possible(v_col) == 1)
		total_road++;
	
	return;
}

int main() {
	ifstream input;
	input.open("input/input.txt");
	
	input >> N >> L;
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			input >> board[i][j];

	for (int i = 0; i < N; i++) {
		check(i);
	}

	cout << total_road;
	return 0;
}