#include<iostream>

using namespace std;

int N;
int num[7];
int result = 0;

bool calc(int i) {
	//cout << i << ": ";
	int origin_i = i;
	int sum = i;
	int temp_num;
	while (i!=0) {
		temp_num = i % 10;
		i = i * 0.1;
		sum += temp_num;
	}
	//cout << ": " << sum<<endl;
	if (sum == N) {
		result= origin_i;
		return true;
	}

	return false;
}

int main() {
	cin >> N;

	for (int i = 0; i < N; i++)
		if (calc(i)) break;

	cout << result;
	
	return 0;
}