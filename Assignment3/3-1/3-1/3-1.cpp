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
	Node() : value(), pNext(nullptr) {};
	void setValue(string value) { this->value = value; }
	void setNext(Node* pNext) { this->pNext = pNext; }
	string getValue() { return value; }
	Node* getNext() { return pNext; }
};

class LinkedList {
public:
	bool initalize(string str, int cur_pos);
	void transfer(string str, int cur_pos);
	void print();

private:
	Node* pHead = new Node;
	Node* pTail = new Node;
};

bool LinkedList::initalize(string str, int cur_pos) {
	int pos;
	string result;

	while ((pos = str.find(' ', cur_pos)) != string::npos) {
		int len = pos - cur_pos;
		result = str.substr(cur_pos, len);

		if (pHead->getNext() == NULL) {
			pHead->setValue(result);
			pHead->setNext(pTail);
		}

		else {
			Node* pNew = new Node; //pNew 메모리할당
			if (pNew == nullptr) //pNew 메모리할당 확인
				return false;

			pNew->setValue(result); //노드 끝에 값 추가 수정

			Node* curNode = pHead;
			while (curNode->getNext() != pTail) { //연결리스트의 끝 찾기
				curNode = curNode->getNext();
			}
			curNode->setNext(pNew); //가장 끝노드가 pNew를 가리키도록

		}
		cur_pos = pos + 1;
	}
	pTail->setNext(pHead);
	pTail->setValue(result);

	Node* curNode = pHead;

	while (curNode->getNext() != pHead) {
		cout << curNode->getValue() << ' ';
		curNode = curNode->getNext();
	}

	return true;
}

void LinkedList::transfer(string str, int cur_pos) {
	int pos;
	int dis = 0;

	dis = rand() % 10;

	while ((pos = str.find(' ', cur_pos)) != string::npos) {
		int len = pos - cur_pos;
		string result = str.substr(cur_pos, len);

		cout << result << endl;
		cur_pos = pos + 1;
	}
}

void LinkedList::print() {
	Node* curNode = pHead;

	while (curNode->getNext() != pHead) {
		cout << curNode->getValue() << ' ';
		curNode = curNode->getNext();
	}
}

int main() {
	LinkedList list;
	string str;
	char tmp[20];
	int pos;
	int cur_pos = 0;

	srand((unsigned)time(NULL));

	while (1) {
		cout << "Command : ";
		getline(cin, str);

		pos = str.find(' ', cur_pos);
		int len = pos - cur_pos;
		string result = str.substr(cur_pos, len);

		strcpy(tmp, result.c_str());
		if (strcmp(tmp, "initilalize")) {
			list.initalize(str, pos + 1);
		}
		else if (strcmp(tmp, "transfer")) {
			list.transfer(str, cur_pos);
		}
		else if (strcmp(tmp, "print")) {
			list.print();
		}
		else if (strcmp(tmp, "exit")) {
			break;
		}
	}

	return 0;
}