#include <iostream>
using namespace std;

int had(int** mat, int n, int num, int pre);

int main() {
	int n;
	int num = 1;
	cout << "Enter the value of n for Hadmard matrix (2^n x 2^n): ";
	cin >> n;

	for (int i = 0; i < n; i++) {
		num = num * 2;
	}
	int** mat = new int*[num];
	for (int i = 0; i < num; i++) {
		mat[i] = new int[num];
	}
	mat[0][0] = 1;

	cout << "Hadamard Matrix of size " << n << "x" << n << ": "<< endl;
	had(mat, n, num, 1);
	for (int i = 0; i < num; i++) {
		for (int j = 0; j < num; j++) {
			cout << mat[i][j] << "\t";
		}
		cout << endl;
	}
}

int had(int** mat, int n, int num, int pre) { //pre는 이전 배열의 크기
	int i = 0;
	int j = 0; 
	int k = 0;

	if (n == 0) { //입력받은 n=0일 때
		mat[0][0] = 1;
		return 0;
	}
	else if (pre * 2 > num) { //이전 배열의 크기가 num을 넘어가면 종료
		return 0;
	}
	else {
		for (i = 0; i < pre; i++) {
			for (j = 0; j < pre; j++) {
				mat[i][pre + j] = mat[i][j]; //1사분면
				mat[pre + i][j] = mat[i][j]; //3사분면
				mat[pre + i][pre + j] = mat[i][j] * -1; //4사분면
			}
		}
		return had(mat, n, num, pre*2);
	}
}