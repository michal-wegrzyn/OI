#include <bits/stdc++.h>
using namespace std;

int trains[300007];
int sub[300007];
vector<int> color_pos[300007];
int l_prefix[300007];
int l_sufix[300007];

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int n, m, k, a;
    cin >> n >> m >> k;
    for(int i=1; i<=n; i++){
        cin >> a;
        trains[i] = a;
    }
    for(int i=1; i<=m; i++){
        cin >> a;
        sub[i] = a;
        color_pos[a].push_back(i);
    }
    a = 0;
    for(int i=1; i<=n; i++){
        if(sub[a+1] == trains[i]) a++;
        l_prefix[i] = a;
    }
    a = m+1;
    for(int i=n; i>0; i--){
        if(sub[a-1] == trains[i]) a--;
        l_sufix[i] = a;
    }
    for(int i=1; i<=n; i++){
        if(lower_bound(color_pos[trains[i]].begin(), color_pos[trains[i]].end(), l_sufix[i]) == color_pos[trains[i]].end()){
            cout << 0 << ' ';
            continue;
        }
        if((*(lower_bound(color_pos[trains[i]].begin(), color_pos[trains[i]].end(), l_sufix[i]))) - l_prefix[i-1] <= 1) cout << 1 << ' ';
        else cout << 0 << ' ';
    }
}