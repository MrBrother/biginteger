#include <iostream>
#include <string>
#include <cmath>
#include <sstream>
#include <cctype>
#include <cstdlib>
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


void BigInteger::setNumber(string s){
  number = s;
}

const string& BigInteger::getNumber(){
  return number;
}
BigInteger BigInteger:: operator+(BigInteger b){
  return BigInteger(add((*this).getNumber(), b.getNumber()));
}

string BigInteger::add(string a, string b){
  string add = (a.length() > b.length() ? a : b);
  char carry = '0';
  int difLn = abs((int) (a.size() - b.size()));

  if(a.size() > b.size())
		b.insert(0, difLn, '0'); // put zeros from left

	else// if(number1.size() < number2.size())
		a.insert(0, difLn, '0');

	for(int i=a.size()-1; i>=0; --i)
	{
		add[i] = ((carry-'0')+(a[i]-'0')+(b[i]-'0')) + '0';

		if(i != 0)
		{
			if(add[i] > '9')
			{
				add[i] -= 10;
				carry = '1';
			}
			else
				carry = '0';
		}
	}
	if(add[0] > '9')
	{
		add[0]-= 10;
		add.insert(0,1,'1');
	}
	return add;
}
