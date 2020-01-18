#ifndef POSTFIX_H
#define POSTFIX_H

#define ID	257
#define NUM 258
#define EQ	259
#define NE	260
#define GE	261
#define LE	262
#define AND 263
#define OR	264
#define UMINUS	265
#define MAXLEN	80
#include <cstring>

struct Expression{
	Expression(char* linebuf, bool inf = false)
		:buf(linebuf), pos(0), len(strlen(buf)), infix(inf){}
	char* buf;
	int pos;
	int len;
	bool infix;
};


struct Token{
	bool operator ==(char);
	bool operator !=(char);
	Token();
	Token(char);			//	1자 토큰 : (연산자) 토큰 자체를 타입으로 취급
	Token(char, char, int);	//	2자 토큰(예 <=)과 그타입(예 LE)
	Token(char*, int);		//	ID 토큰의 이름및 그 길이
	Token(float);			//	NUM토큰의 값 저장				
	bool IsOperand();		//	토큰 타입이 ID 혹은 NUM이면 true
	int type;				//	1자 토큰은 그 자체값 : 그 외는 미리 정의된 값
	union{
		struct{
			char* str;		//	NUM이외 토큰값 및 그 길이
			int len;		//	타입이 NUM인 경우 그 값을 저장
		};
		float val;
	};
};
#endif