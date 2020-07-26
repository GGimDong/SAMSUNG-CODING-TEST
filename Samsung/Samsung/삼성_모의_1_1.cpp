#include <iostream>

using namespace std;

int T, result;
int order[10][2]; // 0이 움직일 값, 1이 그 값의 주인 말

int board[31] = {
  0,5,10,15,20,50, // 6
  30,35,40,45,100, // 5
  55,60,65,70,75, // 5
  80,85,90,95,500,1000, // 6
  275, 250, 300 ,150, 175,// 5
  150, 125, 350, 400 // 4
};

// 해당판에 움직일 거리를 넣으면 이제 값이나옴, 21이 도착지점
int move(int origin, int delta) {
	int next_pos = -1;
	if (origin == 5) {
		origin = 21;
		next_pos = origin + delta;
	}
	else if (origin == 10) {
		if (delta < 3) {
			origin = 26;
			next_pos = origin + delta;
		}
		else if (delta == 3) {
			next_pos = 24;
		}
		else if (delta > 3) {
			origin = 25;
			next_pos = origin + delta;
		}
	}
	else if (origin < 22) {
		next_pos = origin + delta;
		if (next_pos > 21) next_pos = 21;
	}
	else if (origin == 22) {
		next_pos = origin + delta;
		if (next_pos == 27) next_pos = 15;
	}
	else if (origin == 23) {
		if (delta < 4) {
			next_pos = origin + delta;
		}
		else {
			origin = 11;
			next_pos = origin + delta;
		}
	}
	else if (origin == 24) {
		if (delta < 3) origin = 28;
		else if (delta < 5) origin = 17;
		else origin = 16;
		next_pos = origin + delta;
	}
	else if (origin == 25) {
		if (delta == 1) next_pos = 26;
		else next_pos = 13 + delta;
	}
	else if (origin == 26) {
		origin = 14;
		next_pos = origin + delta;
	}
	else if (origin == 27) {
		if (delta == 1) next_pos = 28;
		else if (delta == 2) next_pos = 24;
		else if (delta == 3) next_pos = 29;
		else if (delta == 4) next_pos = 30;
		else next_pos = 20;
	}
	else if (origin == 28) {
		if (delta == 1) next_pos = 24;
		else if (delta == 2) next_pos = 29;
		else if (delta == 3) next_pos = 30;
		else if (delta == 4) next_pos = 20;
		else next_pos = 21;
	}
	else if (origin == 29) {
		if (delta == 1) next_pos = 30;
		else if (delta == 2) next_pos = 20;
		else if (delta == 3) next_pos = 21;
		else if (delta == 4) next_pos = 21;
		else next_pos = 21;
	}
	else if (origin == 30) {
		if (delta == 1) next_pos = 20;
		else if (delta == 2) next_pos = 21;
		else if (delta == 3) next_pos = 21;
		else if (delta == 4) next_pos = 21;
		else next_pos = 21;
	}
	if (next_pos == -1) cout << "ERROR!";
	return next_pos;
}

void calc() {
	int horse_pos[5] = { -1, 0, 0, 0, 0 };

	for (int i = 0; i < 10; i++) {
		int horse_idx = order[i][1];

		int horse_origin = horse_pos[horse_idx];
		if (horse_origin == 21) return;

		int delta_x = order[i][0];
		int next_pos = move(horse_origin, delta_x);

		for (int j = 1; j <= 4; j++) {
			if (horse_pos[j] == next_pos && next_pos != 21) {
				return;
			}
		}

		// 이제 같은 값을 가지지 않음!
		horse_pos[horse_idx] = next_pos;
	}

	int ans = 0;
	for (int i = 1; i <= 4; i++) {
		ans += board[horse_pos[i]];
	}
	if (ans > result) result = ans;

}

void doRecursion(int current) {
	if (current >= 10) {
		calc();
	}
	else {

		for (int i = 1; i <= 4; i++) {
			order[current][1] = i;
			doRecursion(current + 1);
		}
	}
}

int main() {
	cin >> T;
	for (int testcase = 1; testcase <= T; testcase++) {
		result = 0;

		for (int i = 0; i < 10; i++) {
			cin >> order[i][0];
		}

		doRecursion(0);

		cout << "#" << testcase << " " << result << endl;
	}
	return 0;
}