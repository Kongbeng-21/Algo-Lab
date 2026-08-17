#include <iostream>
#include <stack>
using namespace std;

int main() {
    int N, V;
    cin >> N >> V;

    stack<int> st;

    for (int i = 0; i < N; i++) {
        char op;
        cin >> op;

        if (op == '#') {
            V = st.top();
            st.pop();
        } else {
            int x;
            cin >> x;
            st.push(V);

            if (op == '+') {
                V += x;
            } 
            else if (op == '-') {
                V -= x;
            } 
            else if (op == '*') {
                V *= x;
            }
        }
    }

    cout << V << endl;

    return 0;
}