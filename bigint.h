#ifndef BIGINT_H
#define BIGINT_H

#include <string>
#include <vector>
const int sz = 4;
const int base = 10000;

using namespace std;

class BigInteger{
private:
  std::vector<int> numbers;
  bool sign;

public:
  BigInteger();
  BigInteger(string s);

  void setNumber(string s);
  string getNumber();

  BigInteger operator +(BigInteger b);
  friend istream &operator>>( istream  &input, BigInteger &B);
  friend ostream &operator<<( ostream &output, BigInteger &D);
private:
	string add(BigInteger a, BigInteger b);
  string vtostring(std::vector<int> v);

};




#endif
