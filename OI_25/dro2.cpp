#include <iostream>
#include <vector>
using namespace std;

vector <int> graph[50003];
vector <int> transpose_graph[50003];
vector <int> postorder;
int scc[50003];
int scc_count[50003];
bool visited[50003];
vector <int> scc_graph[50003];
int result[50003];

void dfs_postorder(int v){
    visited[v] = true;
    for(int i:graph[v]){
        if(!visited[i]) dfs_postorder(i);
    }
    postorder.push_back(v);
}

void dfs_scc(int v, int scc_num){
    scc[v] = scc_num;
    scc_count[scc_num]++;
    for(int i:transpose_graph[v]){
        if(!scc[i]) dfs_scc(i, scc_num);
    }
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n, m, num1, num2, curr_scc_num = 1;
    cin >> n >> m;
    for(int i=0; i<m; i++){
        cin >> num1 >> num2;
        graph[num1].push_back(num2);
        transpose_graph[num2].push_back(num1);
    }
    for(int i=1; i<=n; i++) if(!visited[i]) dfs_postorder(i);
    for(int i=postorder.size()-1; i>=0; i--){
        if(!scc[postorder[i]]){
            dfs_scc(postorder[i], curr_scc_num);
            curr_scc_num++;
        }
    }
    for(int i=1; i<=n; i++) for(int j:graph[i]) if(scc[i] != scc[j]) scc_graph[scc[i]].push_back(scc[j]);
    int curr_res = 0;
    for(int i=curr_scc_num-1; i>0; i--){
        curr_res = 0;
        for(int j:scc_graph[i]) curr_res += result[j]+1;
        result[i] = curr_res+scc_count[i]-1;
    }
    for(int i=1; i<=n; i++) cout << result[scc[i]] << '\n';
    return 0;
}