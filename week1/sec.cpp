#include <iostream>
#include <cmath>

using namespace std;

int main()
{
  int t;
  cin >> t;
  for (int i=0;i<t;i++) {
      int n;
      cin >> n;
      
      long long total = n;
      total = total * 567;
      total = total / 9;
      total = total + 7492;
      total = total * 235;
      total = total / 47;
      total = total - 498;
      
      cout << abs((total/10)%10) <<endl;
  }
  return 0;
}