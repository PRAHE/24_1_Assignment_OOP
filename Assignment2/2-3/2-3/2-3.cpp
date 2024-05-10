#include <iostream>
#include <ctime>
using namespace std;

void swap(int& org, int& re);
void des(int** arr, int rows);
void print(int** arr);
void asc(int** arr);

int rows = 10;
int cols = 10;
bool tri = 0;

int main() {

	//������ �� ����
	srand((unsigned)time(NULL));

	//������ �迭 ����
	int** arr = new int* [rows];
	for (int i = 0; i < rows; i++) {
		arr[i] = new int[cols+1]; //sum���� ���� �� �ϳ� �߰�
	}

	//0~100������ ������ �ֱ�
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			arr[i][j] = rand() % 101;
		}
	}

	//original ��� ���
	cout << "Orignial Matrix: " << endl;
	print(arr);

	//�������� �Լ��� �̵�
	for (int i = 0; i < 10; i++) {
		des(arr, i);
	}
	
	//�������� ������ ��� ���
	cout << "Sort by Row (Descending Order): " << endl;
	print(arr);

	//���� �������� ������ ��� ���
	cout << "Sort by Sum (Ascending Order): " << endl;
	asc(arr);
	print(arr);

	//�޸� ����
	for (int i = 0; i < rows; i++) {
		delete[] arr[i];
	}
	delete[] arr;

	return 0;
}

//�� ���� ��������
void des(int** arr, int rows) {
	for (int i = 0; i < 9; i++) {
		for (int j = i+1; j < 10; j++) {
			if (arr[rows][i] < arr[rows][j]) { 
				swap(arr[rows][i], arr[rows][j]);
			}
		}
	}
}

//���� ��������
void asc(int** arr) {
	int i;
	int j;
	int temp[10];

	for (i = 0; i < 9; i++) {
		for (j = i + 1; j < 10; j++) {
			if (arr[i][10] > arr[j][10]) {
				swap(arr[i][10], arr[j][10]);

				//sum�� ���������� ���� matrix����
				for (int p = 0; p < 10; p++) { 
					temp[p] = arr[i][p];
					arr[i][p] = arr[j][p];
					arr[j][p] = temp[p];
				}
			}
		}
	}
}

//�ּ� ���� �Լ�
void swap(int& org, int& re) {
	int temp = org;
	org = re;
	re = temp;
	tri = 1;
}

//��� ��� �Լ�
void print(int** arr) {
	for (int i = 0; i < rows; i++) {
		int sum = 0;
		for (int j = 0; j < cols; j++) {
			sum += arr[i][j];
			arr[i][10] = sum;
			cout << arr[i][j] << "\t";
		}
		//������ ���� ���� �հ� ���
		if (tri == 1) {
			cout << "| Sum: " << arr[i][10];
		}
		cout << endl;
	}
	cout << endl;
}