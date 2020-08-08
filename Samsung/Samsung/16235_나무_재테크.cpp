#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>

using namespace std;

vector<int> map[11][11];
int N, M, K, a, b, c;
int A[11][11], yangBoon[11][11], absoredYangBoon[11][11];	// 양분주기
int dir[8][2] = { {-1,-1},{-1,0},{-1,1},{0,-1},{0,1},{1,-1},{1,0},{1,1} };

int main() {
	int result = 0;
	cin >> N >> M >> K;
	for (int i = 1; i <= N; i++) 
		for (int j = 1; j <= N; j++) {
			cin >> A[i][j];
			yangBoon[i][j] = 5;
		}

	for (int i = 0; i < M; i++) {
		cin >> a >> b >> c;
		map[a][b].push_back(c);
	}
	result += M;

	// 4계절 start
	while(K>0){
		for (int i = 1; i <= N; i++) {
			for (int j = 1; j <= N; j++) {
				if (map[i][j].empty()) continue;
				sort(map[i][j].begin(), map[i][j].end());
				memset(absoredYangBoon, 0, sizeof(absoredYangBoon));

				// 나무의 어린 순서대로 양분 먹기
				for (int k = 0; k < map[i][j].size(); k++) {
					// 자기 나이 만큼 양분 먹고 1증가
					if (yangBoon[i][j] >= map[i][j][k]) {
						yangBoon[i][j] -= map[i][j][k];
						map[i][j][k]++;
					}// 못 먹으면 죽고 양분으로 감
					else {
						absoredYangBoon[i][j]+=(map[i][j][k] / 2);
						map[i][j].erase(map[i][j].begin()+k);
						k--;
						result--;
					}
				}
				// 여름 양분 추가는 미리 해주기
				yangBoon[i][j] += absoredYangBoon[i][j];
			}
		}

		// 가을 번식
		for (int i = 1; i <= N; i++) 
			for (int j = 1; j <= N; j++) {
				// 겨울 양분 미리 주기
				yangBoon[i][j] += A[i][j];
				if (map[i][j].empty()) continue;
				for (int k = 0; k < map[i][j].size(); k++) {
					if (map[i][j][k] % 5 != 0) continue;
					for (int idx = 0; idx < 8; idx++) {
						int nx = i + dir[idx][0], ny = j + dir[idx][1];
						if (nx <1 || ny < 1 || nx > N || ny >N) continue;
						map[nx][ny].push_back(1);
						result++;
					}
				}
			}

		K--;
	}
	cout << result;
	return 0;
}