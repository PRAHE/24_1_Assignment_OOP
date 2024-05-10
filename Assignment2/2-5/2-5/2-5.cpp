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

int had(int** mat, int n, int num, int pre) { //pre�� ���� �迭�� ũ��
	int i = 0;
	int j = 0; 
	int k = 0;

	if (n == 0) { //�Է¹��� n=0�� ��
		mat[0][0] = 1;
		return 0;
	}
	else if (pre * 2 > num) { //���� �迭�� ũ�Ⱑ num�� �Ѿ�� ����
		return 0;
	}
	else {
		for (i = 0; i < pre; i++) {
			for (j = 0; j < pre; j++) {
				mat[i][pre + j] = mat[i][j]; //1��и�
				mat[pre + i][j] = mat[i][j]; //3��и�
				mat[pre + i][pre + j] = mat[i][j] * -1; //4��и�
			}
		}
		return had(mat, n, num, pre*2);
	}
}