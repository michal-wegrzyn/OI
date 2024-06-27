#include <iostream>
#include <utility>
#include <vector>
#include <queue>
using namespace std;

int podatek[5003];
vector<pair<int, int>> graf[5003];
vector<pair<int, int>> transponowany[5003];
priority_queue<pair<int, int>> q;
int koszt1[5003];
int koszt2[5003];

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n, m, m1, m2, cena;
    cin >> n;
    for(int i=1; i<=n; i++) cin >> podatek[i];
    cin >> m;
    for(int i=0; i<m; i++){
        cin >> m1 >> m2 >> cena;
        graf[m1].push_back(make_pair(cena, m2));
        transponowany[m2].push_back(make_pair(cena, m1));
    }

    for(int i=2; i<5002; i++){
        koszt1[i] = 2000000000;
        koszt2[i] = 2000000000;
    }

    q.push(make_pair(0, 1));
    while(!q.empty()){
        m1 = q.top().second;
        q.pop();
        for(int i=0; i<graf[m1].size(); i++){
            m2 = graf[m1][i].second;
            if(koszt1[m1]+graf[m1][i].first < koszt1[m2]){
                koszt1[m2] = koszt1[m1]+graf[m1][i].first;
                q.push(make_pair(-koszt1[m2], m2));
            }
        }
    }

    q.push(make_pair(0, 1));
    while(!q.empty()){
        m1 = q.top().second;
        q.pop();
        for(int i=0; i<transponowany[m1].size(); i++){
            m2 = transponowany[m1][i].second;
            if(koszt2[m1]+transponowany[m1][i].first < koszt2[m2]){
                koszt2[m2] = koszt2[m1]+transponowany[m1][i].first;
                q.push(make_pair(-koszt2[m2], m2));
            }
        }
    }

    cena = koszt1[1]+podatek[1]/2+koszt2[1];

    for(int i=2; i<=n; i++){
        if(koszt1[i]+podatek[i]/2+koszt2[i] < cena) cena = koszt1[i]+podatek[i]/2+koszt2[i];
    }
    cout << cena;
    return 0;
}