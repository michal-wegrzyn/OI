#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

long long jeden = (long long)1;
long long zero;
vector<long long> primes;

long long n, k, c, cnt = jeden, num, curr_n;
long long curr_res, curr_iloczyn;
long long num_of_nums(long long num){
    curr_res = zero;
    curr_iloczyn = jeden;
    for(long long i:primes){
        curr_iloczyn *= i;
        if(curr_iloczyn == i) curr_res = num/i;
        else curr_res += num/i - num/curr_iloczyn;
        cout << curr_iloczyn << ' ' << curr_res << '\n';
    }
    return n-curr_res;
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> n >> k >> c;
    /*for(num=1; cnt<k; num++) if(__gcd(num, n)==jeden) cnt++;
    for(;cnt<k+c; num++) if(__gcd(num, n) == jeden){
        cnt++;
        cout << num << ' ';
    }*/
    curr_n = n;
    for(long long i=jeden+jeden; i*i<=n; i++){
        if(curr_n == jeden) break;
        if(curr_n/i*i==curr_n){ primes.push_back(i);
            while(curr_n/i*i==curr_n) curr_n /= i;
        }
    }
    if(curr_n != jeden) primes.push_back(curr_n);
    curr_n = n;
    cout << num_of_nums(n);
    return 0;
}