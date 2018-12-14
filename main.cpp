#include <iostream>
#include <vector>
#include "bigint.h"

using namespace std;

int main(){
  BigInteger a;//("100000000000001");
  BigInteger b;//("2");
  cin >> a >> b;
  BigInteger an = a / b;
  cout << an << endl;
  return 0;
}
