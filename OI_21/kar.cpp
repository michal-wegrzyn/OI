#include <bits/stdc++.h>
using namespace std;

constexpr int base = 1 << 18;
pair<int,int> tree[base*2+3];

int lvl;
void set_value(int v, pair<int,int> p){
    v  += base;
    tree[v] = p;
    v >>= 1;
    lvl = 0;
    while(v){
        if(tree[2*v].first == -1) tree[v].first = -1;
        else if(tree[2*v].first <= tree[(2*v+1)<<lvl].first) tree[v].first = tree[2*v+1].first;
        else if(tree[2*v].first <= tree[(2*v+1)<<lvl].second) tree[v].first = tree[2*v+1].second;
        else tree[v].first = -1;

        if(tree[2*v].second == -1) tree[v].second = -1;
        else if(tree[2*v].second <= tree[(2*v+1)<<lvl].first) tree[v].second = tree[2*v+1].first;
        else if(tree[2*v].second <= tree[(2*v+1)<<lvl].second) tree[v].second = tree[2*v+1].second;
        else tree[v].second = -1;

        v >>= 1;
        lvl++;
    }
}

pair<int,int> aux;

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int n, m, a, b;
    cin >> n;
    for(int i=0; i<n; i++){
        cin >> a >> b;
        if(a>b) swap(a, b);
        set_value(i,{a,b});
    }
    for(int i=n; i<base; i++) set_value(i, {INT_MAX, INT_MAX});
    cin >> m;
    for(int i=0; i<m; i++){
        cin >> a >> b;
        a--; b--;
        aux = tree[base+a];
        set_value(a, tree[base+b]);
        set_value(b, aux);
        cout << (tree[1].first == -1 ? "NIE\n" : "TAK\n");
    }
}