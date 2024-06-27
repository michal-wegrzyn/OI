#include <iostream>
using namespace std;

constexpr int base = 1 << 16;
int tree[(base<<1)+7];
int info_for_children[(base<<1)+7];

int p, k, l;

void add(int v, int v_start, int v_end){
    if(v_end<p || k<v_start) return;
    else if(p <= v_start && v_end <= k){
        tree[v] += l;
        info_for_children[v] += l;
    }
    else{
        tree[v<<1] += info_for_children[v];
        tree[(v<<1)+1] += info_for_children[v];
        info_for_children[v<<1] += info_for_children[v];
        info_for_children[(v<<1)+1] += info_for_children[v];
        info_for_children[v] = 0;
        add(v<<1, v_start, (v_start+v_end)>>1);
        add((v<<1)+1, ((v_start+v_end)>>1)+1, v_end);
        tree[v] = max(tree[v<<1], tree[(v<<1)+1]);
    }
}

int query(int v, int v_start, int v_end){
    if(v_end<p || k<v_start) return 0;
    else if(p <= v_start && v_end <= k) return tree[v];
    else{
        tree[v<<1] += info_for_children[v];
        tree[(v<<1)+1] += info_for_children[v];
        info_for_children[v<<1] += info_for_children[v];
        info_for_children[(v<<1)+1] += info_for_children[v];
        info_for_children[v] = 0;
        return max(query(v<<1, v_start, (v_start+v_end)>>1), query((v<<1)+1, ((v_start+v_end)>>1)+1, v_end));
    }
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n, m, z;
    cin >> n >> m >> z;
    for(int i=0; i<z; i++){
        cin >> p >> k >> l;
        k--;
        if(query(1, 0, base-1)+l>m) cout << 'N' << '\n';
        else{
            add(1, 0, base-1);
            cout << 'T' << '\n';
        }
    }
    return 0;
}