#include <iostream>
#include <list>
using namespace std;
int main()
{
  int m;
  list<int> Q;
  cin >> m;
  for(int i = 0; i < m; i++) {
    int t;
    cin >> t;
    if(t == 1) {
      int n,c;
      cin >> n;
      for(int j = 0; j < n; j++) {
        cin >> c;
        Q.push_back(c);
      }
    } else {       
      cout << Q.front() << "\n";
      Q.pop_front();
    }
  }
  cout << Q.size() << "\n";
}