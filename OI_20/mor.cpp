#include <bits/stdc++.h>
using namespace std;

int n, m, k;
int a, b, c;

struct P{
  int koniec;
  int odl;
  int index;
};

bool odp[100003];
int odl[10003];
vector<P> historie[5003];
vector<int> graf[10003];

void BFS(int start){
  for(int i = 1; i<=2*n; i++) odl[i] = -1;

  queue<int> q;
  odl[start] = 0;
  q.push(start);

  while(q.size()>0){
    int x = q.front();
    q.pop();
    for(int i = 0; i<(int)graf[x].size(); i++)
      if(odl[graf[x][i]]==-1){
        odl[graf[x][i]] = odl[x]+1;
        q.push(graf[x][i]);
      }
  }
}

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  cin >> n >> m >> k;
  for(int i = 1; i<=m; i++){
    cin >> a >> b;
    graf[a].push_back(b+n);
    graf[b].push_back(a+n);
    graf[a+n].push_back(b);
    graf[b+n].push_back(a);
  }

  for(int i=1; i<=k; i++){
    cin >> a >> b >> c;
    historie[a].push_back({b, c, i});
  }

  for(int i=1; i<=n; i++)
    if((int)historie[i].size()>0 && (int)graf[i].size()>0){
      BFS(i);
      for(int j=0; j<(int)historie[i].size(); j++)
        if(odl[historie[i][j].koniec+((historie[i][j].odl%2==0) ? 0 : n)] != -1)
          if(odl[historie[i][j].koniec+((historie[i][j].odl%2==0) ? 0 : n)] <= historie[i][j].odl)
            odp[historie[i][j].index] = true;
    }

  for(int i=1; i<=k; i++) cout << (odp[i] ? "TAK" : "NIE") << '\n';
}