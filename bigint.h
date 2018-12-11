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
  BigInteger(int a);

  void setNumber(string s);
  string getNumber();
  void setSign(bool s);
  const bool getSign();
  BigInteger operator +(BigInteger b);
  BigInteger operator -(BigInteger b);
  BigInteger operator *(BigInteger b);
  BigInteger& operator ++();
  BigInteger operator ++(int);


  bool operator <(BigInteger b);
  bool operator >(BigInteger b);
  bool operator <=(BigInteger b);
  bool operator >=(BigInteger b);
  //BigInteger& operator ++();
  friend istream &operator>>( istream  &input, BigInteger &B);
  friend ostream &operator<<( ostream &output, BigInteger &D);
private:
	string add(BigInteger a, BigInteger b);
  string subtract(BigInteger b1, BigInteger b2);
  string multiply(BigInteger b1, BigInteger b2);
  bool less(BigInteger a, BigInteger b);
  bool equal(BigInteger a, BigInteger b);
  BigInteger absolute();
  string vtostring(std::vector<int> v);


};




#endif
