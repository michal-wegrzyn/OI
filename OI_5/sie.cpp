#include <iostream>
using namespace std;

int tabela[203][203];

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  short n;
  cin >> n;
  for(short i=0; i<n; i++){
    for(short j=0; j<n; j++) cin >> tabela[i][j];
  }

  bool b = true;

  for(short i=0; i<n-1; i++){
    for(short j=i+1; j<n; j++){
      for(short k=0; k<n; k++){
        if(k==i || k==j) continue;
        if(tabela[i][j] == tabela[i][k] + tabela[j][k]){
          b = false;
        }
      }
      if(b) cout << i+1 << ' ' << j+1 << '\n';
      b = true;
    }
  }

  return 0;
}