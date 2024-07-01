#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
using namespace std;

template <typename T>
class Node
{
private:
	Node<T>* m_Next;
	T m_Data;

public:
	Node() { m_Next = nullptr; m_Data = NULL; }
	~Node() {}
	Node<T>* getNext() { return m_Next; }
	T getData() { return m_Data; }
	void setNext(Node<T>* m_next) { this->m_Next = m_next; }
	void setData(T m_data) { this->m_Data = m_data; }
};

template <typename T>

class Queue
{
private:
	Node<T>* m_Front;
	Node<T>* m_Back;

public:
	Queue() { m_Front = nullptr; m_Back = nullptr; }
	~Queue() {}

	void enqueue(T data) {
		Node<T>* newNode = new Node<T>;
		newNode->setData(data);
		if (isEmpty()) {
			m_Front = m_Back = newNode;
		}
		else {
			m_Back->setNext(newNode);
			m_Back = newNode;
		}
	}

	T dequeue() {
		if (isEmpty()) {
			throw std::out_of_range("is empty");
		}
		Node<T>* curNode = m_Front;
		T tmp = Front();
		m_Front = m_Front->getNext();
		delete curNode;
		if (m_Front == nullptr) {
			m_Back = nullptr;
		}
		return tmp;
	}

	bool isEmpty() {
		if (m_Front != nullptr) {
			return 0;
		}
		else return 1;
	}

	T Front() {
		if (isEmpty()) {
			throw std::out_of_range("is empty");
		}
		return m_Front->getData();
	}

	void print() {
		Node<T>* curNode = m_Front;
		while (curNode != nullptr) {
			cout << curNode->getData() << ' ';
			curNode = curNode->getNext();
		}
		cout << endl;
	}
};

int main() {
	Queue<int> queue;
	string str;
	char tmp[20];
	int pos;

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

		if (!strcmp(tmp, "enqueue")) {
			len = str.size() - pos - 1;
			int num = stoi(str.substr(pos + 1, len));
			queue.enqueue(num);
		}
		else if (!strcmp(tmp, "dequeue")) {
			queue.dequeue();
		}
		else if (!strcmp(tmp, "front")) {
			queue.Front();
		}
		else if (!strcmp(tmp, "isEmpty")) {
			queue.isEmpty();
		}
		else if (!strcmp(tmp, "print")) {
			queue.print();
		}
		else if (!strcmp(tmp, "exit")) {
			return 0;
		}
	}

}