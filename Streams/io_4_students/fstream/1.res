/* filecopy.cpp, копирование файлов*/
#include <fstream>
#include <iostream>
#include <string>
using namespace std;

int main(int argc, char * argv[])
{
{
  cout<<ios_base::badbit;
  ifstream input (argv[1]);
  ofstream output("1.res");
  char c;
  while (input.get(c))
    output.put(c);
}

{
  ifstream input (argv[1]);
  ofstream output("2.res");
  char buffer[200];
  while (input && output)
    {
    input.getline(buffer, sizeof(buffer));
    output<< buffer << endl;
    }
}

{
  ifstream input (argv[1]);
  ofstream output("3.res");
  string buffer;
  while (getline(input,buffer),input && output)
    {
    output<< buffer << endl;
    }
}


{
  ifstream input (argv[1], ios::binary);
  ofstream output("4.res", ios::binary);
  char buffer[512];
  while (input && output)
    {
    input.read(buffer, sizeof(buffer));
    output.write(buffer,input.gcount());
    }
}

{
  ifstream input (argv[1], ios::binary);
  ofstream output1("5a.res", ios::binary);
  ofstream output2("5b.res", ios::binary);

  output1 << input.rdbuf();

  input.seekg(0);
  input.clear();

  input >> output2.rdbuf();
}
}
