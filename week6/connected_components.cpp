#include <iostream>
#include <vector>
using namespace std;

vector<int> parent, rnk;

int find(int x) {
    while (parent[x] != x) {
        parent[x] = parent[parent[x]]; 
        x = parent[x];
    }
    return x;
}

void unite(int a, int b) {
    a = find(a);
    b = find(b);
    if (a == b) return;
    if (rnk[a] < rnk[b]) swap(a, b);
    parent[b] = a;
    if (rnk[a] == rnk[b]) rnk[a]++;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    cin >> n >> m;

    parent.resize(n + 1);
    rnk.assign(n + 1, 0);
    for (int i = 1; i <= n; i++) parent[i] = i;

    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        unite(u, v);
    }

    int components = 0;
    for (int i = 1; i <= n; i++) {
        if (find(i) == i) components++;
    }

    cout << components << "\n";
    return 0;
}