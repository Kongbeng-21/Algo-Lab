#include <iostream>
using namespace std;
int main()
{
    int a,b;
    
    cin >> a >> b;
    int total = 0;
    for (int i=a;i<=b;i++) {
        total += i;
    }
    cout << total << endl;
    return 0;
}