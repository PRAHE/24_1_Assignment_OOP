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
	char* line[31]; //한 문장씩 읽어올 때, 포인터배열로 읽어옴
	char assign[50] = { '\0', };
	char* ptr[3];
	int row = 0;
	double num = 0;

	ifstream readFile; //파일을 읽기 위한 변수

	cin.getline(assign, 50, '\n');
	char command = assign[0];

	for (int i = 0; i < 31; i++) {
		line[i] = new char[31];
		for (int k = 0; k < 31; k++) { line[i][k] = '\0'; }
	}

	while (command != 'E') {
		switch (command) {
		case 'l': //load_student
			readFile.open("student.txt"); //오픈할 파일
			if (readFile.is_open()) { //파일 내용 저장
				row = 0;
				while (!readFile.eof()) { //파일이 끝날때 까지
					readFile.getline(line[row], 80); //한줄씩 저장
					row++; //포인터 배열 행 추가
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
		//재입력
		cin.getline(assign, 50, '\n');
		command = assign[0];
	}

	if (command == 'E') { //exit
		cout << "Exit the program" << endl;
	}

	//메모리 해제
	for (int i = 0; i < 3; i++) {
		delete[] ptr[i];
	}
	for (int i = 0; i < 31; i++) {
		delete[] line[i];
	}
	delete school;
	
	return 0;
}

//8,9번과 동일
void separate(char* assign, char** ptr) {
	int j;
	int i = 0; //assign배열 확인하기 위한 변수
	int k = 0; //ptr의 행체크
	int length = 1; //열 개수 동적할당을 위해 띄어쓰기 전까지 길이체크
	while (assign[i] != '\0') { //assign이 끝날 때까지
		if (assign[i + 1] == ',' || assign[i + 1] == '\0') { //다음칸이 빈칸이거나 assign 끝부분일 떄
			ptr[k] = new char[length + 1];
			for (int i = 0; i < length + 1; i++) { ptr[k][i] = '\0'; }
			int start = i - length + 1; //시작부분
			for (j = 0; j < length; j++) { // 내용추가
				ptr[k][j] = assign[start];
				start++;
			}
			ptr[k][j] = '\0'; //배열이 끝났다는 거 알려주기 위함.
			i++;//빈칸이 있으므로 빈칸부분 뛰어넘기
			length = 1; //길이 다시 체크하기 위해 초기화
			k++;
		}
		else {
			length++; //빈칸이 없는 경우 길이만 늘리면 됨.
		}
		i++; //다음 칸으로 넘어가기 위함.
	}
	while (i >= 0) { //assign배열 비우기
		assign[i] = '\0';
		i--;
	}
}

double convert(char* ptr[3], int i) {
	int len = 0;
	double number = 0;
	bool isunder = 0;

	while (ptr[i][len] != '\0') {
		if (ptr[i][len] == '.') { //소수점이 존재할 경우, 소수점 이전까지의 수 계산
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

	if (isunder == 1) { //소수점 아래 계산
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