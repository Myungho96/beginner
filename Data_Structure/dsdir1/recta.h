//김명호,3학년,B590011
#ifndef RECTANGLE_H
#define RECTANGLE_H
class Rectangle{
public:
Rectangle(int,int,int,int);//constructor
void Print();
bool SmallerThan(Rectangle&);//면적이 작은가
bool EqualTo(Rectangle&);//면적이 같은가
int GetHeight();
int GetWidth();
private:
int xLow,yLow,height,width;
};
#endif
