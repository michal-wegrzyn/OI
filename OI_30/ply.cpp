#include <bits/stdc++.h>
using namespace std;

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int n, H, value=0, res=0;
    string s;
    cin >> n >> H;
    cin >> s;

    for(char c:s){
        if(c=='('){
            value += 1;
            if(value > H){
                value -= 2;
                res++;
            }
        }
        else{
            value -= 1;
            if(value < 0){
                value += 2;
                res++;
            }
        }
    }
    cout << res << '\n';
}