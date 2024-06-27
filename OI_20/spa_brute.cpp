#include <bits/stdc++.h>
using namespace std;

bool is_deleted[4200000];
bool is_visited[4200000];
int n;

int str_to_int_res;
int str_to_int(string s){
    str_to_int_res = 0;
    for(char c:s){
        str_to_int_res *= 2;
        str_to_int_res += (c=='1'?1:0);
    }
    return str_to_int_res;
}

void dfs(int v){
    is_visited[v] = true;
    int u;
    for(int i=0; i<n; i++){
        u = v ^ (1 << i);
        if(!is_visited[u] && !is_deleted[u]){
            dfs(u);
        }
    }
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int k, x=0, y=0;
    string str_x, str_y;
    cin >> n >> k;
    cin >> str_x >> str_y;
    x = str_to_int(str_x);
    y = str_to_int(str_y);
    for(int i=0; i<k; i++){
        cin >> str_x;
        is_deleted[str_to_int(str_x)] = true;
    }
    dfs(x);
    if(is_visited[y]) cout << "TAK\n";
    else cout << "NIE\n";
    return 0;
}