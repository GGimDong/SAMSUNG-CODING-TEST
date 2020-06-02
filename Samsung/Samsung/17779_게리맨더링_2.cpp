#include <fstream>
#define MAX_N 20
using namespace std;

int N;
int board[MAX_N][MAX_N];

int main() {

	ifstream input;
	input.open("input/input.txt");

	input >> N;
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			input >> board[i][j];


	return 0;
}