#include <stdio.h>
#include <iostream>
#include <vector>
using namespace std;

int main() 
{
	vector<int> v;

	v.push_back(1);
	v.push_back(2);
	v.push_back(3);
	v.push_back(4);
	v.push_back(5);

	//vector의 요소에 접근하기 위해서는 iterator라는 반복자 개념이 필요.
	//현 code의 iter는 v의 첫번째 원소를 가리키는 포인터처럼 작동
	vector<int>::iterator iter = v.begin();

	//vector.end()는 마지막요소의 다음 부분을 가리키는 포인터. 즉 null이나 쓰레기값을 가리키게됨.
	//이는 반복문을 이용할 때 유용하게 작동하도록 설계해놓은 것.
	for (iter = v.begin(); iter != v.end(); ++iter) {
		cout << *iter << " ";
	}
	cout << endl;

	iter = v.begin();

	cout << "iter[0] : " << iter[0] << endl;
	cout << "iter[3] : " << iter[3] << endl;

	cout << "iterator가 3번째 원소를 가리키도록 변경" << endl;
	iter += 2;
	cout << "iter[0] : " << iter[0] << endl;
	cout << "*iter : " << *iter << endl;

	//iter은 * 연산자를 오버로딩해서 포인터처럼 동작하게 만든 것.
	//* 연산자는 iter이 가리키는 원소의 레퍼런스를 리턴함.
	*iter = 10;
	*(iter + 1) = 20;
	iter[2] = 30;

	for (iter = v.begin(); iter != v.end(); ++iter) {
		cout << *iter << " ";
	}
	cout << endl;

	return 0;
}