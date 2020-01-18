#ifndef POSTFIX_H

#define POSTFIX_H

 

#include <iostream>

using namespace std;

 

#define ID 257

#define NUM 258

#define EQ 259

#define NE 260

#define GE 261

#define LE 262

#define AND 263

#define OR 264

#define UMINUS 265

 

#define MAXLEN 80

 

struct Expression

{

        char *str;

        int pos;

        int len;

        Expression(char *s) :str(s), pos(0)

        {

               for (len = 0; str[len] != '\0'; len++);

        }

};

 

struct Token

{

        int type;

        char *str;

        int len;

        int ival;

        bool operator==(char);

        bool operator!=(char);

        Token();

        Token(char);

        Token(char, char, int);

        Token(char*, int, int);

        bool IsOperand();

};

 

//Stack Á¤ÀÇ

template <typename T>

class Stack

{

private:

        T *stack;

        int top;

        int capacity;

public:

        Stack(int stackCapacity = 10);

        bool isEmpty() const;

        T &Top() const;

        void Push(const T &item);

        T &Pop();

};

 

ostream &operator<<(ostream &, Token);

ostream &operator<<(ostream &, Expression);

Token NextToken(Expression &, bool);

void Postfix(Expression e);

 

#endif

