#include <iostream>

#include "post.h"

using namespace std;

 

int main(void)

{

        char line[MAXLEN];

        while (cin.getline(line, MAXLEN))

        {

               Expression e(line); //line ���۸� �̿�

               try

               {

                       Postfix(e);

               }

               catch (char const *msg)

               {

                       cerr << "Exception: " << msg << endl;

               }

        }

        return 0;

}