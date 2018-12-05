#ifndef BIGINT_H
#define BIGINT_H

#include <string>

using namespace std;

class BigInteger{
private:
  string number;
  bool sign;
  //sda
public:
  BigInteger(); //dsadsa
  BigInteger(string s);

  void setNumber(string s);
  const string& getNumber();

  BigInteger operator +(BigInteger b);

private:
	string add(string a, string b);

};





#endif
