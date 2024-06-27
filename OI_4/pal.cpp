#include <iostream>
using namespace std;

int ceny[2000007];

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);

  for(int i=1; i<2000005; i++) ceny[i] = 3000000;
  int p, n, c, d, it=0, paliwo=0, wynik=0;
  int min_cena, min_j;
  cin >> p;
  cin >> n;
  for(int i=0; i<n; i++){
    cin >> c >> d;
    ceny[it] = c;
    it += d;
  }
  ceny[it] = 0;
  bool b;
  for(int i=0; ceny[i]!=0; ){
    b=true;
    for(int j=i+1; j<=i+p;j++){
      if(ceny[j]<ceny[i]){
        wynik += ceny[i]*(j-i-paliwo);
        i = j;
        paliwo = 0;
        b=false;
        break;
      }
    }
    if(b){
      wynik += ceny[i] * (p-paliwo);
      min_cena = ceny[i+1];
      min_j = i+1;
      for(int j=i+2; j<=i+p; j++){
        if(ceny[j] < min_cena){
          min_cena = ceny[j];
          min_j = j;
        }
      }
      paliwo = p - min_j + i;
      i = min_j;
    }
  }

  cout << wynik;
  return 0;
}