# Algo Lab (01219212) Midterm Cheat Sheet — 19 Oct 2026

เปิดไฟล์นี้ค้างไว้ในห้องสอบได้เลย (เปิดคอมดูได้) ใช้ LLM ของอาจารย์ช่วย syntax ได้ แต่การเลือก pattern/เขียน logic หลักต้องทำเอง — ไฟล์นี้คือส่วนที่ตอบโจทย์ตรงนั้น

## ขั้นตอนอ่านโจทย์ใหม่ (ทำก่อนเขียนโค้ดบรรทัดแรก)

ไล่เช็คสัญญาณจาก 17 pattern ด้านล่างนี้ก่อน (D1-D5 = กราฟ, E1-E12 = ไม่ใช่กราฟ) ถ้าไม่ตรงอันไหนเลย ให้ทำ 3 ขั้นตอนนี้:

1. **ดู constraints ก่อนอ่านรายละเอียด** — N,M ขนาดเท่าไหร่ (บอก complexity ที่รับได้), มี Q queries ไหม (ต้อง precompute ไหม)
2. **ดูลักษณะข้อมูล** — เป็นกราฟไหม (edge weight เท่ากัน/ต่างกัน/0-1), เป็น array/string ที่ต้อง sort/stack/linked-list ไหม, ตัวเลข constraint เล็กผิดปกติไหม (≤10 = brute force)
3. **ดูว่าโจทย์ถามอะไรจริงๆ** — ระยะทาง/จำนวนกลุ่ม/ค่ามากสุด/ตำแหน่งที่ผิด

**กลยุทธ์คะแนน:** ทุกโจทย์ที่มี "Scoring/Subtask" บอก % ไว้ ให้เขียน brute-force ง่ายๆ เก็บ subtask นั้นก่อนเสมอ แล้วค่อยพัฒนาเป็น optimal ถ้าเวลาเหลือ — อย่าข้ามไปเขียน optimal เลยจนไม่มีอะไรส่ง

---

# กราฟ (D1-D5)

## D1 — Multi-source BFS (กระจายพร้อมกันจากหลายจุด)
**สัญญาณ:** "จุด K จุดเริ่มพร้อมกัน" "ลามทุกวินาที" (ไฟไหม้ น้ำท่วม) ถามเวลานานสุดกว่าจะถึงทุกที่

```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int N, K;
    cin >> N >> K;   // N = ขนาดกริด/จำนวนจุด, K = จำนวนจุดเริ่ม

    vector<int> dist(N * N, -1);
    queue<pair<int,int>> q;

    for (int i = 0; i < K; i++) {
        int r, c;
        cin >> r >> c;
        r--; c--;                       // << แก้ถ้าไม่ใช่ 1-indexed
        dist[r * N + c] = 0;
        q.push({r, c});
    }

    int dr[] = {-1, 1, 0, 0};
    int dc[] = {0, 0, -1, 1};           // << แก้ถ้าเดินได้ 8 ทิศ
    int ans = 0;

    while (!q.empty()) {
        auto [r, c] = q.front(); q.pop();
        ans = max(ans, dist[r * N + c]);
        for (int k = 0; k < 4; k++) {
            int nr = r + dr[k], nc = c + dc[k];
            if (nr < 0 || nr >= N || nc < 0 || nc >= N) continue;
            if (dist[nr * N + nc] != -1) continue;
            dist[nr * N + nc] = dist[r * N + c] + 1;
            q.push({nr, nc});
        }
    }

    cout << ans << "\n";
    return 0;
}
```
**แก้ตามโจทย์:** ขนาดกริด, จำนวนทิศ, เงื่อนไขห้ามเดิน (กำแพง), สิ่งที่ต้องตอบ

---

## D2 — Layered BFS (เดินทางฟรีภายในกลุ่ม/สาย)
**สัญญาณ:** มี "สาย/กลุ่ม" ที่สมาชิกเชื่อมถึงกันฟรี (รถเมล์, เที่ยวบิน) ถามเปลี่ยนกลุ่มน้อยที่สุดกี่ครั้ง

```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int N, M, S, T;
    cin >> N >> M >> S >> T;

    vector<vector<int>> pointToGroup(N + 1);
    vector<vector<int>> groupPoints(M + 1);

    for (int i = 1; i <= M; i++) {
        int L;
        cin >> L;
        groupPoints[i].resize(L);
        for (int j = 0; j < L; j++) {
            cin >> groupPoints[i][j];
            pointToGroup[groupPoints[i][j]].push_back(i);
        }
    }

    vector<int> dist(N + 1, -1);
    vector<bool> groupUsed(M + 1, false);
    queue<int> q;
    dist[S] = 0;
    q.push(S);

    while (!q.empty()) {
        int u = q.front(); q.pop();
        if (u == T) break;
        for (int g : pointToGroup[u]) {
            if (groupUsed[g]) continue;
            groupUsed[g] = true;
            for (int v : groupPoints[g]) {
                if (dist[v] == -1) {
                    dist[v] = dist[u] + 1;
                    q.push(v);
                }
            }
        }
    }

    cout << dist[T] << "\n";
    return 0;
}
```
**แก้ตามโจทย์:** ความหมายของ "จุด"/"กลุ่ม", ตอบไป T จุดเดียวหรือทุกจุด (ลบ `if(u==T) break;` ถ้าทุกจุด)

---

## D3 — Multi-query BFS ที่กติกาเปลี่ยนต่อคำถาม
**สัญญาณ:** มี Q คำถาม แต่ละคำถามมีพารามิเตอร์ที่ทำให้ "เดินผ่านได้ไหม" เปลี่ยนไป

```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int N, M, Q;
    cin >> N >> M >> Q;

    vector<array<int,3>> edges(M);
    vector<vector<int>> adj(N + 1);
    for (int j = 0; j < M; j++) {
        int u, v, d;
        cin >> u >> v >> d;
        edges[j] = {u, v, d};
        adj[u].push_back(j);
        adj[v].push_back(j);
    }

    while (Q--) {
        long long B;
        cin >> B;

        vector<int> dist(N + 1, -1);
        queue<int> q;
        dist[1] = 0;                   // << แก้จุดเริ่มถ้าไม่ใช่โหนด 1
        q.push(1);
        int best = 0;

        while (!q.empty()) {
            int u = q.front(); q.pop();
            best = max(best, dist[u]);
            for (int idx : adj[u]) {
                if (edges[idx][2] > B) continue;   // << แก้เงื่อนไขกรอง
                int v = (edges[idx][0] == u) ? edges[idx][1] : edges[idx][0];
                if (dist[v] == -1) {
                    dist[v] = dist[u] + 1;
                    q.push(v);
                }
            }
        }
        cout << best << "\n";
    }
    return 0;
}
```
**แก้ตามโจทย์:** เงื่อนไขกรอง edge, สิ่งที่ตอบต่อ query. ถ้า N,M,Q ใหญ่มากพร้อมกัน อาจ TLE ต้องคิด Union-Find แบบ offline แทน

---

## D4 — Precompute 2 ทาง + เลือกคู่ที่ไม่ซ้ำกัน
**สัญญาณ:** หา "ผลรวมมากสุดจากการเลือก 2 จุดคนละตำแหน่งกัน" (เริ่มจาก A ไปจุดหนึ่ง, เริ่มจาก B ไปอีกจุด ห้ามซ้ำกัน)

```cpp
#include <bits/stdc++.h>
using namespace std;

vector<int> bfsFrom(int src, int N, vector<vector<int>>& adj) {
    vector<int> dist(N + 1, -1);
    queue<int> q;
    dist[src] = 0;
    q.push(src);
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int v : adj[u]) {
            if (dist[v] == -1) {
                dist[v] = dist[u] + 1;
                q.push(v);
            }
        }
    }
    return dist;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int N, M;
    cin >> N >> M;

    vector<long long> P(N + 1);
    for (int i = 1; i <= N; i++) cin >> P[i];

    vector<vector<int>> adj(N + 1);
    for (int i = 0; i < M; i++) {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    vector<int> distA = bfsFrom(1, N, adj);   // << แก้จุดเริ่มฝั่ง A
    vector<int> distB = bfsFrom(N, N, adj);   // << แก้จุดเริ่มฝั่ง B

    long long bestA = -1, bestA2 = -1; int bestAi = -1, bestA2i = -1;
    long long bestB = -1, bestB2 = -1; int bestBi = -1, bestB2i = -1;

    for (int i = 1; i <= N; i++) {
        long long vA = distA[i] + P[i];
        if (vA > bestA) { bestA2 = bestA; bestA2i = bestAi; bestA = vA; bestAi = i; }
        else if (vA > bestA2) { bestA2 = vA; bestA2i = i; }

        long long vB = distB[i] + P[i];
        if (vB > bestB) { bestB2 = bestB; bestB2i = bestBi; bestB = vB; bestBi = i; }
        else if (vB > bestB2) { bestB2 = vB; bestB2i = i; }
    }

    long long ans;
    if (bestAi != bestBi) {
        ans = bestA + bestB;
    } else {
        ans = max(bestA + bestB2, bestA2 + bestB);
    }

    cout << ans << "\n";
    return 0;
}
```
**แก้ตามโจทย์:** จุดเริ่มทั้งสองฝั่ง, สูตรคำนวณค่า, เงื่อนไขห้ามซ้ำ

---

## D5 — Articulation Points / Bridges (DFS low-link)
**สัญญาณ:** "ตัดจุด/เส้นนี้ออกแล้วบางจุดติดต่อกันไม่ได้ไหม" "จุด/เส้นไหนเป็น critical"

```cpp
#include <bits/stdc++.h>
using namespace std;

int N, M, timer_;
vector<vector<int>> adj;
vector<int> disc, low;
vector<bool> visited, isArticulation;

void dfs(int u, int parent) {
    visited[u] = true;
    disc[u] = low[u] = timer_++;
    int children = 0;

    for (int v : adj[u]) {
        if (v == parent) continue;
        if (visited[v]) {
            low[u] = min(low[u], disc[v]);
        } else {
            children++;
            dfs(v, u);
            low[u] = min(low[u], low[v]);
            if (parent != -1 && low[v] >= disc[u]) isArticulation[u] = true;
            // bridge แทน: if (low[v] > disc[u]) { เส้น (u,v) คือ bridge }
        }
    }
    if (parent == -1 && children > 1) isArticulation[u] = true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N >> M;
    adj.assign(N + 1, {});
    disc.assign(N + 1, -1);
    low.assign(N + 1, -1);
    visited.assign(N + 1, false);
    isArticulation.assign(N + 1, false);
    timer_ = 0;

    for (int i = 0; i < M; i++) {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    for (int i = 1; i <= N; i++) if (!visited[i]) dfs(i, -1);

    int count = 0;
    for (int i = 1; i <= N; i++) if (isArticulation[i]) count++;
    cout << count << "\n";
    return 0;
}
```
**แก้ตามโจทย์:** ถามจุดหรือเส้น (สลับเงื่อนไขในคอมเมนต์)

---

## เครื่องมือสำรองกราฟ (ไม่ตรง D1-D5 เลย)

**Dijkstra (edge weight ไม่เท่ากัน):**
```cpp
vector<long long> dist(N + 1, LLONG_MAX);
priority_queue<pair<long long,int>, vector<pair<long long,int>>, greater<>> pq;
dist[S] = 0; pq.push({0, S});
while (!pq.empty()) {
    auto [d, u] = pq.top(); pq.pop();
    if (d > dist[u]) continue;
    for (auto [v, w] : adj[u]) {
        if (dist[u] + w < dist[v]) { dist[v] = dist[u] + w; pq.push({dist[v], v}); }
    }
}
```

**0-1 BFS (edge weight แค่ 0/1):**
```cpp
deque<int> dq;
vector<int> dist(N + 1, -1);
dist[S] = 0; dq.push_back(S);
while (!dq.empty()) {
    int u = dq.front(); dq.pop_front();
    for (auto [v, w] : adj[u]) {
        if (dist[v] == -1 || dist[u] + w < dist[v]) {
            dist[v] = dist[u] + w;
            if (w == 0) dq.push_front(v); else dq.push_back(v);
        }
    }
}
```

**Union-Find (นับกลุ่ม/เชื่อมกันไหม):**
```cpp
vector<int> par(N + 1);
iota(par.begin(), par.end(), 0);
function<int(int)> find = [&](int x) { return par[x] == x ? x : par[x] = find(par[x]); };
auto unite = [&](int a, int b) { par[find(a)] = find(b); };
```

**Topological sort + DAG DP:**
```cpp
vector<int> indeg(N + 1, 0);
for (int u = 1; u <= N; u++) for (int v : adj[u]) indeg[v]++;
queue<int> q;
for (int i = 1; i <= N; i++) if (indeg[i] == 0) q.push(i);
vector<int> order;
while (!q.empty()) {
    int u = q.front(); q.pop();
    order.push_back(u);
    for (int v : adj[u]) if (--indeg[v] == 0) q.push(v);
}
```

---

# ไม่ใช่กราฟ (E1-E12)

## E1 — Insert/Delete ที่ตำแหน่ง k (k เล็กมาก)
**สัญญาณ:** แทรก/ลบที่ตำแหน่ง k (≤5-10) จำนวนคำสั่งเยอะ (1e5+)
```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int T;
    cin >> T;
    list<long long> items;   // list ไม่ใช่ vector

    for (int q = 0; q < T; q++) {
        int L;
        cin >> L;
        if (L == 1) {
            int k; long long x;
            cin >> k >> x;
            auto it = items.begin();
            for (int s = 0; s < k && it != items.end(); s++) it++;
            items.insert(it, x);
        } else {
            int k;
            cin >> k;
            auto it = items.begin();
            for (int s = 0; s < k - 1 && it != items.end(); s++) it++;
            if (it != items.end()) items.erase(it);
        }
    }
    for (long long x : items) cout << x << "\n";
    return 0;
}
```
แบบ circular (Josephus): ใช้ list เหมือนเดิม แต่ wrap iterator กลับ begin() เมื่อถึง end()

## E2 — Monotonic Stack: ลบ K ตัวให้ผลลัพธ์ดีที่สุด
**สัญญาณ:** "ลบตัวเลขออก K ตัว ให้เหลือเล็กสุด/มากสุด"
```cpp
string s; int k;
cin >> s >> k;
string stk;
for (char c : s) {
    while (!stk.empty() && k > 0 && stk.back() > c) { stk.pop_back(); k--; }  // สลับ > เป็น < ถ้าเอามากสุด
    stk.push_back(c);
}
while (k-- > 0) stk.pop_back();
int start = 0;
while (start < (int)stk.size() - 1 && stk[start] == '0') start++;
cout << stk.substr(start) << "\n";
```

## E3 — Stack ลบของเหมือนกัน K ตัวติดกัน
**สัญญาณ:** "K ตัวติดกันค่าเดียวกันแล้วหายไป" (match elimination)
```cpp
vector<pair<int,long long>> stk;  // {value, count}
for (int i = 0; i < N; i++) {
    long long x; cin >> x;
    if (!stk.empty() && stk.back().first == x) stk.back().second++;
    else stk.push_back({(int)x, 1});
    if (stk.back().second == K) stk.pop_back();
}
long long total = 0;
for (auto& [v, c] : stk) total += c;
```

## E4 — Postfix / RPN Stack Evaluator
**สัญญาณ:** คำนวณนิพจน์ postfix หรือทำตามคำสั่ง push/combine บน stack
```cpp
string token;
vector<double> stk;
while (cin >> token) {
    if (isdigit(token[0]) || (token.size() > 1 && token[0] == '-')) {
        stk.push_back(stod(token));
    } else {
        double b = stk.back(); stk.pop_back();
        double a = stk.back(); stk.pop_back();
        double res;
        if (token == "+") res = a + b;
        else if (token == "-") res = a - b;
        else if (token == "*") res = a * b;
        else res = a / b;
        stk.push_back(res);
    }
}
cout << stk.back() << "\n";
```

## E5 — ลบช่วงระหว่างคู่ที่ค่าตรงกัน
**สัญญาณ:** "เจอค่าเท่ากับตัวก่อนหน้า ลบทุกตัวระหว่างกลางทิ้ง"
```cpp
vector<long long> stk;
for (int i = 0; i < N; i++) {
    if (!stk.empty() && stk.back() == a[i]) stk.pop_back();   // คู่ติดกัน
    else stk.push_back(a[i]);
}
cout << stk.size() << "\n";
```
ถ้าต้องลบทั้งช่วง (ไม่ติดกัน) ใช้ map เก็บตำแหน่งล่าสุดที่เจอค่านี้ แล้ว erase ทุกตัวตั้งแต่ตำแหน่งนั้นถึงปัจจุบัน

## E6 — Greedy + Prefix Sum (เลือกทิ้ง K ตัว)
**สัญญาณ:** "ทิ้ง K ตัว (K เล็ก เช่น 0,1,2) ให้ผลรวมที่เหลือดีสุด"
```cpp
sort(val.begin(), val.end());
long long ans = total;
for (int i = 0; i < K && i < N; i++) {
    if (val[i] < 0) ans -= val[i];
}
```

## E7 — Sort + Custom Comparator / Counting ความถี่
**สัญญาณ:** "จัดเรียงตามความถี่" "นับคู่ชนะ/แพ้/เสมอ"
```cpp
map<int,int> freq;
for (auto& x : a) freq[x]++;
vector<pair<int,int>> items(freq.begin(), freq.end());
sort(items.begin(), items.end(), [](auto& p1, auto& p2) {
    if (p1.second != p2.second) return p1.second > p2.second;
    return p1.first < p2.first;
});
```
นับคู่ชนะ/แพ้: sort แล้วใช้ lower_bound/upper_bound แทน O(N²)

## E8 — Two-pointer / Binary Search บน Array ที่ Sort แล้ว
**สัญญาณ:** "นับคู่ที่ผลรวม≥S และผลต่าง≤T"
```cpp
sort(a.begin(), a.end());
long long count = 0;
for (int i = 0; i < N; i++) {
    int lo = i + 1, hi = N - 1, pos = N;
    while (lo <= hi) {
        int mid = (lo + hi) / 2;
        if (a[i] + a[mid] >= S) { pos = mid; hi = mid - 1; }
        else lo = mid + 1;
    }
    count += max(0, N - pos);
}
```
ถ้า N เล็ก ใช้ O(N²) brute-force ตรงๆ ได้คะแนนบางส่วนเสมอ

## E9 — Simulation ทีละ Step
**สัญญาณ:** บรรยายเหตุการณ์ทีละวินาที/ทีละตา มีกติกาเปลี่ยนสถานะชัดเจน
```cpp
long long energy = 0, speed = 0, consecutiveCount = 0, best = 0;
for (int i = 0; i < N; i++) {
    long long event; cin >> event;
    // << ใส่กติกาเปลี่ยนสถานะตามโจทย์ตรงนี้ >>
    best = max(best, energy);
}
```
ตัวแปรสถานะมักมี 2-4 ตัว (speed, energy, จำนวนครั้งติดต่อกัน, ถือของอยู่ไหม)

## E10 — Number Theory: Prime Factors / GCD
**สัญญาณ:** "หาจำนวนตัวประกอบเฉพาะ" N ≤ 1e6-1e9
```cpp
long long N; cin >> N;
int distinctFactors = 0;
for (long long p = 2; p * p <= N; p++) {
    if (N % p == 0) {
        distinctFactors++;
        while (N % p == 0) N /= p;
    }
}
if (N > 1) distinctFactors++;
```
GCD: `__gcd(a,b)` ใช้ได้เลยใน C++

## E11 — Brute-force บน Constraint เล็กมาก
**สัญญาณ:** ตัวเลขในโจทย์เล็กผิดสังเกต (≤4, ≤10, ≤20)
```cpp
int best = 0;
for (int offset = 0; offset < 4; offset++) {
    vector<int> bucket(4, 0);
    for (int i = 0; i < N; i++) {
        int shifted = ((a[i] + offset) % 4 + 4) % 4;
        bucket[shifted]++;
    }
    best = max(best, *max_element(bucket.begin(), bucket.end()));
}
```

## E12 — Ad-hoc Math / Invariant (ไม่มี template ตายตัว)
**สัญญาณ:** "ผลรวมแถว/คอลัมน์ควรเท่ากัน" หาตัวที่ทำให้ค่าคงที่พัง

วิธีคิด: หาค่าคงที่ที่ควรจะจริงเสมอ (คำนวณจากข้อมูลส่วนใหญ่ที่ตรงกัน) → หาตำแหน่งที่ไม่ตรงกับค่านั้น → constraint มักเล็ก (N≤30-100) ใช้ O(N²) ตรงๆ ได้

---

## E13 — Array / Interval Scanning

**สัญญาณ:** เดินสแกน array ทีละช่อง เพื่อหา "ช่วงที่ราบเรียบ/ที่ราบสูง" (plateau) ที่ถูกขอบเขตด้วยค่าที่สูง/ต่ำกว่า หรือ "ทำเครื่องหมายทับซ้อนของช่วง [L,R] หลายช่วง" แล้วถามว่าช่องไหนถูกทับกี่ครั้ง/ถูกทับอย่างน้อย 1 ครั้งกี่ช่อง

**แบบที่ 1 — หา run ที่ราบเรียบ ขอบเขตด้วยเพื่อนบ้าน:**
```cpp
int N; cin >> N;
vector<long long> a(N);
for (auto& x : a) cin >> x;

int count = 0;
int i = 0;
while (i < N) {
    int j = i;
    while (j + 1 < N && a[j+1] == a[i]) j++;   // หา run ของค่าเดียวกัน [i..j]
    bool leftHigher  = (i == 0)     || a[i-1] > a[i];
    bool rightHigher = (j == N - 1) || a[j+1] > a[j];
    // << ปรับเงื่อนไขตามโจทย์ (plateau/swamp ต้องถูกขอบด้วยค่าสูงกว่าทั้งสองฝั่ง เป็นต้น)
    if (leftHigher && rightHigher) count++;
    i = j + 1;
}
cout << count << "\n";
```

**แบบที่ 2 — Interval marking ด้วย diff array (เร็วกว่าการ mark ทีละช่องตรงๆ เมื่อ L ใหญ่):**
```cpp
int L, N;
cin >> L >> N;              // L = ความยาวเส้น/พื้นที่, N = จำนวนช่วง
vector<long long> diff(L + 2, 0);
for (int i = 0; i < N; i++) {
    int l, r;
    cin >> l >> r;           // ช่วง [l, r] ถูกปกคลุม
    diff[l]++;
    diff[r + 1]--;
}
long long covered = 0, running = 0;
for (int i = 0; i < L; i++) {
    running += diff[i];
    if (running > 0) covered++;   // ช่องนี้ถูกทับอย่างน้อย 1 ครั้ง
}
cout << covered << "\n";
```
ถ้า L เล็ก (≤3000) ทำ brute-force mark ทีละช่องตรงๆ ด้วย `for l..r: mark[i]=true` ก็พอ ไม่ต้องทำ diff array ก็ได้คะแนนเต็ม

**จุดที่ต้องแก้ตามโจทย์:** เงื่อนไขขอบเขตของ run (แบบที่ 1), นับ "ถูกทับอย่างน้อย 1 ครั้ง" หรือ "นับจำนวนครั้งที่ทับพอดี" (แบบที่ 2 — ถ้านับจำนวนครั้ง ใช้ `running` แทน `covered` ตรงๆ)

---

# เช็คลิสต์ก่อนส่งทุกข้อ

array +1 เผื่อ 1-indexed เสมอ, ตัวแปรผลรวม/คะแนนใช้ `long long`, อ่าน input ให้ครบ, เช็คทุกโหนดเผื่อกราฟไม่ connected, `ios::sync_with_stdio(false); cin.tie(NULL);` ทุกครั้ง, ท้ายสุดไล่เทียบ output format กับตัวอย่างให้ตรงเป๊ะ (เว้นบรรทัด/วรรค/ตัวพิมพ์)
