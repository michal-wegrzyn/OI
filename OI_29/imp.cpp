#include <iostream>
using namespace std;

int pairs_p[25003];
int pairs_n[25003];
bool info[100003];

long long mod(long long num){
    return num - num/(long long)1000000007*(long long)1000000007;
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n, curr_p, curr_n, prev_p=-1, prev_n=-1, last_pp=0, last_pn=0, prev_ppi=-1, prev_pni=-1;
    long long result = (long long) 1;
    cin >> n;
    for(int i=0; i<n/2; i++){
        cin >> curr_p;
        if(curr_p<1 || curr_p>n){
            cout << 0;
            return 0;
        } 
        if((info[curr_p] == true) && ((prev_p != curr_p) || prev_ppi==i-1)){
            cout << 0;
            return 0;
        }
        info[curr_p] = true;
        if(prev_p == curr_p){
            last_pp++;
            pairs_p[last_pp] = i-prev_ppi-1;
            prev_ppi = i;
        }
        prev_p = curr_p;

        cin >> curr_n;
        if(curr_n<1 || curr_n>n){
            cout << 0;
            return 0;
        } 
        if((info[curr_n] == true) && ((prev_n != curr_n) || prev_pni==i-1)){
            cout << 0;
            return 0;
        }
        info[curr_n] = true;
        if(prev_n == curr_n){
            last_pn++;
            pairs_n[last_pn] = i-prev_pni-1;
            prev_pni = i;
        }
        prev_n = curr_n;
    }

    if(n%2==1){
        cin >> curr_p;
        if(curr_p<1 || curr_p>n){
            cout << 0;
            return 0;
        } 
        if((info[curr_p] == true) && ((prev_p != curr_p) || prev_ppi==n/2-1)){
            cout << 0;
            return 0;
        }
        if(prev_p == curr_p){
            last_pp++;
            pairs_p[last_pp] = n/2-prev_ppi-1;
        }
    }
    last_pp++;
    pairs_p[last_pp] = n/2-prev_ppi;

    last_pn++;
    pairs_n[last_pn] = (n+1)/2-1-prev_pni;

    if(n%2==1){
        if(last_pp==1){
            cout << 0;
            return 0;
        }
        for(int i=2; i<=last_pp-1; i++){
            result *= (long long)(pairs_p[i]);
            result = mod(result);
        }
        for(int i=1; i<=last_pn; i++){
            result *= (long long)(pairs_n[i]);
            result = mod(result);
        }
        for(int i=2; i<=last_pp+last_pn-2; i++){
            result *= (long long)(i);
            result = mod(result);
        }
    }
    else{
        for(int i=2; i<=last_pp; i++){
            result *= (long long)pairs_p[i];
            result = mod(result);
        }
        for(int i=1; i<=last_pn-1; i++){
            result *= (long long)pairs_n[i];
            result = mod(result);
        }
        for(int i=2; i<=last_pp+last_pn-2; i++){
            result *= (long long)i;
            result = mod(result);
        }
    }
    cout << result;
    return 0;
}