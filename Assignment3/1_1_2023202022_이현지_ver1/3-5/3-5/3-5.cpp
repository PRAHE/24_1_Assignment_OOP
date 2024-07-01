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

		//각각 poly받아서 coeff같은거 있는지 확인 후 동일할 경우 덧셈. 없을 경우에는 내림차순으로 정렬
		Term* leftTerm = this->m_pHead;
		Term* rightTerm = poly.m_pHead;
		
		while (leftTerm != NULL) { 
			left_exp = leftTerm->getExpo();
			left_coeff = leftTerm->getCoeff();
			while (rightTerm != NULL) { //leftTerm과 동일한 차수가 있는지 rightTerm 끝까지 확인
				right_exp = rightTerm->getExpo();
				right_coeff = rightTerm->getCoeff();
				if (left_exp == right_exp) { //동일한 차수 발견 수 계수끼리 계산
					result.addTerm(left_coeff + right_coeff, left_exp);
					same = 1;
					break;
				}
				if (rightTerm->getNext() != nullptr) { //가장 마지막 노드가 next로 nullptr을 가리키는 경우 예외처리
					rightTerm = rightTerm->getNext();
				}
			}

			if (same == 0) { //차수가 겹치지 않을 경우.
				result.addTerm(left_coeff, left_exp);
			}
			if (leftTerm->getNext() != nullptr) {
				leftTerm = leftTerm->getNext();
			}
			else { break; }
		}
		//leftTerm기준으로 돌렸기 때문에 rightTerm에서 누락된 부분이 있을 수 있음.
		//result와 expo비교하면서 빠진 부분 채워넣기
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
			if (put_exp != NULL) { //겹치지 않은 부분 추가
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

		//각각 poly받아서 coeff같은거 있는지 확인 후 동일할 경우 덧셈. 없을 경우에는 내림차순으로 정렬
		Term* leftTerm = this->m_pHead;
		Term* rightTerm = poly.m_pHead;

		while (leftTerm != NULL) {
			left_exp = leftTerm->getExpo();
			left_coeff = leftTerm->getCoeff();
			while (rightTerm != NULL) { //leftTerm과 동일한 차수가 있는지 rightTerm 끝까지 확인
				right_exp = rightTerm->getExpo();
				right_coeff = rightTerm->getCoeff();
				if (left_exp == right_exp) { //동일한 차수 발견 수 계수끼리 계산
					result.addTerm(left_coeff + right_coeff*(-1), left_exp);
					same = 1;
					break;
				}
				if (rightTerm->getNext() != nullptr) { //가장 마지막 노드가 next로 nullptr을 가리키는 경우 예외처리
					rightTerm = rightTerm->getNext();
				}
			}

			if (same == 0) { //차수가 겹치지 않을 경우.
				result.addTerm(left_coeff, left_exp);
			}
			if (leftTerm->getNext() != nullptr) {
				leftTerm = leftTerm->getNext();
			}
			else { break; }
		}
		//leftTerm기준으로 돌렸기 때문에 rightTerm에서 누락된 부분이 있을 수 있음.
		//result와 expo비교하면서 빠진 부분 채워넣기
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
			if (put_exp != NULL) { //겹치지 않은 부분 추가
				result.addTerm(put_coeff*(-1), put_exp);
				put_exp = NULL;
				put_coeff = NULL;

			}
			rightTerm = rightTerm->getNext();
		}
		return result;

	}
	//미분
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
	if (curTerm->getCoeff() == NULL) { //term에 처음 값 넣을 때
		m_pHead = pNew;
	}
	else {
		while (curTerm != NULL) {
			exponent = curTerm->getExpo();
			if (exponent == exp) { //차수가 같은 term이 있을 경우
				coeffiecient = curTerm->getCoeff(); //이미 term에 저장된 coeff값에 더함,
				coeff += coeffiecient;
				curTerm->setMono(coeff, exp);
				return; //차수 같은 term에 계수끼리 계산 후 add function 종료
			}
			if (curTerm->getNext() != nullptr) {
				curTerm = curTerm->getNext();
			}
			else if (curTerm->getNext() == nullptr) { //term 끝에 pNew추가. add function종료
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
	//마지막 term
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
			for (int i = 0; i < expo; i++) { //power계산
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