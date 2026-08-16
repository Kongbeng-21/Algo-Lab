#include <iostream>
#include <vector>

using namespace std;

int main() {
    int n;
    cin >> n;
    
    long long total=0;
    
    for (int i=1;i<=n;i++) {
        int exp;
        cin >> exp;
        
        if (i%4==0) {
            total+=exp*2;
        }
        else {
            total+=exp;
        }
    }
    cout << total << endl;
    return 0;
}