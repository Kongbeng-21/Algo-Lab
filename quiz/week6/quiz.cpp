#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <utility>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m, c;
    cin >> n >> m >> c;

    vector<pair<int,int>> edges(m);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        edges[i] = {u, v};
    }

    set<pair<int,int>> forbidden;
    for (int i = 0; i < c; i++) {
        int u, v;
        cin >> u >> v;
        forbidden.insert({u, v});
    }

    vector<vector<int>> adj(n + 1);
    for (auto &e : edges) {
        if (forbidden.count(e)) continue; 
        adj[e.first].push_back(e.second);
    }


    vector<int> dist(n + 1, -1);
    queue<int> q;
    dist[1] = 0;
    q.push(1);

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int v : adj[u]) {
            if (dist[v] == -1) {
                dist[v] = dist[u] + 1;
                q.push(v);
            }
        }
    }

    cout << dist[n] << "\n";
    return 0;
}