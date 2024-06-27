#include <iostream>
#include <vector>
using namespace std;

vector<int> graph[1000003];
long long sizes[1000003];
long long n, total_dist;
int result=1;

void DFS_sizes(int v, int parent, long long dist){
    sizes[v] = (long long)1;
    total_dist += dist;
    for(int u:graph[v]) if(u != parent){
        DFS_sizes(u, v, dist+1);
        sizes[v] += sizes[u];
    }
}

void DFS_result(int v, int parent, long long dist){
    if(dist > total_dist){
        total_dist = dist;
        result = v;
    }
    for(int u:graph[v]) if(u != parent) DFS_result(u, v, dist+n-2*sizes[u]);
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int a, b;
    cin >> n;
    for(int i=1; i<n; i++){
        cin >> a >> b;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }
    DFS_sizes(1, -1, (long long)0);
    DFS_result(1, -1, total_dist);
    cout << result;
    return 0;
}