#include <bits/stdc++.h>
using namespace std;

vector <int> graf[100007];
vector <int> odp[334003];
int odp1, it, x1, x2;
int n, m;
int a, b, c, d;

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  cin >> n >> m;

  for(int i=0; i<m; i++){
    cin >> a >> b >> c >> d;
    if(c!=d){
      graf[a].push_back(b);
      graf[b].push_back(a);
    }
  }

  for(int i = 1; i<=n; i++){
    if(graf[i].size()%2 != 0){
      cout << "NIE";
      return 0;
    }
  }

  for(int i=1; i<=n; i++){
    while(graf[i].size()>0){
      odp[it].push_back(i);
      odp1++;
      x1 = i;
      do{
        x2 =  graf[x1].back();
        odp[it].push_back(x2);
        graf[x1].pop_back();
        for(int j=0; j<graf[x2].size(); j++){
          if(graf[x2][j]==x1){
            graf[x2][j] = graf[x2].back();
            graf[x2].pop_back();
            break;
          }
        }
        x1=x2;
      }while(x2!=i);
      it++;
    }
  }

  //cout << "OK\n";

  cout << odp1 << '\n';
  for(int i=0; i<it; i++){
    cout << odp[i].size()-1;
    for(int j=0; j<odp[i].size(); j++) cout << ' ' << graf[i][j];
    cout << '\n';
  }

  return 0;
}