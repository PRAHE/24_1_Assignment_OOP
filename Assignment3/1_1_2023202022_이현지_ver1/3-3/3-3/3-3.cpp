#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct Member {
	char id[20] = { '\0,' };
	char password[20] = { '\0,' };
};

//password 암호화
void Caesar(char* tmp) {
	for (int i = 0; i < 20; i++) {
		if (tmp[i] < 'x' && tmp[i] >= 'a') {
			tmp[i] = tmp[i] + 3; //아스키코드 기반 +3
		}
		else if (tmp[i] >= 'x' && tmp[i] <= 'z') {
			tmp[i] -= 23; //아스키코드 기반 -23
		}
	}
}

//password부호화
void Decipher(char* tmp) {
	for (int i = 0; i < 20; i++) {
		if (tmp[i] <= 'z' && tmp[i] > 'c') {
			tmp[i] = tmp[i] - 3; //원래대로 돌려놓기
		}
		else if (tmp[i] >= 'a' && tmp[i] <= 'c') {
			tmp[i] += 23; //이하 동문
		}
	}
}

int main() {
	Member member;

	char tmp[20];
	char id[20];
	char password[20];
	int choice;
	ifstream readFile, RtmpFile;
	ofstream writeFile, tmpFile;

	std::cout << "===================" << endl;
	std::cout << "Menu." << endl;
	std::cout << "1. Login" << endl;
	std::cout << "2. Register" << endl;
	std::cout << "3. Withdrawal" << endl;
	std::cout << "4. Exit" << endl;
	std::cout << " : ";

	std::cin >> choice;
	std::cout << "---------------------" << endl;
	std::cin.ignore(); //buffer비우기

	//로그인 이력 확인
	bool logged = 0;

	while (1) {
		std::cout << "===================" << endl;

		bool isID = 0;
		bool isPassword = 0;
		bool alpha = 0;
		bool s_character = 0;
		char special[10] = { '!','@','#','$','%','^','&','*','(',')' }; //특수문자 정렬

		switch (choice) {
		case 1:
			readFile.open("membership.txt");

			std::cout << "User id: ";
			std::cin.getline(id, 20);
			std::cout << "password: ";
			std::cin.getline(password, 20);
			
			if (readFile.is_open()) { //membership파일
				while (!readFile.eof()) {
					readFile.getline(tmp, 20);
					if (!strcmp(tmp, id)) { //동일한 id 있을 떄
						while (!readFile.eof()) {
							readFile.getline(tmp, 20);
							Decipher(tmp); //부호화
							if (!strcmp(tmp, password)) { //동일한 password 있을 때
								strcpy(member.id, id); //struct변수에 저장
								strcpy(member.password, password);
								std::cout << "Login successful." << endl;
								logged = 1;
								break;
							}
							else break;
						}
					}
					else { //로그인 실패
						std::cout << "Login failed. Invalid User id or password." << endl;
						break;
					}
				}
			}
			//파일 닫기
			readFile.close();
			break;

		case 2:
			readFile.open("membership.txt");

			std::cout << "User id: ";
			std::cin.getline(id, 20);
			std::cout << "password: ";
			std::cin.getline(password, 20);
			
			strcpy(tmp, password);

			//패스워드 최소 규정 확인
			for (int i = 0; i < 20; i++) {
				if (tmp[i] >= 'a' && tmp[i] <= 'z') {
					alpha = 1; //알파벳유무
				}

				for (int j = 0; j < 10; j++) {
					if (tmp[i] == special[j]) {
						s_character = 1; //특수문자 유무
					}
				}
			}
			if (sizeof(tmp) < 10) { //패스워드 길이확인
				std::cout << "Registration failed. " << endl;
				break;
			}

			if (readFile.is_open()) {
				while (!readFile.eof()) {
					readFile.getline(tmp, 50);
					if (!strcmp(tmp, id)) {//동일한 id찾았을 시.
						isID = 1; break;
						while (!readFile.eof()) {
							readFile.getline(tmp, 50);
							Decipher(tmp); //부호화
							if (!strcmp(tmp, password)) { //동일한 패스워드 찾았을 시.
								isPassword = 1;
								break;
							}
						}
						break;
					}
					else {
						readFile.close();
						writeFile.open("membership.txt", ios::app); //app붙이면 파일의 내용에 덧붙여 작성 가능.
						strcpy(member.id, id);
						Caesar(password);
						strcpy(member.password, password);
						writeFile << id << endl;
						writeFile << password << endl;
						writeFile.close();
					}
				}
				//register실패
				cout << "Sorry, it's already exist." << endl;
			}
			break;

		case 3:
			readFile.open("membership.txt");
			tmpFile.open("tmp.txt");

			//로그인되어 있을 경우.
			if (logged == 1) {
				std::cout << "Logged in user : (" << member.id << ")" << endl;
				if (readFile.is_open()) {
					while (!readFile.eof()) {
						readFile.getline(tmp, 50);
						if (!strcmp(tmp, member.id) || !strcmp(tmp, member.password)) {}
						else {
							tmpFile << tmp << endl; //로그인되어있는 회원정보 빼고 tmp에 저장.
						}
					}tmpFile.close();

					readFile.close();
					writeFile.open("membership.txt");
					RtmpFile.open("tmp.txt");
					if (RtmpFile.is_open()) {
						while (!RtmpFile.eof()) {
							RtmpFile.getline(tmp, 50);
							writeFile << tmp << endl; //다시 membership파일에 저장.
						}
					}
				}
				if (readFile.is_open()) {
					while (!readFile.eof()) {
						readFile.getline(tmp, 50);
						if (!strcmp(tmp, member.id)) {

							while (!readFile.eof()) {
								readFile.getline(tmp, 50);
								if (!strcmp(tmp, password)) {
									break;
								}
							}
							break;
						}
						else {
							readFile.close();
							writeFile.open("membership.txt", ios::app);
							strcpy(member.id, id);
							strcpy(member.password, id);
							writeFile << id << endl;
							writeFile << password << endl;
							writeFile.close();
						}
					}
				}

			}
			break;
		case 4:
			return 0;
		}

		std::cout << "Menu." << endl;
		std::cout << "1. Login" << endl;
		std::cout << "2. Register" << endl;
		std::cout << "3. Withdrawal" << endl;
		std::cout << "4. Exit" << endl;
		std::cout << " : ";

		std::cin >> choice;
		std::cout << "---------------------" << endl;
		std::cin.ignore();

		std::cout << "---------------------" << endl;

	}
}