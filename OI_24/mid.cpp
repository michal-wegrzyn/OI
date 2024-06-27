#include <iostream>
#include <vector>
using namespace std;

int rooms[1000003][2];
int cost[1000003];
int tz[1000003][2];
vector<int> wierzcholki[1000003];

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n, z, left, right, curr_room = 1, curr_num=0;
    cin >> n;
    for(int i=1; i<=n; i++){
        cin >> left >> right;
        rooms[i][0] = left;
        rooms[i][1] = right;
    }

    cin >> z;

    for(int i=0; i<z; i++){
        cin >> left >> right;
        tz[i][0] = left;
        tz[i][1] = right;
    }

    while(curr_room != 0){
        wierzcholki[0].push_back(curr_room);
        if(rooms[curr_room][1] != 0) wierzcholki[1].push_back(rooms[curr_room][1]);
        curr_room = rooms[curr_room][0];
    }

    int it_wierzcholki_p = 1; int it_wierzcholki_k = 2;
    bool b;

    while(it_wierzcholki_p != it_wierzcholki_k){
        b = false;
        for(int i:wierzcholki[it_wierzcholki_p]){
            if(rooms[i][0] != 0){
                b = true;
                wierzcholki[it_wierzcholki_k].push_back(rooms[i][0]);
            }
        }
        if(b) it_wierzcholki_k++;

        b = false;
        for(int i:wierzcholki[it_wierzcholki_p]){
            if(rooms[i][1] != 0){
                b = true;
                wierzcholki[it_wierzcholki_k].push_back(rooms[i][1]);
            }
        }
        if(b) it_wierzcholki_k++;
        it_wierzcholki_p++;
    }
    

    for(int i=0; i<it_wierzcholki_p; i++){
        for(int j:wierzcholki[i]) cost[j] = i;
    }

    for(int i=0; i<z; i++){
        if(cost[tz[i][0]] < cost[tz[i][1]]) cout << "NIE\n";
        else cout << "TAK\n";
    }

    return 0;
}