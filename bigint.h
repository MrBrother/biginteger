#ifndef BIGINT_H
#define BIGINT_H

#include <string>

using namespace std;

class BigInteger{
private:
  std::vector<int> numbers;
  bool sign;

public:
  BigInteger();
  BigInteger(string s);

  void setNumber(string s);
  const string& getNumber();

  BigInteger operator +(BigInteger b);

private:
	string add(string a, string b);

};

#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;
int main(){
  string a; cin >> a;
  string b; cin >> b;
  if(a.size()%9!=0){
    int df = ((a.size()/9+1)*9-a.size());
    a.insert(0, df, '0');
  }
  vector<int> v;

  for(size_t i = a.size()-9; i >= 0; i-=9) {
    string z = a.substr(i, 9);
    v.push_back(std::stoi(z));
    if(i == 0)break;
  }

  for(int& i : v){
    cout << i << endl;
  }




  return 0;
}






#endif
