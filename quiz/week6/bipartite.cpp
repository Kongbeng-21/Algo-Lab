#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int k;
    cin >> k;

    while (k--) {
        int n, m;
        cin >> n >> m;

        vector<vector<int>> adj(n + 1);
        for (int i = 0; i < m; i++) {
            int u, v;
            cin >> u >> v;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }

        vector<int> color(n + 1, -1); 
        bool bipartite = true;

        for (int start = 1; start <= n; start++) {
            if (color[start] != -1) continue;

            color[start] = 0;
            queue<int> q;
            q.push(start);

            while (!q.empty()) {
                int u = q.front();
                q.pop();
                for (int v : adj[u]) {
                    if (color[v] == -1) {
                        color[v] = 1 - color[u];
                        q.push(v);
                    } else if (color[v] == color[u]) {
                        bipartite = false; 
                    }
                }
            }
        }

        cout << (bipartite ? "yes" : "no") << "\n";
    }

    return 0;
}