#include <iostream>
using namespace std;
 
short tabela[253][253];
short sumy[253][253];
short wynik[253][253];
 
short n, r;
 
short f(short liczba){
  if(liczba<0) return 251;
  else if(liczba>=n) return n-1;
  else return liczba;
}
 
int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
 
  cin >> n >> r;
  for(short i=0; i<n; i++){
    for(short j=0; j<n; j++){
      cin >> tabela[i][j];
    }
  }
 
  for(short i=0; i<n; i++){
    for(short j=0; j<n; j++){
      sumy[i][j] = sumy[f(i-1)][j] + sumy[i][f(j-1)] - sumy[f(i-1)][f(j-1)] + tabela[i][j];
    }
  }
 
  for(short i=0; i<n; i++){
    for(short j=0; j<n; j++){
      wynik[i][j] = sumy[f(i+r)][f(j+r)] + sumy[f(i-r-1)][f(j-r-1)] - sumy[f(i+r)][f(j-r-1)] - sumy[f(i-r-1)][f(j+r)];
    }
  }
 
  for(short i=0; i<n; i++){
    for(short j=0; j<n; j++){
      cout << wynik[i][j] << ' ';
    }
    cout << '\n';
  }
 
  return 0;
}