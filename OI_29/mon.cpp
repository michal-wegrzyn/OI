#include <iostream>
#include <algorithm>
using namespace std;

struct film{
    int czas;
    int termin;
    int index;
};

bool sort_film(film a, film b){
    return (a.termin < b.termin);
}

film filmy[500003];
int tree[1048560];
int base = 1 << 19;

void remove_leaf(int v){
    v += base;
    tree[v] = -1;
    v /= 2;
    while(v>0){
        tree[v] = max(tree[2*v], tree[2*v+1]);
        v /= 2;
    }
}

int max_index(int b){
    int res = tree[base];
    int res2 = tree[base];
    int res_index = base;
    b += base+1;
    while(b>1){
        if(b-b/2*2 == 1){
            res = max(res, tree[b-1]);
            if(res != res2) res_index = b-1;
            res2 = res;
        }
        b /= 2;
    }
    while(res_index < base){
        if(tree[res_index*2] == tree[res_index]) res_index *= 2;
        else res_index = res_index*2+1;
    }
    return res_index;
}


int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n, t, d, p=0, result=0;
    cin >> n;
    for(int i=0; i<n; i++){
        cin >> t >> d;
        if(t>d) p++;
        else filmy[i-p] = {t, d, i+1};
    }
    n -= p;
    sort(filmy, filmy+n, sort_film);
    for(int i=0; i<n; i++) tree[base+i] = filmy[i].czas;
    for(int i=base-1; i>0; i--) tree[i] = max(tree[2*i], tree[2*i+1]);
    
    int laczny_czas=0, curr_max=0;
    for(int i=0; i<n; i++){
        if(laczny_czas+filmy[i].czas <= filmy[i].termin){
            laczny_czas += filmy[i].czas;
            curr_max = max(curr_max, filmy[i].czas);
            result++;
        }
        else{
            if(filmy[i].czas < curr_max){
                remove_leaf(max_index(i)-base);
                laczny_czas = laczny_czas - curr_max + filmy[i].czas;
                curr_max = tree[max_index(i)];
            }
            else remove_leaf(i);
        }
    }

    laczny_czas = 1;
    cout << result << '\n';
    for(int i=0; i<n; i++){
        if(tree[i+base] != -1){
            cout << filmy[i].index << ' ' << laczny_czas << '\n';
            laczny_czas += filmy[i].czas;
        }
    }

    return 0;
}