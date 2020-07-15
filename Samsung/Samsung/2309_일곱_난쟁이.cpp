#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int arr[9] = {0, };
bool visited[9] = {false, };
bool finished = false;

void print_num() {
	vector<int> v;

	for (int i = 0; i < 9; i++)
		if (visited[i])
			v.push_back(arr[i]);
	sort(v.begin(), v.end());
	for (int i = 0; i < 7; i++)
		cout << v[i] << endl;
	finished = true;
}

void doRecursion(int current) {
	if (current == 7) {

		int ans = 0;
		for (int i = 0; i < 9; i++)
			if (visited[i])
				ans += arr[i];

		if (ans == 100)
			print_num();
		
		return;
	}
	else {
		for (int i = current; i < 9; i++) {
			if (!finished && !visited[i]) {
				visited[i] = true;
				doRecursion(current + 1);
				visited[i] = false;
			}
		}

	}

}

int main() {
	for (int i = 0; i < 9; i++)
		cin >> arr[i];

	doRecursion(0);

	return 0;
}