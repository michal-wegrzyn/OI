#include <bits/stdc++.h>
using namespace std;

long long N;
bitset<100000006> is_not_prime;

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    is_not_prime[0] = 1;
    is_not_prime[1] = 1;
    cin >> N;
    for(int i=2;i<=10000;i++) if(is_not_prime[i] == 0){
        for(int j=i*i; j<100000000; j+=i) is_not_prime[j] = 1;
    }
    long long sum = (long long)0;
    int sstart = 0;
    for(int i=1; i<=N; i++){
        if(is_not_prime[i] == 1) continue;
        sum += (long long) i;
        while(sum > N){
            if(is_not_prime[sstart] == 0) sum -= (long long)sstart;
            sstart++;
        }
        if(sum == N){
            while(is_not_prime[sstart] == 1) sstart++;
            cout << sstart << ' ' << i;
            return 0;
        }
    }
    cout << "NIE";
    return 0;
}