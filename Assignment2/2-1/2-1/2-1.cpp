#include <iostream>
#include <ctime>
using namespace std;

void maximum(int size, int* ptr);
void minimum(int size, int* ptr);

//�����Լ�
int main() {
	int size;

	//������ �� ����
	srand((unsigned)time(NULL));

	//�迭ũ���Է�
	cout << "Size of the array: ";
	cin >> size;

	//�Է¹��� ũ�⿡ ���� �����Ҵ�.
	int* ptr = new int[size]; 

	//allocate random number
	for (int i = 0; i < size; i++) {
		ptr[i] = rand() % 100;
		//to check overlapped
		for (int j = 0; j < i; j++) {
			if (ptr[i] == ptr[j])
				i--;
		}
	}
	//print random numbers
	cout << "Random numbers: ";
	for (int i = 0; i < size; i++) {
		cout << ptr[i] << ' ';
	}
	cout << endl;

	//print maximum value & its address
	cout << "Maximum value: ";
	maximum(size, ptr);

	//print minimum value & its address
	cout << "Minimum value: ";
	minimum(size, ptr);

	//�޸� ����
	delete[] ptr;
	return 0;
}

//select maximum 
void maximum(int size, int* ptr) {
	int max = ptr[0]; //�ִ�
	int* ptr_max = nullptr; //�ִ� �ּ�

	//for�ݺ������� Ž���ϸ鼭 �ִ� ã��
	for (int i = 1; i < size; i++) {
		if (ptr[i] > max) {
			max = ptr[i];
			ptr_max = &ptr[i];
		}
	}
	//���
	cout << max << "\t," << "Address: " << ptr_max << endl;
}

//select minimum
void  minimum(int size, int* ptr) {
	int min = ptr[0]; //�ּڰ�
	int* ptr_min = 0; //�ּڰ� �ּ�

	//for�ݺ������� Ž���ϸ鼭 �ּڰ� ã��
	for (int i = 1; i < size; i++) {
		if (ptr[i] < min) {
			min = ptr[i];
			ptr_min = &ptr[i];
		}
	}
	//���
	cout << min << "\t," << "Address: " << ptr_min << endl;
}