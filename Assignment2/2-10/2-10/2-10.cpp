#include <iostream>
#include <fstream>
using namespace std;

double convert(char* ptr[3], int i);
void separate(char* assign, char** ptr);

class Student
{
private:
	char* name;
	char* studentID;
	double Score;
public:
	Student() {}
	Student(char* name, char* id, double score);
	~Student() {}
	char* getname() { return name; }
	char* getID() { return studentID; }
	double getScore() { return Score; }
};

class School
{
private:
	class Student* student_list[100];
	int size = 0;
public:
	School() {}
	~School() {}
	void setInfo(char** ptr, double score);
	void sort(int cnt);
	void print(int member);
};

Student::Student(char* name, char* id, double score) {
	this->name = name;
	studentID = id;
	Score = score;
}

void School::setInfo(char** ptr, double score) {
	size++;
	student_list[size - 1] = new Student(ptr[0], ptr[1], score);
}

void School::print(int member) {
	cout << "Name : " << student_list[member]->getname() << endl;
	cout << "StudentID : " << student_list[member]->getID() << endl;
	cout << "Score : " << student_list[member]->getScore() << endl;
	cout << "-------------" << endl;
}

void School::sort(int cnt) {
	double score_i;
	double score_j;
	for (int i = 0; i < cnt - 1; i++) {
		score_i = student_list[i]->getScore();
		for (int j = i + 1; j < cnt; j++) {
			score_j = student_list[j]->getScore();
			if (score_i < score_j) {
				Student* tmp = student_list[i];
				student_list[i] = student_list[j];
				student_list[j] = tmp;
			}
		}
	}
}

int main() {
	School* school = new School();
	int mem = 0;
	char* line[31]; //�� ���徿 �о�� ��, �����͹迭�� �о��
	char assign[50] = { '\0', };
	char* ptr[3];
	int row = 0;
	double num = 0;

	ifstream readFile; //������ �б� ���� ����

	cin.getline(assign, 50, '\n');
	char command = assign[0];

	for (int i = 0; i < 31; i++) {
		line[i] = new char[31];
		for (int k = 0; k < 31; k++) { line[i][k] = '\0'; }
	}

	while (command != 'E') {
		switch (command) {
		case 'l': //load_student
			readFile.open("student.txt"); //������ ����
			if (readFile.is_open()) { //���� ���� ����
				row = 0;
				while (!readFile.eof()) { //������ ������ ����
					readFile.getline(line[row], 80); //���پ� ����
					row++; //������ �迭 �� �߰�
				}
			}
			break;

		case 'p': //print
			cout << "=====print=====" << endl;

			for (int i = 0; i < row; i++) {
				separate(line[i], ptr);
				num = convert(ptr, 2);
				school->setInfo(ptr, num);
				school->print(i);
			}
			break;

		case 's': //sort_by_score
			school->sort(row);
			break;

		}
		//���Է�
		cin.getline(assign, 50, '\n');
		command = assign[0];
	}

	if (command == 'E') { //exit
		cout << "Exit the program" << endl;
	}

	//�޸� ����
	for (int i = 0; i < 3; i++) {
		delete[] ptr[i];
	}
	for (int i = 0; i < 31; i++) {
		delete[] line[i];
	}
	delete school;
	
	return 0;
}

//8,9���� ����
void separate(char* assign, char** ptr) {
	int j;
	int i = 0; //assign�迭 Ȯ���ϱ� ���� ����
	int k = 0; //ptr�� ��üũ
	int length = 1; //�� ���� �����Ҵ��� ���� ���� ������ ����üũ
	while (assign[i] != '\0') { //assign�� ���� ������
		if (assign[i + 1] == ',' || assign[i + 1] == '\0') { //����ĭ�� ��ĭ�̰ų� assign ���κ��� ��
			ptr[k] = new char[length + 1];
			for (int i = 0; i < length + 1; i++) { ptr[k][i] = '\0'; }
			int start = i - length + 1; //���ۺκ�
			for (j = 0; j < length; j++) { // �����߰�
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
	while (i >= 0) { //assign�迭 ����
		assign[i] = '\0';
		i--;
	}
}

double convert(char* ptr[3], int i) {
	int len = 0;
	double number = 0;
	bool isunder = 0;

	while (ptr[i][len] != '\0') {
		if (ptr[i][len] == '.') { //�Ҽ����� ������ ���, �Ҽ��� ���������� �� ���
			int tmp = 0;
			while (tmp < len) {
				int digit = 1;
				for (int k = 0; k < tmp; k++) {
					digit = digit * 10;
				}
				double converted = ptr[i][tmp] - '0';
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
	else if (isunder == 0) {
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