#include <iostream>
#include <vector>
using namespace std;

int graph[500003];
vector<int> transposed[500003];
int lvl[500003];
int jumps[500003][20];
int scc[500003];
int cycle[500003];
int scc_repr[500003];
bool visited[500003];
int cycle_size[500003];

void DFS(int v, int prev){
    if(cycle[v]) prev = v;
    jumps[v][0] = prev;
    lvl[v] = lvl[prev]+1;
    for(int i:transposed[v]) if(!jumps[i][0]) DFS(i, v);
}

int scc_num = 1;
void DFS_scc(int v){
    scc[v] = scc_num;
    if(!scc[graph[v]]) if(!scc[graph[v]]) DFS_scc(graph[v]);
    for(int i:transposed[v]) if(!scc[i]) DFS_scc(i);
}

int recording = -1;
int dist_to_repr = 1;
void find_cycle(int v){
    if(recording == v){
        recording = -1;
        cycle_size[scc_num] = dist_to_repr-1;
        dist_to_repr = 1;
        return;
    }
    if(visited[v] && recording == -1){
        recording = v;
        scc_repr[scc_num] = v;
    }
    if(recording != -1) cycle[v] = dist_to_repr++;
    visited[v] = true;
    find_cycle(graph[v]);
}

int mx(int a, int b){
    return (a>b?a:b);
}
int mn(int a, int b){
    return (a<b?a:b);
}

int len, len2, start_x, start_y;
bool swapped;
void lca(int x, int y){
    if(scc[x] != scc[y]){
        cout << -1 << ' ' << -1 << '\n';
        return;
    }
    swapped = false;
    start_x = x;
    start_y = y;
    if(cycle[start_x] || cycle[start_y] || jumps[start_x][19]!=jumps[start_y][19]){
        x = jumps[start_x][19];
        y = jumps[start_y][19];
    }
    else{
    if(lvl[x] < lvl[y]){
        swap(x, y);
        swapped = true;
    }
    for(int i=19; i>=0; i--) if(lvl[x] - (1<<i) >= lvl[y]) x = jumps[x][i];
    if(x!=y){
        for(int i=19; i>=0; i--) if(jumps[x][i] != jumps[y][i] && !cycle[jumps[x][i]]){
            x = jumps[x][i];
            y = jumps[y][i];
        }
        x = jumps[x][0];
        y = jumps[y][0];
    }
    else{
        x = x;
        y = y;
    }
    if(swapped){
        swap(x, y);
    }
    }
    if(!cycle[x]){
        cout << lvl[start_x]-lvl[x] << ' ' << lvl[start_y]-lvl[x] << '\n';
        return;
    }
    len = cycle[y] - cycle[x];
    if(len<0) len = cycle_size[scc[x]] + len;
    len2 = cycle_size[scc[x]] - len;
    if(mx(lvl[start_x]+len, lvl[start_y])>mx(lvl[start_y]+len2, lvl[start_x])){
        cout << lvl[start_x]-1 << ' ' << lvl[start_y]-1+len2 << '\n';
        return;
    }
    if(mx(lvl[start_x]+len, lvl[start_y])<mx(lvl[start_y]+len2, lvl[start_x])){
        cout << lvl[start_x]-1+len << ' ' << lvl[start_y]-1 << '\n';
        return;
    }

    if(mn(lvl[start_x]+len, lvl[start_y])>mn(lvl[start_y]+len2, lvl[start_x])){
        cout << lvl[start_x]-1 << ' ' << lvl[start_y]-1+len2 << '\n';
        return;
    }
    if(mn(lvl[start_x]+len, lvl[start_y])<mn(lvl[start_y]+len2, lvl[start_x])){
        cout << lvl[start_x]-1+len << ' ' << lvl[start_y]-1 << '\n';
        return;
    }
    cout << lvl[start_x]-1+len << ' ' << lvl[start_y]-1 << '\n';
    //cout << len;
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n, k, num1, num2;
    cin >> n >> k;
    for(int i=1; i<=n; i++){
        cin >> num2;
        graph[i] = num2;
        transposed[num2].push_back(i);
    }

    for(int i=1; i<=n; i++) if(!scc[i]){
        DFS_scc(i);
        scc_repr[scc_num] = i;
        find_cycle(i);
        scc_num++;
    }
    for(int i=1; i<scc_num; i++) DFS(scc_repr[i], scc_repr[i]);
    
    for(int i=1; i<20; i++){
        for(int j=1; j<=n; j++) jumps[j][i] = jumps[jumps[j][i-1]][i-1];
    }

    for(int i=0; i<k; i++){
        cin >> num1 >> num2;
        lca(num1, num2);
    }

    return 0;
}