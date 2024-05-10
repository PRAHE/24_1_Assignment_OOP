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
	void setKey(int key); //�� ����
 	void setNext(Node* pNext); //���� ��� ����
	int getKey() const { return key; } //����� �� ��ȯ
	Node* getNext() const { return pNext; } //���� ��� �ּ� ��ȯ
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

//�� ����
void Node::setKey(int key) {
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
bool LinkedList::insertKey(int key) {
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

//�ش��ϴ� ���� ��� �����
bool LinkedList::deleteKey(int key) {
	if (!pHead) return false;

	Node* pPre = nullptr;
	Node* pCur = pHead;

	while (pCur) { //��� ��ġ�� null �� ������
		if (pCur->getKey() == key) {
			if (pPre) { //���� ��尡 �ִٸ�
				pPre->setNext(pCur->getNext());
			}
			else { //ù��° ����� ���
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

//�������� ���������� ��ȯ
int convert(char* str) {
	int num = 0;
	while (*str != '\0') {
		num = num * 10 + (*str - '0'); //�ƽ�Ű�ڵ� ����
		str++;
	}
	return num;
}

//�Է¹��� ���ڿ� ���鿡 ���� ������
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
