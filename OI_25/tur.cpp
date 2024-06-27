#include <bits/stdc++.h>
using namespace std;

int pos[1007][3];
vector<int> graph[1007];
vector<int> tr_graph[1007];
vector<int> postorder;
bitset<1007> vis;
int scc[1007];
int curr_scc_num;

void dfs_postorder(int v){
    vis[v] = 1;
    for(int u:graph[v]){
        if(!vis[u]) dfs_postorder(u);
    }
    postorder.push_back(v);
}

void dfs_scc(int v){
    scc[v] = curr_scc_num;
    for(int u:tr_graph[v]){
        if(!scc[u]){
            dfs_scc(u);
        }
    }
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int n, a, b;
    cin >> n;
    for(int j=0; j<3; j++){
        for(int i=0; i<n; i++) cin >> pos[i][j];
    }
    int cnt;
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            cnt = 0;
            for(int k=0; k<3; k++) if(pos[i][k] < pos[j][k]) cnt++;
            if(cnt>=2){
                graph[i].push_back(j);
                tr_graph[j].push_back(i);
            }
        }
    }

    for(int i=0; i<n; i++) if(!vis[i]) dfs_postorder(i);
    reverse(postorder.begin(), postorder.end());
    for(int i:postorder){
        if(!scc[i]){
            curr_scc_num++;
            dfs_scc(i);
        }
    }

    int m; cin >> m;
    for(int i=0; i<m; i++){
        cin >> a >> b; a--; b--;
        cout << (scc[a] <= scc[b] ? "TAK\n" : "NIE\n");
    }
}