#include <iostream>
using namespace std;

template <typename T>
class Stack
{
private:
	Node<T>* m_Top;

public:
	Stack();
	~Stack();

	void push(T data);
	T pop();
	bool isEmpy();
	T top();
	void print();
};

template <typename T>
class Node
{
private:
	Node* m_Next;
	T m_Data;

public:
	Node();
	~Node();
};

int main() {

}