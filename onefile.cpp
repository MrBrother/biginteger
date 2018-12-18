#ifndef BIGINT_H
#define BIGINT_H
#include <iostream>
#include <string>
#include <cmath>
#include <sstream>
#include <cctype>
#include <cstdlib>
#include <vector>
#include <iomanip>
#include <algorithm>
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
  BigInteger operator/(BigInteger b);
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
  string divide(BigInteger b1, BigInteger b2);
  bool less(BigInteger a, BigInteger b);
  bool equal(BigInteger a, BigInteger b);
  BigInteger absolute();
  string vtostring(std::vector<int> v);
  string vtostring(std::vector<long long> v);


};

#endif

BigInteger::BigInteger()
:sign(false), numbers(0){

}

BigInteger::BigInteger(string s){
  if(isdigit(s[0])){
      setNumber(s);
      sign = false;
  }else{
    setNumber(s.substr(1));
    sign = ( s[0] == '-');
  }
}
BigInteger::BigInteger(int a){
  stringstream ss;
  string s;
  ss << a;
  ss >> s;
  if(isdigit(s[0])){
      setNumber(s);
      sign = false;
  }else{
    setNumber(s.substr(1));
    sign = ( s[0] == '-');
  }
}

void BigInteger::setNumber(string s){
  s.erase(0, min(s.find_first_not_of('0'), s.size()-1));
  int flzr = ((s.size()/sz+1)*sz-s.size())%sz;
  s.insert(0, flzr, '0');
  for(int i = s.size()-sz; i >= 0; i-=sz){
    numbers.push_back(std::stoi(s.substr(i, sz)));
  }
}

string BigInteger::getNumber(){
  return vtostring(numbers);
}
BigInteger BigInteger:: operator+(BigInteger b){
  BigInteger addition;
	if( getSign() == b.getSign() ) // both +ve or -ve
	{
		addition.setNumber( add(getNumber(), b.getNumber() ) );
		addition.setSign( getSign() );
	}
	else // sign different
	{
		if( absolute() > b.absolute() )
		{
			addition.setNumber( subtract(getNumber(), b.getNumber() ) );
			addition.setSign( getSign() );
		}
		else
		{
			addition.setNumber( subtract(b.getNumber(), getNumber() ) );
			addition.setSign( b.getSign() );
		}
	}
	if(addition.getNumber() == "0") // avoid (-0) problem
		addition.setSign(false);

	return addition;
}
BigInteger BigInteger:: operator-(BigInteger b){
  b.setSign( ! b.getSign() ); // x - y = x + (-y)
	return (*this) + b;
}
BigInteger BigInteger::operator *(BigInteger b){
  BigInteger ml;
  ml.setNumber(multiply((*this),b));
  ml.setSign(getSign() != b.getSign());
  if(ml.getNumber() == "0")
    ml.setSign(false);
  return ml;
}
BigInteger BigInteger:: operator/(BigInteger b){
  return BigInteger(divide((*this), b));
}
BigInteger& BigInteger:: operator++(){
  (*this) = (*this) + 1;
  return (*this);
}
BigInteger BigInteger:: operator++(int){
  BigInteger before = (*this);
	(*this) = (*this) + 1;
	return before;
}
bool BigInteger:: operator <(BigInteger b){
  return less((*this), b);
}
bool BigInteger:: operator >(BigInteger b){
  return !less((*this), b) and !equal((*this), b);
}
bool BigInteger:: operator <=(BigInteger b){
  return less((*this), b) or equal((*this), b);
}
bool BigInteger:: operator >=(BigInteger b){
  return !less((*this), b) or equal((*this), b);
}
bool BigInteger::less(BigInteger a, BigInteger b){
  int s1 = a.getNumber().size();
  int s2 = b.getNumber().size();
  bool b1 = a.getSign();
  bool b2 = b.getSign();

  if(b1 and !b2) //If (-b1) and (b2)
    return true;

  if(!b1 and b2)//If (b1) and (-b2)
    return false;

  if(!b1){
    if(s1<s2) return true;
    if(s1>s2) return false;
    return a.getNumber() < b.getNumber();
  }else{
    if(s1>s2) return true;
    if(s1<s2) return false;
    return a.getNumber().compare( b.getNumber() ) > 0;

  }
}
bool BigInteger::equal(BigInteger a, BigInteger b){
  return a.getNumber() == b.getNumber()
   and  a.getSign() == a.getSign();
}
string BigInteger::add(BigInteger b1, BigInteger b2){
  std::vector<int> a = b1.numbers;
  std::vector<int> b = b2.numbers;
  if(a.size() < b.size())a.swap(b);
  std::vector<int> out;
  int carry = 0;
  int w;
  for (int i=0; i< a.size(); ++i) {
    w = (i<b.size()?a[i]+b[i]+carry:a[i]+carry);
    carry = 0;
    if(w>base){
      w%=base;
      carry = 1;
    }
    out.push_back(w);
  }
  if(carry){
    out.push_back(1);
  }
	return vtostring(out);
}
string BigInteger::subtract(BigInteger b1, BigInteger b2){
  std::vector<int> a = b1.numbers;
  std::vector<int> b = b2.numbers;
  int carry = 0;
  for(int i = 0; i < b.size() || carry; i++){
      a[i]-= carry + (i < b.size() ? b[i]: 0);
      carry = a[i] < 0;
      if(carry) a[i] += base;
  }
  while(a.size() > 1 && a.back() == 0) a.pop_back();
  return vtostring(a);
}
string BigInteger::multiply(BigInteger b1, BigInteger b2){
  vector<int> a = b1.numbers;
  vector<int> b = b2.numbers;
  vector<long long> c(a.size()+b.size());
  if(a.size()<b.size())a.swap(b);
  long long carry = 0;
  for (size_t i = 0; i < a.size(); i++) {
      for (int j = 0; j < (int)b.size() || carry; j++) {
        long long cur = c[i+j] + a[i] * (j < (int)b.size() ? b[j]:0);
        c[i+j] = int(cur%base);
        carry = int(cur/base);
      }
  }
  while (c.size() > 1 && c.back() == 0) {
    c.pop_back();
  }
  return vtostring(c);
}
string BigInteger::divide(BigInteger b1, BigInteger b2){
  if(b1<b2)
    return string("0");
  vector<int> a = b1.numbers;
  vector<int> b = b2.numbers;
  vector<int> tmp, res;
  int sz = a.size() - 1;
  while(tmp.size() < b.size()){
    tmp.push_back(a[sz--]);
  }
  reverse(tmp.begin(), tmp.end());
  if(BigInteger(vtostring(tmp)) < b2){
    reverse(tmp.begin(), tmp.end());
    tmp.push_back(a[sz--]);
    reverse(tmp.begin(), tmp.end());
  }

  while(true){
    int l=0,r=base;
    while(r-l>1){
      int m = (r+l) >> 1;
      if(b1 < b2 * m){
        r = m;
      }else{
        l = m;
      }
    }
    res.push_back(l);
    tmp = (BigInteger(vtostring(tmp)) - b2 * l).numbers;
    if(sz<0){
      break;
    }

  }

  reverse(res.begin(), res.end());
    return vtostring(res);


}
string BigInteger::vtostring(std::vector<int> v){
  stringstream ss;
  ss << v[v.size()-1];
  for(int i = v.size()-2;i >= 0;i--){
   ss << setfill('0') << setw(sz) << v[i];
  }
  return ss.str();
}
string BigInteger::vtostring(std::vector<long long> v){
  stringstream ss;
  ss << v[v.size()-1];
  for(int i = v.size()-2;i >= 0;i--){
   ss << setfill('0') << setw(sz) << v[i];
  }
  return ss.str();
}
BigInteger BigInteger::absolute(){
	return BigInteger( getNumber() ); // +ve by default
}
void BigInteger::setSign(bool s){
  sign = s;
}
const bool BigInteger::getSign(){
  return sign;
}
istream &operator>>( istream  &input, BigInteger &B){
  string s;
  input >> s;
  B = BigInteger(s);
  return input;
}
ostream &operator<<( ostream &out, BigInteger &D){
  out << (D.getSign()?"-":"") <<D.getNumber();
  return out;
}
#include <iostream>
#include <vector>
#include "bigint.h"

using namespace std;

int main(){
  BigInteger a;//("100000000000001");
  cin >> a;
  cout << ++a << endl;
  return 0;
}
