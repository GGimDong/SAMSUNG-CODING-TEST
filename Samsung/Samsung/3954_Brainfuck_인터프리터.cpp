#include <fstream>
#include <cstdlib>
#include <iostream>
#include <vector>

#define MAX_MEM 100000
#define MAX_CODE 100000
#define MAX_INPUT 4096

using namespace std;

int T, M, C, I;

unsigned char memory[MAX_MEM];
char code[MAX_CODE];
char input_data[MAX_INPUT];

int loop[MAX_CODE];

int mem_idx, code_idx, input_idx;
int left_num;
int right_num;

struct loop_code {
	int start_idx;	// loop 시작 idx
	int end_idx;	// loop 끝 idx
	int mem_value;	// loop가 돌 때의 memory 값
};

vector<loop_code> v;

void init() {
	left_num = 0;
	right_num = 0;
	code_idx = 0;
	input_idx = 0;
	mem_idx = 0;
	for (int i = 0; i < M; i++) { memory[i] = 0; loop[i] = 0; }

	return;
}

void loop_detection() {
	int num = 1;

	for (int i = 0; i < C; i++) {
		if (code[i] == '[') {
			loop[i] = num;
			num++;
		}
		else if (code[i] == ']') {
			loop[i] = num;
		}
	}

	for (int i = 0; i < C; i++) cout << loop[i] ;
	cout << endl;
	return;
}

void excute_code() {
	init();
	loop_detection();
	system("pause");

	for (int j = 0; j < C; j++) {
		/*지워*/ cout << code[j] << ": "<< (int)memory[mem_idx] << endl;
		switch (code[j]) {
			
		case '+': 
			memory[mem_idx]++;
			break;
		case '-':
			memory[mem_idx]--;
			break;
		case '<':
			mem_idx--;
			break;
		case '>':
			mem_idx++;
			break;
		case '[':
			/*if (memory[mem_idx] == 0) {
				left_num = 1;
				right_num = 0;
				while (left_num!=right_num) {
					j++; 
					if (code[j] == ']')
						right_num++;
					else if (code[j] == '[')
						left_num++;
				}
			}*/
			break;
		case ']':
			/*if (memory[mem_idx] != 0) {
				left_num = 0;
				right_num = 1;
				while (left_num != right_num) {
					j--;
					if (code[j] == ']')
						right_num++;
					else if (code[j] == '[')
						left_num++;
				}
			}*/
			break;
		case '.':
			//printf("%c", memory[mem_idx]);
			break;
		case ',':
			if (input_idx != I)
				memory[mem_idx] = input_data[++input_idx];
			else
				memory[mem_idx] = 255;
			break;
		}
	}

	printf("Terminates\n");
	return;
}

int main() {
	ifstream input;
	input.open("input/input.txt");

	
	input >> T;
	
	for (int i = 0; i < T; i++) {
		input >> M >> C >> I;
		for (int j = 0; j < C; j++)
			input >> code[j];
		for (int l = 0; l < I; l++)
			input >> input_data[l];

		excute_code();
		
	}

	return 0;
}