//김명호,3학년,B590011
#include<iostream>
using namespace std;
#include "polyb.h"
int main(){
Polynomial p1,p2,p3;

cin>>p1>>p2;//2개의 다항식을 읽어들인다.
p3=p1*p2;
cout<<p1<<p2<<p3;
}
//실행 결과 :
//3x^5 +2x^3 -4
//x^8 -7x^5 -x^3 -3
//3x^13 +2x^11 -21x^10 -21x^8 -2x^6 +19x^5 -2x^3 +12
