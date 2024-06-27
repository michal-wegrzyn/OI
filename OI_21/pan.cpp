#include <iostream>
using namespace std;

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n, a, b, c, d, k, mx, result;
    cin >> n;
    for(int i=0; i<n; i++){
        cin >> a >> b >> c >> d;
        mx = (b>d?b:d);
        result = 1;
        for(int j=2; j*j <= mx; j++){
            if((a+j-1)/j <= b/j && (c+j-1)/j <= d/j) result = j;
        }
        for(int j=1; j*j<=mx; j++){
            k = b/j;
            if((a+k-1)/k <= b/k && (c+k-1)/k <= d/k) result = (k>result?k:result);
            k = d/j;
            if((a+k-1)/k <= b/k && (c+k-1)/k <= d/k) result = (k>result?k:result);
        }
        cout << result << '\n';
    }
}