#include <bits/stdc++.h>
using namespace std;

int czasy[100003];

int main() {
  cin.tie(0);
  cout.tie(0);
  ios_base::sync_with_stdio(0);

  int n;
  cin >> n;
  for(int i=0; i<n; i++) cin >> czasy[i];
  int res = 0;
  if(n==1){
    cout << czasy[0];
    return 0;
  }
  if((n&1) == 0){
    res += (n-1)*czasy[1] + (n/2-1)*czasy[0];
    for(int i = 3; i<n; i+=2) res += czasy[i];
  }
  else{
    res += (n-2)*czasy[1] + (n-1)/2*czasy[0];
    for(int i=2; i<n; i+=2) res += czasy[i];
  }
  cout << res;
  return 0;
}