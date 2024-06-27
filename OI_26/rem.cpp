#include <bits/stdc++.h>
using namespace std;

vector<int> graph[600007];
vector<int> tr_graph[600007];
int scc[600007];
int nums[150007];
vector<pair<pair<int,int>,int>> pairs;

bitset<600007> vis;
vector<int> postorder;
void dfs_postorder(int v){
    vis[v] = 1;
    for(int u:graph[v]){
        if(vis[u]) continue;
        dfs_postorder(u);
    }
    postorder.push_back(v);
}

int curr_scc_num;
void dfs_scc(int v){
    scc[v] = curr_scc_num;
    for(int u:tr_graph[v]){
        if(scc[u]) continue;
        dfs_scc(u);
    }
}

void add(int a, int b){
    a*=2; b*=2;
    if(a<0) a = -a+1;
    if(b<0) b = -b+1;
    graph[a^1].push_back(b);
    tr_graph[b].push_back(a^1);
    if(a==b) return;
    graph[b^1].push_back(a);
    tr_graph[a].push_back(b^1);
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int t, n, k, a, b, last_v;
    bool is_ok;
    cin >> t;
    while(t--){
        cin >> n >> k;
        for(int i=1; i<=n; i++) cin >> nums[i];
        
        for(int i=1; i<n; i++){
            add(i, i+1);
            pairs.push_back({{nums[i],nums[i+1]}, i});
        }
        add(1,1); add(n-1,n-1);
        pairs.push_back({{-1,-1},-1});
        sort(pairs.begin(), pairs.end());

        for(int i=1; i<pairs.size();i++){
            if(pairs[i].first.first != pairs[i-1].first.first || pairs[i].first.second != pairs[i-1].first.second){
                add(-pairs[i].second, pairs[i].second+n);
                add(pairs[i].second, -pairs[i].second-n);
            }
            else{
                add(-pairs[i].second, -pairs[i-1].second-n);
                add(-pairs[i-1].second-n, pairs[i].second+n);
                add(-pairs[i].second, pairs[i].second+n);
            }
        }

        for(int i=1; i<n*4; i++) if(!vis[i]) dfs_postorder(i);
        reverse(postorder.begin(), postorder.end());
        for(int i:postorder){
            if(scc[i]) continue;
            curr_scc_num++;
            dfs_scc(i);
        }

        is_ok = true;

        for(int i=1; i<n*2; i++){
            if(scc[i*2] == scc[i*2+1]){
                is_ok = false;
                break;
            }
        }

        cout << (is_ok ? "TAK\n" : "NIE\n");

        // for(int i=1; i<n*4; i++) cout << scc[i] << ' ';
        // cout << '\n';

        curr_scc_num = 0;
        postorder.clear();
        vis.reset();
        for(int i=1; i<n*4; i++){
            scc[i] = 0;
            graph[i].clear();
            tr_graph[i].clear();
        }
        pairs.clear();
    }
}