#include <iostream>
using namespace std;

class Term {
private:
	int m_Coefficient;
	int m_Exponent;
	Term* m_pNext;

public:
	Term() { m_Coefficient = NULL; m_Exponent = NULL; m_pNext = nullptr; }
	~Term() {}

	void setMono(int coeff, int exp) {
		m_Coefficient = coeff;
		m_Exponent = exp;
	}
	int getCoeff() { return m_Coefficient; }
	int getExpo() { return m_Exponent; }
	void setNext(Term* m_pNext) { this->m_pNext = m_pNext; }
	Term* getNext() { return m_pNext; }
};

class Polynomial {
private:
	Term* m_pHead;

public:
	Polynomial() { m_pHead = new Term; }
	~Polynomial() {}
	void addTerm(int coeff, int exp);
	void printPolynomial();
	void sort(int coeff, int exp);
	Polynomial operator+(const Polynomial& poly) {
		Polynomial result;

		int left_coeff;
		int left_exp;
		int right_coeff;
		int right_exp;
		bool same = 0;

		//���� poly�޾Ƽ� coeff������ �ִ��� Ȯ�� �� ������ ��� ����. ���� ��쿡�� ������������ ����
		Term* leftTerm = this->m_pHead;
		Term* rightTerm = poly.m_pHead;
		
		while (leftTerm != NULL) { 
			left_exp = leftTerm->getExpo();
			left_coeff = leftTerm->getCoeff();
			while (rightTerm != NULL) { //leftTerm�� ������ ������ �ִ��� rightTerm ������ Ȯ��
				right_exp = rightTerm->getExpo();
				right_coeff = rightTerm->getCoeff();
				if (left_exp == right_exp) { //������ ���� �߰� �� ������� ���
					result.addTerm(left_coeff + right_coeff, left_exp);
					same = 1;
					break;
				}
				if (rightTerm->getNext() != nullptr) { //���� ������ ��尡 next�� nullptr�� ����Ű�� ��� ����ó��
					rightTerm = rightTerm->getNext();
				}
			}

			if (same == 0) { //������ ��ġ�� ���� ���.
				result.addTerm(left_coeff, left_exp);
			}
			if (leftTerm->getNext() != nullptr) {
				leftTerm = leftTerm->getNext();
			}
			else { break; }
		}
		//leftTerm�������� ���ȱ� ������ rightTerm���� ������ �κ��� ���� �� ����.
		//result�� expo���ϸ鼭 ���� �κ� ä���ֱ�
		int put_exp = NULL;
		int put_coeff = NULL;
		rightTerm = poly.m_pHead;
		Term* resultTerm = result.m_pHead;

		while (rightTerm != NULL) {
			right_exp = rightTerm->getExpo();
			right_coeff = rightTerm->getCoeff(); 
			while (resultTerm != NULL) {
				int exp = resultTerm->getExpo();
				if (exp == right_exp) {
					put_exp = NULL;
					put_coeff = NULL;
					break;
				}
				else {
					put_exp = right_exp;
					put_coeff = right_coeff;
				}
				resultTerm = resultTerm->getNext();
			}
			if (put_exp != NULL) { //��ġ�� ���� �κ� �߰�
				result.addTerm(put_coeff, put_exp);
				put_exp = NULL;
				put_coeff = NULL;

			}
			rightTerm = rightTerm->getNext();
		}
		return result;
	}
	Polynomial operator-(const Polynomial& poly) {
		Polynomial result;

		int left_coeff;
		int left_exp;
		int right_coeff;
		int right_exp;
		bool same = 0;

		//���� poly�޾Ƽ� coeff������ �ִ��� Ȯ�� �� ������ ��� ����. ���� ��쿡�� ������������ ����
		Term* leftTerm = this->m_pHead;
		Term* rightTerm = poly.m_pHead;

		while (leftTerm != NULL) {
			left_exp = leftTerm->getExpo();
			left_coeff = leftTerm->getCoeff();
			while (rightTerm != NULL) { //leftTerm�� ������ ������ �ִ��� rightTerm ������ Ȯ��
				right_exp = rightTerm->getExpo();
				right_coeff = rightTerm->getCoeff();
				if (left_exp == right_exp) { //������ ���� �߰� �� ������� ���
					result.addTerm(left_coeff + right_coeff*(-1), left_exp);
					same = 1;
					break;
				}
				if (rightTerm->getNext() != nullptr) { //���� ������ ��尡 next�� nullptr�� ����Ű�� ��� ����ó��
					rightTerm = rightTerm->getNext();
				}
			}

			if (same == 0) { //������ ��ġ�� ���� ���.
				result.addTerm(left_coeff, left_exp);
			}
			if (leftTerm->getNext() != nullptr) {
				leftTerm = leftTerm->getNext();
			}
			else { break; }
		}
		//leftTerm�������� ���ȱ� ������ rightTerm���� ������ �κ��� ���� �� ����.
		//result�� expo���ϸ鼭 ���� �κ� ä���ֱ�
		int put_exp = NULL;
		int put_coeff = NULL;
		rightTerm = poly.m_pHead;
		Term* resultTerm = result.m_pHead;

		while (rightTerm != NULL) {
			right_exp = rightTerm->getExpo();
			right_coeff = rightTerm->getCoeff();
			while (resultTerm != NULL) {
				int exp = resultTerm->getExpo();
				if (exp == right_exp) {
					put_exp = NULL;
					put_coeff = NULL;
					break;
				}
				else {
					put_exp = right_exp;
					put_coeff = right_coeff;
				}
				resultTerm = resultTerm->getNext();
			}
			if (put_exp != NULL) { //��ġ�� ���� �κ� �߰�
				result.addTerm(put_coeff*(-1), put_exp);
				put_exp = NULL;
				put_coeff = NULL;

			}
			rightTerm = rightTerm->getNext();
		}
		return result;

	}
	//�̺�
	Polynomial differentiation() {
		Polynomial diff;

		int coeff;
		int exp;
		int result;

		Term* curTerm = m_pHead;
		while (curTerm != NULL) {
			coeff = curTerm->getCoeff();
			exp = curTerm->getExpo();
			result = coeff * exp;
			if (result != 0) {
				diff.addTerm(result, exp - 1);
			}
			curTerm = curTerm->getNext();
		}
		diff.printPolynomial();
		return diff;
	}
	int calculate(int x);
};

void Polynomial::addTerm(int coeff, int exp) {
	int exponent;
	int coeffiecient;

	Term* pNew = new Term;
	pNew->setMono(coeff, exp);

	Term* curTerm = m_pHead;
	if (curTerm->getCoeff() == NULL) { //term�� ó�� �� ���� ��
		m_pHead = pNew;
	}
	else {
		while (curTerm != NULL) {
			exponent = curTerm->getExpo();
			if (exponent == exp) { //������ ���� term�� ���� ���
				coeffiecient = curTerm->getCoeff(); //�̹� term�� ����� coeff���� ����,
				coeff += coeffiecient;
				curTerm->setMono(coeff, exp);
				return; //���� ���� term�� ������� ��� �� add function ����
			}
			if (curTerm->getNext() != nullptr) {
				curTerm = curTerm->getNext();
			}
			else if (curTerm->getNext() == nullptr) { //term ���� pNew�߰�. add function����
				curTerm->setNext(pNew);
				return;
			}
		}
	}
	pNew->setNext(nullptr);
}

void Polynomial::printPolynomial() {
	int coeff;
	int expo;

	Term* curTerm = m_pHead;
	while (curTerm->getNext() != nullptr) {
		coeff = curTerm->getCoeff();
		expo = curTerm->getExpo();

		if (coeff == 0) {
			continue;
		}
		else if (expo == 0) {
			cout << coeff << " + ";
		}
		else {
			cout << coeff << "x^" << expo << " + ";
		}
		curTerm = curTerm->getNext();
	}
	//������ term
	coeff = curTerm->getCoeff();
	expo = curTerm->getExpo();

	if (coeff == 0) {
		cout << endl;
	}
	else if (expo == 0) {
		cout << coeff << endl;
	}
	else {
		cout << coeff << "x^" << expo << endl;
	}
	curTerm = curTerm->getNext();
}

int Polynomial::calculate(int x) {
	int coeff;
	int expo;
	int result = 0;

	Term* curTerm = m_pHead;
	while (curTerm != NULL) {
		expo = curTerm->getExpo();
		coeff = curTerm->getCoeff();
		int power = 1;

		if (expo > 0) {
			for (int i = 0; i < expo; i++) { //power���
				power *= x;
			}
			power *= coeff;
		}
		else if (expo == 0) {
			power *= coeff;
		}
		result += power;
		curTerm = curTerm->getNext();
	}
	cout << result;
	return result;
}

int main() {
	Polynomial poly1, poly2, result;

	poly1.addTerm(2, 3);
	poly1.addTerm(-4, 2);
	poly1.addTerm(-7, 0);
	cout << "poly1 = ";
	poly1.printPolynomial();
	cout << "diefferentiate poly1 = ";
	poly1.differentiation();
	cout << endl;

	poly2.addTerm(-3, 3);
	poly2.addTerm(1, 2);
	poly2.addTerm(6, 1);
	poly2.addTerm(7, 1);
	poly2.addTerm(4, 0);
	cout << "poly2 = ";
	poly2.printPolynomial();
	cout << endl;

	result = poly1 + poly2;
	cout << "poly1 + poly2 = ";
	result.printPolynomial();

	result = poly1 - poly2;
	cout << "poly1 - poly2 = ";
	result.printPolynomial();
	cout << endl;
	
	cout << "x = 2 in poly1 => ";
	poly1.calculate(2);
	cout << endl;

	return 0;
}