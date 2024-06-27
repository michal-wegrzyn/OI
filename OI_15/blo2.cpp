#include <bits/stdc++.h>
using namespace std;

int n, m;
vector<pair<int,int>> graph[100003];
int curr_preorder_num;
int preorder[100003];
int low[100003];
bool is_AP[100003];
bool is_visited[100003];
int subtree_size[100003];
bool edge_type_in_dfs_tree[500003];  // 1 -> go down   0 -> go up
long long potential_result[100003];

void dfs_tree(int v, int parent){
    is_visited[v] = true;
    preorder[v] = curr_preorder_num;
    low[v] = curr_preorder_num;
    curr_preorder_num++;
    subtree_size[v] = 1;
    potential_result[v] = n-1;
    for(auto u:graph[v]){
        if(!is_visited[u.first]){
            edge_type_in_dfs_tree[u.second] = true;
            dfs_tree(u.first, v);
            subtree_size[v] += subtree_size[u.first];
            potential_result[v] += (long long)subtree_size[u.first] * (long long)(n - subtree_size[u.first]);
        }
    }
    potential_result[v] += (long long)subtree_size[v] * (long long)(n - subtree_size[v]);
}

void dfs_low(int v, int parent){
    for(auto u : graph[v]){
        if(edge_type_in_dfs_tree[u.second] && u.first != parent){
            dfs_low(u.first, v);
            low[v] = min(low[v], low[u.first]);
        }
        else if(!edge_type_in_dfs_tree[u.second]) low[v] = min(low[v], preorder[u.first]);
    }
}

void find_AP(){
    dfs_tree(1, -1);
    dfs_low(1, -1);
    int max_low;
    for(int v=2; v<=n; v++){
        max_low = -1;
        for(auto u : graph[v]) max_low = max(max_low, low[u.first]);
        if(preorder[v] <= max_low) is_AP[v] = true;
    }
    int num_of_tree_edges = 0;
    for(auto u : graph[1]) if(edge_type_in_dfs_tree[u.second]) num_of_tree_edges++;
    if(num_of_tree_edges > 1) is_AP[1] = true;
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int a, b, curr_edge_num=0;
    cin >> n >> m;
    for(int i=0; i<m; i++){
        cin >> a >> b;
        graph[a].push_back({b, curr_edge_num});
        graph[b].push_back({a, curr_edge_num});
        curr_edge_num ++;
    }
    find_AP();
    for(int i=1; i<=n; i++) cout << (is_AP[i] ? potential_result[i] : 2*n-2) << '\n';
    return 0;
}