#include <bits/stdc++.h>
using namespace std;

vector<pair<int,int>> graph[100007];
int lvl[100007];
int jumps[100007][18];
int dist_to_1[100007];

void dfs_lca(int v, int prev){
    jumps[v][0] = prev;
    lvl[v] = lvl[prev]+1;
    for(auto i:graph[v]) if(i.second != prev){
        dist_to_1[i.second] = dist_to_1[v] + i.first;
        dfs_lca(i.second, v);
    }
}

int lca(int x, int y){
    if(lvl[x] < lvl[y]) swap(x, y);
    for(int i=17; i>=0; i--) if(lvl[x] - (1<<i) >= lvl[y]) x = jumps[x][i];
    if(x==y) return x;
    for(int i=17; i>=0; i--) if(jumps[x][i] != jumps[y][i]){
        x = jumps[x][i];
        y = jumps[y][i];
    }
    return jumps[x][0];
}

long long dist(int a, int b){
    return dist_to_1[a] + dist_to_1[b] - dist_to_1[lca(a, b)]*2;
}

struct node{
    int count;
    long long len;
    int parent;
    long long parent_len;
};

node centroid_tree[100007];

int subtree_size[100007];
bitset<100007> is_deleted;

void calculate_subtree_sizes(int v, int prev){
    subtree_size[v] = 1;
    for(auto i:graph[v]) if(i.second != prev && is_deleted[i.second] == false){
        calculate_subtree_sizes(i.second, v);
        subtree_size[v] += subtree_size[i.second];
    }
}

int find_centroid(int v){
    calculate_subtree_sizes(v, -1);
    int total_size = subtree_size[v];
    int prev=-1;
    bool breaked;
    while(true){
        breaked = false;
        for(auto i:graph[v]) if(i.second != prev && is_deleted[i.second] == false){
            if(subtree_size[i.second] > total_size/2){
                prev = v;
                v = i.second;
                breaked = true;
                break;
            }
        }
        if(!breaked) return v;
    }
}

void decompose(int v, int prev){
    int c = find_centroid(v);
    is_deleted[c] = true;
    centroid_tree[c] = {0,0LL,prev,0LL};
    for(auto i : graph[c]) if(!is_deleted[i.second]){
       decompose(i.second, c);
    }
}

long long add_castle(int x){
    long long r = centroid_tree[x].len;
    int curr_v = x;
    while(centroid_tree[curr_v].parent != -1){
        r += centroid_tree[centroid_tree[curr_v].parent].len - centroid_tree[curr_v].parent_len + dist(x, centroid_tree[curr_v].parent)*(centroid_tree[centroid_tree[curr_v].parent].count - centroid_tree[curr_v].count);
        centroid_tree[curr_v].count++;
        centroid_tree[curr_v].len += dist(x, curr_v);
        centroid_tree[curr_v].parent_len += dist(x, centroid_tree[curr_v].parent);
        curr_v = centroid_tree[curr_v].parent;
    }
    centroid_tree[curr_v].count++;
    centroid_tree[curr_v].len += dist(x, curr_v);
    return r;
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int n, k, a, b, c, d;
    cin >> n >> k;
    for(int i=1; i<n; i++){
        cin >> a >> b >> c;
        graph[a].push_back({c, b});
        graph[b].push_back({c, a});
    }

    dfs_lca(1, 1);
    for(int i=1; i<18; i++){
        for(int j=1; j<=n; j++) jumps[j][i] = jumps[jumps[j][i-1]][i-1];
    }

    decompose(1, -1);

    long long result = 0LL;
    add_castle(1);
    for(int i=1; i<=k; i++){
        cin >> d;
        result += add_castle(d)*2LL;
        cout << result << '\n';
    }

    return 0;
}