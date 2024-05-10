#include <iostream>
#include <cstring>
using namespace std;

void token(char* arr, char* sep, char** ptr);

int main() {
	char arr[100] = { 0, };
	char sep[10] = { 0, };
	char* ptr[20];

	cout << "Enter the string: ";
	cin.getline(arr, 100);

	cout << "Enter the delimiter: ";
	cin.getline(sep, 10);

	cout << endl;

	cout << "Separated tokens: " << endl;
	token(arr, sep, ptr);

	for (int i = 0; ptr[i] != nullptr; i++) {
		cout << ptr[i] << endl;
		delete[] ptr[i]; // 동적 할당된 메모리 해제
	}
}

void token(char* arr, char* sep, char** ptr) {
	int k = 0;
	int pp = 0;
	int length = 0;
	int i;

	while (arr[k] != '\0') {
		if (arr[k] == sep[0]) {
			int ch = 0;
			while (arr[k] == sep[ch] && sep[ch] != '\0') {
				ch++;
			}
			if (sep[ch] == '\0') {
				ptr[pp] = new char[length + 1];
				for (i = 0; i < length; i++) {
					ptr[pp][i] = arr[k - length + i]; // 구분자 이전 문자 넣기
				}
				ptr[pp][i] = '\0';
				pp++;
				length = 0;
			}
			k += ch - 1; // ch만큼 k를 이동
		}
		else {
			length++;
		}
		k++;
	}

	if (length > 0) { // 마지막 토큰 처리
		ptr[pp] = new char[length + 1];
		for (i = 0; i < length; i++) {
			ptr[pp][i] = arr[k - length + i]; // 마지막 토큰의 문자 넣기
		}
		ptr[pp][i] = '\0';
	}
}
