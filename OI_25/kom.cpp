#include <bits/stdc++.h>
using namespace std;

int div_count[17000007];
int pref_comp_count[17000007];

vector<int> div8;
vector<int> div9;
vector<long long> primes;
int res_to_7 = 40593;
int res_to_8 = 19714645;
bitset<83000007> is_comp;


int res_for_prefix(int a){
    if(a<=17000000) return pref_comp_count[a];
    int pos = 0;
    if(a>=100000000){
        if(a < div9.front()) return res_to_8;
        for(int i=12; i>=0; i--){
            pos += (1<<i);
            if(pos>=div9.size()){
                pos -= (1<<i);
                continue;
            }
            if(div9[pos]>a){
                pos -= (1<<i);
                continue;
            }
        }
        return res_to_8 + pos + 1;
    }
    else{
        if(a < div8.front()) return res_to_7;
        for(int i=24; i>=0; i--){
            pos += (1<<i);
            if(pos>=div8.size()){
                pos -= (1<<i);
                continue;
            }
            if(div8[pos]>a){
                pos -= (1<<i);
                continue;
            }
        }
        return res_to_7 + pos + 1;
    }
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int base = 1, curr_dig_cnt = 1;
    bool is_ok;

    for(int i=1; i<=4123; i++){
        div_count[i*i]++;
        for(int j=i*i+i; j<=17000000; j+=i) div_count[j] += 2;
    }
    for(int i=1; i<=17000000; i++){
        if(i==base*10){
            base *= 10;
            curr_dig_cnt++;
        }
        pref_comp_count[i] = pref_comp_count[i-1];
        if(div_count[i] == curr_dig_cnt) pref_comp_count[i]++;
    }
    for(int i=2; i<=17000000; i++){
        if(div_count[i] == 2) primes.push_back(i);
    }
    for(int i=10000; i*i<1000000000; i++){
        if(div_count[i] == 4){
            bool is_ok = true;
            for(int j=2; j*j*j<=i; j++){
                if(j*j*j==i) is_ok = false;
            }
            if(is_ok) div9.push_back(i*i);
        }
    }

    for(int i=10000001; i<=17000000; i++) if(div_count[i] == 8) div8.push_back(i);
    // div8.push_back(19487171);
    is_comp[2487171] = 1;
    // div8.push_back(62748517);
    is_comp[45748517] = 1; 
    long long cnnnt = 0;
    long long prime_i, prime_j;
    for(int i=0; primes[i]*primes[i+1]*primes[i+2]<100000000LL; i++){
        prime_i = primes[i];
        for(int j=i+1; primes[i]*primes[j]*primes[j+1]<100000000LL; j++){
            prime_j = primes[j];
            int k = j+1;
            for(int l=20; l>=0; l--){
                k += (1<<l);
                if(k>=primes.size()){
                    k -= (1<<l);
                    continue;
                }
                if(prime_i*prime_j*primes[k]>=17000000){
                    k -= (1<<l);
                    continue;
                }
            }
            for(; prime_i*prime_j*primes[k]<100000000LL; k++){
                if(prime_i*prime_j*primes[k]>=17000000){
                    // div8.push_back(primes[i]*primes[j]*primes[k]);
                    is_comp[prime_i*prime_j*primes[k]-17000000] = 1;
                }
                cnnnt++;
            }
        }
    }
    for(int i=0; i<primes.size() && primes[i]*primes[i]*primes[i]<100000000LL; i++){
        for(int j=0; j<primes.size() && primes[i]*primes[i]*primes[i]*primes[j]<100000000LL; j++){
            if(i==j) continue;
            if(primes[i]*primes[i]*primes[i]*primes[j]>=17000000LL){
                // div8.push_back(primes[i]*primes[i]*primes[i]*primes[j]);
                is_comp[primes[i]*primes[i]*primes[i]*primes[j]-17000000] = 1;
            }
        }
    }


    // sort(div8.begin(), div8.end());
    int pos = is_comp._Find_first();
    // while(pos != 83000007){
    //     div8.push_back(pos+17000000);
    //     pos = is_comp._Find_next(pos);
    // }
    sort(div9.begin(), div9.end());

    int t, a, b;
    cin >> t;
    while(t--){
        cin >> a >> b;
        cout << res_for_prefix(b)-res_for_prefix(a-1) << '\n';
        // cout << pref_comp_count[b] - pref_comp_count[a-1] << '\n';
    }
}