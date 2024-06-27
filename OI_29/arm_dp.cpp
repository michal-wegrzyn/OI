// Michał Węgrzyn
#include <iostream>
using namespace std;

long long dp[200007];
long long jeden = (long long) 1;
long long iinf = jeden << 61;
long long zzero;

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    long long n, a, b, p, q;
    long long curr_res = zzero;
    long long res = iinf;
    cin >> n >> a >> b;
    if(a==b){
        q = jeden;
        for(long long i=0; q<3*n+7; i++){
            p = q;
            curr_res = i*3;
            while(p<n+1){
                p*= 2;
                curr_res += 2;
            }
            if(res > curr_res) res = curr_res;
            q *= 3;
        }
        res *= a;
        cout << res;
        return 0;
    }
    for(int i=2; i<=2*n+3; i++) dp[i] = iinf;
    for(int i=1; i<=n; i++){
        for(int j=1; i+j*i<2*n+3; j++){
            if(dp[i+j*i] > dp[i] + a + j*b) dp[i+j*i] = dp[i] + a + j*b;
        }
    }
    for(int i=n+1; i<2*n+3; i++) if(res>dp[i]) res = dp[i];
    cout << res;
    return 0;
}