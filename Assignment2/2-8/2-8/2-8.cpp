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
	Student() {} //기본생성자
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
	Student* students[10]; //클래스 포인터배열
	char assign[100] = "";
	char* ptr[6]; //띄어쓰기로 assign 나눈 것들 2차원배열에 저장
	int max = 0; //insert받은 학생 수

	//명령입력받기
	cin.getline(assign, 100);
	//공백을 구분자로 분리
	separate(assign, ptr);
	//command의 첫글자
	char com = ptr[0][0];

	//command로 exit을 입력받기 전까지 반복
	while (com != 'e') {
		bool iscorrect = 0;
		switch (com) {
		case 'i': //insert
			double num[3]; //char형 -> double형
			for (int i = 0; i < 3; i++) { 
				num[i] = convert(ptr, i + 3);
			}
			students[max] = new Student(ptr[1], ptr[2], num[0], num[1], num[2]);
			students[max]->calculateScores(num[0], num[1], num[2]);
			max++;
			break;

		case 'f': //find
			cout << "=====find=====" << endl;
			for (int i = 0; i < max; i++) { //insert받은 학생 수 만큼 확인
				iscorrect = students[i]->isNameCorrect(ptr[1]); 
				if (iscorrect == 1) { //명부에 있을 경우
					students[i]->print();
					break;
				}
			}
			if (iscorrect == 0) { //명부에 없을 경우
				cout << "not found" << endl;
				cout << "-----------" << endl;
			}
			break;

		case 'c': //change
			int swap;
			double tmp[3]; //swap하기 위한 임시저장소
			for (swap = 0; swap < max; swap++) {
				iscorrect = students[swap]->isNameCorrect(ptr[1]);
				if (iscorrect == 1) {
					break;
				}
			}
			for (int j = 0; j < 3; j++) { //char형 -> double형
				tmp[j] = convert(ptr, j + 2);
			}
			students[swap]->changeScores(tmp[0], tmp[1], tmp[2]); //점수변환
			students[swap]->calculateScores(tmp[0], tmp[1], tmp[2]);
			break;

		case 'p': //print
			cout << "======print=====" << endl;
			for (int i = 0; i < max; i++) {
				students[i]->print();
			}
			break;
		}
		//재입력
		cin.getline(assign, 100);
		separate(assign, ptr);
		com = ptr[0][0];
	}

	if (com == 'e') { //exit
		cout << "Exit the program" << endl;
	}
	
	//메모리 반환
	for (int i = 0; i < max; i++) {
		delete students[i];
	}

	for (int i = 0; i < 6 ; i++) {
		delete[] ptr[i];
	}
	return 0;
}

//cin.getline으로 받아 char형인 점수, double형으로 변환
double convert(char* ptr[6], int i) {
	int len = 0; //ptr배열의 길이
	double number = 0;
	bool isunder = 0; //소수점 아래자리 있는지 확인

	while(ptr[i][len] != '\0') { //ptr배열이 끝날 때까지
		if (ptr[i][len] == '.') { //소수점이 존재할 경우, 소수점 이전까지의 수 계산
			int tmp = 0;
			while (tmp < len) {
				int digit = 1;
				for (int k = 0; k < tmp; k++) { //자릿수 변환
					digit = digit * 10;
				}
				double converted = ptr[i][tmp] - '0'; //아스키코드참고
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
	else if (isunder == 0) { //소수점이 없을 경우
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
	while (i >= 0) { //assign초기화
		assign[i] = '\0';
		i--;
	}
}