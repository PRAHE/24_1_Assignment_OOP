#include <iostream>
#include <fstream>
using namespace std;

int distinguish(char* dis);
void separate(char* assign, char** ptr);
bool search(char* line, char* check, int size, int* column);

int main() {
	char assign[100] = { 0, }; //�Է¹ޱ����� temp
	char* ptr[4]; //command ���� ����
	char* line[500]; //�� ���徿 �о�� ��
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
			if (readFile.is_open()) { //���� ���� ����
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
				row[i] = 0; //�ʱ�ȭ ���ÿ�
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

//���� ���� ���� �ϳ��� �� �޾Ƽ� �迭�� ������ �� �� �� ������ �ŷ� �սô�
bool search(char* line, char* check, int size, int* column) {
	int j = 0;
	int cols = 0;
	while (line[j] != '\0') { //������ ���� ������
		int cnt = 0;
		int k = 0;
		while (cnt < size) {
			if (line[j] == check[k]) { //�ܾ�� ��
				cnt++; //5
				j++; k++; //4
				if (cnt == size) { j--; k--; break; }
			}
			else {
				while (1) { //���� �ܾ�� �̵�.
					if ((line[j] == ' ') || (line[j] == '\0')) { //�ѹ���
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
	int i = 0; //assign�迭 Ȯ���ϱ� ���� ����
	int k = 0; //ptr�� ��üũ
	int length = 1; //�� ���� �����Ҵ��� ���� ���� ������ ����üũ
	while (assign[i] != '\0') { //assign�� ���� ������
		if (assign[i + 1] == ' ' || assign[i + 1] == '\0') { //����ĭ�� ��ĭ�̰ų� assign ���κ��� ��
			ptr[k] = new char[length + 1]; //�� �����Ҵ�
			int start = i - length + 1; //���ۺκ�
			for (j = 0; j < length; j++) { //�����Ҵ��� ���� �����߰�
				ptr[k][j] = assign[start];
				start++;
			}
			ptr[k][j] = '\0'; //�迭�� �����ٴ� �� �˷��ֱ� ����.
			i++;//��ĭ�� �����Ƿ� ��ĭ�κ� �پ�ѱ�
			length = 1; //���� �ٽ� üũ�ϱ� ���� �ʱ�ȭ
			k++;
		}
		else {
			length++; //��ĭ�� ���� ��� ���̸� �ø��� ��.
		}
		i++; //���� ĭ���� �Ѿ�� ����.
	}

	while (i >= 0) { //assign�迭 ����
		assign[i] = '\0';
		i--;
	}
}

