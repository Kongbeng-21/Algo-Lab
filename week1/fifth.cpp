# include <iostream>
using namespace std;
int main() {
    int n;
    cin >> n;
    
    long long total = 0;
    int last = 0;
    
    for (int i=1;i<=n;i++) {
        int ants;
        cin >> ants;
    
        if (last == 1000) {
        }
        else {
            int eaten = min(1000,ants);
            total += eaten;
        }
        last = (last == 1000) ? 0 : min(1000,ants);
    }
    cout << total << endl;
    return 0;
}