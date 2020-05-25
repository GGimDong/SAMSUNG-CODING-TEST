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
			
			// ���̰� 2�̻��� ���� ������ �� ��
			if ( abs(last_value - v[i]) > 1)
				return -1;

			/* ���� ���� �� Ŀ�� �Ʒ��� �������� ��� */
			if (last_value > v[i]) {
				/* L ���̸�ŭ ���� �������� üũ�ϰ� ���� �α� */
				for (int j = 0; j < L; j++) {
					if (v[i] != v[i + j] || i+j >= N )
						return -1;
					bridge[i + j] = 1; // �� ���� ��� �տ��� �˻縸 ������ �Ǵµ�, ���ΰ� ��ġ�� ���� �� �ʸ� �˻��ϸ� �Ǳ� ����
				}
			}
			/* ���� ���� �� �۾Ƽ� ���� �ö���� ��� */
			else {
				/* L ���̸�ŭ �ڰ� �������� üũ�ϰ� ���� �α� */
				for (int j = 1; j <= L; j++) {
					if (i - j < 0 ) {
						/*����*/ //cout << "Error: Wrong index" << endl;
						return -1;
					}
					if (bridge[i - j] == 1) {
						/*����*/ //cout << "Error: Already bridge was built" << endl;
						return -1;

					}
					if (v[i-1] != v[i - j]) {
						/*����*/ //cout << "Error: Not even" << endl;
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