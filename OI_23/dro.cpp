#include <iostream>
#include <vector>
using namespace std;

int scc[500003];
vector<int> graf[500003];
vector<int> transposed[500003];
vector<int> postorder;
bool visited[500003];
int min_v[500003];
int min_w[500003];
int scc_res[500003];
int scc_size[500003];
int is_visited[500003];
int num_of_visited;

void DFS_is_one(int v){
    num_of_visited++;
    is_visited[v] = true;
    for(int i:graf[v]) if(!is_visited[i]) DFS_is_one(i);
    for(int i:transposed[v]) if(!is_visited[i]) DFS_is_one(i);
}

void DFS_postorder(int v){
    visited[v] = true;
    for(int i:graf[v]) if(!visited[i]) DFS_postorder(i);
    postorder.push_back(v);
}

int scc_num = 0;
void DFS_scc(int v){
    scc[v] = scc_num;
    scc_size[scc_num]++;
    for(int i:transposed[v]) if(!scc[i]) DFS_scc(i);
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n, m, a, b;
    cin >> n >> m;
    for(int i=0; i<m; i++){
        cin >> a >> b;
        graf[a].push_back(b);
        transposed[b].push_back(a);
    }
    DFS_is_one(1);
    if(num_of_visited != n){
        cout << 0;
        return 0;
    }
    for(int i=1; i<=n; i++) if(!visited[i]) DFS_postorder(i);
    for(int i=postorder.size()-1; i>=0; i--) if(!scc[postorder[i]]){
        scc_num++;
        DFS_scc(postorder[i]);
    }
    for(int i=1; i<=scc_num+1; i++) min_v[i] = scc_num+1;
    for(int i=1; i<=scc_num+1; i++) min_w[i] = 0;
    for(int i=1; i<=n; i++){
        for(int j:graf[i]){
            if(min_v[scc[i]]>scc[j] && scc[i]!=scc[j]) min_v[scc[i]] = scc[j];
            if(min_w[scc[j]]<scc[i] && scc[i]!=scc[j]) min_w[scc[j]] = scc[i];
        }
    }
    for(int i=1; i<=scc_num; i++){
        if(i+1<min_v[i]){
            scc_res[i] += 1;
            scc_res[min_v[i]] -= 1;
        }
    }
    for(int i=1; i<=scc_num; i++){
        if(i-1>min_w[i]){
            scc_res[min_w[i]+1] += 1;
            scc_res[i] -= 1;
        }
    }
    int result = 0;
    for(int i=1; i<=scc_num; i++){
        scc_res[i] += scc_res[i-1];
        if(!scc_res[i]) result += scc_size[i];
    }
    cout << result << '\n';
    for(int i=1; i<=n; i++) if(!scc_res[scc[i]]) cout << i << ' ';
    return 0;
}