#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define frac pair<ll,ll>

bool comp_frac(frac f1, frac f2){
    return (f1.first * f2.second > f1.second * f2.first);
}

void printFrac(frac f){
    ll g = __gcd(f.first, f.second);
    cout << f.first/g << '/' << f.second/g;
}

constexpr int base = (1<<19);
pair<int,int> st_taxi[base];
pair<int,int> taxi[base];

frac min_d_tree[base*2];
frac max_d_tree[base*2];

void printTrees(){
    for(int i=1; i<base*2; i++){printFrac(min_d_tree[i]); cout << "   ";} cout << '\n';
    for(int i=1; i<base*2; i++){printFrac(max_d_tree[i]); cout << "   ";} cout << '\n';
}

void setValueMin(int v, frac value){
    v += base;
    min_d_tree[v] = value;
    v /= 2;
    while(v){
        if(comp_frac(min_d_tree[v*2], min_d_tree[v*2+1])) min_d_tree[v] = min_d_tree[v*2];
        else min_d_tree[v] = min_d_tree[v*2+1];
        v /= 2;
    }
}

void setValueMax(int v, frac value){
    v += base;
    max_d_tree[v] = value;
    v /= 2;
    while(v){
        if(comp_frac(max_d_tree[v*2], max_d_tree[v*2+1])) max_d_tree[v] = max_d_tree[v*2+1];
        else max_d_tree[v] = max_d_tree[v*2];
        v /= 2;
    }
}

constexpr frac MIN_FRAC = {1, 1000000000};
constexpr frac MAX_FRAC = {1000000000, 1};

void proceedX(int x){
    if(taxi[x].second - taxi[x+1].second > 0){
        setValueMin(x, MIN_FRAC);
        setValueMax(x,{taxi[x+1].first - taxi[x].first, taxi[x].second - taxi[x+1].second});
    }
    if(taxi[x].second - taxi[x+1].second < 0){
        setValueMin(x, {taxi[x].first - taxi[x+1].first, taxi[x+1].second - taxi[x].second});
        setValueMax(x, MAX_FRAC);
    }
    if(taxi[x].second - taxi[x+1].second == 0){
        if(taxi[x+1].first - taxi[x].first < 0){
            setValueMin(x, MAX_FRAC);
            setValueMax(x, MIN_FRAC);
        }
        else{
            setValueMin(x, MIN_FRAC);
            setValueMax(x, MAX_FRAC);
        }
    }
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int n, q, x, y;
    ll s, c, a, b;
    cin >> n;
    for(int i=1; i<=n; i++){
        cin >> s >> c;
        st_taxi[i] = {s,c};
    }

    for(int i=1; i<=n; i++){
        cin >> x;
        taxi[i] = st_taxi[x];
    }

    for(int i=base; i<2*base; i++) min_d_tree[i] = MIN_FRAC;
    for(int i=base; i<2*base; i++) max_d_tree[i] = MAX_FRAC;

    for(int i=1; i<n; i++){
        if(taxi[i].second - taxi[i+1].second > 0){
            max_d_tree[base+i] = {taxi[i+1].first - taxi[i].first, taxi[i].second - taxi[i+1].second};
        }
        if(taxi[i].second - taxi[i+1].second < 0){
            min_d_tree[base+i] = {taxi[i].first - taxi[i+1].first, taxi[i+1].second - taxi[i].second};
        }
        if(taxi[i].second - taxi[i+1].second == 0){
            if(taxi[i+1].first - taxi[i].first < 0){
                min_d_tree[base+i] = MAX_FRAC;
                max_d_tree[base+i] = MIN_FRAC;
            }
        }
    }

    for(int i=base-1; i>0; i--){
        if(comp_frac(min_d_tree[i*2], min_d_tree[i*2+1])) min_d_tree[i] = min_d_tree[i*2];
        else min_d_tree[i] = min_d_tree[i*2+1];
    }

    for(int i=base-1; i>0; i--){
        if(comp_frac(max_d_tree[i*2], max_d_tree[i*2+1])) max_d_tree[i] = max_d_tree[i*2+1];
        else max_d_tree[i] = max_d_tree[i*2];
    }

    if(comp_frac(min_d_tree[1], max_d_tree[1])) cout << "NIE\n";
    else{
        printFrac(min_d_tree[1]); cout << '\n';
        // cout << simplify(max_d_tree[1]).first << '/' << simplify(max_d_tree[1]).second << '\n';
    }

    // printTrees();

    cin >> q;
    for(int i=0; i<q; i++){
        cin >> x >> y;
        swap(taxi[x], taxi[y]);
        if(x!=1) proceedX(x-1);
        if(x!=n) proceedX(x);
        if(y!=1) proceedX(y-1);
        if(y!=n) proceedX(y);
        if(comp_frac(min_d_tree[1], max_d_tree[1])) cout << "NIE\n";
        else{ printFrac(min_d_tree[1]); cout << '\n';}
        // printTrees();
    }

}