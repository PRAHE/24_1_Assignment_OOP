#include <iostream>
using namespace std;

class Term {
private:
	int m_Coefficient;
	int m_Exponent;
	Term* m_pNext;

public:
	Term() {}
	~Term() {}

	void setMono(int coeff, int exp) {
		m_Coefficient = coeff;
		m_Exponent = exp;
	}
	void getMono() {
		cout << m_Coefficient << "x^";
		cout << m_Exponent;
	}
	void setNext(Term* m_pNext) { this->m_pNext = m_pNext; }
	Term* getNext() { return m_pNext; }
};

class Polynomial {
private:
	Term* m_pHead;

public:
	Polynomial() {}
	~Polynomial() {}
	void addTerm(int coeff, int exp);
	void printPolynomial();
	Polynomial operator+(const Polynomial& poly);
	Polynomial operator-(const Polynomial& poly);
	Polynomial differentiation();
	int calculate(int x);
};

void Polynomial::addTerm(int coeff, int exp) {
	Term* pNew = new Term;
	pNew->setMono(coeff, exp);

	Term* curTerm = m_pHead;
	while (curTerm->getNext() != nullptr) {
		curTerm = curTerm->getNext();
	}
	curTerm->setNext(pNew);
}

void Polynomial::printPolynomial() {
	Term* curTerm = m_pHead;
	while (curTerm->getNext() != nullptr) {
		curTerm->getMono();
		cout << " + ";
	}
	curTerm->getMono();
}

int main() {
	Polynomial poly;

	poly.addTerm(3, 3);
	poly.addTerm(1, 2);
	poly.addTerm(4, 7);

	poly.printPolynomial();

}