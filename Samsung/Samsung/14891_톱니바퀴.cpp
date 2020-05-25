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
	//dir ´Â 1ÀÌ ½Ã°è, -1ÀÌ ¹Ý½Ã°è
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
	// idx»óÀ¸·Î 2 >> 6 ÀÇ ±ØÀÌ °°ÀºÁö¸¦ È®ÀÎ, ±ØÀÌ ´Ù¸£¸é ´Ù¸¥ ¹æÇâÀ¸·Î °¨!
	if (num != 0 && is_move[num - 1] == 0) {
		// ¿ÞÂÊ Åé´Ï¹ÙÄû¸¦ °Ë»ç
		if (gear[num][6] != gear[num - 1][2])
			gear_operate(num - 1, toggle(dir));
	}

	if (num != 3 && is_move[num + 1] == 0) {
		// ¿À¸¥ÂÊ Åé´Ï¹ÙÄû¸¦ °Ë»ç
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
		1¹ø Åé´Ï¹ÙÄûÀÇ 12½Ã¹æÇâÀÌ N±ØÀÌ¸é 0Á¡, S±ØÀÌ¸é 1Á¡
		2¹ø Åé´Ï¹ÙÄûÀÇ 12½Ã¹æÇâÀÌ N±ØÀÌ¸é 0Á¡, S±ØÀÌ¸é 2Á¡
		3¹ø Åé´Ï¹ÙÄûÀÇ 12½Ã¹æÇâÀÌ N±ØÀÌ¸é 0Á¡, S±ØÀÌ¸é 4Á¡
		4¹ø Åé´Ï¹ÙÄûÀÇ 12½Ã¹æÇâÀÌ N±ØÀÌ¸é 0Á¡, S±ØÀÌ¸é 8Á¡
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