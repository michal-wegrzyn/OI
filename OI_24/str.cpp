#include <iostream>
#include <vector>
using namespace std;

vector<int> graf[500003];
int deg[500003];
vector<int> graf2[500003];
vector<int> graf3[500003];
bool strajk[500003];
int mniejsze[500003];

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n, m, a, b, wynik = 1, p=0;
    cin >> n;
    for(int i=1; i<n; i++){
        cin >> a >> b;
        graf[a].push_back(b);
        deg[a]++;
        graf[b].push_back(a);
        deg[b]++;
    }
    for(int i=1; i<=n; i++){
        for(int j:graf[i]){
            if(deg[i]<deg[j]) graf2[i].push_back(j);
            if(deg[i]<=deg[j]) graf3[i].push_back(j);
        }
    }
    cin >> m;
    for(int i=0; i<m; i++){
        cin >> a;
        if(a>0){
            p = mniejsze[a];
            for(int j:graf3[a]) if(strajk[j]) p++;
            p = deg[a] - p - 1;
            wynik += p;
            cout << wynik << "\n";
            for(int j:graf2[a]) mniejsze[j]++;
            strajk[a] = true;
        }
        else{
            a *= -1;
            p = mniejsze[a];
            for(int j:graf3[a]) if(strajk[j]) p++;
            p = deg[a] - p - 1;
            wynik -= p;
            cout << wynik << "\n";
            for(int j:graf2[a]) mniejsze[j]--;
            strajk[a] = false;
        }
    }
    return 0;
}