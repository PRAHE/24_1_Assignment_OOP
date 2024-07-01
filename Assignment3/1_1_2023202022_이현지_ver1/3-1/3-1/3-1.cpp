#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <ctime>
using namespace std;

class Node {
private:
	string value;
	Node* pNext;

public:
	Node() { value = { 0, }; pNext = nullptr; }
	~Node(){}
	void setValue(string value) { this->value = value; } //value setter
	void setNext(Node* pNext) { this->pNext = pNext; } //next setter
	string getValue() { return this->value; } //value getter
	Node* getNext() { return this->pNext; } //next getter
};

class LinkedList {
public:
	LinkedList() { pHead->setNext(NULL); pHead->setValue("\0"); }
	~LinkedList() { delete pHead; } //메모리 해제
	bool initalize(string str, int cur_pos);
	bool transfer(string str, int cur_pos);
	void print();

private:
	Node* pHead = new Node;
};

bool LinkedList::initalize(string str, int cur_pos) {
	int pos;
	string result;

	while ((pos = str.find(' ', cur_pos)) != string::npos || cur_pos == str.size() - 2) {
		int len = pos - cur_pos; 
		result = str.substr(cur_pos, len);
		if (pHead->getValue() == "\0") {
			pHead->setValue(result);
			pHead->setNext(nullptr);
		}

		else {
			Node* pNew = new Node; //pNew 메모리할당
			if (pNew == nullptr) //pNew 메모리할당 확인
				return false;

			pNew->setValue(result); //노드 끝에 값 추가 수정

			Node* curNode = pHead;
			while (curNode->getNext() != nullptr) { //연결리스트의 끝 찾기
				curNode = curNode->getNext();
			}
			curNode->setNext(pNew); //마지막 노드가 pNew를 가리키도록
			pNew->setNext(nullptr); //pNew는 nullptr을 가리키도록
			delete pNew;
		}
		cur_pos = pos + 1;
		if (cur_pos == 0) { break; }
	}

	Node* curNode = pHead;
	while (curNode->getNext() != nullptr) {
		curNode = curNode->getNext();
	}
	curNode->setNext(pHead); //pTail과 마지막 노드 이어줌.
	return true;
}

bool LinkedList::transfer(string str, int cur_pos) {
	int pos;
	int k = 0;
	string result;
	int transfer[2] = { 0, };
	//disconnected
	int num = rand() % 10;

	Node* check = pHead;
	for (int i = 0; i < num; i++) { //num수만큼 노드 건너뛰기
		check = check->getNext();
	}
	check->setNext(nullptr); //disconnect

	while ((pos = str.find(' ', cur_pos)) != string::npos || cur_pos == str.size() - 1) {
		int len = pos - cur_pos;
		result = str.substr(cur_pos, len);

		if (result == "to") {}
		else { 
			transfer[k] = stoi(result);
			k++; 
		}

		cur_pos = pos + 1;
		if (cur_pos == 0) { break; }
	}
	//두 숫자 간의 간격으로 노드 이동
	int sub = transfer[1] - transfer[0];
	//차이가 0보다 작을 경우
	if (sub < 0) {
		sub += 10;
	}

	Node* first = pHead;
	int i;
	for (i = 0; i < transfer[i]; i++) {
		first = first->getNext();
		//disconnected
		if (first == nullptr) {
			cout << "Detected a disconnection between " << i << " and " << i + 1 << endl;
			return 0;
		}
	}
	string key = first->getValue();
	for (int j = i; j < i + sub; j++) {
		first = first->getNext();
		if (first == nullptr) {
			if (j >= 10) {
				j -= 10;
			}
			cout << "Detected a disconnection between " << j << " and " << j + 1 << endl;
			return 0;
		}
	}
	Node* second = first;
	second->setValue(key);

	return 1;
}

void LinkedList::print() {
	Node* curNode = pHead;

	//마지막 노드까지 출력
	while (curNode->getNext() != pHead) {
		cout << curNode->getValue() << ' ';
		curNode = curNode->getNext();
	}
	cout << curNode->getValue() << endl;
}

int main() {
	LinkedList list;
	string str;
	char tmp[20];
	int pos;

	srand((unsigned)time(NULL));

	while (1) {
		cout << "Command : ";
		getline(cin, str);
		int cur_pos = 0;
		
		//빈칸을 기준으로 command 나누기
 		pos = str.find(' ', cur_pos);
		if (pos == string::npos) {
			pos = str.find("\n", cur_pos);
		}
		//문자 길이
		int len = pos - cur_pos;
		//command
		string result = str.substr(cur_pos, len);
		strcpy(tmp, result.c_str());

		if (!strcmp(tmp, "initialize")) {
			list.initalize(str, pos + 1);
		}
		else if (!strcmp(tmp, "transfer")) {
			list.transfer(str, pos + 1);
		}
		else if (!strcmp(tmp, "print")) {
			list.print();
		}
		else if (!strcmp(tmp, "exit")) {
			return 0;
		}
	}
}