/* fio4.cpp, Herritance from fstream*/

#include <fstream>
#include <iostream>
using namespace std;

class SimpleInputFile: public fstream
{
public:
  SimpleInputFile(char * s): fstream(s, ios::in | ios::binary) {}
  friend ostream& operator << (ostream& o,SimpleInputFile &f);
};

ostream& operator << (ostream& o,SimpleInputFile &f)
{
	o<< f.rdbuf();
return o;
}


void main(int argc, char ** argv)
{
SimpleInputFile f("1.res");
  cout << f;  
}
