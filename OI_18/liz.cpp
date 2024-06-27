#include <iostream>
using namespace std;

int results[1000003][2];

int main(){
    int n, m, k, sum=1, sum2;
    string lollypop;
    int first = -1, last = -1;
    cin >> n >> m;
    cin >> lollypop;
    for(int i=0; i<n; i++){
        if(lollypop[i] == 'W'){
            if(first == -1) first = i+1;
            last = i+1;
        }
    }
    if(first == -1){
        for(int i=1; i<=n; i++){
            results[2*i][0] = 1;
            results[2*i][1] = i;
        }
    }
    else{
        results[1][0] = first;
        results[1][1] = first;
        for(int i=first; i<n; i++){
            sum += (lollypop[i] == 'T' ? 2 : 1);
            if(i<last-1) sum2 = sum;
            results[sum][0] = first;
            results[sum][1] = i+1;
            results[sum-1][0] = first+1;
            results[sum-1][1] = i+1;
        }
        for(int i=1; i<first; i++){
            results[sum+2*i][0] = first-i;
            results[sum+2*i][1] = n;
            results[sum2+2*i][0] = first-i;
            results[sum2+2*i][1] = last-1;
        }
    }
    for(int i=0; i<m; i++){
        cin >> k;
        if(results[k][0] != 0) cout << results[k][0] << ' ' << results[k][1] << '\n';
        else cout << "NIE" << '\n';
    }
    return 0;
}