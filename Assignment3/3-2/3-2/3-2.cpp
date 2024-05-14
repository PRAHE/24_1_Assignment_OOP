#include <iostream>
using namespace std;

class Matrix {
private:
	double data[4][4];

public:
	Matrix() {};
	~Matrix() {};

	Matrix operator+(Matrix& mtx) {
		Matrix tmp;
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				tmp.data[i][j] = this->data[i][j] + mtx.data[i][j];
			}
		}
		return tmp;
	}
	Matrix operator-(Matrix& mtx) {
		Matrix tmp;
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				tmp.data[i][j] = this->data[i][j] - mtx.data[i][j];
			}
		}
		return tmp;
	}
	Matrix operator*(Matrix& mtx) {
		Matrix tmp;
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				tmp.data[i][j] = this->data[i][j] * mtx.data[i][j];
			}
		}
		return tmp;
	}

	Matrix operator+(int Scalar) {
		Matrix tmp;
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				tmp.data[i][j] = this->data[i][j] + Scalar;
			}
		}
		return tmp;
	}
	Matrix operator-(int Scalar) {
		Matrix tmp;
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				tmp.data[i][j] = this->data[i][j] - Scalar;
			}
		}
		return tmp;
	}
	Matrix operator*(int Scalar) {
		Matrix tmp;
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				tmp.data[i][j] = this->data[i][j] * Scalar;
			}
		}
		return tmp;
	}
	Matrix operator/(int Scalar) {
		Matrix tmp;
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				tmp.data[i][j] = this->data[i][j] / Scalar;
			}
		}
		return tmp;
	}

	void setValue(double arr[4][4]);
	void display();
};

void Matrix::setValue(double arr[4][4]) {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			data[i][j] = arr[i][j];
		}
	}
}

void Matrix::display() {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			cout << data[i][j] << ' ';
		}
		cout << endl;
	}
	cout << endl;
}

int main() {
	Matrix mat1, mat2;

	double arr1[4][4]{
		{0,0,0,0},
		{1,1,1,1},
		{2,2,2,2},
		{3,3,3,3}
	};
	double arr2[4][4]{
		{0,1,2,3},
		{0,1,2,3},
		{0,1,2,3},
		{0,1,2,3},
	};

	mat1.setValue(arr1);
	mat2.setValue(arr2);

	cout << "Matrix 1: " << endl;
	mat1.display();
	cout << "Matrix 2: " << endl;
	mat2.display();

	Matrix mat3 = mat1 + mat2;
	mat3.display();
	
	mat3 = mat1 - mat2;
	mat3.display();
	
	mat3 = mat1 * mat2;
	mat3.display();

	
	mat3 = mat1 + 5;
	mat3.display();

	mat3 = mat1 - 5;
	mat3.display();
	
	mat3 = mat1 * 5;
	mat3.display();
	
	mat3 = mat1 / 5;
	mat3.display();

	return 0;
}