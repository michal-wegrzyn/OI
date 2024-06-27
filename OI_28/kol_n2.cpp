#include <bits/stdc++.h>
using namespace std;

long long nums[5003][2];

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int n;
    long long a, b, gcd_all_b, max_a;
    cin >> n;
    cin >> a >> b;
    gcd_all_b = b;
    max_a = a;
    nums[0][0] = a;
    nums[0][1] = b;
    bool ok;
    for(int i=1; i<n; i++){
        cin >> a >> b;
        nums[i][0] = a;
        nums[i][1] = b;
        gcd_all_b = __gcd(gcd_all_b, b);
        max_a = max(max_a, a);
    }
    if(gcd_all_b >= max_a){ cout << gcd_all_b << '\n'; return 0;}
    for(int i=max_a; i>0; i--){
        ok = true;
        for(int j=0; j<n; j++){
            if(nums[j][0] % i && nums[j][1] % i){
                ok = false; break;
            }
        }
        if(ok){ cout << i << '\n'; return 0; }
    }
    return 0;
}