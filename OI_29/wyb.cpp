#include <bits/stdc++.h>
using namespace std;

constexpr int base = (1<<20);
int tree[base*2][5];
int lazy[base*2][5];
int aux[5];

int q_st, q_en, qa, qb;

inline void push(int v){
    for(int i=0; i<5; i++) aux[i] = 0;
    for(int i=0; i<5; i++) aux[lazy[v][i]] += tree[v*2][i];
    for(int i=0; i<5; i++) tree[v*2][i] = aux[i];
    for(int i=0; i<5; i++) lazy[v*2][i] = lazy[v][lazy[v*2][i]];

    for(int i=0; i<5; i++) aux[i] = 0;
    for(int i=0; i<5; i++) aux[lazy[v][i]] += tree[v*2+1][i];
    for(int i=0; i<5; i++) tree[v*2+1][i] = aux[i];
    for(int i=0; i<5; i++) lazy[v*2+1][i] = lazy[v][lazy[v*2+1][i]];

    for(int i=0; i<5; i++) lazy[v][i] = i;
}

int findPref(int count, int ch){
    int curr_count = 0;
    int v = 1;
    while(v<base){
        push(v);
        if(curr_count + tree[v*2][ch] < count){
            curr_count += tree[v*2][ch];
            v = v*2+1;
        }
        else v = v*2;
    }

    return v-base;
}

void changeChars(int v, int v_st, int v_en){
    if(v_en < q_st || q_en < v_st) return;
    if(q_st <= v_st && v_en <= q_en){
        tree[v][qb] += tree[v][qa];
        tree[v][qa] = 0;
        for(int i=0; i<5; i++){
            if(lazy[v][i] == qa) lazy[v][i] = qb;
        }
        return;
    }
    push(v);
    changeChars(v*2, v_st, (v_st+v_en-1)/2);
    changeChars(v*2+1, (v_st+v_en+1)/2, v_en);
    for(int i=0; i<5; i++) tree[v][i] = tree[v*2][i] + tree[v*2+1][i];
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int n, m, a;
    string s;
    char c1, c2;
    cin >> n >> m;
    cin >> s;

    for(int i=0; i<n; i++) tree[base+i][s[i]-'a'] = 1;
    for(int i=base-1; i>0; i--){
        for(int j=0; j<5; j++) tree[i][j] = tree[i*2][j] + tree[i*2+1][j];
    }
    for(int i=1; i<base*2; i++){
        for(int j=0; j<5; j++) lazy[i][j] = j;
    }

    for(int i=0; i<m; i++){
        cin >> a >> c1 >> c2;
        q_st = 0; q_en = findPref(a, c1-'a'); qa = c1-'a'; qb = c2-'a';
        changeChars(1, 0, base-1);
    }


    for(int i=1; i<base; i++) push(i);

    for(int i=0; i<n; i++){
        for(int j=0; j<5; j++){
            if(tree[base+i][j]){
                cout << (char)('a'+j);
                break;
            }
        }
    }
}