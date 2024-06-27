#include <iostream>
#include <utility>
#include <vector>
using namespace std;

vector<pair<int, int>> graph[100007];
vector<int> result;
vector<int> result2[333400];
int it_result2;
bool visited_edges[1000007];
bool visited_vertices[100007];
int deg[100003];

void course(int v){
    visited_vertices[v] = true;
    if(!deg[v]){
        result.pop_back();
        return;
    }
    while(visited_edges[graph[v].back().second]) graph[v].pop_back();
    visited_edges[graph[v].back().second] = true;
    int v2 = graph[v].back().first;
    result.push_back(v2);
    deg[v]--;
    deg[v2]--;
    if(visited_vertices[v2]){
        result2[it_result2].push_back(v2);
        result.pop_back();
        while(result.back()!=v2){
            result2[it_result2].push_back(result.back());
            visited_vertices[result.back()] = false;
            result.pop_back();
        }
        it_result2++;
    }
    course(v2);
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n, m, a, b, s, t, curr_edge_num=0;
    cin >> n >> m;
    for(int i=0; i<m; i++){
        cin >> a >> b >> s >> t;
        if(s^t){
            graph[a].push_back(make_pair(b, curr_edge_num));
            graph[b].push_back(make_pair(a, curr_edge_num));
            deg[a]++;
            deg[b]++;
            curr_edge_num++;
        }
    }
    for(int i=1; i<=n; i++) if(deg[i]&1){
        cout << "NIE";
        return 0;
    }
    for(int i=1; i<=n; i++) if(deg[i]){
        result.push_back(i);
        course(i);
    }
    cout << it_result2 << '\n';
    for(int i=0; i<it_result2; i++){
        cout << result2[i].size() << ' ';
        for(int j:result2[i]) cout << j << ' ';
        cout << result2[i][0] << '\n';
    }
    return 0;
}