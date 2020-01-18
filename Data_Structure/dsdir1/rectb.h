//김명호,3학년,B590011
#ifndef RECTANGLE_H
#define RECTANGLE_H
using namespace std;
class Rectangle{
public:
Rectangle(int,int,int,int);//constructor
bool operator<(Rectangle&);
bool operator==(Rectangle&);
int GetHeight();
int GetWidth();
friend ostream& operator<<(ostream&, Rectangle&);
private:
int xLow,yLow,height,width;
};
#endif
