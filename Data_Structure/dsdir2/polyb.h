//김명호,3학년,B590011
#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H
using namespace std;
struct Term{//편의상 클래스 대신 이용
float coef;
int exp;
};
class Polynomial{
public:
	Polynomial();//다항식 p(x)=0인 생성자
	Polynomial operator+(Polynomial&);//다항식의 합을 반환
	void NewTerm(const float,const int);
	Polynomial operator*(Polynomial&);//다항식의 곱을 반환
private:
	Term *termArray;
	int capacity;//1로 초기화
	int terms;//저장된 항의 수로 0으로 초기화
friend ostream& operator<< (ostream&, Polynomial&);
friend istream& operator>> (istream&, Polynomial&);
};
#endif
