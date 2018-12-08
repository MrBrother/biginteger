#include <iostream>
#include <string>
#include <cmath>
#include <sstream>
#include <cctype>
#include <cstdlib>
#include <vector>
#include <iomanip>
#include "bigint.h"
using namespace std;

BigInteger::BigInteger()
:sign(false){

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
  return BigInteger(add((*this), b));
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

string BigInteger::vtostring(std::vector<int> v){
  stringstream ss;
  ss << v[v.size()-1];
  for(int i = v.size()-2;i >= 0;i--){
   ss << setfill('0') << setw(sz) << v[i];
  }
  return ss.str();
}
istream &operator>>( istream  &input, BigInteger &B){
  string s;
  input >> s;
  B.setNumber(s);
  return input;
}
ostream &operator<<( ostream &out, BigInteger &D){
  out << D.getNumber();
  return out;
}
