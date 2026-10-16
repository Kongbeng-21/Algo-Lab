/* ==========================================================
 * ไฟล์ที่ 1: SIMULATION (รวม 2D-array) — 10 ข้อ
 * ========================================================== */

/* ----------------------------------------------------------
 * TEMPLATE 1: SIMULATION (ทั่วไป)
 * ----------------------------------------------------------
 * สัญญาณ:
 * - โจทย์บรรยายขั้นตอน/เหตุการณ์เป็นลำดับ ให้ทำตามกติกาไปทีละสเต็ป
 * - ไม่มีทฤษฎีอัลกอริทึมพิเศษ คำตอบได้จากการรันตามกติกาตรง ๆ
 *
 * DECISION GUIDE (เลือกตามที่โจทย์บอกจริง):
 * ถ้าโจทย์พูดถึง...                            -> ใช้...
 * "คิว/แถวคน เข้าก่อนออกก่อน"                   -> list<T> หรือ queue<T>
 * "ตำแหน่ง/สิ่งของที่อ้างด้วย id คงที่"          -> vector<T>/array ขนาดคงที่ index = id
 * "ตาราง/กริด 2 มิติ"                           -> array 2 มิติ table[r][c]
 * "มี/ไม่มี สถานะหนึ่ง ๆ (ถือของอยู่ไหม)"        -> bool flag
 * "นับเงิน/คะแนน/จำนวนสะสม"                     -> long long accumulator (กันล้น)
 * "คำสั่งมีเลขระบุชัด (T=1,2,3..)"               -> if/else แยกตาม T ตรง ๆ (dispatch)
 * "ไม่มีเลขคำสั่ง แต่มีเงื่อนไข (ถ้า...จะ...)"   -> แปลงประโยคเงื่อนไขเป็น if/else ตรง ๆ
 * "มีข้อยกเว้น/ประโยคแปลกท้ายโจทย์"              -> เขียนเป็น if พิเศษแยกออกมาเสมอ
 *   (เช่น "วันแรกไม่ทำอะไร", "ไม่นับของที่ค้างท้ายสุด")
 *   ** ข้อนี้พลาดบ่อยที่สุด ให้เช็คทุกครั้ง **
 *
 * SKELETON (โครงที่ปรับใช้ได้ทุกข้อในหมวดนี้):
 *
 * #include <bits/stdc++.h>
 * using namespace std;
 * int main() {
 *     ios::sync_with_stdio(false); cin.tie(NULL);
 *     int n; cin >> n;
 *     // === เลือก state ตาม Decision guide ===
 *     for (int i = 0; i < n; i++) {
 *         // === เลือกรูปแบบ dispatch ตาม Decision guide ===
 *         // === เช็คว่ามีข้อยกเว้นที่ยังไม่ใส่ไหม ===
 *     }
 *     // === print ตาม format ที่โจทย์กำหนดเป๊ะ ===
 * }
 * ---------------------------------------------------------- */

// ===== ตัวอย่าง 1: Stock Bot (mid_stockbot) =====
#include <bits/stdc++.h>
using namespace std;
int main() {
    ios::sync_with_stdio(false); cin.tie(NULL);
    int n, k; cin >> n >> k;
    vector<long long> p(n);
    for (int i = 0; i < n; i++) cin >> p[i];
    bool holding = false;
    long long buyPrice = 0, profit = 0;
    for (int i = 1; i < n; i++) {
        long long diff = p[i] - p[i-1];
        if (diff >= k && !holding) { holding = true; buyPrice = p[i]; }
        else if (diff <= -k && holding) { holding = false; profit += p[i] - buyPrice; }
    }
    cout << profit << "\n";
}
// ตรวจแล้ว: 3 ตัวอย่างในโจทย์ -> 3, -40, -30 ตรงหมด

// ===== ตัวอย่าง 2: Accelerator (mid59_acc) =====
#include <bits/stdc++.h>
using namespace std;
int main(){
    ios::sync_with_stdio(false); cin.tie(NULL);
    int n,s; cin>>n>>s;
    vector<int> t(n);
    int maxT=0;
    vector<bool> ignite(10002,false);
    for(int i=0;i<n;i++){ cin>>t[i]; ignite[t[i]]=true; maxT=max(maxT,t[i]); }
    long long v=0, maxV=0;
    for(int cur=1; cur<=maxT+1; cur++){
        if(ignite[cur-1]) v += s;
        else v = max(v-1, 0LL);
        maxV = max(maxV, v);
    }
    cout << maxV << "\n";
}
// ตรวจแล้ว: ตัวอย่าง1->18, ตัวอย่าง2->9 ตรงทั้งคู่

// ===== ตัวอย่าง 3: Tiniest machines (mid59_tiny) =====
// หมายเหตุ: โครงสร้างใกล้ Linked List มากกว่า — ย้ายไปไฟล์ 3 ได้ถ้าสะดวกกว่า
#include <bits/stdc++.h>
using namespace std;
int main(){
    ios::sync_with_stdio(false); cin.tie(NULL);
    int n,m; cin>>n>>m;
    list<int> lst;
    for(int i=0;i<n;i++){ int x; cin>>x; lst.push_back(x); }
    auto cur = lst.begin();
    for(int q=0;q<m;q++){
        int t; cin>>t;
        if(t==1){ auto nxt = next(cur); if(nxt != lst.end()) cur = nxt; }
        else if(t==2){ cur = lst.begin(); }
        else if(t==3){
            int k; cin>>k;
            auto it = next(cur);
            while(k-- > 0 && it != lst.end()) it = lst.erase(it);
        } else {
            int l; cin>>l;
            auto pos = next(cur);
            for(int i=0;i<l;i++){ int v; cin>>v; lst.insert(pos, v); }
        }
    }
    bool first=true;
    for(int v : lst){ if(!first) cout << " "; cout << v; first=false; }
    cout << "\n";
}
// ตรวจแล้ว: เดินตามตัวอย่าง 3 ในโจทย์ทีละ op ตรงกับ "1 4 2 1 4 2 1 3 2"

// ===== ตัวอย่าง 4: Climb (mid64_climb) =====
#include <bits/stdc++.h>
using namespace std;
int main(){
    ios::sync_with_stdio(false); cin.tie(NULL);
    int n; cin>>n;
    long long prevH=0, total=0, streak=0;
    for(int i=0;i<n;i++){
        long long h; cin>>h;
        if(h > prevH){ total += (h - prevH) + streak; streak++; }
        else streak = 0;
        prevH = h;
    }
    cout << total << "\n";
}
// ตรวจแล้ว: ตัวอย่างในโจทย์ -> 29 ตรง

// ===== ตัวอย่าง 5: LLM Accounts (mid68_llm) =====
#include <bits/stdc++.h>
using namespace std;
int main(){
    ios::sync_with_stdio(false); cin.tie(NULL);
    int n,m; cin>>n>>m;
    vector<long long> X(n), Q(n);
    for(int i=0;i<n;i++) cin>>X[i]>>Q[i];
    long long totalPay=0; int discarded=0;
    for(int q=0;q<m;q++){
        long long T,R; cin>>T>>R;
        int best=-1;
        for(int j=0;j<n;j++)
            if(Q[j]>=R && X[j]>=T)
                if(best==-1 || Q[j]<Q[best]) best=j;
        if(best==-1) discarded++;
        else { X[best]-=T; totalPay += T*Q[best]; }
    }
    cout << totalPay << " " << discarded << "\n";
}
// ตรวจแล้ว: ตัวอย่างในโจทย์ -> "31600 1" ตรง

// ===== ตัวอย่าง 6: Buckets (mid_buckets) =====
#include <bits/stdc++.h>
using namespace std;
int main(){
    ios::sync_with_stdio(false); cin.tie(NULL);
    int n; cin>>n;
    long long amt[5]={0,0,0,0,0}, tank=0;
    for(int i=0;i<n;i++){
        long long x; cin>>x;
        int idx=0;
        for(int b=1;b<5;b++) if(amt[b]<amt[idx]) idx=b;
        long long canTake = min(x, 1000-amt[idx]);
        amt[idx]+=canTake;
        if(amt[idx]==1000){ tank+=1000; amt[idx]=0; }
    }
    cout << tank << "\n";
}
// ตรวจแล้ว: ตัวอย่างในโจทย์ -> 2000 ตรง

// ===== ตัวอย่าง 7: Broken Tretis (mid_practice_tretis) =====
#include <bits/stdc++.h>
using namespace std;
int main(){
    ios::sync_with_stdio(false); cin.tie(NULL);
    int n; cin>>n;
    vector<long long> height(14, 0);
    long long maxHeight = 0;
    for(int i=0;i<n;i++){
        char type; int c; cin >> type >> c;
        int width, h;
        if(type=='-'){ width=4; h=1; }
        else if(type=='i'){ width=1; h=4; }
        else { width=2; h=2; }
        long long base = 0;
        for(int col=c; col<c+width; col++) base = max(base, height[col]);
        for(int col=c; col<c+width; col++) height[col] = base + h;
        maxHeight = max(maxHeight, base + h);
    }
    cout << maxHeight << "\n";
}
// ตรวจแล้ว: ตัวอย่าง1->6, ตัวอย่าง2->2 ตรงทั้งคู่
// ข้อควรระวัง: ไม่แน่ใจว่าชิ้นชนขอบขวา (col เกิน10) จะเกิดอะไรขึ้น -> array กันไว้ล่วงหน้า


/* ----------------------------------------------------------
 * TEMPLATE 2: 2D-ARRAY (2 เทคนิคย่อย)
 * ----------------------------------------------------------
 * สัญญาณ: โจทย์ให้ตาราง/กริด 2 มิติเป็น input หลัก
 *
 * DECISION GUIDE:
 * ถ้าโจทย์ถามว่า...                                       -> ใช้เทคนิค...
 * "หมุน/สลับแถวหรือคอลัมน์ได้ แล้วหาคะแนนดีที่สุด"         -> 2A: Rotation Search
 * "ตารางควรมี sum เท่ากันทุกแถว/คอลัมน์ แต่ผิดปกติ 1 จุด"  -> 2B: Sum-Consistency Check
 * "นับ/รวมค่าตามแถว-คอลัมน์ธรรมดา ไม่มีหมุน/ไม่มี sum คงที่" -> ไม่เข้าหมวดนี้ เช็คไฟล์ 5 แทน
 *
 * ถ้าใช้ 2A ต่อเลือกย่อย:
 *   N เล็กมาก (<=4-6)        -> แบบ implicit (เร็วกว่า)
 *   N ใหญ่ขึ้นหน่อยแต่ brute-force ได้ -> แบบ explicit (เขียน/debug ง่ายกว่า)
 * ---------------------------------------------------------- */

// ===== 2A: Rotation Search — Rotating Slot Machine (mid64_slot) =====
#include <bits/stdc++.h>
using namespace std;
int table_slot[4][4];
int compute_score(int a0, int a1, int a2, int a3) {
    int shift[4] = {a0, a1, a2, a3};
    int score = 0;
    for (int r = 0; r < 4; r++) {
        int v = table_slot[(r + shift[0]) % 4][0];
        bool allSame = true;
        for (int c = 1; c < 4; c++)
            if (table_slot[(r + shift[c]) % 4][c] != v) { allSame = false; break; }
        if (allSame) score++;
    }
    return score;
}
int main_slot() {
    for (int r = 0; r < 4; r++) for (int c = 0; c < 4; c++) cin >> table_slot[r][c];
    int mx = 0;
    for (int a1 = 0; a1 < 4; a1++)
        for (int a2 = 0; a2 < 4; a2++)
            for (int a3 = 0; a3 < 4; a3++)
                mx = max(mx, compute_score(0, a1, a2, a3));
    cout << mx << "\n";
    return 0;
}
// ตรวจแล้ว: ตรงกับทั้ง 4 ตัวอย่างในโจทย์ (2, 4, 3, 4)

// ===== 2B: Sum-Consistency Check — Wrong Number (mid63_table) =====
#include <bits/stdc++.h>
using namespace std;
int main_table(){
    ios::sync_with_stdio(false); cin.tie(NULL);
    int n; cin >> n;
    vector<vector<long long>> t(n, vector<long long>(n));
    for(int i=0;i<n;i++) for(int j=0;j<n;j++) cin >> t[i][j];
    vector<long long> rowSum(n,0), colSum(n,0);
    for(int i=0;i<n;i++) for(int j=0;j<n;j++){ rowSum[i]+=t[i][j]; colSum[j]+=t[i][j]; }
    map<long long,int> freq;
    for(int i=0;i<n;i++) freq[rowSum[i]]++;
    long long modeSum=-1; int best=0;
    for(auto& p : freq) if(p.second>best){ best=p.second; modeSum=p.first; }
    int badRow=-1, badCol=-1;
    for(int i=0;i<n;i++) if(rowSum[i]!=modeSum) badRow=i;
    for(int j=0;j<n;j++) if(colSum[j]!=modeSum) badCol=j;
    cout << t[badRow][badCol] << "\n";
    return 0;
}
// ตรวจแล้ว: ตัวอย่างในโจทย์ -> 5 ตรง