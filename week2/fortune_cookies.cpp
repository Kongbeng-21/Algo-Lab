#include <iostream>
#include <vector>
using namespace std;
int main() {
    int n,m;
    cin >> n >> m;
    vector<int> bonus(n,0);
    int current = 0;
    for (int i=0;i<=m;i++) {
        int t;
        cin >> t;
        if (t==0) {
            current=0;
        }
        else if (t==1) {
            if (current < bonus.size() -1) {
                current++;
            }
        }
        else if (t==2) {
            bonus.insert(bonus.begin()+current+1,0);
        }
        else if (t==3) {
            int x;
            cin >> x;
            bonus[current] += x;
        }
    }
    for (int b : bonus) {
        cout << b << " ";
    }
    cout << endl;
    return 0;
}
        