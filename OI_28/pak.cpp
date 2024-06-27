#include <bits/stdc++.h>
using namespace std;

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    __int128_t a=123456789123456;
    __int128_t b=987654321987654;
    __int128_t m = a*b;
    while(m){
        cout << (int)(m%10);
        m/=10;
    }
    
}