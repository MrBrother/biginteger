#include <iostream>
#include "bigint.h"

using namespace std;

int main(){
  BigInteger a("125");
  BigInteger b("75");
  BigInteger an = a + b;
  cout << an.getNumber() << endl;
  return 0;
}
