/*
	항상 하는 말이지만, 코드를 잘 보고 제발 실수하지 말자
*/
#include <iostream>

using namespace std;

//종말의 숫자란 어떤 수에 6이 적어도 3개이상 연속으로 들어가는 수
bool is_666(int n) {

	int count = 0;
	bool start_six = false;

	while (n != 0) {
		
		int temp = n % 10;
		if (temp == 6 && !start_six) {
			start_six = true;
			count++;
		}
		else if (temp != 6 && start_six) {
			count = 0;
			start_six = false;
		}
		else if (temp == 6 && start_six) {
			count++;
		}

		n = n * 0.1;
		if (count == 3)
			return true;
	}

	return false;
}

int main() {
	
	int N, ans;
	int count = 0;

	cin >> N;
	
	
	for (int i = 666; i < 2147483647; i++) {
		if (is_666(i))
			count++;
		if (count == N) {
			ans = i;
			break;
		}
	}

	cout << ans;
	return 0;
}