#include <iostream>
#include <vector>
using namespace std;

int main() {
    int t;
    cin >> t;
    vector<int> cookies;

    for (int i = 0; i < t; i++) {
        int l;
        cin >> l;

        if (l == 1) {
            int k, x;
            cin >> k >> x;
            if (k >= cookies.size()) {
                cookies.push_back(x);
            } else {
                cookies.insert(cookies.begin() + k + 1, x);
            }
        } else if (l == 2) {
            int k;
            cin >> k;
            if (k <= cookies.size()) {
                cookies.erase(cookies.begin() + k - 1);
            }
        }
    }

    for (int i = 0; i < cookies.size(); i++) {
        cout << cookies[i] << endl;
    }

    return 0;
}