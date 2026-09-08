#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n, r;
    cin >> n >> r;

    int total = n + 2;
    vector<int> x(total), y(total);
    x[0] = 0; y[0] = 0;
    for (int i = 1; i <= n; i++) cin >> x[i] >> y[i];
    x[n + 1] = 100; y[n + 1] = 100;

    long long R2 = (long long)r * r;

    vector<vector<int>> adj(total);
    for (int i = 0; i < total; i++) {
        for (int j = i + 1; j < total; j++) {
            long long dx = x[i] - x[j];
            long long dy = y[i] - y[j];
            if (dx * dx + dy * dy <= R2) {
                adj[i].push_back(j);
                adj[j].push_back(i);
            }
        }
    }

    vector<int> dist(total, -1);
    dist[0] = 0;
    queue<int> q;
    q.push(0);
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

    cout << dist[n + 1] << "\n";
    return 0;
}