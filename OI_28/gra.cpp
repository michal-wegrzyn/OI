#include <bits/stdc++.h>
using namespace std;

vector <pair <int, int>> vp;
int odp[100001];
int zp[100007];

int m(int c, int d){
  return (c<d?c:d);
}

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);

  int n, x, z, p, l, a, b;
  cin >> n >> x >> z;
  for(int i=0; i<n; i++){
    cin >> p;
    for(int j=0; j<p; j++){
      cin >> l;
      vp.push_back(make_pair(l, i));
    }
  }

  for(int i=0; i<z; i++){
    cin >> p;
    zp[i] = p-1;
  }

  sort(vp.begin(), vp.end());
  odp[n] = 10000000;

  for(int i=vp.size()-1; i>-1; i--){
    p = vp[i].second;
    a = min(odp[p]+1, odp[p+1]);
    odp[p] = a;
    odp[p+1] = a;
    if(p+1 == n) odp[n] = 10000000;
  }

  for(int i=0; i<z; i++){
    cout << odp[zp[i]] << '\n';
  }
}