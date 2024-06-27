#include <bits/stdc++.h>
using namespace std;

constexpr int base = 1<<19;
int pos[base][3];
int place[base][3];
int sm_def[base];
int scc[base];

bool isBetter(int a, int b){
    int points = 0;
    for(int i=0; i<3; i++) if(pos[a][i] < pos[b][i]) points++;
    return (points >= 2);
}

vector<int> ham_path[base*2];
int pos_in_ham_cycle[base];

int tree[base*2];
void setValue(int v, int value){
    v += base;
    tree[v] = value;
    v /= 2;
    while(v){
        tree[v] = min(tree[v*2], tree[v*2+1]);
        v /= 2;
    }
}

int minQuery(int a, int b){
    a += base-1; b += base+1;
    int res = base;
    while(a/2 != b/2){
        if(!(a&1)) res = min(res, tree[a+1]);
        if(b&1) res = min(res, tree[b-1]);
        a /= 2; b /= 2;
    }
    return res;
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int n, itr1, itr2, q, a, b;
    cin >> n;
    for(int j=0; j<3; j++){
        for(int i=0; i<n; i++){
            cin >> itr1;
            pos[i][j] = itr1 - 1;
        }
    }
    for(int i=0; i<n; i++) ham_path[base+i].push_back(i);
    for(int i=base-1; i>0; i--){
        itr1 = 0; itr2 = 0;
        while(itr1 != ham_path[i*2].size() && itr2 != ham_path[i*2+1].size()){
            if(isBetter(ham_path[i*2][itr1], ham_path[i*2+1][itr2])){
                ham_path[i].push_back(ham_path[i*2][itr1]);
                itr1++;
            }
            else{
                ham_path[i].push_back(ham_path[i*2+1][itr2]);
                itr2++;
            }
        }
        if(itr1 == ham_path[i*2].size()){
            for(; itr2<ham_path[i*2+1].size(); itr2++) ham_path[i].push_back(ham_path[i*2+1][itr2]);
        }
        else{
            for(; itr1<ham_path[i*2].size(); itr1++) ham_path[i].push_back(ham_path[i*2][itr1]);
        }
    }

    for(int i=0; i<n; i++) pos_in_ham_cycle[ham_path[1][i]] = i;

    for(int j=0; j<3; j++){
        for(int i=0; i<n; i++) place[pos[i][j]][j] = i;
    }

    for(int i=0; i<n; i++) sm_def[i] = base;

    for(int i=0; i<2*base; i++) tree[i] = base;
    for(int i=n-1; i>=0; i--){
        itr1 = place[i][0];
        itr2 = pos[itr1][1];
        a = minQuery(itr2, n+7);
        sm_def[itr1] = min(sm_def[itr1], a);
        setValue(itr2, pos_in_ham_cycle[itr1]);
    }

    for(int i=0; i<2*base; i++) tree[i] = base;
    for(int i=n-1; i>=0; i--){
        itr1 = place[i][1];
        itr2 = pos[itr1][2];
        a = minQuery(itr2, n+7);
        sm_def[itr1] = min(sm_def[itr1], a);
        setValue(itr2, pos_in_ham_cycle[itr1]);
    }

    for(int i=0; i<2*base; i++) tree[i] = base;
    for(int i=n-1; i>=0; i--){
        itr1 = place[i][0];
        itr2 = pos[itr1][2];
        a = minQuery(itr2, n+7);
        sm_def[itr1] = min(sm_def[itr1], a);
        setValue(itr2, pos_in_ham_cycle[itr1]);
    }

    itr1 = n-1; itr2 = 0;
    for(int i=n-1; i>=0; i--){
        a = ham_path[1][i];
        if(itr1 > i){
            itr2++;
            itr1 = i;
        }
        itr1 = min(itr1, sm_def[a]);
        scc[a] = itr2;
    }

    cin >> q;
    for(int i=0; i<q; i++){
        cin >> a >> b;
        a--; b--;
        cout << (scc[a] >= scc[b] ? "TAK\n" : "NIE\n");
    }
}