#include <bits/stdc++.h>
using namespace std;

#define ll long long

int aux;
pair<ll,ll> nums[1000007];
ll d[500007][19];
int tab_log[500007];

bool isDivByG(int a, int b, ll g){
    aux = tab_log[b-a+1];
    if(d[a][aux]%g) return false;
    if(d[b-(1<<aux)+1][aux]%g) return false;
    return true;
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int n;
    ll a, b, gcd_all_b=0LL;
    int mx_a = 0;
    cin >> n;
    for(int i=0; i<n; i++){
        cin >> a >> b;
        nums[i] = {a, b};
        d[a][0] = __gcd(d[a][0], b);
        if(a>mx_a) mx_a = a;
        gcd_all_b = __gcd(gcd_all_b, b);
    }

    if(gcd_all_b>=mx_a){
        cout << gcd_all_b << '\n';
        return 0;
    }

    aux = 0;
    for(int i=1; i<=mx_a; i++){
        if(i>=(1<<(aux+1))) aux++;
        tab_log[i] = aux;
    }

    for(int j=1; j<19; j++){
        for(int i=1; i<=mx_a-(1<<j)+1; i++){
            d[i][j] = __gcd(d[i][j-1], d[i+(1<<(j-1))][j-1]);
        }
    }

    bool is_ok;

    for(int i=mx_a; i>=2; i--){
        is_ok = true;
        for(int j=0; i*j<mx_a; j++){
            if(!isDivByG(i*j+1, min(i*(j+1)-1, mx_a), i)){
                is_ok = false;
                break;
            }
        }
        if(is_ok){
            cout << i << '\n';
            return 0;
        }
    }

    cout << 1 << '\n';
    return 0;
}