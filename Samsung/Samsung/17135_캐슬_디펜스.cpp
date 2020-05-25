#include <fstream>
#define MAX_N 100
#define MAX_M 15

using namespace std;

int board[MAX_N][MAX_M];
int board_origin[MAX_N][MAX_M];
int N, M, D;
int point = 0;
int max_point = 0;

void print_board() {
	for (int i = 0; i <= N; i++) {
		for (int j = 0; j < M; j++)
			printf("%d ", board[i][j]);
		printf("\n");
	}
}

// 적이 있나 없나 체크
int is_clear() {
	for (int i = 0; i < N; i++)
		for (int j = 0; j < M; j++)
			if (board[i][j] == 1)
				return 0;
	return 1;
}

int num_archer() {
	int result = 0;
	for (int i = 0; i < M; i++)
		if (board[N][i] == 2)
			result++;
	return result;
}

void kill_monster() {
	for (int i = 0; i < N; i++)
		for (int j = 0; j < M; j++)
			if (board[i][j] == 3) {
				board[i][j] = 0;
				point++;
				/*지워*///printf("kill!\n");
			}
}

int positive(int x) {
	if (x < 0)
		x = -1*x;
	return x;
}

int board_for_distance[MAX_N][MAX_M];
int detection_complete = 0;

void init_board_for_distance() {
	for (int i = 0; i < N; i++)
		for (int j = 0; j < M; j++)
			board_for_distance[i][j] = 0;
}

void check_enemy() {
	for(int d=1;d<=D;d++)
		for (int j = 0; j < M; j++)
			for (int i = 0; i < N; i++)			
				if (board_for_distance[i][j] == d) {
					board[i][j] = 3;
					return;
				}
	return;
}

void is_attackable(int archer) {
	int is_enemy = 0;
	for (int i = 0; i < N; i++)
		for (int j = 0; j < M; j++) {
			int distance = 0;
			distance = positive(N - i) + positive(archer-j);
			if (distance <= D)
				if(board[i][j] == 1 || board[i][j] == 3) {
					board_for_distance[i][j] = distance;
					is_enemy = 1;
			}
		}

	/* 최단거리, 그리고 왼쪽놈을 check*/
	if(is_enemy==1)
		check_enemy();
	
	/* 지워 */
	//printf("\nChecking enemy! ************** \n");
	//print_board();


	init_board_for_distance();
	return;
}

void playgame() {
	point = 0;
	while (is_clear()==0) {
		
		/* TODO: 궁수들이 한대씩 때림*/
		for (int i = 0; i < M; i++)
			if (board[N][i] == 2) {
				/*공격가능한지 체크*/
				//printf("%d자리의 아처가 : 공격\n", i + 1);
				is_attackable(i);
			}
		
		kill_monster();



		/* TODO:  한칸씩 전진*/
		for (int i = N-1; i >=0 ; i--)
			for (int j = 0; j < M; j++)
				if (board[i][j] == 1) {
					board[i][j] = 0;
					if(i!=N-1)
						board[i+1][j] = 1;
				}
		/*지워*/
		//printf("After killing, go ahead!\n");
		//print_board();
		//printf("\n");
		/**/
	}

	/*지워*///printf("result: %d\n", point);
	if (point > max_point) {
		/*지워*///printf("new record!**************************\n");
		max_point = point;
	}
	return;
}

void dfs(int start_point) {
	if (num_archer() == 3) {
		for (int i = 0; i < N; i++)
			for (int j = 0; j < M; j++)
				board[i][j] = board_origin[i][j];
		
		/*지워*/
		//printf("input\n");
		//print_board();
		//printf("\n");
		/**/

		playgame();
		return;
	}
	for (int i = start_point; i < M; i++) {
		// 빈 곳을 찾으면, 궁수를 세움
		if (board[N][i] == 0) {
			board[N][i] = 2;
			dfs(i);
			board[N][i] = 0;
		}
	}
	return;
}


int main() {
	
	ifstream input;
	// input	1 2 3  4 5  6 
	// output	3 3 5 15 9 14
	input.open("input/Castle_defence/input4.txt");
	input >> N >> M >> D;

	for (int i = 0; i < N; i++)
		for (int j = 0; j < M; j++) {
			input >> board[i][j];
			board_origin[i][j] = board[i][j];
		}

	dfs(0);

	printf("%d", max_point);
	return 0;
}