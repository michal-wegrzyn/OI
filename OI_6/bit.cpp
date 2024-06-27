#include <bits/stdc++.h>
using namespace std;

unsigned short n, m;
char a;
vector<unsigned short> graf[33130];
int odp[33130];
queue<unsigned short> q;

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);

  cin >> n >> m;

  for(unsigned short i=1; i<n; i++){
    for(unsigned short j=1; j<m; j++){
      graf[i*m+j].push_back(i*m+j-1);
      graf[i*m+j-1].push_back(i*m+j);
      graf[i*m+j].push_back((i-1)*m+j);
      graf[(i-1)*m+j].push_back(i*m+j);
    }
  }
  for(unsigned short i = 1; i<m; i++){
    graf[i].push_back(i-1);
    graf[i-1].push_back(i);
  }
  for(unsigned short i = 1; i<n; i++){
    graf[i*m].push_back((i-1)*m);
    graf[(i-1)*m].push_back(i*m);
  }


  for(unsigned short i=0; i<33130; i++) odp[i] = -1;
  for(unsigned short i=0; i<n; i++){
    for(unsigned short j=0; j<m; j++){
      cin >> a;
      if(a=='1'){
        odp[i*m+j] = 0; 
        q.push(i*m+j);
      }
    }
  }

  while(q.size()>0){
    int x = q.front();
    q.pop();
    for(int i = 0; i<(int)graf[x].size(); i++)
      if(odp[graf[x][i]]==-1){
        odp[graf[x][i]] = odp[x]+1;
        q.push(graf[x][i]);
      }
  }

  for(unsigned short i=0; i<n; i++){
    for(unsigned short j=0; j<m; j++){
      cout << odp[i*m+j] << ' ';
    }
    cout << '\n';
  }

  return 0;
}