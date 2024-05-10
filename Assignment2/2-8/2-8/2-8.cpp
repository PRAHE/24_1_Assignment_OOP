#include <iostream>
using namespace std;
void separate(char* assign, char** ptr);
double convert(char* ptr[6], int i);

class Student
{
private:
	char* name;
	char* studentID;
	double assignmentScore;
	double examScore;
	double attendance;
	double finalScore;

public:
	Student() {} //�⺻������
	Student(char* name, char* id, double aScore, double eScore, double att);
	~Student();
	bool isNameCorrect(char* name);
	void calculateScores(double aScore, double eScore, double att);
	void changeScores(double aScore, double eScore, double att);
	void print();
};

Student::Student(char* name, char* id, double aScore, double eScore, double att) {
	this->name = name;
	studentID = id;
	assignmentScore = aScore;
	examScore = eScore;
	attendance = att;
}

Student::~Student() {
}

bool Student::isNameCorrect(char* name) {
	int i = 0;
	while (this->name[i] != '\0') {
		if (this->name[i] != name[i]) {
			return 0;
		}
		else
			i++;
	}
	return 1;
}

void Student::calculateScores(double aScore, double eScore, double att) {
	this->finalScore = aScore * 0.4 + eScore * 0.5 + att * 0.1;
}

void Student::changeScores(double aScore, double eScore, double att) {
	assignmentScore = aScore;
	examScore = eScore;
	attendance = att;
}

void Student::print() {
	cout << "Name : " << name << endl;
	cout << "Student ID : " << studentID << endl;
	cout << "Final Score : " << finalScore << endl;
	cout << "-----------" << endl;
}


int main() {
	Student* students[10]; //Ŭ���� �����͹迭
	char assign[100] = "";
	char* ptr[6]; //����� assign ���� �͵� 2�����迭�� ����
	int max = 0; //insert���� �л� ��

	//����Է¹ޱ�
	cin.getline(assign, 100);
	//������ �����ڷ� �и�
	separate(assign, ptr);
	//command�� ù����
	char com = ptr[0][0];

	//command�� exit�� �Է¹ޱ� ������ �ݺ�
	while (com != 'e') {
		bool iscorrect = 0;
		switch (com) {
		case 'i': //insert
			double num[3]; //char�� -> double��
			for (int i = 0; i < 3; i++) { 
				num[i] = convert(ptr, i + 3);
			}
			students[max] = new Student(ptr[1], ptr[2], num[0], num[1], num[2]);
			students[max]->calculateScores(num[0], num[1], num[2]);
			max++;
			break;

		case 'f': //find
			cout << "=====find=====" << endl;
			for (int i = 0; i < max; i++) { //insert���� �л� �� ��ŭ Ȯ��
				iscorrect = students[i]->isNameCorrect(ptr[1]); 
				if (iscorrect == 1) { //��ο� ���� ���
					students[i]->print();
					break;
				}
			}
			if (iscorrect == 0) { //��ο� ���� ���
				cout << "not found" << endl;
				cout << "-----------" << endl;
			}
			break;

		case 'c': //change
			int swap;
			double tmp[3]; //swap�ϱ� ���� �ӽ������
			for (swap = 0; swap < max; swap++) {
				iscorrect = students[swap]->isNameCorrect(ptr[1]);
				if (iscorrect == 1) {
					break;
				}
			}
			for (int j = 0; j < 3; j++) { //char�� -> double��
				tmp[j] = convert(ptr, j + 2);
			}
			students[swap]->changeScores(tmp[0], tmp[1], tmp[2]); //������ȯ
			students[swap]->calculateScores(tmp[0], tmp[1], tmp[2]);
			break;

		case 'p': //print
			cout << "======print=====" << endl;
			for (int i = 0; i < max; i++) {
				students[i]->print();
			}
			break;
		}
		//���Է�
		cin.getline(assign, 100);
		separate(assign, ptr);
		com = ptr[0][0];
	}

	if (com == 'e') { //exit
		cout << "Exit the program" << endl;
	}
	
	//�޸� ��ȯ
	for (int i = 0; i < max; i++) {
		delete students[i];
	}

	for (int i = 0; i < 6 ; i++) {
		delete[] ptr[i];
	}
	return 0;
}

//cin.getline���� �޾� char���� ����, double������ ��ȯ
double convert(char* ptr[6], int i) {
	int len = 0; //ptr�迭�� ����
	double number = 0;
	bool isunder = 0; //�Ҽ��� �Ʒ��ڸ� �ִ��� Ȯ��

	while(ptr[i][len] != '\0') { //ptr�迭�� ���� ������
		if (ptr[i][len] == '.') { //�Ҽ����� ������ ���, �Ҽ��� ���������� �� ���
			int tmp = 0;
			while (tmp < len) {
				int digit = 1;
				for (int k = 0; k < tmp; k++) { //�ڸ��� ��ȯ
					digit = digit * 10;
				}
				double converted = ptr[i][tmp] - '0'; //�ƽ�Ű�ڵ�����
				number = number + digit * converted;
				tmp++;
			}
			isunder = 1;
			len++;
			break;
		}
		len++;
	}

	if (isunder == 1) { //�Ҽ��� �Ʒ� ���
		int under = 0;
		while (ptr[i][len] != '\0') {
			double digit = 0.1;
			for (int k = 0; k < under; k++) {
				digit = digit * 0.1;
			}
			double converted = ptr[i][len] - '0';
			number = number + digit * converted;
			len++;
			under++;
		}
	}
	else if (isunder == 0) { //�Ҽ����� ���� ���
		int m = 0;
		while (ptr[i][m] != '\0') {
			int digit = 1;
			for (int k = 0; k < len - 1; k++) {
				digit = digit * 10;
			}
			double converted = ptr[i][m] - '0';
			number = number + digit * converted;
			m++;
			len--;
		}
	}
	return number;
}

void separate(char* assign, char** ptr) {
	int j;
	int i = 0; //assign�迭 Ȯ���ϱ� ���� ����
	int k = 0; //ptr�� ��üũ
	int length = 1; //�� ���� �����Ҵ��� ���� ���� ������ ����üũ
	while (assign[i] != '\0') { //assign�� ���� ������
		if (assign[i + 1] == ' ' || assign[i + 1] == '\0') { //����ĭ�� ��ĭ�̰ų� assign ���κ��� ��
			ptr[k] = new char[length + 1]; //�� �����Ҵ�
			int start = i - length + 1; //���ۺκ�
			for (j = 0; j < length; j++) { //�����Ҵ��� ���� �����߰�
				ptr[k][j] = assign[start];
				start++;
			}
			ptr[k][j] = '\0'; //�迭�� �����ٴ� �� �˷��ֱ� ����.
			i++;//��ĭ�� �����Ƿ� ��ĭ�κ� �پ�ѱ�
			length = 1; //���� �ٽ� üũ�ϱ� ���� �ʱ�ȭ
			k++;
		}
		else {
			length++; //��ĭ�� ���� ��� ���̸� �ø��� ��.
		}
		i++; //���� ĭ���� �Ѿ�� ����.
	}
	while (i >= 0) { //assign�ʱ�ȭ
		assign[i] = '\0';
		i--;
	}
}