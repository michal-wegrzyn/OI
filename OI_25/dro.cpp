#include <bits/stdc++.h>
using namespace std;

vector <int> graf[100007];
bool b[100007];
int n, m, p, r;

void odp(int start){
  for(int i=0; i<100007; i++) b[i] = false;
  b[start] = true;
  int w = 0;
  queue<int> q;
  q.push(start);

  while(q.size()>0){
    int x = q.front();
    q.pop();
    for(int i = 0; i<(int)graf[x].size(); i++)
      if(b[graf[x][i]]==false){
        b[graf[x][i]] = true;
        q.push(graf[x][i]);
        w++;
      }
  }
  cout << w << '\n';
}

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  cin >> n >> m;
  for(int i=0; i<m; i++){
    cin >> p >> r;
    graf[p].push_back(r);
  }
  for(int i=1; i<=n; i++) odp(i);
}
