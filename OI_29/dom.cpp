#include <iostream>
using namespace std;

long long f[85];

int main(){
    f[0] = 2; f[1] = 3;
    for(int i=2; i<85; i++) f[i] = f[i-1] + f[i-2];
    f[4] = 144; f[9] = 13;
    
    long long m; cin >> m;
    int result = -1;
    if(m==(long long)1){cout << 1; return 0;}
    for(int i=84; i>=0; i--) while(m/f[i]*f[i] == m){
        m /= f[i];
        if(i!=4 && i!=9) result += i+3;
        if(i==4) result += 12;
        if(i==9) result += 7;
    }
    
    if(m==1) cout << result;
    else cout << "NIE";
    return 0;
}