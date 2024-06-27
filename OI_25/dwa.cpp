#include <bits/stdc++.h>
using namespace std;

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int n, curr_x=0, curr_y=0, x, y;
    cin >> n;
    for(int i=0; i<n; i++){
        cin >> x >> y;
        if((curr_x+x)*(curr_x+x) + (curr_y+y)*(curr_y+y) >= (curr_x-x)*(curr_x-x) + (curr_y-y)*(curr_y-y)){ curr_x += x; curr_y += y;}
        else{ curr_x -= x; curr_y -= y;}
    }
    cout << (long long)curr_x*curr_x + (long long)curr_y*curr_y << '\n';

    return 0;
}