#include <iostream>
using namespace std;

int plansza[200000];

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);

  int n, pole, l_pionkow;
  cin >> n;
  for(short i=0; i<n; i++){
    cin >> pole >> l_pionkow;
    plansza[pole+100000] = l_pionkow;
  }

  for(int i=110000; i>2;){
    if(plansza[i]>2){
      plansza[i+2] += plansza[i]/3;
      plansza[i-2] += plansza[i]/3;
      plansza[i] %= 3;
      i += 2;
    }
    else i -= 1;
  }

  for(int i=199998; i>2;){
    if(plansza[i]>2){
      plansza[i+2] += plansza[i]/3;
      plansza[i-2] += plansza[i]/3;
      plansza[i] %= 3;
      i += 2;
    }
    else
      if(plansza[i]==2){
        plansza[i+1] +=1;
        plansza[i-2] += 1;
        plansza[i] = 0;
        i += 1;
      }
      else i -= 1;
  }

  for(int i=199998; i>2;){
    if(plansza[i]==1 && plansza[i-1]==1){
      plansza[i+1] = 1;
      plansza[i] = 0;
      plansza[i-1] = 0;
      i += 2;
    }
    else i-=1;
  }

  for(int i=2; i<199998; i++){
    if(plansza[i] != 0) cout << i - 100000 << ' ';
  }

  return 0;
}