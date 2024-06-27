#include <bits/stdc++.h>
using namespace std;

int n = 7;
int przelozeni[8] = {0,0,1,2,1,1,2,2};

int daj_n(){
    return n;
}

int daj_przelozonego(int v){
    return przelozeni[v];
}

int ruch(int v){
    int a;
    cout << v << '^'; cin >> a;
    return a;
}