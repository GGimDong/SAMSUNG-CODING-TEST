#include <fstream>
#include <cstdlib>
#include <cstdio>
#include <vector>
#include <iostream>

using namespace std;

vector<vector<int>> gear;
int K, num, dir;
int is_move[4];

void print_gear() {
	for (int i = 0; i < 4; i++) {
		cout << "Gear " << i + 1<<"("<<gear[i].size() <<"): ";
		for (int j = 0; j < 8; j++)
			cout << gear[i][j];
		cout << endl;
	}
	return;
}

void init_array(int arr[4]) {
	for (int i = 0; i < 4; i++) arr[i] = 0;
}

int toggle(int n) {
	n = -1 * n;
	return n;
}

void rotate_gear(int num, int dir) {
	//dir �� 1�� �ð�, -1�� �ݽð�
	if (dir == 1) {
		gear[num].insert(gear[num].begin(), gear[num].back());
		gear[num].pop_back();
	}
	else if (dir == -1) {
		gear[num].insert(gear[num].end(), gear[num].front());
		gear[num].erase(gear[num].begin());
	}
}


void gear_operate(int num, int dir) {
	is_move[num] = 1;
	// idx������ 2 >> 6 �� ���� �������� Ȯ��, ���� �ٸ��� �ٸ� �������� ��!
	if (num != 0 && is_move[num - 1] == 0) {
		// ���� ��Ϲ����� �˻�
		if (gear[num][6] != gear[num - 1][2])
			gear_operate(num - 1, toggle(dir));
	}

	if (num != 3 && is_move[num + 1] == 0) {
		// ������ ��Ϲ����� �˻�
		if (gear[num][2] != gear[num + 1][6])
			gear_operate(num + 1, toggle(dir));
	}

	rotate_gear(num, dir);	
}

int main() {
	ifstream input;
	input.open("input/input.txt");

	char temp;

	for (int i = 0; i < 4; i++){
		vector<int> temp_gear;
		for (int j = 0; j < 8; j++) {
			input >> temp;
			temp_gear.push_back(temp-'0');
		}
		gear.push_back(temp_gear);
	}

	input >> K;
	for (int i = 0; i < K; i++) {
		init_array(is_move);
		input >> num >> dir;
		gear_operate(num-1, dir);
	}

	int point = 0;
	/*
		1�� ��Ϲ����� 12�ù����� N���̸� 0��, S���̸� 1��
		2�� ��Ϲ����� 12�ù����� N���̸� 0��, S���̸� 2��
		3�� ��Ϲ����� 12�ù����� N���̸� 0��, S���̸� 4��
		4�� ��Ϲ����� 12�ù����� N���̸� 0��, S���̸� 8��
	*/

	if (gear[0][0] == 1)
		point += 1;
	if (gear[1][0] == 1)
		point += 2;
	if (gear[2][0] == 1)
		point += 4;
	if (gear[3][0] == 1)
		point += 8;
	cout << point;
	return 0;
}