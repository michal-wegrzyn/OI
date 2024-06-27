#include <bits/stdc++.h>
#include "OI_29_glolib.hpp"
// #include "glolib.h"
using namespace std;

vector<int> graph[200007];
int boss[200007];
int index0[200007];
bitset<200007> occ;
int leaf[200007];
int leaves_count;

void dfs_leaf(int v){
    if(graph[v].size() == 0){
        leaf[v] = v;
        leaves_count ++;
        return;
    }
    for(int u:graph[v]){
        dfs_leaf(u);
    }
    leaf[v] = leaf[graph[v][0]];
}

int main(){
    int n = daj_n();
    int a;
    for(int i=2; i<=n; i++){
        a = daj_przelozonego(i);
        boss[i] = a;
        graph[a].push_back(i);
    }

    dfs_leaf(1);

    a = leaf[1];
    occ[a] = 1;
    while(boss[a]){
        a = boss[a];
        occ[a] = true;
    }

    int last_opp_move;
    last_opp_move = ruch(leaf[1]);

    for(int i=0; i<leaves_count/2; i++){
        while(!occ[last_opp_move]){
            occ[last_opp_move] = 1;
            last_opp_move = boss[last_opp_move];
        }
        for(;occ[graph[last_opp_move][index0[last_opp_move]]]; index0[last_opp_move]++);
        a = leaf[graph[last_opp_move][index0[last_opp_move]]];
        last_opp_move = ruch(a);
        while(!occ[a]){
            occ[a] = 1;
            a = boss[a];
        }
    } 
}