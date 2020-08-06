#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int r, c, k;
int arr[101][101];
int X = 3, Y = 3;
int temp_X, temp_Y;

struct p {
	int idx;
	int num = 0;
};

p make_p(int a) {
	p t;
	t.idx = a, t.num = 1;
	return t;
}

bool cmp(p a, p b) {
	if (a.num < b.num) return true;
	else if (a.num == b.num && a.idx < b.idx) return true;
	return false;
}

void R(int idx) {
	vector<p> v;
	/*µð¹ö±ë*/ //cout << "work line " << idx << ": ";
	for (int i = 1; i <= Y; i++) {
		int t = arr[idx][i];
		if (t == 0) continue;
		arr[idx][i] = 0;
		/*µð¹ö±ë*/ //cout << t << " ";
		bool is_new = true;
		for (int j = 0; j < v.size(); j++)
			if (v[j].idx == t) {
				is_new = false;
				v[j].num++;
				break;
			}
		
		if (is_new) v.push_back(make_p(t));
	}
	sort(v.begin(), v.end(), cmp);
	/*µð¹ö±ë*/// cout << endl; for (int i = 0; i < v.size(); i++) cout << v[i].idx << " " << v[i].num << " "; cout << endl;
	int size = 2 * v.size();
	if (size > 100) size = 100;
	temp_Y = max(temp_Y, size);
	for (int i = 0; i < size / 2; i++) {
		arr[idx][1+2*i] = v[i].idx, arr[idx][2+2*i] = v[i].num;
	}
}

void C(int idx) {
	vector<p> v;
	/*µð¹ö±ë*/ //cout << "work line " << idx << ": ";
	for (int i = 1; i <= Y; i++) {
		int t = arr[i][idx];
		if (t == 0) continue;
		arr[i][idx] = 0;
		/*µð¹ö±ë*/ //cout << t << " ";
		bool is_new = true;
		for (int j = 0; j < v.size(); j++)
			if (v[j].idx == t) {
				is_new = false;
				v[j].num++;
				break;
			}

		if (is_new) v.push_back(make_p(t));
	}
	sort(v.begin(), v.end(), cmp);
	/*µð¹ö±ë*/ //cout << endl; for (int i = 0; i < v.size(); i++) cout << v[i].idx << " " << v[i].num << " "; cout << endl;
	int size = 2 * v.size();
	if (size > 100) size = 100;
	temp_X = max(temp_X, size);
	for (int i = 0; i < size/2; i++) {
		arr[1 + 2 * i][idx] = v[i].idx, arr[2 + 2 * i][idx] = v[i].num;
	}
}

int main() {
	cin >> r >> c >> k;
	for (int i = 1; i <= 3; i++)
		for (int j = 1; j <= 3; j++)
			cin >> arr[i][j];

	int ans = -1;
	for (int time = 0; time <= 100; time++) {
		if (arr[r][c] == k) {
			ans = time;
			break;
		}
		temp_X = -1, temp_Y = -1;
		if (X >= Y) {	// R ¿¬»ê
			for (int i = 1; i <= X; i++) R(i);
			Y = temp_Y;
			/*µð¹ö±ë*/ //cout << "New Y: " << Y << endl;
			
		}
		else {			// C ¿¬»ê
			for (int i = 1; i <= Y; i++) C(i);
			X = temp_X;
			/*µð¹ö±ë*/ //cout << "New X: " << X << endl;
		}
		/*µð¹ö±ë*/
		/*for (int i = 1; i <= X; i++) {
			for (int j = 1; j <= Y; j++) {
				cout << arr[i][j] << " ";
			}cout << endl;
		}*/
		/*µð¹ö±ë*///system("pause");
	}
	
	cout << ans;
	return 0;
}