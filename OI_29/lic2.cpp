#include <bits/stdc++.h>
using namespace std;

bitset<10000007> is_not_prime;
vector<long long> primes;
vector<pair<long long,bool>> sub_nums;

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    long long n, n2, k, c, sq_n;
    cin >> n >> k >> c;
    n2 = n;
    sq_n = 0LL;
    for(long long i=(1<<23); i>0; i>>=1){
        sq_n += i;
        if(sq_n*sq_n>n) sq_n -= i;
    }
    is_not_prime[0] = true;
    is_not_prime[1] = true;
    for(long long i=2; i<=sq_n; i++){
        if(!is_not_prime[i]){
            for(long long j=i*i; j<=sq_n; j+=i) is_not_prime[j] = true;
            if(n2 % i == 0) primes.push_back(i);
            while(n2 % i == 0) n2 /= i;
        }
    }
    
    if(n2 > (long long)1) primes.push_back(n2);
    int sn_size = 0;
    for(long long i:primes){
        for(int j=0; j<sn_size; j++) sub_nums.push_back({sub_nums[j].first*i,!sub_nums[j].second});
        sub_nums.push_back({i, 1});
        sn_size = sn_size*2+1;
    }
    long long add = (long long)1 << 62;
    long long res = (long long)0, curr_k;
    while(add){
        res += add;
        curr_k = res;
        for(auto i:sub_nums) curr_k += res/i.first*(i.second?-1:1);
        if(curr_k >= k) res -= add;
        add >>= 1;
    }
    while(c){
        res++; 
        if(__gcd(res, n) == 1){
            cout << res << ' ';
            c--;
        }
    }
}