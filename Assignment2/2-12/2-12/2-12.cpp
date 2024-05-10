#include <iostream>
using namespace std;

class Node
{
private:
	char* key;
	Node* pNext;

public:
	Node(char* val = 0) : key(val), pNext(nullptr) {}
	void setKey(char* key); //값 설정
	void setNext(Node* pNext); //다음 노드 설정
	char* getKey() const { return key; } //저장된 값 반환
	Node* getNext() const { return pNext; } //다음 노드 주소 반환
};

class LinkedList
{
private:
	Node* pHead;

public:
	LinkedList() : pHead(nullptr) {}
	~LinkedList();

	bool insertKey(char* key);
	void printList();
};

//값 설정
void Node::setKey(char* key) {
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
bool LinkedList::insertKey(char* key) {
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


	return 0;
}