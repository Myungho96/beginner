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
	Token(char);			//	1�� ��ū : (������) ��ū ��ü�� Ÿ������ ���
	Token(char, char, int);	//	2�� ��ū(�� <=)�� ��Ÿ��(�� LE)
	Token(char*, int);		//	ID ��ū�� �̸��� �� ����
	Token(float);			//	NUM��ū�� �� ����				
	bool IsOperand();		//	��ū Ÿ���� ID Ȥ�� NUM�̸� true
	int type;				//	1�� ��ū�� �� ��ü�� : �� �ܴ� �̸� ���ǵ� ��
	union{
		struct{
			char* str;		//	NUM�̿� ��ū�� �� �� ����
			int len;		//	Ÿ���� NUM�� ��� �� ���� ����
		};
		float val;
	};
};
#endif