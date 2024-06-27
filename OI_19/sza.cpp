#include <bits/stdc++.h>
using namespace std;

struct S{
  int t;
  int w;
  int b;
  int k;
  int s;
  int a;
};

vector <S> v;
int a, b, c, p;
bool odp[1000003];

bool srt(S &a, S &b){
  bool b2=false;
  b2 =  a.t < b.t;
  if(a.t==b.t){
    if(b.b == -1) b2=true;
    else if(a.b == -2) b2=true;
  }
  return b2;
}

int main() {
  cin >> p;
  for(int i=0; i<p; i++){
    cin >> c >> a >> b;
    v.push_back({a, c, -2, 0, 0, 0});
    v.push_back({b, -c, -1, 0, 0, -1});
  }

  cin >> p;
  for(int i=0; i<p; i++){
    cin >> c >> a >> b; //m, k, s
    v.push_back({c, 0, i, a, b, 0});
  }

  sort(v.begin(), v.end(), srt);
  v.push_back({1000000003, 0, -1, 0, 0, -1});

  a=0;
  for(int i=v.size()-1; i>=0; i--){
    if(v[i].a == -1) a=v[i].t;
    else v[i].a = a;
  }

  //for(auto y:v) cout << y.t << ' ' << y.w << ' ' << y.b << ' ' << y.k << ' ' << '\n'; cout<<'\n';
  a=0;
  for(int i=0; i<v.size(); i++){v[i].w += a; a = v[i].w;}
  for(int i=0; i<v.size()-1; i++){
    //S z = v[i];
    if(v[i].b>=0){
      if(v[i].k <= v[i].w && v[i].t + v[i].s < v[i].a){
        //a=1000000003;
        /*
        for(int j=i+1; j<v.size(); j++){
          if(v[j].b==-1){a=v[j].t; break;}
        }
        */
        cout << "K";
        odp[v[i].b]=true;
      }
    }
  }
  for(int i=0; i<p; i++){
    if(odp[i]) cout << "TAK\n";
    else cout << "NIE\n";
  }
  for(auto y:v) cout << y.t << ' ' << y.w << ' ' << y.b << ' ' << y.k << ' ' << y.s << ' ' << y.a << '\n';
  return 0;
}