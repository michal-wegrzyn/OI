#include <bits/stdc++.h>
using namespace std;

#define ll long long
ll pol[1<<20];
ll values[1<<20][21];

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int n;
    ll m, q, a, lg_n;
    cin >> n >> m >> q;
    for(int i=0; i<n; i++){
        cin >> pol[i];
    }

    lg_n = 31 - __builtin_clz(n);
    for(int j=lg_n; j>=0; j++){
        // for(int i=0; i<)
    }
}