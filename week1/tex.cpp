#include <iostream>
#include <string>
using namespace std;

int main() {
    string line;
    bool open = true;

    while (getline(cin, line)) {
        for (char c : line) {
            if (c == '"') {
                if (open) {
                    cout << "``";
                } else {
                    cout << "''";
                }
                open = !open;
            } else {
                cout << c;
            }
        }
        cout << endl;
    }

    return 0;
}