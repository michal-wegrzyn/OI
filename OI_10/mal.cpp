#include <iostream>
#include <vector>
using namespace std;

struct info{
    int v1;
    int v2;
    bool t;
};

vector<int> graph[200003];
int repr[200003];
int sizes[200003];
int result[200003];
vector<info> finish_graph;
vector<int> to_be_added;

int F(int v){
    if(repr[v]==v) return v;
    else return repr[v] = F(repr[v]);
}

void U(int a, int b){
    a = F(a);
    b = F(b);
    if(a==b) return;
    if(sizes[a] > sizes[b]) swap(a, b);
    sizes[b] += sizes[a];
    repr[a] = b;
}

int value;
bool visited[200003];
void dfs(int v){
    if(visited[v]) return;
    result[v] = value;
    visited[v] = true;
    for(int i:graph[v]){
        if(!visited[i]){
            dfs(i);
        }
    }
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n, m, num1, num2;
    info w;
    cin >> n >> m;
    for(int i=0; i<=n; i++){
        repr[i] = i;
        sizes[i] = 1;
        result[i] = 1000000;
    }
    info x;
    for(int i=1; i<=n; i++){
        cin >> num1 >> num2;
        finish_graph.push_back({i, num1, true});
        finish_graph.push_back({i, num2, true});
    }
    for(int i=0; i<m; i++){
        cin >> num1 >> num2;
        to_be_added.push_back(num1*2+num2-3);
        finish_graph[num1*2+num2-3].t = false;
    }
    for(int i=0; i<2*n; i++) if(finish_graph[i].t && finish_graph[i].v2!=-1){
        graph[finish_graph[i].v1].push_back(finish_graph[i].v2);
        graph[finish_graph[i].v2].push_back(finish_graph[i].v1);
        U(finish_graph[i].v1, finish_graph[i].v2);
    }
    for(int i=1; i<=n; i++) if(F(i)==F(1)) result[i] = -1;
    for(int i=m-1; i>=0; i--){
        w = finish_graph[to_be_added[i]];
        if(w.v2 == -1) continue;
        value = i;
        if((F(w.v1)==F(1) && F(w.v2)!=F(1))) dfs(w.v2);
        else if((F(w.v1)!=F(1) && F(w.v2)==F(1))) dfs(w.v1);
        U(w.v1, w.v2);
        graph[w.v1].push_back(w.v2);
        graph[w.v2].push_back(w.v1);
    }
    for(int i=1; i<=n; i++) cout << result[i] << '\n';
    return 0;
}