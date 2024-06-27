#include <bits/stdc++.h>
using namespace std;

#define ll long long

constexpr int base = 1 << 19;
ll tree[base*2+7][2];
ll lazy[base*2+7];
ll nums[base+7];
int n;

int q_st, q_en; ll q_val;
void add(int v, int v_st, int v_en){
    if(v_en < q_st || q_en < v_st) return;
    if(q_st <= v_st && v_en <= q_en){
        tree[v][0] += q_val;
        tree[v][1] += q_val;
        lazy[v] += q_val;
        return;
    }
    tree[v*2][0] += lazy[v];
    tree[v*2][1] += lazy[v];
    tree[v*2+1][0] += lazy[v];
    tree[v*2+1][1] += lazy[v];
    lazy[v*2] += lazy[v];
    lazy[v*2+1] += lazy[v];
    lazy[v] = 0;
    add(v*2, v_st, (v_st+v_en)/2);
    add(v*2+1, (v_st+v_en+1)/2, v_en);
    tree[v][0] = max(tree[v*2][0], tree[v*2+1][0]);
    tree[v][1] = max(tree[v*2][1], tree[v*2+1][1]);
}

int firstGeqV(ll num){
    if(tree[1][0]<num) return n;
    int v = 1;
    while(v<base){
        tree[v*2][0] += lazy[v];
        tree[v*2][1] += lazy[v];
        tree[v*2+1][0] += lazy[v];
        tree[v*2+1][1] += lazy[v];
        lazy[v*2] += lazy[v];
        lazy[v*2+1] += lazy[v];
        lazy[v] = 0;
        if(tree[v*2][0]>=num){
            v = v*2;
        }
        else{
            v = v*2+1;
        }
    }
    return v-base;
}

int lastLeqV(ll num){
    num ++;
    if(tree[1][0]<num) return n-1;
    int v = 1;
    while(v<base){
        tree[v*2][0] += lazy[v];
        tree[v*2][1] += lazy[v];
        tree[v*2+1][0] += lazy[v];
        tree[v*2+1][1] += lazy[v];
        lazy[v*2] += lazy[v];
        lazy[v*2+1] += lazy[v];
        lazy[v] = 0;
        if(tree[v*2][0]>=num){
            v = v*2;
        }
        else{
            v = v*2+1;
        }
    }
    return v-base-1;
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    for(int i=1; i<base*2; i++) tree[i][0] = LONG_LONG_MIN/10;
    for(int i=1; i<base*2; i++) tree[i][1] = LONG_LONG_MIN/10;
    int q, ppos;
    ll a, b, aux;
    cin >> n >> q;
    for(int i=0; i<n; i++){
        cin >> a;
        nums[i] = a;
    }
    sort(nums, nums+n);
    for(int i=0; i<n; i++) tree[base+i][0] = nums[i];
    for(int i=0; i<n; i++) tree[base+i][1] = nums[i] + n - i;
    for(int i=base-1; i>0; i--){
        tree[i][0] = max(tree[i*2][0], tree[i*2+1][0]);
        tree[i][1] = max(tree[i*2][1], tree[i*2+1][1]);
    }
    char c;
    // cout << firstGeqV(10) << '\n';
    // cout << lastLeqV(8) << '\n';
    // cout << firstGeqV(9)-1;
    for(int i=0; i<q; i++){
        // for(int j=1; j<base*2; j++) cout << tree[j][0] << ' '; cout << '\n';
        // for(int j=1; j<base*2; j++) cout << tree[j][1] << ' '; cout << '\n';
        // for(int j=1; j<base*2; j++) cout << lazy[j] << ' '; cout << '\n';
        cin >> c;
        if(c=='Z'){
            aux = tree[1][1]-n;
            cout << n-firstGeqV(aux) << '\n';
        }
        if(c=='B'){
            cin >> a >> b;
            q_st = firstGeqV(a);
            if(q_st>n-1) continue;
            q_en = n-1;
            q_val = b;
            add(1,0,base-1);
        }
        if(c=='K'){
            cin >> a >> b;
            q_st = 0;
            q_en = lastLeqV(a);
            if(q_en<0) continue;
            q_val = -b;
            add(1,0,base-1);
        }
    }
}