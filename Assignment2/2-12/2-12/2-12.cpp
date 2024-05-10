#include <iostream>
using namespace std;

class Node
{
private:
	char* key;
	Node* pNext;

public:
	Node(char* val = 0) : key(val), pNext(nullptr) {}
	void setKey(char* key); //�� ����
	void setNext(Node* pNext); //���� ��� ����
	char* getKey() const { return key; } //����� �� ��ȯ
	Node* getNext() const { return pNext; } //���� ��� �ּ� ��ȯ
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

//�� ����
void Node::setKey(char* key) {
	this->key = key;
}

//���� ������ ����
void Node::setNext(Node* pNext) {
	this->pNext = pNext;
}

//�Ҹ���
LinkedList::~LinkedList() {
	Node* curr = pHead;
	while (curr) {
		Node* temp = curr;
		curr = curr->getNext();
		delete temp;
	}
}

//�Է¹��� ���� ���Ḯ��Ʈ�� �ְ� �ٸ� ���� ����
bool LinkedList::insertKey(char* key) {
	Node* pNew = new Node(key);
	if (!pNew) return false;

	if (!pHead || pHead->getKey() <= key) { //������������
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

//���Ḯ��Ʈ ���
void LinkedList::printList() {
	Node* curr = pHead;
	while (curr) {
		cout << curr->getKey(); //key�޾ƿ���
		curr = curr->getNext(); //�ּҵ� �޾ƿ���
		if (curr) { cout << " -> "; } //���簡 NULL�� �ƴϸ� ���� ��� key�� ���� ȭ��ǥ
	}
	cout << endl;
}

int main() {
	LinkedList list;
	char assign[20] = { '\0', };


	return 0;
}