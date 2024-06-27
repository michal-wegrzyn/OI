#include <iostream>
using namespace std;

int rampa[100003];
int skoki[100333][320];

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n, k, a, l, d;
    cin >> n >> k;
    for(int i=0; i<k; i++){
        cin >> a >> l >> d;
        if(d>318) for(int i=0; i<l; i++) rampa[a+i*d] += 1;
        else{
            skoki[a][d]++;
            skoki[a+l*d][d]--;
        }
    }
    for(int i=1; i<319; i++){
        for(int j=1; j<=i; j++) rampa[j] += skoki[j][i];
        for(int j=i+1; j<=n; j++){
            skoki[j][i] += skoki[j-i][i];
            rampa[j] += skoki[j][i];
        }
    }
    for(int i=1; i<=n; i++) cout << rampa[i] << ' ';
    return 0;
}