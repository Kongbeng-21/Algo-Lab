#include <iostream>
#include <vector>
using namespace std;

int N, M;
vector<vector<pair<int,int>>> adj; 
vector<int> disc, low, sz;
int timer_ = 0;
int best = 0;

void dfs(int u, int parentEdge) {
    disc[u] = low[u] = timer_++;
    sz[u] = 1;
    int childFailSum = 0;

    for (auto [v, eid] : adj[u]) {
        if (eid == parentEdge) continue;
        if (disc[v] == -1) {
            dfs(v, eid);
            sz[u] += sz[v];
            low[u] = min(low[u], low[v]);
            if (low[v] >= disc[u]) {
                childFailSum += sz[v];
            }
        } else {
            low[u] = min(low[u], disc[v]);
        }
    }

    if (u != 1) {
        best = max(best, childFailSum + 1);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N >> M;
    adj.assign(N + 1, {});
    for (int i = 0; i < M; i++) {
        int a, b;
        cin >> a >> b;
        adj[a].push_back({b, i});
        adj[b].push_back({a, i});
    }

    disc.assign(N + 1, -1);
    low.assign(N + 1, -1);
    sz.assign(N + 1, 0);

    dfs(1, -1);

    cout << best << "\n";
    return 0;
}