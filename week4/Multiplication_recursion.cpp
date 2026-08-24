#include <iostream>
using namespace std;

int multiply(int a, int b) {
    if (b == 0) {
        return 0;
    }
    return a + multiply(a, b - 1);
}

int main() {
    int A, B;
    cin >> A >> B;
    cout << multiply(A, B) << endl;
    return 0;
}