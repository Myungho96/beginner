#include <iostream>
#include <stack>
#include "post.h"
using namespace std;

Token::Token(){}
Token::Token(char c) : len(1), type(c){
	str = new char[1];
	str[0] = c;
}
Token::Token(char c, char c2, int ty) : len(2), type(ty){
	str = new char[2];
	str[0] = c;
	str[1] = c2;
}
Token::Token(char*arr, int l) : type(ID), len(l){
	str = new char[len + 1];
	for (int i = 0; i < len; i++)
		str[i] = arr[i];
	str[len] = '\0';
}
Token::Token(float v) : val(v), type(NUM){}

bool Token::operator==(char b){
	return len == 1 && str[0] == b;
}
bool Token::operator!=(char b){
	return len != 1 || str[0] != b;
}
bool Token::IsOperand(){
	return type == ID || type == NUM;
}

ostream& operator << (ostream& os, Token t){
	if (t.type == UMINUS)
		os << "-u";
	else if (t.type == NUM)
		os << t.val;
	else
		for (int i = 0; i < t.len; i++)
			os << t.str[i];
	os << " ";
	return os;
}
bool IsAlpha(char c){
	return c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z';
}
bool IsDigit(char c){
	return c >= '0' && c <= '9';
}
bool GetID(Expression & e, Token& tok){
	char c = e.buf[e.pos];
	if (!IsAlpha(c))
		return false;
	int pos_start = e.pos;
	e.pos++;
	while (IsAlpha(c = e.buf[e.pos]) || IsDigit(c))
		e.pos++;
	int idlen = e.pos - pos_start;
	tok = Token(e.buf + pos_start, idlen);
	return true;
}
bool GetNUM(Expression& e, Token& tok){
	char c; //	"357" 같은 숫자가 나오면 실수 357.0 으로 바꾸자
	if (!IsDigit(c = e.buf[e.pos]))	// 숫자가 아니면 false 리턴
		return false;
	float val = c - '0';		// 숫자가 나온경우 '0'의 아스키 코드값을 빼서 숫자로 저장
	e.pos++;
	while (IsDigit(c = e.buf[e.pos])){		// 다음 자리도 숫자라면
		val = val * 10 + c - '0';			// 가중치를 반영한다
		e.pos++;							// 다음숫자도 검사
	}
	// 소숫점 이하 숫자 처리
	if ((c= e.buf[e.pos]) == '.'){			// 소숫점 이하 숫자 추가
		e.pos++;
		while (IsDigit(c = e.buf[e.pos])){		// 다음 자리도 숫자라면
			val = val + (c - '0')/10 ;			// 가중치를 반영한다
			e.pos++;							// 다음숫자도 검사
		}
	}
	tok = Token(val);
	return true;
}
void SkipBlanks(Expression& e){
	char c;
	while (e.pos < e.len && ((c = e.buf[e.pos]) == ' ' || c == '\t'))
		e.pos++;
}

bool TwoCharOp(Expression& e, Token& tok){
	// 7가지 2자 토큰들 <= >= == != && || -u을 처리
	char c = e.buf[e.pos];
	char c2 = e.buf[e.pos + 1];
	int op; // LE GE EQ NE AND OR UMINUS
	if (c == '<' && c2 == '=')
		op = LE;
	else if (c == '=' && c2 == '=')
		op = EQ;
	else if (c == '!' && c2 == '=')
		op = NE;
	else if (c == '>' && c2 == '=')
		op = GE;
	else if (c == '&' && c2 == '&')
		op = AND;
	else if (c == '|' && c2 == '|')
		op = OR;
	else if (c == '-' && c2 == 'u')
		op = UMINUS;
	else
		return false;
	tok = Token(c, c2, op);
	e.pos += 2;
	return true;
}
bool OneCharOp(Expression& e, Token& tok){
	char c = e.buf[e.pos];
	if (c == '-' || c == '!' || c == '*' || c == '/' || c == '%' || c == '+' || c == '<' || c == '>' || c == '(' || c == ')' || c == '=')
	{
		tok = Token(c);
		e.pos++;
		return true;
	}
	return false;
}

Token NextToken(Expression& e){
	static bool opndFound = false;	// operand 미발견(for infix 식)
	Token tok;
	SkipBlanks(e);	// skip blanks if any
	if (e.pos == e.len)
		tok = Token('#');	// 토큰없음을 알리는 토큰
	else if (GetID(e, tok) || GetNUM(e, tok)){}	// do nothing
	else if (TwoCharOp(e, tok)){}				// do nothing
	else if (OneCharOp(e, tok)){						// 1자 토큰 여부 점검
		if (e.infix && tok.type == '-' && !opndFound)	// operand 후 아님
			tok = Token('-', 'u', UMINUS);				// -u(즉 unary -)로 바꾼다
	}
	else throw "Illegal Character Found";
	if (e.infix)	opndFound = tok.IsOperand();
	return tok;
}
int icp(Token& t){		// in-coming priority
	// t.type이 '('면 0 , UMINUS나 '!'면 1, '*'나 '/'나 '%'면 2
	// '+'나 '-'면 3, '<'나'>'면 LE나 GE면 4, EQ나 NE면 5,
	// AND면 6, OR이면 7 , '='이면 8, '#'면 10을 return 한다.
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
int isp(Token& t){
	//'('경우 9를 기타는 icp(t)를 반환
	if (t.type == '(')
		return 9;
	else
		return icp(t);
}
void Postfix(Expression e){
	stack<Token> stack;
	stack.push('#');
	for (Token x = NextToken(e); x != '#'; x = NextToken(e))
		if (x.IsOperand())
			cout << x;
		else if (x == ')'){
			for (; stack.top() != '('; stack.pop())
				cout << stack.top();
			stack.pop();
		}
		else{
			for (; isp(stack.top()) <= icp(x); stack.pop())
				cout << stack.top();
			stack.push(x);
		}

		while(stack.top() != '#') { cout << stack.top(); stack.pop();}
		stack.pop();
		cout << endl;
}
