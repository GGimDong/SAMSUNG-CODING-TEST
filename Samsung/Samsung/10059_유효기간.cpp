#include <cstdio>

bool MMYY_Check(int a, int b, int c, int d) {
	if (a > 1)
		return false;
	else if (a == 1) {
		if (b <= 2)
			return true;
		else
			return false;
	}
	else if (a == 0)
		if (b == 0) return false;
		else return true;
}

bool YYMM_Check(int a, int b, int c, int d) {
	if (c > 1)
		return false;
	else if (c == 1) {
		if (d <= 2)
			return true;
		else
			return false;
	}
	else if (c == 0)
		if (d == 0) return false;
		else return true;
}

int main() {
	int T, input, ans;
	scanf("%d", &T);
	char arr[5];

	for (int test = 1; test <= T; test++) {
		scanf("%str", arr);
		int a = arr[0] - '0', b = arr[1] - '0', c = arr[2] - '0', d = arr[3] - '0';
		bool is_MMYY, is_YYMM;
		is_MMYY = MMYY_Check(a, b, c, d), is_YYMM = YYMM_Check(a, b, c, d);
		
		if(is_MMYY && is_YYMM)
			printf("#%d AMBIGUOUS\n", test);
		else if(!is_MMYY && is_YYMM)
			printf("#%d YYMM\n", test);
		else if(is_MMYY && !is_YYMM)
			printf("#%d MMYY\n", test);
		else
			printf("#%d NA\n", test);
	}

	return 0;
}