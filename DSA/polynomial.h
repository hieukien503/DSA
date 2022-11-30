#ifndef polynomial_h
#define polynomial_h
#include <iostream>
using namespace std;

class Polynomials
{
public:
	class Node;
public:
	Node* head;
	Node* tail;
public:
	Polynomials()
	{
		this->head = this->tail = NULL;
	}
	~Polynomials()
	{
		while (head != nullptr)
		{
			Node* temp = head;
			head = head->next;
			if (head == nullptr)
			{
				tail = nullptr;
			}
			delete temp;
		}
	}
public:
	void insertTerm(double coeff, int exponent);
	friend Polynomials operator+(Polynomials A, Polynomials B)
	{
		if (A.head == nullptr)
		{
			return B;
		}
		else if (B.head == nullptr)
		{
			return A;
		}
		Node* p = A.head;
		Node* q = B.head;
		Polynomials result;
		while (p != nullptr || q != nullptr)
		{
			if (p == nullptr)
			{
				result.insertTerm(q->coeff, q->exponent);
				q = q->next;
			}
			else if (q == nullptr)
			{
				result.insertTerm(p->coeff, p->exponent);
				p = p->next;
			}
			else
			{
				result.insertTerm(q->coeff, q->exponent);
				result.insertTerm(p->coeff, p->exponent);
				q = q->next;
				p = p->next;
			}
		}
		return result;
	}
	friend Polynomials operator-(Polynomials A, Polynomials B)
	{
		Polynomials result;
		if (A.head == nullptr)
		{
			if (B.head == nullptr)
			{
				result.head = nullptr;
				return result;
			}
		}
		else if (B.head == nullptr)
		{
			return A;
		}
		Node* p = A.head;
		Node* q = B.head;
		while (p != nullptr || q != nullptr)
		{
			if (p == nullptr)
			{
				result.insertTerm(-q->coeff, q->exponent);
				q = q->next;
			}
			else if (q == nullptr)
			{
				result.insertTerm(p->coeff, p->exponent);
				p = p->next;
			}
			else
			{
				result.insertTerm(p->coeff, p->exponent);
				result.insertTerm(-(q->coeff), q->exponent);
				q = q->next;
				p = p->next;
			}
		}
		return result;
	}
	friend Polynomials operator*(Polynomials A, Polynomials B)
	{
		Polynomials result;
		if (A.head == nullptr || B.head == nullptr)
		{
			result.head = nullptr;
			return result;
		}

		for (Node* p = A.head; p != nullptr; p = p->next)
		{

			for (Node* q = B.head; q != nullptr; q = q->next)
			{
				result.insertTerm(p->coeff * q->coeff, p->exponent + q->exponent);
			}
		}
		return result;
	}
	void printPoly();
	friend void operator/(Polynomials A, Polynomials B)
	{
		Polynomials result;
		if (A.head == nullptr)
		{
			throw runtime_error("0");
		}
		else if (B.head == nullptr)
		{
			throw runtime_error("Cannot divide");
		}
		else
		{
			if (A.head->exponent < B.head->exponent)
			{
				throw runtime_error("Degree of 1st polynomial is smaller than degree of 2nd polynomial, cannot divide");
			}
			else
			{
				Polynomials remainder = A;
				Polynomials product;
				do
				{
					if (remainder.head->exponent >= B.head->exponent)
					{
						result.insertTerm(remainder.head->coeff / B.head->coeff, remainder.head->exponent - B.head->exponent);
						product = result * B;
						remainder = A - product;
					}
					else
					{
						break;
					}
				} while (remainder.head != nullptr);
				cout << "Result of division is: ";
				result.printPoly();
				cout << endl;
				cout << "Remainder of division is: ";
				remainder.printPoly();
			}
		}
	}
public:
	class Node
	{
	public:
		double coeff;
		int exponent;
		Node* next;
		friend class Polynomials;
	public:
		Node(double coeff, int exponent)
		{
			this->coeff = coeff;
			this->exponent = exponent;
			this->next = nullptr;
		}
	};
};

void Polynomials::insertTerm(double coeff, int exponent)
{
	Node* temp = new Node(coeff, exponent);
	if (temp->coeff == 0)
	{
		return;
	}
	else
	{
		if (head == nullptr)
		{
			head = tail = temp;
		}
		else
		{
			if (temp->exponent > head->exponent)
			{
				temp->next = head;
				head = temp;
			}
			else if (temp->exponent < tail->exponent)
			{
				tail->next = temp;
				tail = temp;
			}
			else if (temp->exponent == head->exponent)
			{
				head->coeff += temp->coeff;
				if (head->coeff == 0)
				{
					Node* p = head;
					head = head->next;
					if (head == NULL)
					{
						tail = NULL;
					}
					p->next = NULL;
					p = NULL;
					delete p;
				}
			}
			else if (temp->exponent == tail->exponent)
			{
				Node* p = head;
				Node* q = NULL;
				while (p->next != NULL)
				{
					q = p;
					p = p->next;
				}
				tail->coeff += temp->coeff;
				if (tail->coeff == 0)
				{
					delete tail;
					tail = q;
				}
			}
			else
			{
				Node* p = head;
				Node* q = p->next;
				Node* ptr = NULL;
				while (q->next != NULL)
				{
					if (p->exponent >= temp->exponent && q->exponent < temp->exponent)
					{
						break;
					}
					else
					{
						ptr = p;
						p = q;
						q = q->next;
					}
				}
				if (p->exponent == temp->exponent)
				{
					if (p->coeff + temp->coeff != 0)
					{
						p->coeff += temp->coeff;
					}
					else
					{
						if (p == head)
						{
							Node* p = head;
							head = head->next;
							if (head == NULL)
							{
								tail = NULL;
							}
							p->next = NULL;
							p = NULL;
							delete p;
						}
						else
						{
							ptr->next = p->next;
							p->next = NULL;
							p = NULL;
							delete p;
						}
					}
				}
				else
				{
					p->next = temp;
					temp->next = q;
				}
			}
		}
	}
}

void Polynomials::printPoly()
{
	if (head == NULL)
	{
		cout << 0;
	}
	else
	{
		Node* p = head;
		while (p != NULL)
		{
			if (p->coeff == 1)
			{
				if (p->next != NULL)
				{
					cout << "";
				}
				else
				{
					cout << p->coeff;
				}
			}
			else if (p->coeff == -1)
			{
				if (p->next != NULL)
				{
					cout << " - ";
				}
				else
				{
					cout << p->coeff;
				}
			}
			else
			{
				cout << p->coeff;
			}
			if (p->exponent > 1)
			{
				cout << "x^" << p->exponent;
			}
			else if (p->exponent == 1)
			{
				cout << "x";
			}
			else
			{
				cout << "";
			}
			if (p->next != NULL)
			{
				if (p->next->coeff > 0)
				{
					cout << " + ";
				}
				else
				{
					if (p->next->coeff == -1)
					{
						cout << " - ";
						p->next->coeff = abs(p->next->coeff);
					}
					else
					{
						cout << " ";
					}
				}
			}
			p = p->next;
		}
	}
}
#endif
