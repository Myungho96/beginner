//B590011,3학년,김명호
#include<iostream>
#include<stack>
#include"post.h"
using namespace std;

int temp;//과학적 표기법을 위한 변수

Token::Token() {}
Token::Token(char c) :len(1), type(c) {
	str = new char[1];
	str[0] = c;
}

Token::Token(char c, char c2, int ty) : len(2), type(ty) {
	str = new char[2]; 
	str[0] = c;
	str[1] = c2;
}

Token::Token(char* arr, int l) :type(ID), len(l) {
	str = new char[len + 1];
	for (int i = 0; i < len; i++) {
		str[i] = arr[i];
	}
	str[len] = '\0';
}

Token::Token(float v):val(v),type(NUM){}

bool Token::operator==(char b) { return len == 1 && str[0] == b; }
bool Token::operator!=(char b) { return len != 1 || str[0] != b; }
bool Token::IsOperand() { return type == ID || type == NUM; }

ostream& operator<<(ostream& os, Token t) {
	if (t.type == NUM)os << t.val;
	else for (int i = 0; i < t.len; i++)os << t.str[i];
	os << " "; return os;
}

bool IsAlpha(char c) { return c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z'; }
bool IsDigit(char c) { return c >= '0' && c <= '9'; }
bool GetID(Expression& e, Token& tok) {
	char c = e.buf[e.pos];
	if (!IsAlpha(c))return false;
	int pos_start = e.pos;
	e.pos++;
	while (IsAlpha(c = e.buf[e.pos]) || IsDigit(c))e.pos++;
	int idlen = e.pos - pos_start;
	tok = Token(e.buf + pos_start, idlen);
	return true;
}

bool GetNUM(Expression& e, Token& tok) {
	char c;
	if (!IsDigit(c = e.buf[e.pos]))
		return false;
	float val = c - '0';
	e.pos++;
	while (IsDigit(c = e.buf[e.pos])) {
		val = val * 10 + c - '0'; 
		e.pos++;
	}
	//소수점 표기법
	if ((c = e.buf[e.pos]) == '.') {
		temp=0;
		e.pos++;
		while (IsDigit(c = e.buf[e.pos])) {
			val = val * 10 + c - '0';
			temp++;
			e.pos++;
		}
		while(temp!=0){
			val/=10.0;
			temp--;
		}
	}
	//과학적 표기법
	if ((c = e.buf[e.pos]) == 'e') {
		e.pos++;
		if ((c = e.buf[e.pos]) == '+') {
			temp=0;
			e.pos++;
			c = e.buf[e.pos];
			temp = c - '0';
			e.pos++;
			while (IsDigit(c = e.buf[e.pos])) {
				temp = temp * 10 + c - '0';
				e.pos++;
			}
			while (temp!=0) {
				val *= 10.0;
				temp--;
			}
		}
		else if ((c = e.buf[e.pos]) == '-') {
			temp=0;
			e.pos++;
			c = e.buf[e.pos];
			temp = c - '0';
			e.pos++;
			while (IsDigit(c = e.buf[e.pos])) {
				temp = temp * 10 + c - '0';
				e.pos++;
			}
			while (temp!=0) {
				val/= 10.0;
				temp--;
			}
		}
	}	
	tok=Token(val);
	return true;
}

void SkipBlanks(Expression& e) {
	char c;
	while (e.pos < e.len && ((c = e.buf[e.pos]) == ' ' || c == '\t'))
		e.pos++;
}

bool TwoCharOp(Expression& e, Token& tok) {
	if (e.pos >= e.len - 1)return false;
	char c = e.buf[e.pos]; char c2 = e.buf[e.pos + 1];
	int op;//LE GE EQ NE AND OR UMINUS
	if (c == '<' && c2 == '=')op = LE;
	else if (c == '>' && c2 == '=')op = GE;
	else if (c == '=' && c2 == '=')op = EQ;
	else if (c == '!' && c2 == '=')op = NE;
	else if (c == '&' && c2 == '&')op = AND;
	else if (c == '|' && c2 == '|')op = OR;
	else if (c == '-' && c2 == 'u')op = UMINUS;
	else return false;
	tok = Token(c, c2, op); e.pos += 2;
	return true;
}

bool OneCharOp(Expression& e, Token& tok) {
	char c = e.buf[e.pos];
	if (c == '-' || c == '!' || c == '*' || c == '/' || c == '%' || c == '+' || c == '<' || c == '>' || c == '(' || c == ')' || c == '=') {
		tok = Token(c); e.pos++; return true;
	}
	return false;
}

Token NextToken(Expression& e) {
	static bool opndFound = false;
	Token tok;
	SkipBlanks(e);
	if (e.pos == e.len)
		tok = Token('#');
	else if (GetID(e, tok) || GetNUM(e, tok)) {}
	else if (TwoCharOp(e, tok)) {}
	else if (OneCharOp(e, tok)) {
		if (e.infix && tok.type == '-' && !opndFound)
			tok = Token('-', 'u', UMINUS);
	}
	else throw "Illegal Character Found";
	if (e.infix)opndFound = tok.IsOperand();
	return tok;
}

int icp(Token& t) {
	if (t.type == '(')
		return 0;
	else if (t.type == UMINUS || t.type == '!')
		return 1;
	else if (t.type == '*' || t.type == '/' || t.type == '%')
		return 2;
	else if (t.type == '+' || t.type == '-')
		return 3;
	else if (t.type == '<' || t.type == '>' || t.type == LE || t.type == GE)
		return 4;
	else if (t.type == EQ || t.type == NE)
		return 5;
	else if (t.type == AND)
		return 6;
	else if (t.type == OR)
		return 7;
	else if (t.type == '=')
		return 8;
	else if (t.type == '#')
		return 10;
}

int isp(Token& t) {
	if (t.type == '(')
		return 9;
	else
		return icp(t);
}

void Postfix(Expression e)
{
	stack<Token> stack;
	stack.push('#');
	for (Token x = NextToken(e); x != '#'; x = NextToken(e)) {
		if (x.IsOperand())
			cout << x;
		else if (x == ')') {
			for (; stack.top() != '('; stack.pop())
				cout << stack.top();
			stack.pop();
		}
		else {
			for (; isp(stack.top()) <= icp(x); stack.pop()) {
				if (x == '=' && stack.top() == '=')
					break;
				cout << stack.top();
			}
			stack.push(x);
		}
	}
	while (stack.top() != '#') {
		cout << stack.top(); stack.pop();
	}
	cout << endl;
}
