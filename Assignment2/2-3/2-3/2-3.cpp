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

	//랜덤한 수 생성
	srand((unsigned)time(NULL));

	//이차원 배열 생성
	int** arr = new int* [rows];
	for (int i = 0; i < rows; i++) {
		arr[i] = new int[cols+1]; //sum값을 넣을 열 하나 추가
	}

	//0~100사이의 랜덤값 넣기
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			arr[i][j] = rand() % 101;
		}
	}

	//original 행렬 출력
	cout << "Orignial Matrix: " << endl;
	print(arr);

	//내림차순 함수로 이동
	for (int i = 0; i < 10; i++) {
		des(arr, i);
	}
	
	//내림차순 정렬한 행렬 출력
	cout << "Sort by Row (Descending Order): " << endl;
	print(arr);

	//합을 오름차순 정렬한 행렬 출력
	cout << "Sort by Sum (Ascending Order): " << endl;
	asc(arr);
	print(arr);

	//메모리 해제
	for (int i = 0; i < rows; i++) {
		delete[] arr[i];
	}
	delete[] arr;

	return 0;
}

//각 행의 내림차순
void des(int** arr, int rows) {
	for (int i = 0; i < 9; i++) {
		for (int j = i+1; j < 10; j++) {
			if (arr[rows][i] < arr[rows][j]) { 
				swap(arr[rows][i], arr[rows][j]);
			}
		}
	}
}

//합의 오름차순
void asc(int** arr) {
	int i;
	int j;
	int temp[10];

	for (i = 0; i < 9; i++) {
		for (j = i + 1; j < 10; j++) {
			if (arr[i][10] > arr[j][10]) {
				swap(arr[i][10], arr[j][10]);

				//sum의 오름차순에 따른 matrix정렬
				for (int p = 0; p < 10; p++) { 
					temp[p] = arr[i][p];
					arr[i][p] = arr[j][p];
					arr[j][p] = temp[p];
				}
			}
		}
	}
}

//주소 변경 함수
void swap(int& org, int& re) {
	int temp = org;
	org = re;
	re = temp;
	tri = 1;
}

//행렬 출력 함수
void print(int** arr) {
	for (int i = 0; i < rows; i++) {
		int sum = 0;
		for (int j = 0; j < cols; j++) {
			sum += arr[i][j];
			arr[i][10] = sum;
			cout << arr[i][j] << "\t";
		}
		//정렬한 이후 부터 합계 출력
		if (tri == 1) {
			cout << "| Sum: " << arr[i][10];
		}
		cout << endl;
	}
	cout << endl;
}