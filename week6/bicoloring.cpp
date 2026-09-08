#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    while (cin >> n && n != 0) {
        int l;
        cin >> l;

        vector<vector<int>> adj(n);
        for (int i = 0; i < l; i++) {
            int a, b;
            cin >> a >> b;
            adj[a].push_back(b);
            adj[b].push_back(a);
        }

        vector<int> color(n, -1); 
        bool bicolorable = true;

        color[0] = 0;
        queue<int> q;
        q.push(0);

        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (int v : adj[u]) {
                if (color[v] == -1) {
                    color[v] = 1 - color[u];
                    q.push(v);
                } else if (color[v] == color[u]) {
                    bicolorable = false;
                }
            }
        }

        cout << (bicolorable ? "BICOLORABLE." : "NOT BICOLORABLE.") << "\n";
    }

    return 0;
}