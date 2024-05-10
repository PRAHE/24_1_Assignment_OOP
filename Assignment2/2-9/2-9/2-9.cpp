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
	char* getname() { return name; } //&name 반환
	char* getID() { return studentID; } //&studentID 반환
	double getScore() { return Score; } //Score 반환
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

//studnet_list배열에 정보 저장
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

//점수에 따른 내림차순 정렬
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

//grade 비율 확인
void School::calculateGrade(int cnt, int* grade) {
	double sum = cnt; //총 학생 수
	grade[0] = sum * 0.3;
	grade[1] = sum * 0.5;
}


int main() {
	School* school = new School(); //기본 생성자 호출
	char assign[50] = { '\0', };
	char* ptr[4]; //assign으로 받은 문자 띄어쓰기를 구분자로 ptr0~3까지의 배열에 넣기
	int grade[2] = { 0, };
	int mem = 0;
	double num;

	//명령 입력
	cin.getline(assign, 50, '\n');
	separate(assign, ptr);
	int dis = distinguish(ptr[0]);

	while (dis != 5) { //exit입력하기 전까지 반복
		switch (dis) {
		case 0: //new_student
			mem++;
			num = convert(ptr, 3); //score 변환
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
			school->sort(mem); //내림차순 정렬 필요. 순위별
			school->calculateGrade(mem, grade);
			for (int i = 0; i < grade[0]; i++) { //grade[0]내의 순위에 있는 학생만 출력
				school->print(i);
			}
			break;

		case 4: //print_B_grade
			cout << "=====B grade=====" << endl;
			school->sort(mem);
			school->calculateGrade(mem, grade);
			for (int i = grade[0]; i < grade[1]; i++) { //A등급인 사람 이후부터 grade[1]순위 내에 있는 학생 출력
				school->print(i);
			}
			break;
		}
		for (int i = 0; i < mem; i++) { //ptr 초기화
			ptr[i] = nullptr;
		}
		//재입력
		cin.getline(assign, 50, '\n');
		separate(assign, ptr);
		dis = distinguish(ptr[0]);
	}

	//exit입력
	if (dis == 5) {
		cout << "Exit the program" << endl; 
	}
	
	//메모리 반환
	for (int i = 0; i < 3; i++) {
		delete[] ptr[i];
	}
	delete school;

	return 0;
}

//command 구별
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

//8번과 동일
double convert(char* ptr[4], int i) {
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

void separate(char* assign, char** ptr) {
	int j;
	int i = 0; //assign배열 확인하기 위한 변수
	int k = 0; //ptr의 행체크
	int length = 1; //열 개수 동적할당을 위해 띄어쓰기 전까지 길이체크
	while (assign[i] != '\0') { //assign이 끝날 때까지
		if (assign[i + 1] == ' ' || assign[i + 1] == '\0') { //다음칸이 빈칸이거나 assign 끝부분일 떄
			ptr[k] = new char[length + 1]; //열 동적할당
			int start = i - length + 1; //시작부분
			for (j = 0; j < length; j++) { //동적할당한 열에 내용추가
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
