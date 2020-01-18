//김명호,3학년,B590011
#include<iostream>
#include"polyb.h"

using namespace std;

istream& operator>> (istream& is,Polynomial& p){
//#yerms and(coefficoent,exponent)의 pair들을 읽어들인다.
//높은 차수의 항부터 저장되었다고 가정한다.
int noofterms; float coef; int exp;
is>>noofterms;
for(int i=0;i<noofterms;i++){
is>>coef>>exp;//계수와 지수 pair를 읽어들인다.
p.NewTerm(coef,exp);
}
return is;
}

ostream& operator<< (ostream& os,Polynomial& p)
{
for(int i=0;i<p.terms;i++){
if(p.termArray[i].coef!=1 && p.termArray[i].coef!=-1){os<<p.termArray[i].coef;}
else if(p.termArray[i].coef==-1){os<<"-";}
if(p.termArray[i].exp==0){os<<" ";}
else if(p.termArray[i].exp==1){os<<"x ";}
else{os<<"x^"<<p.termArray[i].exp<<" ";}
if(p.termArray[i+1].coef>0){os<<"+";}
}
os<<endl;
return os;
}

Polynomial::Polynomial():capacity(4), terms(0){
termArray=new Term[capacity];
}

void Polynomial::NewTerm(const float theCoeff,const int theExp){//다항식 뒤에 새로운 항을 추가하는 함수로 교재에 있음
if(terms==capacity){
capacity*=2;
Term *temp=new Term[capacity];
copy(termArray,termArray+terms,temp);
delete [] termArray;
termArray=temp;
}
termArray[terms].coef=theCoeff;
termArray[terms++].exp=theExp;
}

Polynomial Polynomial::operator+(Polynomial& b)
{
Polynomial c;
int aPos=0,bPos=0;
while((aPos<terms)&&(bPos<b.terms)){
if(termArray[aPos].exp==b.termArray[bPos].exp){
	float t=termArray[aPos].coef+b.termArray[bPos].coef;
	if(t){c.NewTerm(t,termArray[aPos].exp);}
	aPos++; bPos++;
}
else if(termArray[aPos].exp<b.termArray[bPos].exp){
c.NewTerm(b.termArray[bPos].coef,b.termArray[bPos].exp);
bPos++;
}
else{
c.NewTerm(termArray[aPos].coef,termArray[aPos].exp);
aPos++;
}
}
for(;aPos<terms;aPos++){c.NewTerm(termArray[aPos].coef,termArray[aPos].exp);}
for(;bPos<b.terms;bPos++){c.NewTerm(b.termArray[bPos].coef,b.termArray[bPos].exp);}
return c;
}

Polynomial Polynomial::operator*(Polynomial& b)
{
Polynomial c,compare;
int aPos=0,bPos=0;
float comp;
int exmp;
for(aPos=0;aPos<terms;aPos++){
	for(bPos=0;bPos<b.terms;bPos++){
		int count=0;
		comp=termArray[aPos].coef*b.termArray[bPos].coef;
		exmp=termArray[aPos].exp+b.termArray[bPos].exp;
		for(int i=0;i<c.terms;i++){
			if (c.termArray[i].exp==exmp){
					c.termArray[i].coef+=comp;
					count++;}
			}
		if(count==0){c.NewTerm(comp,exmp);}
		}
}
//정렬을 위한 추가함수
for(int i=0; i<c.terms; i++){
	for(int j=i+1; j<c.terms; j++){
		if (c.termArray[i].exp < c.termArray[j].exp){
			compare.termArray[0] = c.termArray[i];
			c.termArray[i] = c.termArray[j];
			c.termArray[j] = compare.termArray[0];
		}
	}
}
return c;
}
