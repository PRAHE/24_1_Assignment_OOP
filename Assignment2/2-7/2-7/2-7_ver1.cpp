#include <iostream>
using namespace std;

int classify(char op);
char convert(char* formula, int iszero, int size);
int blank(char* form, int* priority);

int main() {
	char formula[50] = { 0, }; //입력받은 식; 빈칸 없이
	char change[50] = { "\0", }; //숫자형태는 숫자로 바꾸고 문자로 넣은 배열
	int priority[20]; //구분자 배열
	int site = 0; int k = 0;
	int size;
	int iszero = 0; //숫자가 있는지 확인
	int pri; //구분자 구별

	cout << "Enter the formula: ";
	cin.getline(formula, 50); //식 입력받음

	size = blank(formula, priority); //입력받은 배열에서 빈칸 지우기
	for (int i = 0; i < size + 1; i++) { //formula배열에서 숫자인 부분 int형으로 변환
		if (priority[i] == 5) { //숫자형태
			iszero++;
		}
		else if (priority[i] != 5 && iszero > 0) { //
			change[k] = convert(formula, iszero, i); k++;
			iszero = 0; //값 전달만 됐음.
		}
		else { //숫자가 아닌 다른 문자
			change[k] = formula[i]; k++;
		}
	}
	size = blank(change, priority);

	//for (int i = 0; i < size; i++) {
	//	if (priority[i] == 1 && priority[i + 1] == 0) { //괄호시작부분
	//		while (priority[i] != 2) {
	//			if (priority[i] == 3) {
	//				calculate(formula, i, formula[i]);
	//			}
	//		}
	//	}
	//}
}

//void calculate(char* digit, int i, char op) {
//	int k = i;
//	switch (op) {
//	case '*':
//		while(digit[k]!=0)
//	}
//}

char convert(char* formula, int iszero, int i) { //숫자로 변환하는 역할만, 탐색은 메인이나 다른 곳에서
	int digit = 0;
	while (iszero > 0) {
		int tmp = 1;
		for (int i = 0; i < iszero - 1; i++) {
			tmp = tmp * 10;
		}
		int num = formula[i - iszero] - '0'; 
		digit = digit + tmp * num;
		iszero--;
	}
	char sending = digit + '0';
	return sending;
}

int blank(char* form,int* priority) { //배열의 빈칸 지우기 && 우선순위배열 정리
	int k = 0;
	int size = 0;
	while (form[k] != '\0') {
		if (form[k] == ' ') {
			int tmp = k;
			while (form[tmp] != '\0') {
				form[tmp] = form[tmp + 1];
				tmp++;
			}
		}
		int pri = classify(form[k]); //우선순위 정리
		priority[k] = pri; 
		k++;
		size++;
	}
	return size;
}


int classify(char op) {
	if (op == '(')
		return 1;
	if (op == ')')
		return 2;
	if (op == '*' || op == '/') 
		return 3;
	if (op == '+' || op == '-')
		return 4;
	return 5; //숫자

}
