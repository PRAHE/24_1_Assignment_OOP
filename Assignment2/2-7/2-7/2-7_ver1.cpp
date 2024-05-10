#include <iostream>
using namespace std;

int classify(char op);
char convert(char* formula, int iszero, int size);
int blank(char* form, int* priority);

int main() {
	char formula[50] = { 0, }; //�Է¹��� ��; ��ĭ ����
	char change[50] = { "\0", }; //�������´� ���ڷ� �ٲٰ� ���ڷ� ���� �迭
	int priority[20]; //������ �迭
	int site = 0; int k = 0;
	int size;
	int iszero = 0; //���ڰ� �ִ��� Ȯ��
	int pri; //������ ����

	cout << "Enter the formula: ";
	cin.getline(formula, 50); //�� �Է¹���

	size = blank(formula, priority); //�Է¹��� �迭���� ��ĭ �����
	for (int i = 0; i < size + 1; i++) { //formula�迭���� ������ �κ� int������ ��ȯ
		if (priority[i] == 5) { //��������
			iszero++;
		}
		else if (priority[i] != 5 && iszero > 0) { //
			change[k] = convert(formula, iszero, i); k++;
			iszero = 0; //�� ���޸� ����.
		}
		else { //���ڰ� �ƴ� �ٸ� ����
			change[k] = formula[i]; k++;
		}
	}
	size = blank(change, priority);

	//for (int i = 0; i < size; i++) {
	//	if (priority[i] == 1 && priority[i + 1] == 0) { //��ȣ���ۺκ�
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

char convert(char* formula, int iszero, int i) { //���ڷ� ��ȯ�ϴ� ���Ҹ�, Ž���� �����̳� �ٸ� ������
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

int blank(char* form,int* priority) { //�迭�� ��ĭ ����� && �켱�����迭 ����
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
		int pri = classify(form[k]); //�켱���� ����
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
	return 5; //����

}
