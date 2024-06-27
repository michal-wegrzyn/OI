#include <bits/stdc++.h>
using namespace std;

#define ll long long

ll pow_m(ll n, int m){
    ll res = 1;
    if(m==1) return n;
    while(m){
        if((1LL<<61)/n<res) break;
        if(m&1) res *= n;
        m >>= 1;
        if(n>(1LL<<30)) break;
        n *= n;
    }
    if(m) return LLONG_MAX;
    else return res;
}

ll mth_root(ll n, int m){
    ll res = 0LL;
    if(m == 1) return n;
    for(ll i=(1<<29); i>0; i>>=1){
        res += i;
        if(pow_m(res,m)==n) return res;
        if(pow_m(res,m)>n) res -= i;
    }
    return res;
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    ll n, a, b, s, mult;
    int k;
    cin >> n >> a >> b; n++;
    ll best_cost = LLONG_MAX;
    for(int m=1; m<=60; m++){
        s = mth_root(n, m);
        mult = pow_m(s,m);
        for(k=m; mult<n; k--){
            mult = mult/s*(s+1);
        }
        if((1LL<<61)/b>s*m+k) if(best_cost > a*m+(s*m-k)*b){
            best_cost = a*m+(s*m-k)*b;
        }
    }
    cout << best_cost << '\n';
}