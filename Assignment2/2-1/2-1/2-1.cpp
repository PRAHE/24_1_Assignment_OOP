#include <iostream>
#include <ctime>
using namespace std;

void maximum(int size, int* ptr);
void minimum(int size, int* ptr);

//메인함수
int main() {
	int size;

	//랜덤한 수 생성
	srand((unsigned)time(NULL));

	//배열크기입력
	cout << "Size of the array: ";
	cin >> size;

	//입력받은 크기에 따른 동적할당.
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

	//메모리 해제
	delete[] ptr;
	return 0;
}

//select maximum 
void maximum(int size, int* ptr) {
	int max = ptr[0]; //최댓값
	int* ptr_max = nullptr; //최댓값 주소

	//for반복문으로 탐색하면서 최댓값 찾기
	for (int i = 1; i < size; i++) {
		if (ptr[i] > max) {
			max = ptr[i];
			ptr_max = &ptr[i];
		}
	}
	//출력
	cout << max << "\t," << "Address: " << ptr_max << endl;
}

//select minimum
void  minimum(int size, int* ptr) {
	int min = ptr[0]; //최솟값
	int* ptr_min = 0; //최솟값 주소

	//for반복문으로 탐색하면서 최솟값 찾기
	for (int i = 1; i < size; i++) {
		if (ptr[i] < min) {
			min = ptr[i];
			ptr_min = &ptr[i];
		}
	}
	//출력
	cout << min << "\t," << "Address: " << ptr_min << endl;
}