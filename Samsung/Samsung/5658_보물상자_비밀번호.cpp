#include<iostream>
#include<vector>
#include <algorithm>

using namespace std;

void print_q(vector<char> q) { for (int i = 0; i < q.size(); i++) cout << q[i] << " ";    cout << endl; }
void print_q(vector<int> q) { for (int i = 0; i < q.size(); i++) cout << q[i] << " ";    cout << endl; }

void rotate_q(vector<char> &q) {
	char temp = q.back();
	q.insert(q.begin(), temp);
	q.pop_back();
}

int get_result(vector<char> q, int n) {
	int res = 0;
	int temp;
	for (int i = 0; i < n; i++) {
		if (q[i] == 'A') temp = 10;
		else if (q[i] == 'B') temp = 11;
		else if (q[i] == 'C') temp = 12;
		else if (q[i] == 'D') temp = 13;
		else if (q[i] == 'E') temp = 14;
		else if (q[i] == 'F') temp = 15;
		else temp = q[i] - '0';

		res += temp * pow(16, (n - i - 1));
	}
	return res;
}

int check_same_value(vector<int> order, int new_value) {
	for (int i = 0; i < order.size(); i++)
		if (order[i] == new_value) return -1;
	return 1;
}

int main(int argc, char** argv)
{
	int test_case;
	int T;
	cin >> T;

	for (test_case = 1; test_case <= T; ++test_case)
	{
		vector<char> q;
		int N, K;
		char temp;
		cin >> N >> K;

		for (int i = 0; i < N; i++) {
			cin >> temp;
			q.push_back(temp);
		}
		int side_n;
		side_n = q.size() / 4;
		vector<int> value;
		for (int i = 0; i < q.size(); i++) {
			int result = get_result(q, side_n);
			if (check_same_value(value, result) == 1) value.push_back(result);
			rotate_q(q);
		}

		sort(value.begin(), value.end());

		cout << "#" << test_case << " " << value[value.size() - K] << endl;
	}
	return 0;
}