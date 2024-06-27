#include <iostream>
using namespace std;

int repr[500003];
int sizes[500003];
int result;

int F(int v){
    if(repr[v]==v) return v;
    return repr[v] = F(repr[v]);
}

void U(int a, int b){
    a = F(a); b = F(b);
    if(a==b) return;
    result--;
    if(sizes[a]>sizes[b]) swap(a, b);
    repr[a] = b;
    sizes[b] += sizes[a];
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n, m, a, b, l;
    cin >> n >> m;
    result = n;
    for(int i=1; i<=n; i++) repr[i] = i;
    for(int i=0; i<m; i++){
        cin >> a >> b >> l;
        for(int j=0; j<l; j++) U(a+j, b+j);
    }
    cout << result;
    return 0;
}