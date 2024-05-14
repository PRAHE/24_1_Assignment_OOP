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
	void setValue(string value) { this->value = value; }
	void setNext(Node* pNext) { this->pNext = pNext; }
	string getValue() { return this->value; }
	Node* getNext() { return this->pNext; }
};

class LinkedList {
public:
	LinkedList() { Node node; pHead->setNext(NULL); pHead->setValue("\0"); }
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
		int len = pos - cur_pos; //40으로 결과값 나올 때 pos가 -1로 됨. 확인필요
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
	cout << "num: " << num << endl;
	Node* check = pHead;
	for (int i = 0; i < num; i++) { //num수만큼 노드 건너뛰기
		check = check->getNext();
	}
	cout << check->getValue() << endl;
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
	int sub = transfer[1] - transfer[0];
	if (sub < 0) {
		sub += 10;
	}

	Node* first = pHead;
	int i;
	for (i = 0; i < transfer[i]; i++) {
		first = first->getNext();
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

 		pos = str.find(' ', cur_pos);
		if (pos == string::npos) {
			pos = str.find("\n", cur_pos);
		}
		int len = pos - cur_pos;
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
			break;
		}
	}
	return 0;
}