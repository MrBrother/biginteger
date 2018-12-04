#include <iostream>
#include <string>
#include <cmath>
#include <ssrtrem>

#include "bigint.h"
using namespace std;

BigInteger::BigInteger()
: number("0"), sign(false){

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
BigInteger::BigInteger(string s, bool si){
  setNumber(s);
  setSign(si);
}
BigInteger::BigInteger(int n){
  sstringstream ss;
  string s;
  ss << n;
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
  number = s;
}

const string& BigInteger::getNumber(){
  return number;
}

void BigInteger::setSign(bool s){
  sign = s;
}

const bool& BigInteger::getSign(){
  return sign;
}

BigInteger BigInteger::absolute(){
  return BigInteger(getNumber);
}

void BigInteger::operator = (BigInteger b){
  setNumber(b.getNumber());
  setSign(b.getSign());
}

bool BigInteger::operator == (BigInteger b){
  return equals((*this), b);
}

bool BigInteger::operator != (BigInteger b){
  return ! equals((*this), b);
}

bool BigInteger::operator > (BigInteger b){
  return greater((*this), b);
}
bool BigInteger::operator < (BigInteger b){
  return less((*this), b);
}
bool BigInteger::operator >= (BigInteger b){
  return greater((*this), b) or equals((*this), b);
}
bool BigInteger::operator <= (BigInteger b){

}


bool BigInteger::equals(BigInteger a, BigInteger b){
  return a.getNumber() == b.getNumber()
    and a.getSign() == b.getSign();
}
bool BigInteger::less(BigInteger n1, BigInteger n2){
  
}
bool greater(BigInteger n1, BigInteger n2);
