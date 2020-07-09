#include <iostream>

using namespace std;

const int MAX = 14;
int board[MAX+1];


int N;
int ans = 0;

// 세로, 가로
bool is_pos(int ver, int hor) {
	for (int i = 1; i < ver; i++)
		if (board[i] == hor)
			return false;
	
	// TODO: Diagonal
	for (int i = 1; i < ver; i++)
		if (board[ver - i] == hor - i || board[ver - i] == hor + i)
			return false;

	return true;
}

void print_nums() {
	for (int i = 1; i <= N; i++)
		cout<< board[i] <<" ";
	cout << endl;
}

void doRecursion(int current) {
	if (current >= N)
		ans++;//print_nums();
	else {
		for (int i = 1; i <= N; i++)
			if (is_pos(current+1, i)) {
				board[current+1] = i;
				doRecursion(current + 1);
				board[current+1] = 0;
			}
	}
}

int main() {
	cin >> N;
		
	doRecursion(0);

	cout << ans;
	return 0;
}