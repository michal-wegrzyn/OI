#include <bits/stdc++.h>
using namespace std;

pair<int,int> input_data[1000003];
vector<pair<int,int>> graph[1000003];
int n, m;
int curr_preorder_num;
int preorder[1000003];
int low[1000003];
bool is_deleted[1000003];
bool result[1000003];
bool is_visited[1000003];
bool is_visited_edge[1000003];
bool edge_type_in_dfs_tree[1000003];  // 1 -> go down   0 -> go up

void dfs_tree(int v, int parent){
    is_visited[v] = true;
    preorder[v] = curr_preorder_num;
    low[v] = curr_preorder_num;
    curr_preorder_num++;
    for(auto u:graph[v]){
        if(!is_visited[u.first]){
            edge_type_in_dfs_tree[u.second] = true;
            dfs_tree(u.first, v);
        }
    }
}

int num_of_bridges, scc_num;

void dfs_low(int v, int parent){
    for(auto u : graph[v]){
        if(edge_type_in_dfs_tree[u.second] && u.first != parent){
            dfs_low(u.first, v);
            low[v] = min(low[v], low[u.first]);
        }
        else if(!edge_type_in_dfs_tree[u.second]) low[v] = min(low[v], preorder[u.first]);
    }
    if(low[v] == preorder[v] && parent != -1) num_of_bridges++;
}

void dfs_result(int v){
    for(auto u : graph[v]){
        if(!is_visited_edge[u.second]){
            // cout << v << ' ' << u.first << '\n';
            is_visited_edge[u.second] = true;
            if(input_data[u.second] == make_pair(v, u.first)) result[u.second] = true;
            dfs_result(u.first);
        }
    }
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int a, b;
    cin >> n >> m;
    for(int i=0; i<m; i++){
        cin >> a >> b;
        graph[a].push_back({b, i});
        graph[b].push_back({a, i});
        input_data[i] = {a, b};
    }

    for(int i=1; i<=n; i++) if(!is_visited[i]){
        scc_num++;
        dfs_tree(i, -1);
        dfs_low(i, -1);
        dfs_result(i);
    }

    cout << scc_num + num_of_bridges << '\n';
    for(int i=0; i<m; i++) cout << (result[i] ? '>' : '<');
}