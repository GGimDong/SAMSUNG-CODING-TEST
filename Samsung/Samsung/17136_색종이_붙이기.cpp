#include <cstdio>
#include <fstream>
#include <iostream>
#define MAX_SIZE 10

using namespace std;

// ���������� �ϳ� ��
int total_min_paper=-1;

int board[10][10];
int paper_leftover[5] = { 0,0,0,0,0 };

// �̹� flow�� ���� �� paper�� ������ �˰��� �������� �־��ָ� �ɵ�
int calc_total_papers() {
	int result = 0;
	for (int i = 0; i < 5; i++) {
		result+=paper_leftover[i];
	}

	return result;
}

// �� ����� ���� �־��� üũ��
bool is_done() {
	for (int i = 0; i < MAX_SIZE; i++) 
		for (int j = 0; j < MAX_SIZE; j++) 
			if (board[i][j] == 1)
				return false;
	
	return true;
}

bool paper_possible(int x, int y, int size) {
	
	if (x + size-1 >= MAX_SIZE || y + size-1 >= MAX_SIZE)
		return false;

	for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++) 
			if (board[x+i][y+j] == 0)
				return false;
		
	return true;
}


void dfs(int x, int y) {
	// ����
	//if (x == 0)
	//	system("pause");

	if (total_min_paper != -1 && total_min_paper <= calc_total_papers())
		return;

	if (is_done()) {
		int new_result = calc_total_papers();
		if (total_min_paper == -1 || total_min_paper > new_result)
			total_min_paper = new_result;
		
		return;
	}

	//int pre_y = y;

	// ����
	//cout << "Start to find!" << endl;

	while (board[x][y] == 0) {
		
		// ����
		//cout << "Check point: " << x << ", " << y << endl;

		if (y != MAX_SIZE-1) {
			y++;
		}
		else {
			y = 0;
			x++;
		}
	}

	// ����
	//cout << "Work point: " << x << ", " << y << endl;


	// ���� x,y�� 1�� ������
	for (int i = 5; i > 0; i--) {
		// ���� I x I �����۸� ����, ���� �� �ִ���, �ִٸ� �ٵ� ���̱Ⱑ ��������
		if (paper_possible(x, y, i) && paper_leftover[i - 1] < 5) {
			// ���̱�
			for (int ii = 0; ii < i; ii++)
				for (int jj = 0; jj < i; jj++)
					board[x + ii][y + jj] = 0;

			paper_leftover[i - 1]+=1;

			// ����
			/*cout << "Attach paper: " << i << endl;
			cout << "# of papers: " << calc_total_papers() << endl;
			for (int ii = 0; ii < MAX_SIZE; ii++){
				for (int jj = 0; jj < MAX_SIZE; jj++)
					cout << board[ii][jj]<<" ";
				cout << endl;
			}*/

			dfs(x, y);

			// ����
			for (int ii = 0; ii < i; ii++)
				for (int jj = 0; jj < i; jj++)
					board[x + ii][y + jj] = 1;
			
			paper_leftover[i - 1] -= 1;
		
		}
		
	}



}


int main() {
	ifstream input;
	input.open("input.txt");
	
	for (int i = 0; i < MAX_SIZE; i++)
		for (int j = 0; j < MAX_SIZE; j++)
			input >> board[i][j];

	dfs(0, 0);
	printf("%d", total_min_paper);
	return 0;
}