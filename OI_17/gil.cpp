#include <bits/stdc++.h>
using namespace std;

vector <int> graf[200003];
bool b[200003];
bool odw[200003];
int n, m, p, r;
bool w;

void BFS(int s){
  queue<int> q;
  q.push(s);
  odw[s] = true;

  if(graf[s].size()==0) w=true;
  else{
    while(q.size()>0){
    int x = q.front();
    q.pop();
    for(int i = 0; i<graf[x].size(); i++)
      if(!odw[graf[x][i]]){
        odw[graf[x][i]] = true;
        b[graf[x][i]] = !b[x];
        q.push(graf[x][i]);
      }
    }
  }
}

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  
  cin >> n >> m;
  for(int i=0; i<m; i++){
    cin >> p >> r;
    graf[p].push_back(r);
    graf[r].push_back(p);
  }

  BFS(1);

  for(int i=1; i<=n && !w; i++){
    if(!odw[i]) BFS(i);
  }
  if(w){cout << "NIE"; return 0;}
  cout << "TAK\n";
  for(int i=1; i<=n; i++){
    if(b[i]) cout << "K\n";
    else cout << "S\n";
  }

  return 0;
}