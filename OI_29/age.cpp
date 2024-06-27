#include <iostream>
#include <vector>
using namespace std;

int sasiedzi2[500003][2];
bool czyAgent[500003];
int lisc1, lisc2, liscp;
vector<int> graf[500003];

int max_odl;
int pierwszy_agent;
void DFS(int v, int p, int odl){
    if(odl > max_odl) max_odl = odl;
    for(int u:graf[v]) if(u!=p){
        DFS(u, v, odl+1);
    }
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n, k, a, b, min_odl = 10000000, curr_odl = 0, cnt = 0;
    bool b2 = true;
    cin >> n >> k;
    cin >> a;
    czyAgent[a] = true;
    pierwszy_agent = a;
    for(int i=1; i<k; i++){
        cin >> a;
        czyAgent[a] = true;
    }
    for(int i=1; i<n; i++){
        cin >> a >> b;
        graf[a].push_back(b);
        graf[b].push_back(a);
        if(!sasiedzi2[a][0]) sasiedzi2[a][0] = b;
        else if(!sasiedzi2[a][1]) sasiedzi2[a][1] = b;
        else b2 = false;
        if(!sasiedzi2[b][0]) sasiedzi2[b][0] = a;
        else if(!sasiedzi2[b][1]) sasiedzi2[b][1] = a;
        else b2 = false;
    }
    if(k==1){
        DFS(pierwszy_agent, 0, 0);
        cout << 2*n-2-max_odl;
        return 0;
    }
    if(b2){
        for(lisc1=1; lisc1<=n; lisc1++) if(!sasiedzi2[lisc1][1]) break;
        while(lisc1!=0){
            if(czyAgent[lisc1]){
                min_odl = (curr_odl<min_odl?curr_odl:min_odl);
                curr_odl = 0;
            }
            else{
                curr_odl++;
            }
            if(sasiedzi2[lisc1][1] == liscp) lisc2 = sasiedzi2[lisc1][0];
            else lisc2 = sasiedzi2[lisc1][1];
            liscp = lisc1;
            lisc1 = lisc2;
            cnt++;
        }
        min_odl = (curr_odl<min_odl?curr_odl:min_odl);
        cout << n-k+min_odl;
        return 0;
    }
    return 0;
}