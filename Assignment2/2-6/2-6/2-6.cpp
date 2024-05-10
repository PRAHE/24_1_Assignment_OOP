#include <iostream>
#include <fstream>
using namespace std;

int distinguish(char* dis);
void separate(char* assign, char** ptr);
bool search(char* line, char* check, int size, int* column);

int main() {
	char assign[100] = { 0, }; //입력받기위한 temp
	char* ptr[4]; //command 문장 정리
	char* line[500]; //한 문장씩 읽어올 때
	int k; int found;
	int size, size_2;
	int dis;
	int column[10] = { 0, };
	int row[10] = { 0, };
	int rows = 0;

	ifstream readFile;
	ofstream writeFile;

	cin.getline(assign, 100, '\n');
	separate(assign, ptr);
	dis = distinguish(ptr[0]);

	for (int i = 0; i < 500; i++) {
		line[i] = new char[200];
		for (int k = 0; k < 200; k++) { line[i][k] = '0'; }

	}

	while (dis != 6) {
		switch (dis) {
		case 0: //open
			readFile.open(ptr[1]);
			if (readFile.is_open()) { //파일 내용 저장
				int i = 0;
				while (!readFile.eof()) {
					readFile.getline(line[i], 200);
					i++;
				}
			}
			break;

		case 1: //search
			k = 0;
			size = 1;
			found = 0;
			while (ptr[1][size] != '\0') {
				size++;
			}
			while (line[k][0] != '0') {
				if (search(line[k], ptr[1], size, column)) {
					row[rows] = k;
					found++;
					rows++;
				}
				k++;
			}
			cout << "==='" << ptr[1] << "'search(" << found << ")===" << endl;
			for (int i = 0; i < found; i++) {
				cout << "(" << row[i] << "," << column[i] << ")" << endl;
				row[i] = 0; //초기화 동시에
				column[i] = 0;
			}
			cout << "---------------" << endl;
			break;

		case 2: //save

			break;
		//case 3: //change
		//	k = 0;
		//	size = 1;
		//	size_2 = 1;
		//	found = 0;
		//	while (ptr[1][size] != '\0') {
		//		size++;
		//	}
		//	while (ptr[2][size_2] != '\0') {
		//		size_2++;
		//	}

		//	while (line[k][0] != '0') {
		//		if (search(line[k], ptr[1], size, column)) {
		//			row[rows] = k;
		//			found++;
		//			rows++;
		//			cout << found << " " << endl;
		//		}
		//		k++;
		//		if (line[k][0] == '0') { cout << "success" << endl; }
		//	}//case2 //search

		//	if (size_2 > size) {
		//		int sub = size_2 - size;
		//		for (int i = 0; i < sub; i++) {
		//			while(line[k][])
		//		}
		//	}
		//	for (int j = 0; j < found; j++) {
		//		for (int i = column[j]; i < size+column[j]; i++) {
		//			line[row[j]][i] = ptr[2][i];
		//		}

		//	}
		//	break;
		case 4: //insert
		case 5: //delete
			break;
		}
		assign[0] = '\0';
		cin.getline(assign, 100, '\n');
		separate(assign, ptr);
		dis = distinguish(ptr[0]);

	}
	readFile.close();
}

//파일 내용 글자 하나씩 다 받아서 배열에 저장한 후 싹 다 돌리는 거로 합시다
bool search(char* line, char* check, int size, int* column) {
	int j = 0;
	int cols = 0;
	while (line[j] != '\0') { //문장이 끝날 때까지
		int cnt = 0;
		int k = 0;
		while (cnt < size) {
			if (line[j] == check[k]) { //단어끼리 비교
				cnt++; //5
				j++; k++; //4
				if (cnt == size) { j--; k--; break; }
			}
			else {
				while (1) { //다음 단어로 이동.
					if ((line[j] == ' ') || (line[j] == '\0')) { //한문장
						j++;
						k = 0;
						break;
					}
					j++; 
					k = 0;
				}
				break;
			}
		}

		if (cnt == size) { //
			if ((line[j + 1] == ' ') || (line[j + 1] == '\0')) {
				column[cols] = j - size+1;
				cols++;
				return true;
			}
		}
	}
}

int distinguish(char* dis) {
	if (dis[0] == 'o') { //open
		return 0;
	}
	else if (dis[0] == 's') {
		if (dis[1] == 'e') { //search
			return 1;
		}
		else if (dis[1] == 'a') { //save
			return 2;
		}
	}
	else if (dis[0] == 'c') { //change
		return 3;
	}
	else if (dis[0] == 'i') { //insert
		return 4;
	}
	else if (dis[0] == 'd') { //delete
		return 5;
	}
	else if (dis[0] == 'e') { //exit
		return 6;
	}
}

void separate(char* assign, char** ptr) {
	int j;
	int i = 0; //assign배열 확인하기 위한 변수
	int k = 0; //ptr의 행체크
	int length = 1; //열 개수 동적할당을 위해 띄어쓰기 전까지 길이체크
	while (assign[i] != '\0') { //assign이 끝날 때까지
		if (assign[i + 1] == ' ' || assign[i + 1] == '\0') { //다음칸이 빈칸이거나 assign 끝부분일 떄
			ptr[k] = new char[length + 1]; //열 동적할당
			int start = i - length + 1; //시작부분
			for (j = 0; j < length; j++) { //동적할당한 열에 내용추가
				ptr[k][j] = assign[start];
				start++;
			}
			ptr[k][j] = '\0'; //배열이 끝났다는 거 알려주기 위함.
			i++;//빈칸이 있으므로 빈칸부분 뛰어넘기
			length = 1; //길이 다시 체크하기 위해 초기화
			k++;
		}
		else {
			length++; //빈칸이 없는 경우 길이만 늘리면 됨.
		}
		i++; //다음 칸으로 넘어가기 위함.
	}

	while (i >= 0) { //assign배열 비우기
		assign[i] = '\0';
		i--;
	}
}

