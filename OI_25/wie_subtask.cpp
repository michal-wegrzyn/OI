#include <bits/stdc++.h>
using namespace std;

#define ll long long

ll pol[1<<20];
ll q_pow[1<<20];

ll n, m, q;

ll sumGeo(ll r, ll count){
    if(count == 0) return 1LL;
    ll a = sumGeo((r*r)%m, (count-1)/2);
    if(count&1) return (a+r*a)%m;
    return (a*r*r+1 + r*a)%m;
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    ll a;
    cin >> n >> m >> q;

    for(int i=0; i<n; i++) cin >> pol[i];

    q_pow[0] = 1;
    for(int i=1; i<n; i++) q_pow[i] = (q_pow[i-1] * q) % m;

    ll sum = 0;
    for(int i=0; i<n; i++){
        sum += ((pol[i]*q_pow[i])%m)*sumGeo(q_pow[i], n-1);
        sum %= m;
    }

    cout << sum << '\n';

    if(n > (1<<10)){
        for(int i=0; i<n; i++) cout << 0 << ' ';
        return 0;
    }

    for(int i=1; i<=n; i++){
        sum = 0;
        for(int j=0; j<n; j++){
            sum += pol[j] * q_pow[i*j%n];
            sum %= m;
        }
        cout << sum << ' ';
    }
}