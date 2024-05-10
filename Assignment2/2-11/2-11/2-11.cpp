#include <iostream>
using namespace std;

int convert(char* str);
void separate(char* assign, char** ptr);

class Node
{
private:
	int key;
	Node* pNext;

public:
	Node(int val = 0) : key(val), pNext(nullptr) {}
	void setKey(int key); //값 설정
 	void setNext(Node* pNext); //다음 노드 설정
	int getKey() const { return key; } //저장된 값 반환
	Node* getNext() const { return pNext; } //다음 노드 주소 반환
};

class LinkedList
{
private:
	Node* pHead;

public:
	LinkedList() : pHead(nullptr) {}
	~LinkedList();

	bool insertKey(int key); 
	bool deleteKey(int key);
	void printList();
};

//값 설정
void Node::setKey(int key) {
	this->key = key;
}

//다음 포인터 설정
void Node::setNext(Node* pNext) {
	this->pNext = pNext;
}

//소멸자
LinkedList::~LinkedList() {
	Node* curr = pHead;
	while (curr) {
		Node* temp = curr;
		curr = curr->getNext();
		delete temp;
	}
}

//입력받은 숫자 연결리스트에 넣고 다른 노드와 연결
bool LinkedList::insertKey(int key) {
	Node* pNew = new Node(key);
	if (!pNew) return false;

	if (!pHead || pHead->getKey() <= key) { //내림차순정렬
		pNew->setNext(pHead);
		pHead = pNew;
		return true;
	}

	Node* pPre = pHead;
	Node* pCur = pPre->getNext();

	while (pCur) {
		if (pCur->getKey() <= key) break;
		pPre = pCur;
		pCur = pCur->getNext();
	}

	pNew->setNext(pCur);
	pPre->setNext(pNew);
	return true;
}

//해당하는 값의 노드 지우기
bool LinkedList::deleteKey(int key) {
	if (!pHead) return false;

	Node* pPre = nullptr;
	Node* pCur = pHead;

	while (pCur) { //노드 위치가 null 일 때까지
		if (pCur->getKey() == key) {
			if (pPre) { //이전 노드가 있다면
				pPre->setNext(pCur->getNext());
			}
			else { //첫번째 노드일 경우
				pHead = pCur->getNext();
			}
			delete pCur;
			return true;
		}
		pPre = pCur;
		pCur = pCur->getNext();
	}
	return false;
}

//연결리스트 출력
void LinkedList::printList() {
	Node* curr = pHead;
	while (curr) {
		cout << curr->getKey(); //key받아오기
		curr = curr->getNext(); //주소도 받아오기
		if (curr) { cout << " -> "; } //현재가 NULL이 아니면 다음 노드 key를 위한 화살표
	}
	cout << endl;
}

int main() {
	LinkedList list;
	char assign[20] = { '\0', };
	char* ptr[2];
	char command;

	cin.getline(assign, 20);
	separate(assign, ptr);
	command = ptr[0][0];

	while (command != 'e') {
		int key = convert(ptr[1]);
		switch (command) {
		case 'i': //insert
			list.insertKey(key);
			cout << "Linked list : ";
			list.printList();
			break;
		case 'd': //delete
			if (list.deleteKey(key)) {
				cout << "Linked list : ";
				list.printList();
			}
			break;
		}
		cin.getline(assign, 20);
		separate(assign, ptr);
		command = ptr[0][0];
	}

	return 0;
}

//문자형을 정수형으로 변환
int convert(char* str) {
	int num = 0;
	while (*str != '\0') {
		num = num * 10 + (*str - '0'); //아스키코드 참고
		str++;
	}
	return num;
}

//입력받은 문자열 공백에 따라 나누기
void separate(char* assign, char** ptr) {
	int i = 0;
	int j;
	int k = 0;
	int length = 1;
	while (assign[i] != '\0') {
		if (assign[i + 1] == ' ' || assign[i + 1] == '\0') {
			ptr[k] = new char[length + 1];
			int start = i - length + 1;
			for (j = 0; j < length; j++) {
				ptr[k][j] = assign[start];
				start++;
			}
			ptr[k][j] = '\0';
			i++;
			k++;
			length = 1;
		}
		else {
			length++;
		}
		i++;
	}
}
