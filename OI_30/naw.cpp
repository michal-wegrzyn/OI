	
#include <bits/stdc++.h>
using namespace std;

int parent_centroid[200007];
vector<int> graph[200007];
vector<int> centroid_graph[200007];
bitset<200007> is_del;
int jumps[200007][18];
int depth[200007];

int subtreeSize(int v, int p){
    int res = 1;
    for(int u:graph[v]){
        if(u==p || is_del[u]) continue;
        res += subtreeSize(u, v);
    }
    return res;
}

int findCentroid(int v, int p, int tree_sz){
    int u_size;
    for(int u:graph[v]){
        if(u==p || is_del[u]) continue;
        u_size = subtreeSize(u, v);
        if(u_size*2 == tree_sz) return v;
        if(u_size*2 >= tree_sz) return findCentroid(u,v,tree_sz);
    }
    return v;
}

void centroidDecomposition(int v, int p){
    int c = findCentroid(v, -1, subtreeSize(v, -1));
    parent_centroid[c] = p;
    if(p != -1) centroid_graph[p].push_back(c);
    is_del[c] = 1;
    for(int u:graph[c]){
        if(is_del[u]) continue;
        centroidDecomposition(u,c);
    }
}

void dfs(int v, int p){
    depth[v] = depth[p] + 1;
    jumps[v][0] = p;
    for(int u:graph[v]){
        if(u==p) continue;
        dfs(u,v);
    }
}

int lca(int a, int b){
    if(depth[a] < depth[b]) swap(a,b);
    int diff = depth[a] - depth[b];
    for(int i=0; i<18; i++){
        if(diff & (1<<i)) a = jumps[a][i];
    }
    if(a==b) return a;
    for(int i=17; i>=0; i--){
        if(jumps[a][i] != jumps[b][i]){
            a = jumps[a][i];
            b = jumps[b][i];
        }
    }
    return jumps[a][0];
}

inline int dist(int a, int b){
    return depth[a] + depth[b] - depth[lca(a,b)]*2;
}

string enc_part[200007];

string encode_num(int v, int l){
    string res = "";
    for(int i=0; i<l; i++){
        if(v&1) res.push_back('1');
        else res.push_back('0');
        v >>= 1;
    }
    reverse(res.begin(), res.end());
    return res;
}

int cent_graph_depth[200007];

void dfsCalcDepth(int v, int p){
    cent_graph_depth[v] = cent_graph_depth[p] + 1;
    for(int u:centroid_graph[v]) dfsCalcDepth(u, v);
}

void enkoder(){
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int n, a, b; cin >> n;
    for(int i = 1; i<n; i++){
        cin >> a >> b;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }

    int main_centr = findCentroid(1,-1, n);

    centroidDecomposition(1,-1);

    dfs(1,1);
    for(int j=1; j<18; j++){
        for(int i=1; i<=n; i++){
            jumps[i][j] = jumps[jumps[i][j-1]][j-1];
        }
    }
    dfsCalcDepth(main_centr, main_centr);
    for(int i=1; i<=n; i++){
        cout << encode_num(cent_graph_depth[i], 18);
        a = i;
        for(int j=0; j<cent_graph_depth[i]; j++){
            cout << encode_num(a, 18) << encode_num(dist(a,i), 18-cent_graph_depth[a]);
            a = parent_centroid[a];
        }
        cout << '\n';
    }
}

string str_dec[2];

int decodeNum(int st, int en, int pos){
    int res = 0;
    for(int i=st; i<en; i++){
        res *= 2;
        res += (str_dec[pos][i]=='1' ? 1 : 0);
    }
    return res;
}

vector<pair<int,int>> v1;
vector<pair<int,int>> v2;
void solve_dekoder(){
    int count1 = decodeNum(0,18, 0);
    v1.clear(); v2.clear();
    int curr_pos = 18;
    for(int i=0; i<count1; i++){
        v1.push_back({decodeNum(curr_pos, curr_pos+18, 0), decodeNum(curr_pos+18, curr_pos+18+18-count1+i, 0)});
        curr_pos = curr_pos+18+18-count1+i;
    }

    int count2 = decodeNum(0,18, 1);
    curr_pos = 18;
    for(int i=0; i<count2; i++){
        v2.push_back({decodeNum(curr_pos, curr_pos+18, 1), decodeNum(curr_pos+18, curr_pos+18+18-count2+i, 1)});
        curr_pos = curr_pos+18+18-count2+i;
    }
    int sm_sz = min(v1.size(), v2.size());
    int best_dist = INT_MAX/4;
    for(int i=0; i<sm_sz; i++){
        if(v1[v1.size()-1-i].first == v2[v2.size()-1-i].first) best_dist = min(best_dist, v1[v1.size()-1-i].second + v2[v2.size()-1-i].second);
    }

    cout << best_dist << '\n';
}

void dekoder(){
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int n; cin >> n;
    for(int i=0; i<n; i++){
        cin >> str_dec[0] >> str_dec[1];
        solve_dekoder();
    }
}

int main(){
    dekoder();
}