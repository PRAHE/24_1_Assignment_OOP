#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct Member {
	char id[20];
	char password[20];
};

class Menu {
	
};

int main() {
	Member member;
	int choice;
	ifstream readFile;
	ofstream writeFile;
	
	cout << "===================" << endl;
	cout << "Menu." << endl;
	cout << "1. Login" << endl;
	cout << "2. Register" << endl;
	cout << "3. Withdrawal" << endl;
	cout << "4. Exit" << endl;
	cout << " : ";

	cin >> choice;
	cout << "---------------------" << endl;
	switch (choice) {
	case 1:
		cout << "User id: ";
		cin.getline(member.id, 20);
		cout << "password: ";
		cin.getline(member.password, 20);
	case 2:
		
	case 3:

	case 4:
		return 0;
	}
	cout << "---------------------" << endl;


}