#include <iostream>
using namespace std;

void separate(char* assign, char** ptr);
double convert(char* ptr[4], int i);
int distinguish(char* command);

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
	char* getname() { return name; } //&name ��ȯ
	char* getID() { return studentID; } //&studentID ��ȯ
	double getScore() { return Score; } //Score ��ȯ
};

class School
{
private:
	class Student* student_list[100];
	int size = 0;
public:
	School(){}
	~School(){}
	void setInfo(char** ptr, double score);
	void sort(int cnt);
	void print(int member);
	void calculateGrade(int cnt, int* grade);
};

Student::Student(char* name, char* id, double score) {
	this->name = name;
	studentID = id;
	Score = score;
}

//studnet_list�迭�� ���� ����
void School::setInfo(char**ptr, double score) {
	size++;
	student_list[size-1] = new Student(ptr[1], ptr[2], score);
}

void School::print(int member) {
	cout << "Name : " << student_list[member]->getname() << endl;
	cout << "StudentID : " << student_list[member]->getID() << endl;
	cout << "Name : " << student_list[member]->getScore() << endl;
	cout << "-------------" << endl;
}

//������ ���� �������� ����
void School::sort(int cnt) {
	double score_i;
	double score_j;
	for (int i = 0; i < cnt - 1; i++) {
		score_i = student_list[i]->getScore();
		for (int j = i + 1; j < cnt; j++) {
			score_j = student_list[j]->getScore();
			if (score_i < score_j) { //swap
				Student* tmp = student_list[i];
				student_list[i] = student_list[j];
				student_list[j] = tmp;
			}
		}
	}
}

//grade ���� Ȯ��
void School::calculateGrade(int cnt, int* grade) {
	double sum = cnt; //�� �л� ��
	grade[0] = sum * 0.3;
	grade[1] = sum * 0.5;
}


int main() {
	School* school = new School(); //�⺻ ������ ȣ��
	char assign[50] = { '\0', };
	char* ptr[4]; //assign���� ���� ���� ���⸦ �����ڷ� ptr0~3������ �迭�� �ֱ�
	int grade[2] = { 0, };
	int mem = 0;
	double num;

	//��� �Է�
	cin.getline(assign, 50, '\n');
	separate(assign, ptr);
	int dis = distinguish(ptr[0]);

	while (dis != 5) { //exit�Է��ϱ� ������ �ݺ�
		switch (dis) {
		case 0: //new_student
			mem++;
			num = convert(ptr, 3); //score ��ȯ
			school->setInfo(ptr, num);
			break;

		case 1: //sort_by_score
			school->sort(mem);
			break;

		case 2: //print_all
			cout << "=====print=====" << endl;
			for (int i = 0; i < mem; i++) {
				school->print(i);
			}
			break;

		case 3: //print_A_grade
			cout << "=====A grade=====" << endl;
			school->sort(mem); //�������� ���� �ʿ�. ������
			school->calculateGrade(mem, grade);
			for (int i = 0; i < grade[0]; i++) { //grade[0]���� ������ �ִ� �л��� ���
				school->print(i);
			}
			break;

		case 4: //print_B_grade
			cout << "=====B grade=====" << endl;
			school->sort(mem);
			school->calculateGrade(mem, grade);
			for (int i = grade[0]; i < grade[1]; i++) { //A����� ��� ���ĺ��� grade[1]���� ���� �ִ� �л� ���
				school->print(i);
			}
			break;
		}
		for (int i = 0; i < mem; i++) { //ptr �ʱ�ȭ
			ptr[i] = nullptr;
		}
		//���Է�
		cin.getline(assign, 50, '\n');
		separate(assign, ptr);
		dis = distinguish(ptr[0]);
	}

	//exit�Է�
	if (dis == 5) {
		cout << "Exit the program" << endl; 
	}
	
	//�޸� ��ȯ
	for (int i = 0; i < 3; i++) {
		delete[] ptr[i];
	}
	delete school;

	return 0;
}

//command ����
int distinguish(char* command) {
	if (command[0] == 'n') { //new_student
		return 0;
	}
	else if (command[0] == 's') { //sort_by_score
		return 1;
	}
	else if (command[6] == 'a') { //print_all
		return 2;
	}
	else if (command[6] == 'A') { //print_A_grade
		return 3;
	}
	else if (command[6] == 'B') { //print_B_grade
		return 4;
	}
	else if (command[0] == 'e') { //exit
		return 5;
	}
	return -1;
}

//8���� ����
double convert(char* ptr[4], int i) {
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

	while (i >= 0) { //assign�迭 ����
		assign[i] = '\0';
		i--;
	}
}
