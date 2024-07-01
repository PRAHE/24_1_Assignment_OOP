#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdexcept>
#include <string>
using namespace std;

template <typename T>
class Node
{
private:
	Node* m_Next;
	T m_Data;
	
public:
	Node() { m_Next = nullptr; m_Data = NULL; }
	~Node() {}

	T getData() { return m_Data; }
	Node* getNext() { return m_Next; }
	void setData(T m_data) { this->m_Data = m_data; }
	void setNext(Node* m_next) { this->m_Next = m_next; }
};

template <typename T>
class Stack
{
private:
	Node<T>* m_Top;

public:
	Stack() { m_Top = nullptr; }
	~Stack() {}

	void push(T data) {
		Node<T>* newNode = new Node<T>;
		newNode->setData(data);
		newNode->setNext(m_Top);
		m_Top = newNode;
	}

	T pop() {
		if (isEmpty()) {
			throw std::out_of_range("is empty");
		}
		Node<T>* curNode = m_Top;
		T tmp = top();
		m_Top = m_Top->getNext();
		delete curNode;

		return tmp;
	}

	bool isEmpty() {
		if (m_Top == nullptr) {
			return 1;
		}
		else return 0;
	}

	T top() {
		if (isEmpty()) {
			throw std::out_of_range("is empty");
		}
		return m_Top->getData();
	}

	void print() {
		Node<T>* curNode = m_Top; 
		while (curNode != nullptr) {
			cout << curNode->getData() << ' ';
			curNode = curNode->getNext();
		}
		cout << endl;
	}
};

int main() {
	Stack<int> stack;
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

		if (!strcmp(tmp, "push")) {
			len = str.size() - pos - 1;
			int num = stoi(str.substr(pos + 1, len));
			stack.push(num);
		}
		else if (!strcmp(tmp, "pop")) {
			stack.pop();
		}
		else if (!strcmp(tmp, "print")) {
			stack.print();
		}
		else if (!strcmp(tmp, "exit")) {
			return 0;
		}
	}

	
}