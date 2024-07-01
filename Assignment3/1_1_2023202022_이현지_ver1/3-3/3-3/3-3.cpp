#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct Member {
	char id[20] = { '\0,' };
	char password[20] = { '\0,' };
};

//password ��ȣȭ
void Caesar(char* tmp) {
	for (int i = 0; i < 20; i++) {
		if (tmp[i] < 'x' && tmp[i] >= 'a') {
			tmp[i] = tmp[i] + 3; //�ƽ�Ű�ڵ� ��� +3
		}
		else if (tmp[i] >= 'x' && tmp[i] <= 'z') {
			tmp[i] -= 23; //�ƽ�Ű�ڵ� ��� -23
		}
	}
}

//password��ȣȭ
void Decipher(char* tmp) {
	for (int i = 0; i < 20; i++) {
		if (tmp[i] <= 'z' && tmp[i] > 'c') {
			tmp[i] = tmp[i] - 3; //������� ��������
		}
		else if (tmp[i] >= 'a' && tmp[i] <= 'c') {
			tmp[i] += 23; //���� ����
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
	std::cin.ignore(); //buffer����

	//�α��� �̷� Ȯ��
	bool logged = 0;

	while (1) {
		std::cout << "===================" << endl;

		bool isID = 0;
		bool isPassword = 0;
		bool alpha = 0;
		bool s_character = 0;
		char special[10] = { '!','@','#','$','%','^','&','*','(',')' }; //Ư������ ����

		switch (choice) {
		case 1:
			readFile.open("membership.txt");

			std::cout << "User id: ";
			std::cin.getline(id, 20);
			std::cout << "password: ";
			std::cin.getline(password, 20);
			
			if (readFile.is_open()) { //membership����
				while (!readFile.eof()) {
					readFile.getline(tmp, 20);
					if (!strcmp(tmp, id)) { //������ id ���� ��
						while (!readFile.eof()) {
							readFile.getline(tmp, 20);
							Decipher(tmp); //��ȣȭ
							if (!strcmp(tmp, password)) { //������ password ���� ��
								strcpy(member.id, id); //struct������ ����
								strcpy(member.password, password);
								std::cout << "Login successful." << endl;
								logged = 1;
								break;
							}
							else break;
						}
					}
					else { //�α��� ����
						std::cout << "Login failed. Invalid User id or password." << endl;
						break;
					}
				}
			}
			//���� �ݱ�
			readFile.close();
			break;

		case 2:
			readFile.open("membership.txt");

			std::cout << "User id: ";
			std::cin.getline(id, 20);
			std::cout << "password: ";
			std::cin.getline(password, 20);
			
			strcpy(tmp, password);

			//�н����� �ּ� ���� Ȯ��
			for (int i = 0; i < 20; i++) {
				if (tmp[i] >= 'a' && tmp[i] <= 'z') {
					alpha = 1; //���ĺ�����
				}

				for (int j = 0; j < 10; j++) {
					if (tmp[i] == special[j]) {
						s_character = 1; //Ư������ ����
					}
				}
			}
			if (sizeof(tmp) < 10) { //�н����� ����Ȯ��
				std::cout << "Registration failed. " << endl;
				break;
			}

			if (readFile.is_open()) {
				while (!readFile.eof()) {
					readFile.getline(tmp, 50);
					if (!strcmp(tmp, id)) {//������ idã���� ��.
						isID = 1; break;
						while (!readFile.eof()) {
							readFile.getline(tmp, 50);
							Decipher(tmp); //��ȣȭ
							if (!strcmp(tmp, password)) { //������ �н����� ã���� ��.
								isPassword = 1;
								break;
							}
						}
						break;
					}
					else {
						readFile.close();
						writeFile.open("membership.txt", ios::app); //app���̸� ������ ���뿡 ���ٿ� �ۼ� ����.
						strcpy(member.id, id);
						Caesar(password);
						strcpy(member.password, password);
						writeFile << id << endl;
						writeFile << password << endl;
						writeFile.close();
					}
				}
				//register����
				cout << "Sorry, it's already exist." << endl;
			}
			break;

		case 3:
			readFile.open("membership.txt");
			tmpFile.open("tmp.txt");

			//�α��εǾ� ���� ���.
			if (logged == 1) {
				std::cout << "Logged in user : (" << member.id << ")" << endl;
				if (readFile.is_open()) {
					while (!readFile.eof()) {
						readFile.getline(tmp, 50);
						if (!strcmp(tmp, member.id) || !strcmp(tmp, member.password)) {}
						else {
							tmpFile << tmp << endl; //�α��εǾ��ִ� ȸ������ ���� tmp�� ����.
						}
					}tmpFile.close();

					readFile.close();
					writeFile.open("membership.txt");
					RtmpFile.open("tmp.txt");
					if (RtmpFile.is_open()) {
						while (!RtmpFile.eof()) {
							RtmpFile.getline(tmp, 50);
							writeFile << tmp << endl; //�ٽ� membership���Ͽ� ����.
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