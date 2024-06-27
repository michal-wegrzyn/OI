#include <iostream>
#include <map>
#include <set>
using namespace std;

long long powers_of_prime[1003];
long long hashes[1003];
char trains[1003][1003];
map<long long, set<int>> map_of_hashes;
int results[1003];

long long mod(long long num, long long p){
    while(num<0) num += p;
    return num - num/p*p;
}

long long char_to_num(char c){
    return (long long)c - 96;
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n, l, m, s, aux_int;
    long long mod_prime = 1000000007, prime = 29, aux_var = 1;
    set<int>::iterator itr;
    char aux_c;
    for(int i=0; i<1002; i++){
        powers_of_prime[i] = aux_var;
        aux_var *= prime;
        aux_var = mod(aux_var, mod_prime);
        //cout << i << ' ' << powers_of_prime[i] << '\n';
    }
    cin >> n >> l >> m;
    for(int i=0; i<n; i++){
        for(int j=0; j<l; j++){
            cin >> aux_c;
            trains[i][j] = aux_c;
            hashes[i] += char_to_num(aux_c)*powers_of_prime[j];
            hashes[i] = mod(hashes[i], mod_prime);
        }
        map_of_hashes[hashes[i]].insert(i);
    }
    for(int i=0; i<n; i++) results[i] = map_of_hashes[hashes[i]].size();
    long long p1, w1, p2, w2;
    for(int i=0; i<m; i++){
        cin >> p1 >> w1 >> p2 >> w2;
        p1--; w1--; p2--; w2--;
        map_of_hashes[hashes[p1]].erase(p1);
        map_of_hashes[hashes[p2]].erase(p2);
        hashes[p1] += (char_to_num(trains[p2][w2]) - char_to_num(trains[p1][w1]))*powers_of_prime[w1];
        hashes[p1] = mod(hashes[p1], mod_prime);
        hashes[p2] += (char_to_num(trains[p1][w1]) - char_to_num(trains[p2][w2]))*powers_of_prime[w2];
        hashes[p2] = mod(hashes[p2], mod_prime);
        aux_c = trains[p1][w1];
        trains[p1][w1] = trains[p2][w2];
        trains[p2][w2] = aux_c;
        map_of_hashes[hashes[p1]].insert(p1);
        map_of_hashes[hashes[p2]].insert(p2);
        s = map_of_hashes[hashes[p1]].size();
        for(itr=map_of_hashes[hashes[p1]].begin(); itr!=map_of_hashes[hashes[p1]].end(); itr++){
            aux_int = *itr;
            if(results[aux_int] < s) results[aux_int] = s;
        }
        s = map_of_hashes[hashes[p2]].size();
        for(itr=map_of_hashes[hashes[p2]].begin(); itr!=map_of_hashes[hashes[p2]].end(); itr++){
            aux_int = *itr;
            if(results[aux_int] < s) results[aux_int] = s;
        }
    }
    
    for(int i=0; i<n; i++) cout << results[i] << '\n';
    return 0;
}