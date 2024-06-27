#include <bits/stdc++.h>
using namespace std;

int ll_zmian[100003];

void result(string a, string b, int k) {
  string c;
  int i, l_zmian, ile_zostalo_znakow, pozostale_k;
  int res_index;
  ll_zmian[0] = 0;
  if(a[0] != b[0]) ll_zmian[0] = 1;
  for(i = 1; i < (int)a.size(); ++i) {
    ll_zmian[i] = ll_zmian[i - 1];
    if(a[i] != b[i]) ++ll_zmian[i];
  }
  res_index = -1;
  for(i = 0; i < (int)a.size(); ++i) {
    if(b[i] == '0') continue;
    l_zmian = 0;
    if(i != 0) l_zmian = ll_zmian[i - 1];
    if(a[i] >= b[i]) ++l_zmian;
    ile_zostalo_znakow = a.length() - i - 1;
    if((a[i]<b[i]) && (b[i]!='1'))++ile_zostalo_znakow;
    pozostale_k = k-l_zmian;
    if (l_zmian <= k) 
    if (ile_zostalo_znakow >= pozostale_k) res_index = i;
  }
  if(res_index == -1) {
    cout << "-1\n";
    return;
  }

  c = b;
  i = res_index;
  pozostale_k = k;
  if(i != 0) pozostale_k = k - ll_zmian [i-1];
  if((pozostale_k>0) && (a[i] != b[i]-1)){
    c[i] = b[i] - 1;
    --pozostale_k;
  }else{
    c[i] = a[i];
  }
  for(++i; i < (int)a.size(); ++i) {
    if((pozostale_k>0) && (a[i]!='9')) {
      c[i] = '9';
      --pozostale_k;
	  } else c[i] = a[i];
  }
  for(i = (int)a.size() - 1; i >= 0; --i) {
    if(pozostale_k > 0 && c[i] == a[i]) {
      c[i] = c[i] - 1;
      --pozostale_k;
	  }
  }
  cout << c << "\n";
}

int main () {
  cin.tie(0);
  cout.tie(0);
  ios_base::sync_with_stdio(0);
  int n, k, i;
  string a, b;
  cin >> n;
  for(i = 1; i <= n; ++i) {
    cin >> a >> b >> k;
    result(a, b, k);
  }

return 0;
}