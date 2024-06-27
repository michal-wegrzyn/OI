#include <iostream>
using namespace std;

constexpr int base = 1 << 16;

int tree[base << 1];
int tree2[base << 1];

void add(int v, int a, int b, int p, int k, int x)
{
  if(b<p || k<a) return;
  else if(p<=a && b<=k){
    tree[v] += x;
    tree2[v] += x;
  }
  else{
    int l = v << 1;
    int r = (v << 1)+1;
    int mid = (a+b) >> 1;
    tree[l] += tree2[v];
    tree[r] += tree2[v];
    tree2[l] += tree2[v];
    tree2[r] += tree2[v];
    tree2[v] = 0;
    add(l, a, mid, p, k, x);
    add(r, mid+1, b, p, k, x);
    tree[v] = max(tree[l], tree[r]);
  }
}

int query(int v, int a, int b, int p, int k){
  if(b<p || k<a) return 0;
  else if(p<=a && b<=k) return tree[v];
  else{
    int l = v << 1;
    int r = (v << 1)+1;
    int mid = (a+b) >> 1;
    tree[l] += tree2[v];
    tree[r] += tree2[v];
    tree2[l] += tree2[v];
    tree2[r] += tree2[v];
    tree2[v] = 0;
    return max(query(l, a, mid, p, k), query(r, mid+1, b, p, k));
  }
}

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  int n, m, z, p, k, l, q;
  cin >> n >> m >> z;
  for(int i=0; i<z; i++){
    cin >> p >> k >> l;
    if(m - query(1, 0, base-1, p-1, k-1) >= l){
      add(1, 0, base-1, p-1, k-1, l);
      cout << 'T' << '\n';
    }else cout << 'N' << '\n';
  }

  return 0;
}