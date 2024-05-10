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
		delete[] ptr[i]; // ���� �Ҵ�� �޸� ����
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
					ptr[pp][i] = arr[k - length + i]; // ������ ���� ���� �ֱ�
				}
				ptr[pp][i] = '\0';
				pp++;
				length = 0;
			}
			k += ch - 1; // ch��ŭ k�� �̵�
		}
		else {
			length++;
		}
		k++;
	}

	if (length > 0) { // ������ ��ū ó��
		ptr[pp] = new char[length + 1];
		for (i = 0; i < length; i++) {
			ptr[pp][i] = arr[k - length + i]; // ������ ��ū�� ���� �ֱ�
		}
		ptr[pp][i] = '\0';
	}
}
