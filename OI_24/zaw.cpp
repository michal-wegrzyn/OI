#include <iostream>
#include <vector>
#include <utility>
using namespace std;

vector<pair<int,int>> graf[1000003];
int deg[1000003];
bool zajete_miejsce[1000003];
int miejsca[1000003];
long long jeden = (long long)1;

bool usunzajete(int v){
    for(auto i:graf[v]){
        if(miejsca[i.second]) continue;
        if(zajete_miejsce[i.first]) return false;
        miejsca[i.second] = i.first;
        zajete_miejsce[i.first] = true;
        deg[v]--;
        deg[i.first]--;
        if(!usunzajete(i.first)) return false;
    }
    return true;
}

bool usun(int v){
    if(deg[v]==1){
        for(auto i:graf[v]){
            if(!miejsca[i.second]){
                miejsca[i.second] = v;
                zajete_miejsce[v] = true;
                deg[v]--;
                deg[i.first]--;
                if(!deg[i.first]) return false;
                usun(i.first);
                return true;
            }
        }
    }
    return true;
}
int n;
long long dlugosc_cyklu(int v, long long dlugosc){
    zajete_miejsce[v] = true;
    for(auto i:graf[v]) if(!zajete_miejsce[i.first]) return dlugosc_cyklu(i.first, dlugosc+jeden);
    if(n>100000) cout << 'c' << dlugosc;
    return dlugosc;
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int a, b, num_krawedzi=0;
    long long liczba_mozliwosci = jeden;
    char c;
    cin >> n;
    for(int i=1; i<=n; i++){
        cin >> c;
        if(c=='T'){
            cin >> a;
            if(zajete_miejsce[a]){
                cout << "NIE\n" << 0;
                return 0;
            }
            zajete_miejsce[a] = true;
            miejsca[i] = a;
        }
        else{
            cin >> a >> b;
            if(zajete_miejsce[a]){
                if(zajete_miejsce[b]){
                    cout << "NIE\n" << 0;
                    return 0;
                }
                zajete_miejsce[b] = true;
                miejsca[i] = b;
            }
            else if(zajete_miejsce[b]){
                zajete_miejsce[a] = true;
                miejsca[i] = a;
            }else{
                graf[a].push_back(make_pair(b, i));
                deg[a]++;
                graf[b].push_back(make_pair(a, i));
                deg[b]++;
            }
        }
    }
    for(int i=1; i<=n; i++){
        if(zajete_miejsce[i] && deg[i]){
            if(!usunzajete(i)){
                cout << "NIE\n" << 0;
                return 0;
            }
        }
    }
    for(int i=1; i<=n; i++){
        if(deg[i]==0 && zajete_miejsce[i]==false){
            cout << "NIE\n" << 0;
            return 0;
        }
        if(deg[i]==1) if(!usun(i)){
            cout << "NIE\n" << 0;
            return 0;
        }
    }
    bool jedna_mozliwosc = true;
    for(int i=1; i<=n; i++){
        if(!zajete_miejsce[i]){
            jedna_mozliwosc = false;
            liczba_mozliwosci *= dlugosc_cyklu(i, jeden);
            liczba_mozliwosci -= liczba_mozliwosci/1000000007*1000000007;
        }
    }
    if(jedna_mozliwosc){
        cout << "TAK\n";
        for(int i=1; i<=n; i++) cout << miejsca[i] << '\n';
    }
    else{
        cout << "NIE\n" << liczba_mozliwosci;
    }
    return 0;
}