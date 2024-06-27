#include <iostream>
using namespace std;

int t[1003];

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n, m, p;
    cin >> n >> m;
    int result = (n-2)*(n-1)*n/6;
    for(int i=0; i<2*m; i++){
        cin >> p;
        t[p]++;
    }
    
    p=0;
    for(int i=1; i<=n; i++){
        p += t[i]*(n-1-t[i]);
    }

    result -= p/2;

    cout << result;
    return 0;
}